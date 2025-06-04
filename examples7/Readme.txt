This is an example usage of the DIS implementation.
It shows how to send/receive data to a DIS network.

The main idea is to use the library to pack and send/receive data.
The example socket implementation is outside the scope
of the DIS implementation, but provided so that the
testing is complete.  This socket implementation depends upon the SDL2_net
library. Please visit https://www.libsdl.org/ for information about how to
download, build, and install the Libraries.

SDL2 also provides timing functionality. I.e. calculating delta between frames
and for sleep delays.

Build instructions:

These executable are built within the main project build process, see the project
README.md, in repo root directory.

Additionally, these executables can be built using the `CMakeList.txt`
file to test an OpenDIS installation.
To do so, run the following commands in this directory:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```
If everything worked correctly, then OpenDIS is installed correctly.
If you installed OpenDIS in a custom location you may have to add the flag
`-DOpenDIS7_DIR=<path to OpenDIS install>/lib/cmake/OpenDIS7` to the cmake
command - this will apply to any other CMake projects you wish to include
OpenDIS7 in.

Running instructions:
Run `ExampleReceiver7` and `ExampleSender7` in separate terminals
