add_executable(stdhw_list_test list.c)
	target_link_libraries(stdhw_list_test PRIVATE stdhw)
add_test(NAME stdhw_list_test COMMAND stdhw_list_test)
