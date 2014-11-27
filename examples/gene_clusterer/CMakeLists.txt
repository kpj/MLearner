add_subdirectory(clusterer)
add_subdirectory(analyzer)

aux_source_directory(. SRC_LIST)
add_library(gene_handler ${SRC_LIST} ../../src/utils.cpp)

target_include_directories(gene_handler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
