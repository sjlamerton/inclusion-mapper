// Copyright: 2014 Steven Lamerton
// License: MIT, see LICENSE

#include <llvm/Support/raw_ostream.h>
#include "callbacks.h"

int main(int argc, const char **argv) {
  llvm::cl::OptionCategory options("inclusion-mapper options");
  clang::tooling::CommonOptionsParser parser(argc, argv, options);

  llvm::outs() << "digraph name {\n";

  clang::tooling::ClangTool tool(parser.getCompilations(),
                                 parser.getSourcePathList());
  SharedInclusions inclusions(new std::set<Inclusion>);
  tool.run(new FrontendActionFactory(inclusions));

  for (auto pair : *inclusions.get()) {
    llvm::outs() << "\"" << pair.first << "\""
                 << " -> "
                 << "\"" << pair.second << "\""
                 << ";\n";
  }
  llvm::outs() << "}\n";
}
