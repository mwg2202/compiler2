cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

project("compiler")

include(FetchContent)

set(files
    "src/CmdParser.cpp"
    "src/Preprocessor.cpp" 
    "src/Lexer.cpp"
)

add_executable(${PROJECT_NAME} 
    "src/main.cpp"
    ${files}
)
target_include_directories(${PROJECT_NAME} PUBLIC src)

add_executable(test 
    "tests/test.cpp"
    ${files})
target_include_directories(test PUBLIC src tests)
