file(GLOB_RECURSE TEST_FILES *.cpp)
file(GLOB_RECURSE jsonFiles *.json)

set(SRC_FILES_COPY ${SRC_FILES})

list(REMOVE_ITEM SRC_FILES_COPY ${CMAKE_SOURCE_DIR}/src/main.cpp)

foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(FILE ${TEST_FILE} NAME_WE)
    get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    set(OUTPUT ${DIR}_${FILE})
    add_executable(${OUTPUT} ${TEST_FILE} ${SRC_FILES_COPY} ${HEADER_FILES} ${SHADER_FILES} ${ASSET_FILES} ${jsonFiles})
    target_link_libraries(${OUTPUT} ${ALL_LIBRARIES} )
endforeach()
