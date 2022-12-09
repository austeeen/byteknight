cmake_minimum_required(VERSION 3.16.3)

project(${APP_NAME})

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "-O -g")
set(CMAKE_CXX_FLAGS "-Wall -ggdb3")
set(CMAKE_BUILD_TYPE Debug)

set(SFML_DIR "C:/msys64/home/pants/SFML/lib/cmake/SFML")


find_package(SFML 3.0.0
  COMPONENTS System Window Graphics REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}
    C:/msys64/home/pants/SFML/include
)

file(GLOB
    SOURCES ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/*/*.cpp)

add_executable(
    ${APP_NAME}.app
    ${CMAKE_PROJECT_NAME}/main.cpp
    ${SOURCES}
)
target_include_directories(
    ${APP_NAME}.app
    PRIVATE
        ${CMAKE_BINARY_DIR}
)
target_link_libraries(
    ${APP_NAME}.app
    sfml-graphics sfml-window sfml-system
)
