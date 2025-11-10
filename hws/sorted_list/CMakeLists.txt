add_executable(sorted_list main.c)
target_link_libraries(sorted_list PRIVATE stdhw)

add_executable(sorted_list_test test.c)
add_test(NAME sorted_list_test COMMAND sorted_list_test $<TARGET_FILE:sorted_list>)
