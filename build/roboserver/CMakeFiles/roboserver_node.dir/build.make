# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /root/ros_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/ros_ws/build

# Include any dependencies generated for this target.
include roboserver/CMakeFiles/roboserver_node.dir/depend.make

# Include the progress variables for this target.
include roboserver/CMakeFiles/roboserver_node.dir/progress.make

# Include the compile flags for this target's objects.
include roboserver/CMakeFiles/roboserver_node.dir/flags.make

roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.o: roboserver/CMakeFiles/roboserver_node.dir/flags.make
roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.o: /root/ros_ws/src/roboserver/src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ros_ws/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.o"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/roboserver_node.dir/src/main.cpp.o -c /root/ros_ws/src/roboserver/src/main.cpp

roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/roboserver_node.dir/src/main.cpp.i"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ros_ws/src/roboserver/src/main.cpp > CMakeFiles/roboserver_node.dir/src/main.cpp.i

roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/roboserver_node.dir/src/main.cpp.s"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ros_ws/src/roboserver/src/main.cpp -o CMakeFiles/roboserver_node.dir/src/main.cpp.s

roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.o.requires:
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.o.requires

roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.o.provides: roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.o.requires
	$(MAKE) -f roboserver/CMakeFiles/roboserver_node.dir/build.make roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.o.provides.build
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.o.provides

roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.o.provides.build: roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.o

roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o: roboserver/CMakeFiles/roboserver_node.dir/flags.make
roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o: /root/ros_ws/src/roboserver/src/usb2serial.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ros_ws/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o -c /root/ros_ws/src/roboserver/src/usb2serial.cpp

roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.i"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ros_ws/src/roboserver/src/usb2serial.cpp > CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.i

roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.s"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ros_ws/src/roboserver/src/usb2serial.cpp -o CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.s

roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o.requires:
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o.requires

roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o.provides: roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o.requires
	$(MAKE) -f roboserver/CMakeFiles/roboserver_node.dir/build.make roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o.provides.build
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o.provides

roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o.provides.build: roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o

roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.o: roboserver/CMakeFiles/roboserver_node.dir/flags.make
roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.o: /root/ros_ws/src/roboserver/src/robolink.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ros_ws/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.o"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/roboserver_node.dir/src/robolink.cpp.o -c /root/ros_ws/src/roboserver/src/robolink.cpp

roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/roboserver_node.dir/src/robolink.cpp.i"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ros_ws/src/roboserver/src/robolink.cpp > CMakeFiles/roboserver_node.dir/src/robolink.cpp.i

roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/roboserver_node.dir/src/robolink.cpp.s"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ros_ws/src/roboserver/src/robolink.cpp -o CMakeFiles/roboserver_node.dir/src/robolink.cpp.s

roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.o.requires:
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.o.requires

roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.o.provides: roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.o.requires
	$(MAKE) -f roboserver/CMakeFiles/roboserver_node.dir/build.make roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.o.provides.build
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.o.provides

roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.o.provides.build: roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.o

roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.o: roboserver/CMakeFiles/roboserver_node.dir/flags.make
roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.o: /root/ros_ws/src/roboserver/src/robot.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ros_ws/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.o"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/roboserver_node.dir/src/robot.cpp.o -c /root/ros_ws/src/roboserver/src/robot.cpp

roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/roboserver_node.dir/src/robot.cpp.i"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ros_ws/src/roboserver/src/robot.cpp > CMakeFiles/roboserver_node.dir/src/robot.cpp.i

roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/roboserver_node.dir/src/robot.cpp.s"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ros_ws/src/roboserver/src/robot.cpp -o CMakeFiles/roboserver_node.dir/src/robot.cpp.s

roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.o.requires:
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.o.requires

roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.o.provides: roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.o.requires
	$(MAKE) -f roboserver/CMakeFiles/roboserver_node.dir/build.make roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.o.provides.build
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.o.provides

roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.o.provides.build: roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.o

roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.o: roboserver/CMakeFiles/roboserver_node.dir/flags.make
roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.o: /root/ros_ws/src/roboserver/src/imu.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ros_ws/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.o"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/roboserver_node.dir/src/imu.cpp.o -c /root/ros_ws/src/roboserver/src/imu.cpp

roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/roboserver_node.dir/src/imu.cpp.i"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ros_ws/src/roboserver/src/imu.cpp > CMakeFiles/roboserver_node.dir/src/imu.cpp.i

roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/roboserver_node.dir/src/imu.cpp.s"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ros_ws/src/roboserver/src/imu.cpp -o CMakeFiles/roboserver_node.dir/src/imu.cpp.s

roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.o.requires:
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.o.requires

roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.o.provides: roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.o.requires
	$(MAKE) -f roboserver/CMakeFiles/roboserver_node.dir/build.make roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.o.provides.build
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.o.provides

roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.o.provides.build: roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.o

roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.o: roboserver/CMakeFiles/roboserver_node.dir/flags.make
roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.o: /root/ros_ws/src/roboserver/src/motion.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ros_ws/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.o"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/roboserver_node.dir/src/motion.cpp.o -c /root/ros_ws/src/roboserver/src/motion.cpp

roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/roboserver_node.dir/src/motion.cpp.i"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ros_ws/src/roboserver/src/motion.cpp > CMakeFiles/roboserver_node.dir/src/motion.cpp.i

roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/roboserver_node.dir/src/motion.cpp.s"
	cd /root/ros_ws/build/roboserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ros_ws/src/roboserver/src/motion.cpp -o CMakeFiles/roboserver_node.dir/src/motion.cpp.s

roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.o.requires:
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.o.requires

roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.o.provides: roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.o.requires
	$(MAKE) -f roboserver/CMakeFiles/roboserver_node.dir/build.make roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.o.provides.build
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.o.provides

roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.o.provides.build: roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.o

# Object files for target roboserver_node
roboserver_node_OBJECTS = \
"CMakeFiles/roboserver_node.dir/src/main.cpp.o" \
"CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o" \
"CMakeFiles/roboserver_node.dir/src/robolink.cpp.o" \
"CMakeFiles/roboserver_node.dir/src/robot.cpp.o" \
"CMakeFiles/roboserver_node.dir/src/imu.cpp.o" \
"CMakeFiles/roboserver_node.dir/src/motion.cpp.o"

# External object files for target roboserver_node
roboserver_node_EXTERNAL_OBJECTS =

/root/ros_ws/devel/lib/roboserver/roboserver_node: roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.o
/root/ros_ws/devel/lib/roboserver/roboserver_node: roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o
/root/ros_ws/devel/lib/roboserver/roboserver_node: roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.o
/root/ros_ws/devel/lib/roboserver/roboserver_node: roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.o
/root/ros_ws/devel/lib/roboserver/roboserver_node: roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.o
/root/ros_ws/devel/lib/roboserver/roboserver_node: roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.o
/root/ros_ws/devel/lib/roboserver/roboserver_node: roboserver/CMakeFiles/roboserver_node.dir/build.make
/root/ros_ws/devel/lib/roboserver/roboserver_node: /opt/ros/jade/lib/libroscpp.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /usr/lib/arm-linux-gnueabihf/libboost_signals.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /usr/lib/arm-linux-gnueabihf/libboost_filesystem.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /opt/ros/jade/lib/librosconsole.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /opt/ros/jade/lib/librosconsole_log4cxx.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /opt/ros/jade/lib/librosconsole_backend_interface.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /usr/lib/liblog4cxx.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /usr/lib/arm-linux-gnueabihf/libboost_regex.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /opt/ros/jade/lib/libroscpp_serialization.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /opt/ros/jade/lib/librostime.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /opt/ros/jade/lib/libxmlrpcpp.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /opt/ros/jade/lib/libcpp_common.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /usr/lib/arm-linux-gnueabihf/libboost_system.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /usr/lib/arm-linux-gnueabihf/libboost_thread.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /usr/lib/arm-linux-gnueabihf/libpthread.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so
/root/ros_ws/devel/lib/roboserver/roboserver_node: roboserver/CMakeFiles/roboserver_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /root/ros_ws/devel/lib/roboserver/roboserver_node"
	cd /root/ros_ws/build/roboserver && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/roboserver_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
roboserver/CMakeFiles/roboserver_node.dir/build: /root/ros_ws/devel/lib/roboserver/roboserver_node
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/build

roboserver/CMakeFiles/roboserver_node.dir/requires: roboserver/CMakeFiles/roboserver_node.dir/src/main.cpp.o.requires
roboserver/CMakeFiles/roboserver_node.dir/requires: roboserver/CMakeFiles/roboserver_node.dir/src/usb2serial.cpp.o.requires
roboserver/CMakeFiles/roboserver_node.dir/requires: roboserver/CMakeFiles/roboserver_node.dir/src/robolink.cpp.o.requires
roboserver/CMakeFiles/roboserver_node.dir/requires: roboserver/CMakeFiles/roboserver_node.dir/src/robot.cpp.o.requires
roboserver/CMakeFiles/roboserver_node.dir/requires: roboserver/CMakeFiles/roboserver_node.dir/src/imu.cpp.o.requires
roboserver/CMakeFiles/roboserver_node.dir/requires: roboserver/CMakeFiles/roboserver_node.dir/src/motion.cpp.o.requires
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/requires

roboserver/CMakeFiles/roboserver_node.dir/clean:
	cd /root/ros_ws/build/roboserver && $(CMAKE_COMMAND) -P CMakeFiles/roboserver_node.dir/cmake_clean.cmake
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/clean

roboserver/CMakeFiles/roboserver_node.dir/depend:
	cd /root/ros_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ros_ws/src /root/ros_ws/src/roboserver /root/ros_ws/build /root/ros_ws/build/roboserver /root/ros_ws/build/roboserver/CMakeFiles/roboserver_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : roboserver/CMakeFiles/roboserver_node.dir/depend

