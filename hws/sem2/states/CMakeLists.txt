add_executable(states main.c alg.c data.c queue.c)

add_test(NAME states_test1
    COMMAND bash -c "diff <(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/states ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt) ${CMAKE_CURRENT_SOURCE_DIR}/test1_expected.txt"
)

add_test(NAME states_test2
    COMMAND bash -c "diff <(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/states ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt) ${CMAKE_CURRENT_SOURCE_DIR}/test2_expected.txt"
)

add_test(NAME states_test3
    COMMAND bash -c "diff <(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/states ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt) ${CMAKE_CURRENT_SOURCE_DIR}/test3_expected.txt"
)

add_test(NAME states_test4
    COMMAND bash -c "diff <(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/states ${CMAKE_CURRENT_SOURCE_DIR}/test4.txt) ${CMAKE_CURRENT_SOURCE_DIR}/test4_expected.txt"
)
