# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = C:\Users\Andreas\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\212.5080.54\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Andreas\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\212.5080.54\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Andreas\ikt203\worksheets\worksheet_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Andreas\ikt203\worksheets\worksheet_1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/worksheet_1.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/worksheet_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/worksheet_1.dir/flags.make

CMakeFiles/worksheet_1.dir/main.c.obj: CMakeFiles/worksheet_1.dir/flags.make
CMakeFiles/worksheet_1.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Andreas\ikt203\worksheets\worksheet_1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/worksheet_1.dir/main.c.obj"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\worksheet_1.dir\main.c.obj -c C:\Users\Andreas\ikt203\worksheets\worksheet_1\main.c

CMakeFiles/worksheet_1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/worksheet_1.dir/main.c.i"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Andreas\ikt203\worksheets\worksheet_1\main.c > CMakeFiles\worksheet_1.dir\main.c.i

CMakeFiles/worksheet_1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/worksheet_1.dir/main.c.s"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Andreas\ikt203\worksheets\worksheet_1\main.c -o CMakeFiles\worksheet_1.dir\main.c.s

# Object files for target worksheet_1
worksheet_1_OBJECTS = \
"CMakeFiles/worksheet_1.dir/main.c.obj"

# External object files for target worksheet_1
worksheet_1_EXTERNAL_OBJECTS =

worksheet_1.exe: CMakeFiles/worksheet_1.dir/main.c.obj
worksheet_1.exe: CMakeFiles/worksheet_1.dir/build.make
worksheet_1.exe: CMakeFiles/worksheet_1.dir/linklibs.rsp
worksheet_1.exe: CMakeFiles/worksheet_1.dir/objects1.rsp
worksheet_1.exe: CMakeFiles/worksheet_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Andreas\ikt203\worksheets\worksheet_1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable worksheet_1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\worksheet_1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/worksheet_1.dir/build: worksheet_1.exe
.PHONY : CMakeFiles/worksheet_1.dir/build

CMakeFiles/worksheet_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\worksheet_1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/worksheet_1.dir/clean

CMakeFiles/worksheet_1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Andreas\ikt203\worksheets\worksheet_1 C:\Users\Andreas\ikt203\worksheets\worksheet_1 C:\Users\Andreas\ikt203\worksheets\worksheet_1\cmake-build-debug C:\Users\Andreas\ikt203\worksheets\worksheet_1\cmake-build-debug C:\Users\Andreas\ikt203\worksheets\worksheet_1\cmake-build-debug\CMakeFiles\worksheet_1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/worksheet_1.dir/depend

