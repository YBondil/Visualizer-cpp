cmake_minimum_required(VERSION 3.16)
project(visualizer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# 1. Automatically find all .cpp files in the src directory
file(GLOB SOURCES "src/*.cpp")

# 2. Automatically find all .hpp and .h files in the lib/include directory
file(GLOB HEADERS "lib/include/*.hpp" "lib/include/*.h")

add_subdirectory(lib/SDL EXCLUDE_FROM_ALL)

# 3. Create the executable using the discovered source and header files
add_executable(visualizer ${SOURCES} ${HEADERS})

# 4. Ensure the compiler knows where to look for the headers during compilation
target_include_directories(visualizer PRIVATE lib/include)

target_link_libraries(visualizer PRIVATE SDL3::SDL3)
