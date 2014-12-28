// Copyright: 2014 Steven Lamerton
// License: MIT, see LICENSE

#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>

typedef std::pair<std::string, std::string> Inclusion;
typedef std::shared_ptr<std::set<Inclusion>> SharedInclusions;

class Callbacks : public clang::PPCallbacks {
 public:
  Callbacks(clang::Preprocessor &pp, SharedInclusions inclusions)
    : pp_(pp), inclusions_(inclusions) {}

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

 private:
  const clang::Preprocessor& pp_;
  SharedInclusions inclusions_;
};

class Consumer : public clang::ASTConsumer {
 public:
  Consumer(clang::Preprocessor &pp, SharedInclusions inclusions);
};

class Action : public clang::SyntaxOnlyAction {
 public:
  Action(SharedInclusions inclusions) : inclusions_(inclusions) {}

  std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
    clang::CompilerInstance &ci,
    llvm::StringRef in_file) override;

 private:
  SharedInclusions inclusions_;
};

class FrontendActionFactory : public clang::tooling::FrontendActionFactory {
 public:
  FrontendActionFactory(SharedInclusions inclusions)
  : inclusions_(inclusions) {}
  
  virtual Action *create();

 private:
  SharedInclusions inclusions_;
};
