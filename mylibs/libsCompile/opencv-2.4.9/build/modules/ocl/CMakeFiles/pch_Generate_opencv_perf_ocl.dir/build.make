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

# Utility rule file for pch_Generate_opencv_perf_ocl.

# Include the progress variables for this target.
include modules/ocl/CMakeFiles/pch_Generate_opencv_perf_ocl.dir/progress.make

modules/ocl/CMakeFiles/pch_Generate_opencv_perf_ocl: modules/ocl/perf_precomp.hpp.gch/opencv_perf_ocl_Release.gch


modules/ocl/perf_precomp.hpp.gch/opencv_perf_ocl_Release.gch: ../modules/ocl/perf/perf_precomp.hpp
modules/ocl/perf_precomp.hpp.gch/opencv_perf_ocl_Release.gch: modules/ocl/perf_precomp.hpp
modules/ocl/perf_precomp.hpp.gch/opencv_perf_ocl_Release.gch: lib/libopencv_perf_ocl_pch_dephelp.a
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating perf_precomp.hpp.gch/opencv_perf_ocl_Release.gch"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/ocl && /usr/bin/cmake -E make_directory /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/ocl/perf_precomp.hpp.gch
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/ocl && /usr/bin/c++ -O3 -DNDEBUG -DNDEBUG -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ocl/perf" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/features2d/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/highgui/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/imgproc/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/flann/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/core/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/highgui/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ts/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ocl/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/video/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/objdetect/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ml/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/calib3d/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/features2d/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/highgui/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/imgproc/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/flann/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/core/include" -isystem"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/ocl" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ocl/src" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ocl/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ocl/test" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/features2d/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/highgui/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/imgproc/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/flann/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/core/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/highgui/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ts/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ocl/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/video/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/objdetect/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ml/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/calib3d/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/features2d/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/highgui/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/imgproc/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/flann/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/core/include" -isystem"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/ocl" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ocl/src" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ocl/include" -isystem"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/3rdparty/include/opencl/1.2" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/video/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/objdetect/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ml/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/calib3d/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/features2d/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/highgui/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/imgproc/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/flann/include" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/core/include" -isystem"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/ocl" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ocl/src" -I"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ocl/include" -isystem"/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build" -fsigned-char -W -Wall -Werror=return-type -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wno-narrowing -Wno-delete-non-virtual-dtor -fdiagnostics-show-option -pthread -fomit-frame-pointer -ffunction-sections -x c++-header -o /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/ocl/perf_precomp.hpp.gch/opencv_perf_ocl_Release.gch /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/ocl/perf_precomp.hpp

modules/ocl/perf_precomp.hpp: ../modules/ocl/perf/perf_precomp.hpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating perf_precomp.hpp"
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/ocl && /usr/bin/cmake -E copy /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ocl/perf/perf_precomp.hpp /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/ocl/perf_precomp.hpp

pch_Generate_opencv_perf_ocl: modules/ocl/CMakeFiles/pch_Generate_opencv_perf_ocl
pch_Generate_opencv_perf_ocl: modules/ocl/perf_precomp.hpp.gch/opencv_perf_ocl_Release.gch
pch_Generate_opencv_perf_ocl: modules/ocl/perf_precomp.hpp
pch_Generate_opencv_perf_ocl: modules/ocl/CMakeFiles/pch_Generate_opencv_perf_ocl.dir/build.make

.PHONY : pch_Generate_opencv_perf_ocl

# Rule to build all files generated by this target.
modules/ocl/CMakeFiles/pch_Generate_opencv_perf_ocl.dir/build: pch_Generate_opencv_perf_ocl

.PHONY : modules/ocl/CMakeFiles/pch_Generate_opencv_perf_ocl.dir/build

modules/ocl/CMakeFiles/pch_Generate_opencv_perf_ocl.dir/clean:
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/ocl && $(CMAKE_COMMAND) -P CMakeFiles/pch_Generate_opencv_perf_ocl.dir/cmake_clean.cmake
.PHONY : modules/ocl/CMakeFiles/pch_Generate_opencv_perf_ocl.dir/clean

modules/ocl/CMakeFiles/pch_Generate_opencv_perf_ocl.dir/depend:
	cd /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9 /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/modules/ocl /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/ocl /home/firefly/Work/mylibs/libsCompile/opencv-2.4.9/build/modules/ocl/CMakeFiles/pch_Generate_opencv_perf_ocl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/ocl/CMakeFiles/pch_Generate_opencv_perf_ocl.dir/depend

