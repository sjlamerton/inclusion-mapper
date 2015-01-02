// Copyright: 2014 Steven Lamerton
// License: MIT, see LICENSE

#include <clang/Tooling/CommonOptionsParser.h>
#include "callbacks.h"
#include "map_generator.h"

int main(int argc, const char **argv) {
  llvm::cl::OptionCategory options("inclusion-mapper options");
  llvm::cl::opt<bool> exclude_system(
      "x",
      llvm::cl::desc("Exclude system headers"),
      llvm::cl::cat(options));
  clang::tooling::CommonOptionsParser parser(argc, argv, options);

  clang::tooling::ClangTool tool(parser.getCompilations(),
                                 parser.getSourcePathList());
  auto map_generator = std::make_shared<MapGenerator>();
  tool.run(new FrontendActionFactory(map_generator));

  if (exclude_system) {
    map_generator->RemoveSystemInclusions();
  }
  map_generator->PrintMap();
}
