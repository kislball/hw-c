add_executable(bit_addition main.c addition.c)
target_link_libraries(bit_addition PRIVATE stdhw)

add_executable(bit_addition_test test.c addition.c)
target_link_libraries(bit_addition_test PRIVATE stdhw)

add_test(NAME bit_addition_test COMMAND bit_addition_test)
