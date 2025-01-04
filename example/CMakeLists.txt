# Add the executable
add_executable(main_example main.cpp)

# Link the include directory
target_link_libraries(main_example PRIVATE library_include)
