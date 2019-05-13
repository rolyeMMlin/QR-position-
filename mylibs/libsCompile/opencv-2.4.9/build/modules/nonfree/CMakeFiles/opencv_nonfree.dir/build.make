# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build

# Include any dependencies generated for this target.
include modules/nonfree/CMakeFiles/opencv_nonfree.dir/depend.make

# Include the progress variables for this target.
include modules/nonfree/CMakeFiles/opencv_nonfree.dir/progress.make

# Include the compile flags for this target's objects.
include modules/nonfree/CMakeFiles/opencv_nonfree.dir/flags.make

modules/nonfree/opencl_kernels.cpp: ../modules/nonfree/src/opencl/surf.cl
modules/nonfree/opencl_kernels.cpp: ../cmake/cl2cpp.cmake
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating opencl_kernels.cpp, opencl_kernels.hpp"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/cmake -DCL_DIR="/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/opencl" -DOUTPUT="/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/opencl_kernels.cpp" -P /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/cmake/cl2cpp.cmake

modules/nonfree/opencl_kernels.hpp: modules/nonfree/opencl_kernels.cpp
	@$(CMAKE_COMMAND) -E touch_nocreate modules/nonfree/opencl_kernels.hpp

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o: modules/nonfree/CMakeFiles/opencv_nonfree.dir/flags.make
modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o: ../modules/nonfree/src/surf_ocl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -o CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o -c /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/surf_ocl.cpp

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.i"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -E /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/surf_ocl.cpp > CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.i

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.s"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -S /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/surf_ocl.cpp -o CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.s

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o.requires:

.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o.requires

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o.provides: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o.requires
	$(MAKE) -f modules/nonfree/CMakeFiles/opencv_nonfree.dir/build.make modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o.provides.build
.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o.provides

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o.provides.build: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o


modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o: modules/nonfree/CMakeFiles/opencv_nonfree.dir/flags.make
modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o: ../modules/nonfree/src/nonfree_init.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -o CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o -c /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/nonfree_init.cpp

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.i"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -E /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/nonfree_init.cpp > CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.i

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.s"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -S /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/nonfree_init.cpp -o CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.s

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o.requires:

.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o.requires

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o.provides: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o.requires
	$(MAKE) -f modules/nonfree/CMakeFiles/opencv_nonfree.dir/build.make modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o.provides.build
.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o.provides

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o.provides.build: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o


modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o: modules/nonfree/CMakeFiles/opencv_nonfree.dir/flags.make
modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o: ../modules/nonfree/src/surf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -o CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o -c /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/surf.cpp

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_nonfree.dir/src/surf.cpp.i"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -E /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/surf.cpp > CMakeFiles/opencv_nonfree.dir/src/surf.cpp.i

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_nonfree.dir/src/surf.cpp.s"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -S /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/surf.cpp -o CMakeFiles/opencv_nonfree.dir/src/surf.cpp.s

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o.requires:

.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o.requires

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o.provides: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o.requires
	$(MAKE) -f modules/nonfree/CMakeFiles/opencv_nonfree.dir/build.make modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o.provides.build
.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o.provides

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o.provides.build: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o


modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o: modules/nonfree/CMakeFiles/opencv_nonfree.dir/flags.make
modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o: ../modules/nonfree/src/surf_gpu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -o CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o -c /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/surf_gpu.cpp

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.i"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -E /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/surf_gpu.cpp > CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.i

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.s"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -S /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/surf_gpu.cpp -o CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.s

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o.requires:

.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o.requires

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o.provides: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o.requires
	$(MAKE) -f modules/nonfree/CMakeFiles/opencv_nonfree.dir/build.make modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o.provides.build
.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o.provides

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o.provides.build: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o


modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o: modules/nonfree/CMakeFiles/opencv_nonfree.dir/flags.make
modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o: ../modules/nonfree/src/sift.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -o CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o -c /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/sift.cpp

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_nonfree.dir/src/sift.cpp.i"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -E /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/sift.cpp > CMakeFiles/opencv_nonfree.dir/src/sift.cpp.i

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_nonfree.dir/src/sift.cpp.s"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -S /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree/src/sift.cpp -o CMakeFiles/opencv_nonfree.dir/src/sift.cpp.s

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o.requires:

.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o.requires

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o.provides: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o.requires
	$(MAKE) -f modules/nonfree/CMakeFiles/opencv_nonfree.dir/build.make modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o.provides.build
.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o.provides

modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o.provides.build: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o


modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o: modules/nonfree/CMakeFiles/opencv_nonfree.dir/flags.make
modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o: modules/nonfree/opencl_kernels.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -o CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o -c /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/opencl_kernels.cpp

modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.i"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -E /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/opencl_kernels.cpp > CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.i

modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.s"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -include "/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/precomp.hpp" -Winvalid-pch  -S /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/opencl_kernels.cpp -o CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.s

modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o.requires:

.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o.requires

modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o.provides: modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o.requires
	$(MAKE) -f modules/nonfree/CMakeFiles/opencv_nonfree.dir/build.make modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o.provides.build
.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o.provides

modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o.provides.build: modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o


# Object files for target opencv_nonfree
opencv_nonfree_OBJECTS = \
"CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o" \
"CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o" \
"CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o" \
"CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o" \
"CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o" \
"CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o"

# External object files for target opencv_nonfree
opencv_nonfree_EXTERNAL_OBJECTS =

lib/libopencv_nonfree.so.2.4.9: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o
lib/libopencv_nonfree.so.2.4.9: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o
lib/libopencv_nonfree.so.2.4.9: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o
lib/libopencv_nonfree.so.2.4.9: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o
lib/libopencv_nonfree.so.2.4.9: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o
lib/libopencv_nonfree.so.2.4.9: modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o
lib/libopencv_nonfree.so.2.4.9: modules/nonfree/CMakeFiles/opencv_nonfree.dir/build.make
lib/libopencv_nonfree.so.2.4.9: lib/libopencv_gpu.so.2.4.9
lib/libopencv_nonfree.so.2.4.9: lib/libopencv_ocl.so.2.4.9
lib/libopencv_nonfree.so.2.4.9: lib/libopencv_legacy.so.2.4.9
lib/libopencv_nonfree.so.2.4.9: lib/libopencv_photo.so.2.4.9
lib/libopencv_nonfree.so.2.4.9: lib/libopencv_calib3d.so.2.4.9
lib/libopencv_nonfree.so.2.4.9: lib/libopencv_features2d.so.2.4.9
lib/libopencv_nonfree.so.2.4.9: lib/libopencv_flann.so.2.4.9
lib/libopencv_nonfree.so.2.4.9: lib/libopencv_ml.so.2.4.9
lib/libopencv_nonfree.so.2.4.9: lib/libopencv_video.so.2.4.9
lib/libopencv_nonfree.so.2.4.9: lib/libopencv_objdetect.so.2.4.9
lib/libopencv_nonfree.so.2.4.9: lib/libopencv_highgui.so.2.4.9
lib/libopencv_nonfree.so.2.4.9: lib/libopencv_imgproc.so.2.4.9
lib/libopencv_nonfree.so.2.4.9: lib/libopencv_core.so.2.4.9
lib/libopencv_nonfree.so.2.4.9: modules/nonfree/CMakeFiles/opencv_nonfree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX shared library ../../lib/libopencv_nonfree.so"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opencv_nonfree.dir/link.txt --verbose=$(VERBOSE)
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && $(CMAKE_COMMAND) -E cmake_symlink_library ../../lib/libopencv_nonfree.so.2.4.9 ../../lib/libopencv_nonfree.so.2.4 ../../lib/libopencv_nonfree.so

lib/libopencv_nonfree.so.2.4: lib/libopencv_nonfree.so.2.4.9
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libopencv_nonfree.so.2.4

lib/libopencv_nonfree.so: lib/libopencv_nonfree.so.2.4.9
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libopencv_nonfree.so

# Rule to build all files generated by this target.
modules/nonfree/CMakeFiles/opencv_nonfree.dir/build: lib/libopencv_nonfree.so

.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/build

modules/nonfree/CMakeFiles/opencv_nonfree.dir/requires: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_ocl.cpp.o.requires
modules/nonfree/CMakeFiles/opencv_nonfree.dir/requires: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/nonfree_init.cpp.o.requires
modules/nonfree/CMakeFiles/opencv_nonfree.dir/requires: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf.cpp.o.requires
modules/nonfree/CMakeFiles/opencv_nonfree.dir/requires: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/surf_gpu.cpp.o.requires
modules/nonfree/CMakeFiles/opencv_nonfree.dir/requires: modules/nonfree/CMakeFiles/opencv_nonfree.dir/src/sift.cpp.o.requires
modules/nonfree/CMakeFiles/opencv_nonfree.dir/requires: modules/nonfree/CMakeFiles/opencv_nonfree.dir/opencl_kernels.cpp.o.requires

.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/requires

modules/nonfree/CMakeFiles/opencv_nonfree.dir/clean:
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree && $(CMAKE_COMMAND) -P CMakeFiles/opencv_nonfree.dir/cmake_clean.cmake
.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/clean

modules/nonfree/CMakeFiles/opencv_nonfree.dir/depend: modules/nonfree/opencl_kernels.cpp
modules/nonfree/CMakeFiles/opencv_nonfree.dir/depend: modules/nonfree/opencl_kernels.hpp
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9 /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/nonfree /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/nonfree/CMakeFiles/opencv_nonfree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/nonfree/CMakeFiles/opencv_nonfree.dir/depend

