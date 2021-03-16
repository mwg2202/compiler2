cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER clang++)
project("compiler")


execute_process(
    COMMAND llvm-config --cxxflags
    OUTPUT_VARIABLE LLVM_FLAGS)
separate_arguments(LLVM_FLAGS)

# list of files to be compiled
set(files
    "src/CmdParser.cpp"
    "src/Preprocessor.cpp" 
    "src/Lexer.cpp"
    "src/Parser.cpp"
    "src/CodeGenerator.cpp")

# make main executable
add_executable(${PROJECT_NAME} 
    "src/main.cpp"
    ${files})
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_compile_options(${PROJECT_NAME} PUBLIC -g ${LLVM_FLAGS})

# make test
add_executable(test 
    "tests/test.cpp"
    ${files})
target_include_directories(test PUBLIC src tests)

# copy over test files
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
