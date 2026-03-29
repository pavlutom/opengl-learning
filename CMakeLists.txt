cmake_minimum_required(VERSION 3.15)
project(LearnOpenGL)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find our dependencies
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(gltest src/main.cpp)

# Link everything together
target_link_libraries(gltest PRIVATE glfw glad::glad glm::glm)

# Copy resources
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/src/resources" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
