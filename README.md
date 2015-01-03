inclusion-mapper is a tool that produces a [dot-file][1] describing the links
between different files in a C++ codebase. It uses the Clang LibTooling
interface and works with the CMake built system.

Building inclusion-mapper
=========================

inclusion-mapper has the following build time prerequisites:

 *  CMake
 *  Boost
 *  Clang

Once the inclusion mapper code has been checked out it can be built with:

    mkdir build && cd build
    cmake <PATH TO SOURCE>
    make

Using inclusion-mapper
======================

inclusion-mapper uses the standard LibTooling command line interface and
requirs that the codebase you wish to analyse is built with CMake. When running
CMake pass the command `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` to produce the
command database that inclusion-mapper uses. You can then run the following
command to generate an inclusion map:

    inclusion-mapper -p "/path/to/command/database" source1 source2

For example to analyse the code for the inclusion-mapper tool, from the source
directory run:

    inclusion-mapper -p build *.cpp

You can pass the output straight into the `dot` tool provided by [Graphviz][2] to
create an image, for example:

    inclusion-mapper -p build *.cpp | dot -Tpng > map.png

![Example image](/docs/example.png?raw=true)

inclusion-mapper also allows you to ignore includes that are system files by
passing the `-x` flag.
    
![Example image without system headers](/docs/example-nosystem.png?raw=true)

[1]: http://en.wikipedia.org/wiki/DOT_%28graph_description_language%29
[2]: http://www.graphviz.org/
