add_executable(binary_comparison compare.c test.c)
target_link_libraries(binary_comparison PRIVATE stdhw)

add_test(NAME binary_comparison COMMAND binary_comparison)
