add_library(stdhw STATIC list.c prompt.c stack.c)
target_include_directories(stdhw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
