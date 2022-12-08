project(Domotics-base-tests)

add_subdirectory(third-party/googletest)

add_executable(${PROJECT_NAME}
        mqtt_message_parser_test.cpp
        string_append_unsafe_test.cpp
        string_append_test.cpp
        array_test.cpp
        logger_test.cpp)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        gtest_main
        gtest
        gmock
        DomoticsBase)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})