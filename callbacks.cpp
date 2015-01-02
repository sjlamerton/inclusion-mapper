// Copyright: 2014 Steven Lamerton
// License: MIT, see LICENSE

#include <boost/filesystem.hpp>
#include "callbacks.h"

void Callbacks::InclusionDirective(
    clang::SourceLocation hash_loc,
    const clang::Token&,
    llvm::StringRef,
    bool,
    clang::CharSourceRange,
    const clang::FileEntry*,
    llvm::StringRef search_path,
    llvm::StringRef relative_path,
    const clang::Module*) {
  if (pp_.getSourceManager().getFileCharacteristic(hash_loc) ==
      clang::SrcMgr::C_User) {
    // Normalise the file paths before adding the relationship
    llvm::StringRef current_file_ref =
        pp_.getSourceManager().getFilename(hash_loc);
    boost::filesystem::path current_file(
        current_file_ref.begin(),
        current_file_ref.end());

    boost::filesystem::path included_file(std::string(search_path) +
        "/" + std::string(relative_path));

    map_generator_->AddInclusion(std::make_pair(
        boost::filesystem::canonical(current_file).string(),
        boost::filesystem::canonical(included_file).string()));
  }
}

Consumer::Consumer(
    clang::Preprocessor &pp,
    std::shared_ptr<MapGenerator> map_generator) {
  pp.addPPCallbacks(llvm::make_unique<Callbacks>(pp, map_generator));
}

std::unique_ptr<clang::ASTConsumer> Action::CreateASTConsumer(
    clang::CompilerInstance &ci,
    llvm::StringRef) {
  return llvm::make_unique<Consumer>(ci.getPreprocessor(), map_generator_);
}

Action* FrontendActionFactory::create() {
  return new Action(map_generator_);
}

