# Header-only libraries don't need to compile anything
# Just specify the directory as an include path
add_library(library_include INTERFACE)
target_include_directories(library_include INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
