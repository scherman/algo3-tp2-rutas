# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jscherman/CLionProjects/algo3-tp2-rutas

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jscherman/CLionProjects/algo3-tp2-rutas

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/local/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jscherman/CLionProjects/algo3-tp2-rutas/CMakeFiles /home/jscherman/CLionProjects/algo3-tp2-rutas/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jscherman/CLionProjects/algo3-tp2-rutas/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named ej1

# Build rule for target.
ej1: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ej1
.PHONY : ej1

# fast build rule for target.
ej1/fast:
	$(MAKE) -f CMakeFiles/ej1.dir/build.make CMakeFiles/ej1.dir/build
.PHONY : ej1/fast

#=============================================================================
# Target rules for targets named ej2

# Build rule for target.
ej2: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ej2
.PHONY : ej2

# fast build rule for target.
ej2/fast:
	$(MAKE) -f CMakeFiles/ej2.dir/build.make CMakeFiles/ej2.dir/build
.PHONY : ej2/fast

#=============================================================================
# Target rules for targets named ej3

# Build rule for target.
ej3: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ej3
.PHONY : ej3

# fast build rule for target.
ej3/fast:
	$(MAKE) -f CMakeFiles/ej3.dir/build.make CMakeFiles/ej3.dir/build
.PHONY : ej3/fast

problema1.o: problema1.cpp.o

.PHONY : problema1.o

# target to build an object file
problema1.cpp.o:
	$(MAKE) -f CMakeFiles/ej1.dir/build.make CMakeFiles/ej1.dir/problema1.cpp.o
.PHONY : problema1.cpp.o

problema1.i: problema1.cpp.i

.PHONY : problema1.i

# target to preprocess a source file
problema1.cpp.i:
	$(MAKE) -f CMakeFiles/ej1.dir/build.make CMakeFiles/ej1.dir/problema1.cpp.i
.PHONY : problema1.cpp.i

problema1.s: problema1.cpp.s

.PHONY : problema1.s

# target to generate assembly for a file
problema1.cpp.s:
	$(MAKE) -f CMakeFiles/ej1.dir/build.make CMakeFiles/ej1.dir/problema1.cpp.s
.PHONY : problema1.cpp.s

problema2.o: problema2.cpp.o

.PHONY : problema2.o

# target to build an object file
problema2.cpp.o:
	$(MAKE) -f CMakeFiles/ej2.dir/build.make CMakeFiles/ej2.dir/problema2.cpp.o
.PHONY : problema2.cpp.o

problema2.i: problema2.cpp.i

.PHONY : problema2.i

# target to preprocess a source file
problema2.cpp.i:
	$(MAKE) -f CMakeFiles/ej2.dir/build.make CMakeFiles/ej2.dir/problema2.cpp.i
.PHONY : problema2.cpp.i

problema2.s: problema2.cpp.s

.PHONY : problema2.s

# target to generate assembly for a file
problema2.cpp.s:
	$(MAKE) -f CMakeFiles/ej2.dir/build.make CMakeFiles/ej2.dir/problema2.cpp.s
.PHONY : problema2.cpp.s

problema3.o: problema3.cpp.o

.PHONY : problema3.o

# target to build an object file
problema3.cpp.o:
	$(MAKE) -f CMakeFiles/ej3.dir/build.make CMakeFiles/ej3.dir/problema3.cpp.o
.PHONY : problema3.cpp.o

problema3.i: problema3.cpp.i

.PHONY : problema3.i

# target to preprocess a source file
problema3.cpp.i:
	$(MAKE) -f CMakeFiles/ej3.dir/build.make CMakeFiles/ej3.dir/problema3.cpp.i
.PHONY : problema3.cpp.i

problema3.s: problema3.cpp.s

.PHONY : problema3.s

# target to generate assembly for a file
problema3.cpp.s:
	$(MAKE) -f CMakeFiles/ej3.dir/build.make CMakeFiles/ej3.dir/problema3.cpp.s
.PHONY : problema3.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... ej1"
	@echo "... edit_cache"
	@echo "... ej2"
	@echo "... ej3"
	@echo "... problema1.o"
	@echo "... problema1.i"
	@echo "... problema1.s"
	@echo "... problema2.o"
	@echo "... problema2.i"
	@echo "... problema2.s"
	@echo "... problema3.o"
	@echo "... problema3.i"
	@echo "... problema3.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

