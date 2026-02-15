add_executable(double_microscope main.c number.c)
target_link_libraries(double_microscope PRIVATE stdhw)

add_executable(double_microscope_test test.c number.c)
target_link_libraries(double_microscope_test PRIVATE stdhw)
add_test(NAME double_microscope_test COMMAND double_microscope_test)