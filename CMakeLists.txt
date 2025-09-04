cmake_minimum_required(VERSION 3.10)
project(AnnotationParser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------
# GitHub Coverage Support
# ------------------------------
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
# ------------------------------

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

# Enable testing
enable_testing()

# Define source files
set(PARSER_SOURCES
    ASTVisitor.cpp
    ComponentParser.cpp
    Reference.cpp
    Component.cpp
    JsonGenerator.cpp
    PropertyParser.cpp
    ReferenceParser.cpp
    ErrorCollector.cpp
    ErrorReporter.cpp
    SyntaxChecker.cpp
    ManifestMerger.cpp
)

# Create a library from the parser sources
add_library(parser_lib ${PARSER_SOURCES})

target_include_directories(parser_lib
    PUBLIC 
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# --- Platform-dependent linking ---
if (WIN32)
    set(CLANG_LIBS
        clangTooling
        clangFrontend
        clangDriver
        clangParse
        clangSerialization
        clangSema
        clangEdit
        clangAnalysis
        clangAST
        clangLex
        clangBasic
    )
    llvm_map_components_to_libnames(LLVM_LIBS
        support
        core
        option
        binaryformat
        demangle
    )
else()
    set(CLANG_LIBS clang-cpp)
    set(LLVM_LIBS LLVM)
endif()

target_link_libraries(parser_lib
    PUBLIC
    ${CLANG_LIBS}
    ${LLVM_LIBS}
)

target_compile_definitions(parser_lib
    PUBLIC
    ${LLVM_DEFINITIONS}
)

# ------------------------------
# Coverage flags applied after target creation
# ------------------------------
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Apply coverage to library
    target_compile_options(parser_lib PRIVATE --coverage -O0 -g)
    target_link_options(parser_lib PRIVATE --coverage)
endif()
# ------------------------------

# Create the executable
add_executable(parser main.cpp)
target_link_libraries(parser PRIVATE parser_lib)

# ------------------------------
# Apply coverage to executable as well
# ------------------------------
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(parser PRIVATE --coverage -O0 -g)
    target_link_options(parser PRIVATE --coverage)
endif()
# ------------------------------

# Add tests subdirectory
add_subdirectory(tests)
