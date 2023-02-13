cmake_minimum_required(VERSION 3.8)
project(feetech_scs)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

# ===============================================================
set(TARGET feetech_scs)
ament_auto_add_executable(${TARGET}_exec src/${TARGET}.cpp
  src/scs/SCS.cpp
  src/scs/SCSerial.cpp
  src/scs/SCSCL.cpp
)
# ===============================================================

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package()
