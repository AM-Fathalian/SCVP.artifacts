cmake_minimum_required(VERSION 3.10)

project(Cpp_playground)
add_executable(cpp_playground testing.cpp)



target_include_directories(cpp_playground
    PRIVATE $ENV{SYSTEMC_HOME}/include/
)

find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

target_link_libraries(cpp_playground
    PRIVATE ${SYSTEMC_LIBRARY}
)
