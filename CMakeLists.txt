cmake_minimum_required(VERSION 3.10)

# Name your project and set its version and languages.
project(Engine VERSION 0.1.0 LANGUAGES C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect source files
file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_SOURCE_DIR}/include/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

# Create the engine library.
add_library(EngineSource ${ENGINE_SOURCES})

# Include directories for the engine
target_include_directories(EngineSource PUBLIC "${CMAKE_SOURCE_DIR}/include")

# Add GLAD
add_library(glad STATIC "${CMAKE_SOURCE_DIR}/src/glad.c")
target_include_directories(glad PUBLIC "${CMAKE_SOURCE_DIR}/include")

# Link GLFW manually
set(GLFW_LIB "${CMAKE_SOURCE_DIR}/lib/libglfw3dll.a")

# Create the main engine application.
add_executable(EngineApp "${CMAKE_SOURCE_DIR}/main.cpp")
target_link_libraries(EngineApp PUBLIC EngineSource glad ${GLFW_LIB} opengl32)

# Testing Framework (Catch2)
add_library(catch INTERFACE)
target_include_directories(catch INTERFACE "${CMAKE_SOURCE_DIR}/testing/catch")

# Create test executables
add_executable(TestRegistry "${CMAKE_SOURCE_DIR}/testing/test_registry.cpp")
target_link_libraries(TestRegistry PUBLIC EngineSource catch)

add_executable(TestList "${CMAKE_SOURCE_DIR}/testing/test_dynamicList.cpp")
target_link_libraries(TestList PUBLIC EngineSource catch)

add_executable(TestSparse "${CMAKE_SOURCE_DIR}/testing/test_sparseSet.cpp")
target_link_libraries(TestSparse PUBLIC EngineSource catch)

add_executable(TestParse "${CMAKE_SOURCE_DIR}/testing/test_parse.cpp")
target_link_libraries(TestParse PUBLIC EngineSource catch)

add_executable(TestRessource "${CMAKE_SOURCE_DIR}/testing/test_ressources.cpp")
target_link_libraries(TestRessource PUBLIC EngineSource catch)

add_executable(TestGpu "${CMAKE_SOURCE_DIR}/testing/test_gpu.cpp")
target_link_libraries(TestGpu PUBLIC EngineSource glad ${GLFW_LIB} opengl32)

add_executable(TestEngine "${CMAKE_SOURCE_DIR}/testing/test_engine.cpp")
target_link_libraries(TestEngine PUBLIC EngineSource glad ${GLFW_LIB} opengl32)
