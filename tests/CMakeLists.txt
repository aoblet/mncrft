file(GLOB_RECURSE TEST_FILES *.cpp)

foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(FILE ${TEST_FILE} NAME_WE)
    get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    set(OUTPUT ${DIR}_${FILE})
    add_executable(${OUTPUT} ${TEST_FILE} ${HEADER_FILES} ${SHADER_FILES} ${ASSET_FILES})
    target_link_libraries(${OUTPUT} ${ALL_LIBRARIES} )
endforeach()
