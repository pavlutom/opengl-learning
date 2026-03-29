cmake_minimum_required(VERSION 3.15)
project(LearnOpenGL)

# Find our dependencies
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(gltest src/main.cpp)

# Link everything together
target_link_libraries(gltest PRIVATE glfw glad::glad glm::glm)
