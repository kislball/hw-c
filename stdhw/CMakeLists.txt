add_library(stdhw STATIC prompt.c stack.c)
target_include_directories(stdhw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
