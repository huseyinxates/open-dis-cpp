cmake_minimum_required(VERSION 3.2)
project(OpenDIS7-Examples VERSION 1.0.0)

# include GNUInstallDirs Module to get more generic directory handling
include(GNUInstallDirs)

# set cmake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Require the OpenDIS7 target
if(NOT TARGET OpenDIS7)
  find_package(OpenDIS REQUIRED)
endif()

# SDL2 is required to build the examples
find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)

# create list of ExampleSender source files
set(examplesender_src
  main.cpp
  Connection.cpp
  Utils.cpp
  Timer.cpp
)

# Define ExampleSender Executable
add_executable(ExampleSender7 ${examplesender_src})

# Link OpenDIS into ExampleSender
target_link_libraries(ExampleSender7 PRIVATE OpenDIS7 SDL2::Main SDL2::Net)

# create list of ExampleReceiver source files
set(examplereceiver_src
  main_receive.cpp
  Connection.cpp
  Utils.cpp
  Timer.cpp
  EntityStatePduProcessor.cpp
)

# Define ExampleReceiver Executable
add_executable(ExampleReceiver7 ${examplereceiver_src})

# Link OpenDIS into ExampleReceiver
target_link_libraries(ExampleReceiver7 PRIVATE OpenDIS7 SDL2::Main SDL2::Net)

# if Windows add M_PI definition
# - issues occurred during testing in Visual Studio
if (WIN32)
  target_compile_definitions(ExampleSender7 PRIVATE M_PI=3.14159265358979323846)
  target_compile_definitions(ExampleReceiver7 PRIVATE M_PI=3.14159265358979323846)
endif (WIN32)

install(TARGETS ExampleSender7 ExampleReceiver7 DESTINATION ${CMAKE_INSTALL_BINDIR})
