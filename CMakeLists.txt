cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(hello_world VERSION 1.0.0)

# set(CMAKE_PREFIX_PATH ".")

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)

include_directories( 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/resources
)

file(GLOB SRCS
    "${PROJECT_SOURCE_DIR}/include/*"
    "${PROJECT_SOURCE_DIR}/src/*"
    "${PROJECT_SOURCE_DIR}/*"
)

add_executable(
    ${PROJECT_NAME}
    ${SRCS} 
)


target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_LIBRARIES})
# target_link_libraries(${PROJECT_NAME} glfw)

# add_definitions(-DDEBUG)

# How to build use cmake and minGW
# mkdir build
# cd build
# cmake -G "MinGW Makefiles" ..
# cmake --build .