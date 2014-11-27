aux_source_directory(. SRC_LIST)
add_library(mlearner ${SRC_LIST})

target_include_directories(mlearner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
