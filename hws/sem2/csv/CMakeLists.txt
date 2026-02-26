add_executable(csv main.c display.c csv.c common.c)
target_link_libraries(csv PRIVATE stdhw)

add_executable(test_csv test.c display.c csv.c common.c)
target_link_libraries(test_csv PRIVATE stdhw)
add_test(NAME test_csv COMMAND test_csv)
