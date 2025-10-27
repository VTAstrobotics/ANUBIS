cmake_minimum_required(VERSION 3.8)
project(motor_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(motor_messages REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(phoenix6 REQUIRED)
find_package(sparkcan REQUIRED)
add_definitions(-DUNIT_LIB_DISABLE_FMT -DUNIT_LIB_ENABLE_IOSTREAM)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)




add_executable(kraken_control_node src/kraken_controller_executable.cpp src/kraken_controller.cpp)

ament_target_dependencies(kraken_control_node rclcpp motor_messages rclcpp_components sparkcan)
target_include_directories(kraken_control_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(kraken_control_node phoenix6)

install(TARGETS
  kraken_control_node
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch files
install(
  DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}/
)


ament_export_include_directories(include)



if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
