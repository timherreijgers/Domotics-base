project(Domotics-base-tests)

add_subdirectory(third-party/googletest)

add_executable(${PROJECT_NAME}
        string_append_unsafe_test.cpp
        string_append_test.cpp
        array_test.cpp
        )

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        gtest_main
        gtest
        gmock)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})