# Copyright: 2014 Steven Lamerton
# License: MIT, see LICENSE

cmake_minimum_required(VERSION 2.8)
project(inclusion-mapper)

# Enable C++11 support
add_definitions(-std=c++11)

# Find LLVM
find_package(LLVM REQUIRED)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs core option support mc native)

add_definitions(-fno-rtti -Wall -Wextra -pedantic)

# Add our files to some variables
set(source inclusion_mapper.cpp main.cpp)
set(headers inclusion_mapper.h)

# Create our executable
add_executable(inclusion-mapper ${source} ${headers})
target_link_libraries(inclusion-mapper
  clangTooling
  clangFrontend
  clangSerialization
  clangDriver
  clangRewriteFrontend
  clangToolingCore
  clangRewrite
  clangParse
  clangSema
  clangAnalysis
  clangAST
  clangASTMatchers
  clangEdit
  clangLex
  clangBasic
  ${llvm_libs}
)

