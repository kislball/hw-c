add_executable(stdhw_list_test list.c)
	target_link_libraries(stdhw_list_test PRIVATE stdhw)
add_test(NAME stdhw_list_test COMMAND stdhw_list_test)

add_executable(stdhw_queue_test queue.c)
	target_link_libraries(stdhw_queue_test PRIVATE stdhw)
add_test(NAME stdhw_queue_test COMMAND stdhw_queue_test)

add_executable(stdhw_strings_test strings.c)
	target_link_libraries(stdhw_strings_test PRIVATE stdhw)
add_test(NAME stdhw_strings_test COMMAND stdhw_strings_test)
