
# cmake 指定特定路经下的qt库

``` sh
cmake -DCMAKE_PREFIX_PATH=$HOME/Qt/5.11.2/gcc_64 ..
```
## CMAKE_PREFIX_PATH
Semicolon-separated list of directories specifying installation prefixes to be searched by the find_package(), find_program(), find_library(), find_file(), and find_path() commands. Each command will add appropriate subdirectories (like bin, lib, or include) as specified in its own documentation.

- Make sure to clear the build directory before changing CMAKE_PREFIX_PATH
- Are you sure there's a lib/cmake folder inside /home/cavit/Qt/5.6? (That's where CMake finds the Qt5 config files)

# cmake 构建安装

``` sh
mkdir build && cd build
cmake ../ -G Ninja -DCMAKE_INSTALL_PREFIX=/usr/local
ninja -C .
sudo ninja install
```

# cmake-basic

``` cmake
# specify the minimum version of CMake
cmake_minimum_required(VERSION 3.5)

# A CMakeLists.txt file can include and call sub-directories which include a CMakeLists.txt files.
add_subdirectory(subbinary)

# include a project name to make referencing certain variables easier when using multiple projects.
project (hello_cmake)  # create a variable ${PROJECT_NAME} with the value hello_cmake

# find a boost install with the libraries filesystem and system
find_package(Boost 1.46.1 REQUIRED COMPONENTS filesystem system)
# find_package() function will search for CMake modules in the formant "FindXXX.cmake" from the list of folders in CMAKE_MODULE_PATH.

# check if boost was found
if(Boost_FOUND)
    message ("boost found")
else()
    message (FATAL_ERROR "Cannot find Boost")
endif()

# Set Default Build Type
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

# Set Per-Target C++ Flags
target_compile_definitions(cmake_examples_compile_flags
    PRIVATE EX3
)
#  Set Default C++ Flags 
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)
# Setting C compiler flags using CMAKE_C_FLAGS
# Setting linker flags using CMAKE_LINKER_FLAGS
# This method is not recommended for general usage now and the target_compile_definitions function is preferred.

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/Hello.cpp
    src/main.cpp
)
# An alternative to setting specific file names in the SOURCES variable is to use a GLOB command to find files using wildcard pattern matching.
# file(GLOB SOURCES "src/*.cpp")

# Creating a static library  libhello_library.a  
add_library(hello_library STATIC
    src/Hello.cpp
)

#  Creating a shared library  libhello_library.so 
add_library(hello_library SHARED
    src/Hello.cpp
)
#  an alias target is an alternative name for a target
add_library(hello::library ALIAS hello_library)

# Creating an Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Including Directories
# add these directories to the compiler with the -I flag e.g. -I/directory/path
target_include_directories(target
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# Linking a Library
target_link_libraries( hello_binary
    PRIVATE
        hello_library
)

# Linking a Library using the alias target name.
target_link_libraries(hello_binary
    PRIVATE
        hello::library
        Boost::filesystem
)

# The base install location is controlled by the variable CMAKE_INSTALL_PREFIX which can be set using ccmake or by calling cmake with cmake .. -DCMAKE_INSTALL_PREFIX=/install/location

# Install the binary generated from the target cmake_examples_inst_bin target to the destination ${CMAKE_INSTALL_PREFIX}/bin
install (TARGETS cmake_examples_inst_bin
    DESTINATION bin)

# Install the shared library generated from the target cmake_examples_inst target to the destination ${CMAKE_INSTALL_PREFIX}/lib
install (TARGETS cmake_examples_inst
    LIBRARY DESTINATION lib)

# Install the header files for developing against the cmake_examples_inst library into the ${CMAKE_INSTALL_PREFIX}/include directory.
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION include)    

# Install a configuration file to the destination ${CMAKE_INSTALL_PREFIX}/etc
install (FILES cmake-examples.conf
    DESTINATION etc)

# After make install has been run, CMake generates an install_manifest.txt file which includes details on all installed files.

# To do variable substitution in a file you can use the configure_file() function in CMake. 
configure_file(path.h.in ${PROJECT_BINARY_DIR}/path.h @ONLY)
# const char* path = "@CMAKE_SOURCE_DIR@"; // path.h.in
# const char* path = "/home/matrim/workspace/cmake-examples/03-code-generation/configure-files"; // path.h 
```

# Directory Paths

|Variable|Info|
|--|--|
CMAKE_SOURCE_DIR |  The root source directory
CMAKE_CURRENT_SOURCE_DIR | The current source directory if using sub-projects and directories.
PROJECT_SOURCE_DIR | The source directory of the current cmake project.
CMAKE_BINARY_DIR |  The root binary / build directory. This is the directory where you ran the cmake command.
CMAKE_CURRENT_BINARY_DIR | The build directory you are currently in.
PROJECT_BINARY_DIR |  The build directory for the current project.

# sub-projects

```cmake
add_subdirectory(sublibrary1)
add_subdirectory(sublibrary2)
add_subdirectory(subbinary)
```
# To reference the source directory for a different project you can use.

${sublibrary1_SOURCE_DIR}
${sublibrary2_SOURCE_DIR}

|Variable|Info|
|--|--|
PROJECT_NAME | The name of the project set by the current project().
CMAKE_PROJECT_NAME | the name of the first project set by the project() command, i.e. the top level project.
PROJECT_SOURCE_DIR | The source directory of the current project.
PROJECT_BINARY_DIR | The build directory for the current project.
name_SOURCE_DIR | The source directory of the project called "name". sublibrary1_SOURCE_DIR
name_BINARY_DIR | The binary directory of the project called "name". sublibrary1_BINARY_DIR
# Public VS Private VS Interface

https://leimao.github.io/blog/CMake-Public-Private-Interface/

## Include Inheritance

|Link Type|Description|
|--|--|
PUBLIC	| All the directories following PUBLIC will be used for the current target and the other targets that have dependencies on the current target, i.e., appending the directories to INCLUDE_DIRECTORIES and INTERFACE_INCLUDE_DIRECTORIES.
PRIVATE	| All the include directories following PRIVATE will be used for the current target only, i.e., appending the directories to INCLUDE_DIRECTORIES.
INTERFACE | All the include directories following INTERFACE will NOT be used for the current target but will be accessible for the other targets that have dependencies on the current target, i.e., appending the directories to INTERFACE_INCLUDE_DIRECTORIES. 

## Link Inheritance

|Link Type|Description|
|--|--|
PUBLIC | All the objects following PUBLIC will be used for linking to the current target and providing the interface to the other targets that have dependencies on the current target.
PRIVATE	| All the objects following PRIVATE will only be used for linking to the current target.
INTERFACE | All the objects following INTERFACE will only be used for providing the interface to the other targets that have dependencies on the current target.

## Conclusion

PRIVATE only cares about himself and does not allow inheritance. INTERFACE only cares about others and allows inheritance. PUBLIC cares about everyone and allows inheritance.
