// Copyright: 2014 Steven Lamerton
// License: MIT, see LICENSE

#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/SmallVector.h>
#include "inclusion_mapper.h"

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
    llvm::SmallVector<char, 128> normalised_current_file(
        current_file_ref.begin(),
        current_file_ref.end());
    llvm::sys::fs::make_absolute(normalised_current_file);

    std::string included_file =
        std::string(search_path) + "/" + std::string(relative_path);
    llvm::SmallVector<char, 128> normalised_included_file(
        included_file.begin(),
        included_file.end());
    llvm::sys::fs::make_absolute(normalised_included_file);

    inclusions_->emplace(
        std::string(
            normalised_current_file.begin(),
            normalised_current_file.end()),
        std::string(
            normalised_included_file.begin(),
            normalised_included_file.end()));
  }
}

Consumer::Consumer(clang::Preprocessor &pp, SharedInclusions inclusions) {
  pp.addPPCallbacks(llvm::make_unique<Callbacks>(pp, inclusions));
}

std::unique_ptr<clang::ASTConsumer> Action::CreateASTConsumer(
    clang::CompilerInstance &ci,
    llvm::StringRef) {
  return llvm::make_unique<Consumer>(ci.getPreprocessor(), inclusions_);
}

Action* FrontendActionFactory::create() {
  return new Action(inclusions_);
}

