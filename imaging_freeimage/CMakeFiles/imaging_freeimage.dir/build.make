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
include source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/depend.make

# Include the progress variables for this target.
include source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/progress.make

# Include the compile flags for this target's objects.
include source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/flags.make

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/flags.make
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.cxx
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -o CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch -c /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.cxx

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.i"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.cxx > CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.i

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.s"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.cxx -o CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.s

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/flags.make
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_.cpp.o: source/app/imaging_freeimage/_.cpp
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_.cpp.o"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -o CMakeFiles/imaging_freeimage.dir/_.cpp.o -c /home/pi/solution/basis/source/app/imaging_freeimage/_.cpp

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imaging_freeimage.dir/_.cpp.i"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/imaging_freeimage/_.cpp > CMakeFiles/imaging_freeimage.dir/_.cpp.i

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imaging_freeimage.dir/_.cpp.s"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/imaging_freeimage/_.cpp -o CMakeFiles/imaging_freeimage.dir/_.cpp.s

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_factory.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/flags.make
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_factory.cpp.o: source/app/imaging_freeimage/_factory.cpp
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_factory.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_factory.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_factory.cpp.o"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -o CMakeFiles/imaging_freeimage.dir/_factory.cpp.o -c /home/pi/solution/basis/source/app/imaging_freeimage/_factory.cpp

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_factory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imaging_freeimage.dir/_factory.cpp.i"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/imaging_freeimage/_factory.cpp > CMakeFiles/imaging_freeimage.dir/_factory.cpp.i

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_factory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imaging_freeimage.dir/_factory.cpp.s"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/imaging_freeimage/_factory.cpp -o CMakeFiles/imaging_freeimage.dir/_factory.cpp.s

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/context_image.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/flags.make
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/context_image.cpp.o: source/app/imaging_freeimage/context_image.cpp
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/context_image.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/context_image.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/context_image.cpp.o"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -o CMakeFiles/imaging_freeimage.dir/context_image.cpp.o -c /home/pi/solution/basis/source/app/imaging_freeimage/context_image.cpp

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/context_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imaging_freeimage.dir/context_image.cpp.i"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/imaging_freeimage/context_image.cpp > CMakeFiles/imaging_freeimage.dir/context_image.cpp.i

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/context_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imaging_freeimage.dir/context_image.cpp.s"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/imaging_freeimage/context_image.cpp -o CMakeFiles/imaging_freeimage.dir/context_image.cpp.s

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/flags.make
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure.cpp.o: source/app/imaging_freeimage/file_procedure.cpp
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure.cpp.o"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -o CMakeFiles/imaging_freeimage.dir/file_procedure.cpp.o -c /home/pi/solution/basis/source/app/imaging_freeimage/file_procedure.cpp

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imaging_freeimage.dir/file_procedure.cpp.i"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/imaging_freeimage/file_procedure.cpp > CMakeFiles/imaging_freeimage.dir/file_procedure.cpp.i

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imaging_freeimage.dir/file_procedure.cpp.s"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/imaging_freeimage/file_procedure.cpp -o CMakeFiles/imaging_freeimage.dir/file_procedure.cpp.s

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure_ex1.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/flags.make
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure_ex1.cpp.o: source/app/imaging_freeimage/file_procedure_ex1.cpp
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure_ex1.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure_ex1.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure_ex1.cpp.o"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -o CMakeFiles/imaging_freeimage.dir/file_procedure_ex1.cpp.o -c /home/pi/solution/basis/source/app/imaging_freeimage/file_procedure_ex1.cpp

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure_ex1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imaging_freeimage.dir/file_procedure_ex1.cpp.i"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/imaging_freeimage/file_procedure_ex1.cpp > CMakeFiles/imaging_freeimage.dir/file_procedure_ex1.cpp.i

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure_ex1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imaging_freeimage.dir/file_procedure_ex1.cpp.s"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/imaging_freeimage/file_procedure_ex1.cpp -o CMakeFiles/imaging_freeimage.dir/file_procedure_ex1.cpp.s

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/framework.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/flags.make
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/framework.cpp.o: source/app/imaging_freeimage/framework.cpp
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/framework.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/framework.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/framework.cpp.o"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -o CMakeFiles/imaging_freeimage.dir/framework.cpp.o -c /home/pi/solution/basis/source/app/imaging_freeimage/framework.cpp

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/framework.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imaging_freeimage.dir/framework.cpp.i"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/imaging_freeimage/framework.cpp > CMakeFiles/imaging_freeimage.dir/framework.cpp.i

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/framework.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imaging_freeimage.dir/framework.cpp.s"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/imaging_freeimage/framework.cpp -o CMakeFiles/imaging_freeimage.dir/framework.cpp.s

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/flags.make
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading.cpp.o: source/app/imaging_freeimage/loading.cpp
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading.cpp.o"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -o CMakeFiles/imaging_freeimage.dir/loading.cpp.o -c /home/pi/solution/basis/source/app/imaging_freeimage/loading.cpp

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imaging_freeimage.dir/loading.cpp.i"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/imaging_freeimage/loading.cpp > CMakeFiles/imaging_freeimage.dir/loading.cpp.i

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imaging_freeimage.dir/loading.cpp.s"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/imaging_freeimage/loading.cpp -o CMakeFiles/imaging_freeimage.dir/loading.cpp.s

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_multi_frame.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/flags.make
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_multi_frame.cpp.o: source/app/imaging_freeimage/loading_multi_frame.cpp
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_multi_frame.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_multi_frame.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_multi_frame.cpp.o"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -o CMakeFiles/imaging_freeimage.dir/loading_multi_frame.cpp.o -c /home/pi/solution/basis/source/app/imaging_freeimage/loading_multi_frame.cpp

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_multi_frame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imaging_freeimage.dir/loading_multi_frame.cpp.i"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/imaging_freeimage/loading_multi_frame.cpp > CMakeFiles/imaging_freeimage.dir/loading_multi_frame.cpp.i

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_multi_frame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imaging_freeimage.dir/loading_multi_frame.cpp.s"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/imaging_freeimage/loading_multi_frame.cpp -o CMakeFiles/imaging_freeimage.dir/loading_multi_frame.cpp.s

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/saving.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/flags.make
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/saving.cpp.o: source/app/imaging_freeimage/saving.cpp
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/saving.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/saving.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/saving.cpp.o"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -o CMakeFiles/imaging_freeimage.dir/saving.cpp.o -c /home/pi/solution/basis/source/app/imaging_freeimage/saving.cpp

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/saving.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imaging_freeimage.dir/saving.cpp.i"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/imaging_freeimage/saving.cpp > CMakeFiles/imaging_freeimage.dir/saving.cpp.i

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/saving.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imaging_freeimage.dir/saving.cpp.s"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/imaging_freeimage/saving.cpp -o CMakeFiles/imaging_freeimage.dir/saving.cpp.s

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_svg.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/flags.make
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_svg.cpp.o: source/app/imaging_freeimage/loading_svg.cpp
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_svg.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_svg.cpp.o: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_svg.cpp.o"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -o CMakeFiles/imaging_freeimage.dir/loading_svg.cpp.o -c /home/pi/solution/basis/source/app/imaging_freeimage/loading_svg.cpp

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_svg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imaging_freeimage.dir/loading_svg.cpp.i"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app/imaging_freeimage/loading_svg.cpp > CMakeFiles/imaging_freeimage.dir/loading_svg.cpp.i

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_svg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imaging_freeimage.dir/loading_svg.cpp.s"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app/imaging_freeimage/loading_svg.cpp -o CMakeFiles/imaging_freeimage.dir/loading_svg.cpp.s

# Object files for target imaging_freeimage
imaging_freeimage_OBJECTS = \
"CMakeFiles/imaging_freeimage.dir/_.cpp.o" \
"CMakeFiles/imaging_freeimage.dir/_factory.cpp.o" \
"CMakeFiles/imaging_freeimage.dir/context_image.cpp.o" \
"CMakeFiles/imaging_freeimage.dir/file_procedure.cpp.o" \
"CMakeFiles/imaging_freeimage.dir/file_procedure_ex1.cpp.o" \
"CMakeFiles/imaging_freeimage.dir/framework.cpp.o" \
"CMakeFiles/imaging_freeimage.dir/loading.cpp.o" \
"CMakeFiles/imaging_freeimage.dir/loading_multi_frame.cpp.o" \
"CMakeFiles/imaging_freeimage.dir/saving.cpp.o" \
"CMakeFiles/imaging_freeimage.dir/loading_svg.cpp.o"

# External object files for target imaging_freeimage
imaging_freeimage_EXTERNAL_OBJECTS =

output/libimaging_freeimage.so: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/cmake_pch.hxx.gch
output/libimaging_freeimage.so: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_.cpp.o
output/libimaging_freeimage.so: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/_factory.cpp.o
output/libimaging_freeimage.so: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/context_image.cpp.o
output/libimaging_freeimage.so: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure.cpp.o
output/libimaging_freeimage.so: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/file_procedure_ex1.cpp.o
output/libimaging_freeimage.so: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/framework.cpp.o
output/libimaging_freeimage.so: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading.cpp.o
output/libimaging_freeimage.so: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_multi_frame.cpp.o
output/libimaging_freeimage.so: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/saving.cpp.o
output/libimaging_freeimage.so: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/loading_svg.cpp.o
output/libimaging_freeimage.so: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/build.make
output/libimaging_freeimage.so: output/libaura.so
output/libimaging_freeimage.so: output/libaqua.so
output/libimaging_freeimage.so: output/libapex.so
output/libimaging_freeimage.so: output/libacme.so
output/libimaging_freeimage.so: source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX shared library ../../../output/libimaging_freeimage.so"
	cd /home/pi/solution/basis/source/app/imaging_freeimage && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imaging_freeimage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/build: output/libimaging_freeimage.so

.PHONY : source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/build

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/clean:
	cd /home/pi/solution/basis/source/app/imaging_freeimage && $(CMAKE_COMMAND) -P CMakeFiles/imaging_freeimage.dir/cmake_clean.cmake
.PHONY : source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/clean

source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/depend:
	cd /home/pi/solution/basis && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/solution/basis /home/pi/solution/basis/source/app/imaging_freeimage /home/pi/solution/basis /home/pi/solution/basis/source/app/imaging_freeimage /home/pi/solution/basis/source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/app/imaging_freeimage/CMakeFiles/imaging_freeimage.dir/depend

