add_executable(shunting_yard main.c yard.c)
    target_link_libraries(shunting_yard PRIVATE stdhw)

add_executable(shunting_yard_test yard.c test.c)
    target_link_libraries(shunting_yard_test PRIVATE stdhw)
add_test(NAME shunting_yard_test COMMAND shunting_yard_test)
