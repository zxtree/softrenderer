# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/zxtree/projects/softrender

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zxtree/projects/softrender

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/zxtree/projects/softrender/CMakeFiles /home/zxtree/projects/softrender//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/zxtree/projects/softrender/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named softrender

# Build rule for target.
softrender: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 softrender
.PHONY : softrender

# fast build rule for target.
softrender/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/build
.PHONY : softrender/fast

src/light.o: src/light.cpp.o

.PHONY : src/light.o

# target to build an object file
src/light.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/light.cpp.o
.PHONY : src/light.cpp.o

src/light.i: src/light.cpp.i

.PHONY : src/light.i

# target to preprocess a source file
src/light.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/light.cpp.i
.PHONY : src/light.cpp.i

src/light.s: src/light.cpp.s

.PHONY : src/light.s

# target to generate assembly for a file
src/light.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/light.cpp.s
.PHONY : src/light.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/render.o: src/render.cpp.o

.PHONY : src/render.o

# target to build an object file
src/render.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/render.cpp.o
.PHONY : src/render.cpp.o

src/render.i: src/render.cpp.i

.PHONY : src/render.i

# target to preprocess a source file
src/render.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/render.cpp.i
.PHONY : src/render.cpp.i

src/render.s: src/render.cpp.s

.PHONY : src/render.s

# target to generate assembly for a file
src/render.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/render.cpp.s
.PHONY : src/render.cpp.s

src/scene.o: src/scene.cpp.o

.PHONY : src/scene.o

# target to build an object file
src/scene.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/scene.cpp.o
.PHONY : src/scene.cpp.o

src/scene.i: src/scene.cpp.i

.PHONY : src/scene.i

# target to preprocess a source file
src/scene.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/scene.cpp.i
.PHONY : src/scene.cpp.i

src/scene.s: src/scene.cpp.s

.PHONY : src/scene.s

# target to generate assembly for a file
src/scene.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/scene.cpp.s
.PHONY : src/scene.cpp.s

src/triangles.o: src/triangles.cpp.o

.PHONY : src/triangles.o

# target to build an object file
src/triangles.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/triangles.cpp.o
.PHONY : src/triangles.cpp.o

src/triangles.i: src/triangles.cpp.i

.PHONY : src/triangles.i

# target to preprocess a source file
src/triangles.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/triangles.cpp.i
.PHONY : src/triangles.cpp.i

src/triangles.s: src/triangles.cpp.s

.PHONY : src/triangles.s

# target to generate assembly for a file
src/triangles.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/softrender.dir/build.make CMakeFiles/softrender.dir/src/triangles.cpp.s
.PHONY : src/triangles.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... softrender"
	@echo "... src/light.o"
	@echo "... src/light.i"
	@echo "... src/light.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/render.o"
	@echo "... src/render.i"
	@echo "... src/render.s"
	@echo "... src/scene.o"
	@echo "... src/scene.i"
	@echo "... src/scene.s"
	@echo "... src/triangles.o"
	@echo "... src/triangles.i"
	@echo "... src/triangles.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

