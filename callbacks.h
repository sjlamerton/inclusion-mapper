// Copyright: 2014 Steven Lamerton
// License: MIT, see LICENSE
#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Tooling/Tooling.h>
#include "map_generator.h"

class Callbacks : public clang::PPCallbacks {
 public:
  Callbacks(
      clang::Preprocessor &pp,
      std::shared_ptr<MapGenerator> map_generator)
    : pp_(pp), map_generator_(map_generator) {}

  void InclusionDirective(
      clang::SourceLocation hash_loc,
      const clang::Token &include_tok,
      llvm::StringRef filename,
      bool is_angled,
      clang::CharSourceRange filename_range,
      const clang::FileEntry *file,
      llvm::StringRef search_path,
      llvm::StringRef relative_path,
      const clang::Module *imported) override;

  void FileChanged(
      clang::SourceLocation loc,
      clang::PPCallbacks::FileChangeReason reason,
      clang::SrcMgr::CharacteristicKind file_type,
      clang::FileID prev_fid) override;

 private:
  const clang::Preprocessor& pp_;
  std::shared_ptr<MapGenerator> map_generator_;
};

class Consumer : public clang::ASTConsumer {
 public:
  Consumer(clang::Preprocessor &pp, std::shared_ptr<MapGenerator> inclusions);
};

class Action : public clang::SyntaxOnlyAction {
 public:
  Action(std::shared_ptr<MapGenerator> map_generator)
    : map_generator_(map_generator) {}

  std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
      clang::CompilerInstance &ci,
      llvm::StringRef in_file) override;

 private:
  std::shared_ptr<MapGenerator> map_generator_;
};

class FrontendActionFactory : public clang::tooling::FrontendActionFactory {
 public:
  FrontendActionFactory(std::shared_ptr<MapGenerator> map_generator)
    : map_generator_(map_generator) {}
  
  virtual Action *create();

 private:
  std::shared_ptr<MapGenerator> map_generator_;
};

#endif
