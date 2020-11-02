cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

project("compiler")

set(files
    "src/CmdParser.cpp"
    "src/Preprocessor.cpp" 
    "src/Lexer.cpp")

# make main executable
add_executable(${PROJECT_NAME} 
    "src/main.cpp"
    ${files})
target_include_directories(${PROJECT_NAME} PUBLIC src)

# Make test
add_executable(test 
    "tests/test.cpp"
    ${files})
target_include_directories(test PUBLIC src tests)

add_custom_command(
    TARGET test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/tests/test.code
            ${CMAKE_CURRENT_BINARY_DIR}/test.code)

add_custom_command(
    TARGET test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/tests/test2.code
            ${CMAKE_CURRENT_BINARY_DIR}/test2.code)
