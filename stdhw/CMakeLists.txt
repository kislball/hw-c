add_library(stdhw STATIC prompt.c)

target_include_directories(stdhw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
