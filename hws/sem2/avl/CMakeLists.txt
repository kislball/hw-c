add_executable(avl_test avl.c test.c)
target_link_libraries(avl_test PRIVATE stdhw)

add_test(NAME avl_test COMMAND avl_test)

add_executable(linked_list_map_test listmap.c test.c)
target_link_libraries(linked_list_map_test PRIVATE stdhw)

add_test(NAME linked_list_map_test COMMAND linked_list_map_test)

add_executable(aerosoft_avl avl.c main.c file.c)
target_link_libraries(aerosoft_avl PRIVATE stdhw)

add_executable(aerosoft_listmap listmap.c main.c file.c)
target_link_libraries(aerosoft_listmap PRIVATE stdhw)

add_executable(bench1_avl avl.c bench1.c file.c)
target_link_libraries(bench1_avl PRIVATE stdhw)

add_executable(bench1_listmap listmap.c bench1.c file.c)
target_link_libraries(bench1_listmap PRIVATE stdhw)

add_executable(bench2_avl avl.c bench2.c file.c)
target_link_libraries(bench2_avl PRIVATE stdhw)

add_executable(bench2_listmap listmap.c bench2.c file.c)
target_link_libraries(bench2_listmap PRIVATE stdhw)
