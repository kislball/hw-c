add_executable(avl_test avl.c test.c)
target_link_libraries(avl_test PRIVATE stdhw)

add_test(NAME avl_test COMMAND avl_test)

add_executable(linked_list_map_test listmap.c test.c)
target_link_libraries(linked_list_map_test PRIVATE stdhw)

add_test(NAME linked_list_map_test COMMAND linked_list_map_test)
