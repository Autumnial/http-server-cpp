cmake_minimum_required(VERSION 3.28)
set (CMAKE_CXX_STANDARD 23)
project(http_server)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_compile_options(-g)
# add_library(${PROJECT_NAME} src/lib.cpp)
add_executable(${PROJECT_NAME} src/Router.cpp src/Request.cpp src/Response.cpp src/Enums.cpp src/Server.cpp src/main.cpp)

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
target_link_libraries(${PROJECT_NAME} ncurses)
