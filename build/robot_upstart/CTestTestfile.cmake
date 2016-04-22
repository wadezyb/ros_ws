# CMake generated Testfile for 
# Source directory: /root/ros_ws/src/robot_upstart
# Build directory: /root/ros_ws/build/robot_upstart
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(_ctest_robot_upstart_roslint_package "/root/ros_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/jade/share/catkin/cmake/test/run_tests.py" "/root/ros_ws/build/test_results/robot_upstart/roslint-robot_upstart.xml" "--working-dir" "/root/ros_ws/build/robot_upstart" "--return-code" "/opt/ros/jade/share/roslint/cmake/../../../lib/roslint/test_wrapper /root/ros_ws/build/test_results/robot_upstart/roslint-robot_upstart.xml make roslint_robot_upstart")
ADD_TEST(_ctest_robot_upstart_nosetests_test "/root/ros_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/jade/share/catkin/cmake/test/run_tests.py" "/root/ros_ws/build/test_results/robot_upstart/nosetests-test.xml" "--return-code" "/usr/bin/cmake -E make_directory /root/ros_ws/build/test_results/robot_upstart" "/usr/bin/nosetests-2.7 -P --process-timeout=60 --where=/root/ros_ws/src/robot_upstart/test --with-xunit --xunit-file=/root/ros_ws/build/test_results/robot_upstart/nosetests-test.xml")
