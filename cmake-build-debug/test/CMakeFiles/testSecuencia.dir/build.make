# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2021.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2021.3.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug

# Include any dependencies generated for this target.
include test/CMakeFiles/testSecuencia.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/testSecuencia.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/testSecuencia.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/testSecuencia.dir/flags.make

test/CMakeFiles/testSecuencia.dir/testSecuencia.cpp.obj: test/CMakeFiles/testSecuencia.dir/flags.make
test/CMakeFiles/testSecuencia.dir/testSecuencia.cpp.obj: test/CMakeFiles/testSecuencia.dir/includes_CXX.rsp
test/CMakeFiles/testSecuencia.dir/testSecuencia.cpp.obj: ../test/testSecuencia.cpp
test/CMakeFiles/testSecuencia.dir/testSecuencia.cpp.obj: test/CMakeFiles/testSecuencia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/testSecuencia.dir/testSecuencia.cpp.obj"
	cd /d D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug\test && "D:\CLion 2021.3.3\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/testSecuencia.dir/testSecuencia.cpp.obj -MF CMakeFiles\testSecuencia.dir\testSecuencia.cpp.obj.d -o CMakeFiles\testSecuencia.dir\testSecuencia.cpp.obj -c D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\test\testSecuencia.cpp

test/CMakeFiles/testSecuencia.dir/testSecuencia.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testSecuencia.dir/testSecuencia.cpp.i"
	cd /d D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug\test && "D:\CLion 2021.3.3\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\test\testSecuencia.cpp > CMakeFiles\testSecuencia.dir\testSecuencia.cpp.i

test/CMakeFiles/testSecuencia.dir/testSecuencia.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testSecuencia.dir/testSecuencia.cpp.s"
	cd /d D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug\test && "D:\CLion 2021.3.3\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\test\testSecuencia.cpp -o CMakeFiles\testSecuencia.dir\testSecuencia.cpp.s

test/CMakeFiles/testSecuencia.dir/__/src/secuenciaEnteros.cpp.obj: test/CMakeFiles/testSecuencia.dir/flags.make
test/CMakeFiles/testSecuencia.dir/__/src/secuenciaEnteros.cpp.obj: test/CMakeFiles/testSecuencia.dir/includes_CXX.rsp
test/CMakeFiles/testSecuencia.dir/__/src/secuenciaEnteros.cpp.obj: ../src/secuenciaEnteros.cpp
test/CMakeFiles/testSecuencia.dir/__/src/secuenciaEnteros.cpp.obj: test/CMakeFiles/testSecuencia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/testSecuencia.dir/__/src/secuenciaEnteros.cpp.obj"
	cd /d D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug\test && "D:\CLion 2021.3.3\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/testSecuencia.dir/__/src/secuenciaEnteros.cpp.obj -MF CMakeFiles\testSecuencia.dir\__\src\secuenciaEnteros.cpp.obj.d -o CMakeFiles\testSecuencia.dir\__\src\secuenciaEnteros.cpp.obj -c D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\src\secuenciaEnteros.cpp

test/CMakeFiles/testSecuencia.dir/__/src/secuenciaEnteros.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testSecuencia.dir/__/src/secuenciaEnteros.cpp.i"
	cd /d D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug\test && "D:\CLion 2021.3.3\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\src\secuenciaEnteros.cpp > CMakeFiles\testSecuencia.dir\__\src\secuenciaEnteros.cpp.i

test/CMakeFiles/testSecuencia.dir/__/src/secuenciaEnteros.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testSecuencia.dir/__/src/secuenciaEnteros.cpp.s"
	cd /d D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug\test && "D:\CLion 2021.3.3\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\src\secuenciaEnteros.cpp -o CMakeFiles\testSecuencia.dir\__\src\secuenciaEnteros.cpp.s

# Object files for target testSecuencia
testSecuencia_OBJECTS = \
"CMakeFiles/testSecuencia.dir/testSecuencia.cpp.obj" \
"CMakeFiles/testSecuencia.dir/__/src/secuenciaEnteros.cpp.obj"

# External object files for target testSecuencia
testSecuencia_EXTERNAL_OBJECTS =

test/testSecuencia.exe: test/CMakeFiles/testSecuencia.dir/testSecuencia.cpp.obj
test/testSecuencia.exe: test/CMakeFiles/testSecuencia.dir/__/src/secuenciaEnteros.cpp.obj
test/testSecuencia.exe: test/CMakeFiles/testSecuencia.dir/build.make
test/testSecuencia.exe: test/CMakeFiles/testSecuencia.dir/linklibs.rsp
test/testSecuencia.exe: test/CMakeFiles/testSecuencia.dir/objects1.rsp
test/testSecuencia.exe: test/CMakeFiles/testSecuencia.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable testSecuencia.exe"
	cd /d D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug\test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\testSecuencia.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/testSecuencia.dir/build: test/testSecuencia.exe
.PHONY : test/CMakeFiles/testSecuencia.dir/build

test/CMakeFiles/testSecuencia.dir/clean:
	cd /d D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug\test && $(CMAKE_COMMAND) -P CMakeFiles\testSecuencia.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/testSecuencia.dir/clean

test/CMakeFiles/testSecuencia.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\test D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug\test D:\MigueCc99\Escritorio\Universidad\TFG\busquedaSecuencia\cmake-build-debug\test\CMakeFiles\testSecuencia.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/testSecuencia.dir/depend
