# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/solution/basis

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/solution/basis

# Include any dependencies generated for this target.
include source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/depend.make

# Include the progress variables for this target.
include source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/progress.make

# Include the compile flags for this target's objects.
include source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/flags.make

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/flags.make
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.cxx
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -o CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch -c /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.cxx

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.i"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.cxx > CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.i

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.s"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.cxx -o CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.s

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/flags.make
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_.cpp.o: source/app/gpu_opengl/_.cpp
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_.cpp.o"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -o CMakeFiles/gpu_opengl.dir/_.cpp.o -c /home/pi/solution/basis/source/app/gpu_opengl/_.cpp

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gpu_opengl.dir/_.cpp.i"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/gpu_opengl/_.cpp > CMakeFiles/gpu_opengl.dir/_.cpp.i

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gpu_opengl.dir/_.cpp.s"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/gpu_opengl/_.cpp -o CMakeFiles/gpu_opengl.dir/_.cpp.s

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_factory.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/flags.make
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_factory.cpp.o: source/app/gpu_opengl/_factory.cpp
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_factory.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_factory.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_factory.cpp.o"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -o CMakeFiles/gpu_opengl.dir/_factory.cpp.o -c /home/pi/solution/basis/source/app/gpu_opengl/_factory.cpp

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_factory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gpu_opengl.dir/_factory.cpp.i"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/gpu_opengl/_factory.cpp > CMakeFiles/gpu_opengl.dir/_factory.cpp.i

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_factory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gpu_opengl.dir/_factory.cpp.s"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/gpu_opengl/_factory.cpp -o CMakeFiles/gpu_opengl.dir/_factory.cpp.s

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/buffer.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/flags.make
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/buffer.cpp.o: source/app/gpu_opengl/buffer.cpp
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/buffer.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/buffer.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/buffer.cpp.o"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -o CMakeFiles/gpu_opengl.dir/buffer.cpp.o -c /home/pi/solution/basis/source/app/gpu_opengl/buffer.cpp

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gpu_opengl.dir/buffer.cpp.i"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/gpu_opengl/buffer.cpp > CMakeFiles/gpu_opengl.dir/buffer.cpp.i

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gpu_opengl.dir/buffer.cpp.s"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/gpu_opengl/buffer.cpp -o CMakeFiles/gpu_opengl.dir/buffer.cpp.s

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/flags.make
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context.cpp.o: source/app/gpu_opengl/context.cpp
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context.cpp.o"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -o CMakeFiles/gpu_opengl.dir/context.cpp.o -c /home/pi/solution/basis/source/app/gpu_opengl/context.cpp

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gpu_opengl.dir/context.cpp.i"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/gpu_opengl/context.cpp > CMakeFiles/gpu_opengl.dir/context.cpp.i

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gpu_opengl.dir/context.cpp.s"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/gpu_opengl/context.cpp -o CMakeFiles/gpu_opengl.dir/context.cpp.s

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/framework.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/flags.make
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/framework.cpp.o: source/app/gpu_opengl/framework.cpp
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/framework.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/framework.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/framework.cpp.o"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -o CMakeFiles/gpu_opengl.dir/framework.cpp.o -c /home/pi/solution/basis/source/app/gpu_opengl/framework.cpp

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/framework.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gpu_opengl.dir/framework.cpp.i"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/gpu_opengl/framework.cpp > CMakeFiles/gpu_opengl.dir/framework.cpp.i

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/framework.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gpu_opengl.dir/framework.cpp.s"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/gpu_opengl/framework.cpp -o CMakeFiles/gpu_opengl.dir/framework.cpp.s

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/image_opengl.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/flags.make
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/image_opengl.cpp.o: source/app/gpu_opengl/image_opengl.cpp
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/image_opengl.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/image_opengl.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/image_opengl.cpp.o"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -o CMakeFiles/gpu_opengl.dir/image_opengl.cpp.o -c /home/pi/solution/basis/source/app/gpu_opengl/image_opengl.cpp

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/image_opengl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gpu_opengl.dir/image_opengl.cpp.i"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/gpu_opengl/image_opengl.cpp > CMakeFiles/gpu_opengl.dir/image_opengl.cpp.i

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/image_opengl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gpu_opengl.dir/image_opengl.cpp.s"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/gpu_opengl/image_opengl.cpp -o CMakeFiles/gpu_opengl.dir/image_opengl.cpp.s

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/opengl.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/flags.make
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/opengl.cpp.o: source/app/gpu_opengl/opengl.cpp
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/opengl.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/opengl.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/opengl.cpp.o"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -o CMakeFiles/gpu_opengl.dir/opengl.cpp.o -c /home/pi/solution/basis/source/app/gpu_opengl/opengl.cpp

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/opengl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gpu_opengl.dir/opengl.cpp.i"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/gpu_opengl/opengl.cpp > CMakeFiles/gpu_opengl.dir/opengl.cpp.i

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/opengl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gpu_opengl.dir/opengl.cpp.s"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/gpu_opengl/opengl.cpp -o CMakeFiles/gpu_opengl.dir/opengl.cpp.s

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/program.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/flags.make
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/program.cpp.o: source/app/gpu_opengl/program.cpp
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/program.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/program.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/program.cpp.o"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -o CMakeFiles/gpu_opengl.dir/program.cpp.o -c /home/pi/solution/basis/source/app/gpu_opengl/program.cpp

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/program.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gpu_opengl.dir/program.cpp.i"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/gpu_opengl/program.cpp > CMakeFiles/gpu_opengl.dir/program.cpp.i

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/program.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gpu_opengl.dir/program.cpp.s"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/gpu_opengl/program.cpp -o CMakeFiles/gpu_opengl.dir/program.cpp.s

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/shader.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/flags.make
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/shader.cpp.o: source/app/gpu_opengl/shader.cpp
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/shader.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/shader.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/shader.cpp.o"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -o CMakeFiles/gpu_opengl.dir/shader.cpp.o -c /home/pi/solution/basis/source/app/gpu_opengl/shader.cpp

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gpu_opengl.dir/shader.cpp.i"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/gpu_opengl/shader.cpp > CMakeFiles/gpu_opengl.dir/shader.cpp.i

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gpu_opengl.dir/shader.cpp.s"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/gpu_opengl/shader.cpp -o CMakeFiles/gpu_opengl.dir/shader.cpp.s

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_egl.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/flags.make
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_egl.cpp.o: source/app/gpu_opengl/context_egl.cpp
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_egl.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_egl.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_egl.cpp.o"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -o CMakeFiles/gpu_opengl.dir/context_egl.cpp.o -c /home/pi/solution/basis/source/app/gpu_opengl/context_egl.cpp

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_egl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gpu_opengl.dir/context_egl.cpp.i"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/gpu_opengl/context_egl.cpp > CMakeFiles/gpu_opengl.dir/context_egl.cpp.i

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_egl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gpu_opengl.dir/context_egl.cpp.s"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/gpu_opengl/context_egl.cpp -o CMakeFiles/gpu_opengl.dir/context_egl.cpp.s

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_glx.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/flags.make
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_glx.cpp.o: source/app/gpu_opengl/context_glx.cpp
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_glx.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_glx.cpp.o: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_glx.cpp.o"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -o CMakeFiles/gpu_opengl.dir/context_glx.cpp.o -c /home/pi/solution/basis/source/app/gpu_opengl/context_glx.cpp

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_glx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gpu_opengl.dir/context_glx.cpp.i"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/gpu_opengl/context_glx.cpp > CMakeFiles/gpu_opengl.dir/context_glx.cpp.i

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_glx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gpu_opengl.dir/context_glx.cpp.s"
	cd /home/pi/solution/basis/source/app/gpu_opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/gpu_opengl/context_glx.cpp -o CMakeFiles/gpu_opengl.dir/context_glx.cpp.s

# Object files for target gpu_opengl
gpu_opengl_OBJECTS = \
"CMakeFiles/gpu_opengl.dir/_.cpp.o" \
"CMakeFiles/gpu_opengl.dir/_factory.cpp.o" \
"CMakeFiles/gpu_opengl.dir/buffer.cpp.o" \
"CMakeFiles/gpu_opengl.dir/context.cpp.o" \
"CMakeFiles/gpu_opengl.dir/framework.cpp.o" \
"CMakeFiles/gpu_opengl.dir/image_opengl.cpp.o" \
"CMakeFiles/gpu_opengl.dir/opengl.cpp.o" \
"CMakeFiles/gpu_opengl.dir/program.cpp.o" \
"CMakeFiles/gpu_opengl.dir/shader.cpp.o" \
"CMakeFiles/gpu_opengl.dir/context_egl.cpp.o" \
"CMakeFiles/gpu_opengl.dir/context_glx.cpp.o"

# External object files for target gpu_opengl
gpu_opengl_EXTERNAL_OBJECTS =

output/libgpu_opengl.so: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/cmake_pch.hxx.gch
output/libgpu_opengl.so: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_.cpp.o
output/libgpu_opengl.so: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/_factory.cpp.o
output/libgpu_opengl.so: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/buffer.cpp.o
output/libgpu_opengl.so: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context.cpp.o
output/libgpu_opengl.so: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/framework.cpp.o
output/libgpu_opengl.so: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/image_opengl.cpp.o
output/libgpu_opengl.so: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/opengl.cpp.o
output/libgpu_opengl.so: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/program.cpp.o
output/libgpu_opengl.so: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/shader.cpp.o
output/libgpu_opengl.so: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_egl.cpp.o
output/libgpu_opengl.so: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/context_glx.cpp.o
output/libgpu_opengl.so: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/build.make
output/libgpu_opengl.so: output/libaura_posix.so
output/libgpu_opengl.so: output/libaura.so
output/libgpu_opengl.so: output/libaqua.so
output/libgpu_opengl.so: output/libapex.so
output/libgpu_opengl.so: output/libacme.so
output/libgpu_opengl.so: source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX shared library ../../../output/libgpu_opengl.so"
	cd /home/pi/solution/basis/source/app/gpu_opengl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gpu_opengl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/build: output/libgpu_opengl.so

.PHONY : source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/build

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/clean:
	cd /home/pi/solution/basis/source/app/gpu_opengl && $(CMAKE_COMMAND) -P CMakeFiles/gpu_opengl.dir/cmake_clean.cmake
.PHONY : source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/clean

source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/depend:
	cd /home/pi/solution/basis && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/solution/basis /home/pi/solution/basis/source/app/gpu_opengl /home/pi/solution/basis /home/pi/solution/basis/source/app/gpu_opengl /home/pi/solution/basis/source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/app/gpu_opengl/CMakeFiles/gpu_opengl.dir/depend

