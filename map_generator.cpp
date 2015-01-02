// Copyright: 2015 Steven Lamerton
// License: MIT, see LICENSE

#include <llvm/Support/raw_ostream.h>
#include "map_generator.h"

void MapGenerator::AddInclusion(Inclusion inclusion) {
  inclusions_.insert(inclusion);
}

void MapGenerator::PrintMap() {
  llvm::outs() << "digraph name {\n";
  for (auto& pair : inclusions_) {
    llvm::outs() << "\"" << pair.first << "\""
                 << " -> "
                 << "\"" << pair.second << "\""
                 << ";\n";
  }
  llvm::outs() << "}\n";
}
