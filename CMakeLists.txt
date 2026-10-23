
cmake_minimum_required(VERSION 3.20)

project(cpp_lib LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

find_package(PkgConfig REQUIRED)
pkg_check_modules(UUID REQUIRED IMPORTED_TARGET uuid)

find_package(GTest REQUIRED)


######################################################################
# PROJECT LIBRARY
######################################################################
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# -------------------------------------------------------
# Exclude the executable entry point from the library.
# -------------------------------------------------------
list(FILTER PROJECT_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

add_library(cpp_lib STATIC ${PROJECT_SOURCES})

target_include_directories(cpp_lib PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
)

target_link_libraries(cpp_lib PUBLIC
    PkgConfig::UUID
)


######################################################################
# APPLICATION (For BINARY use cases ...)
######################################################################
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    add_executable(cpp_lib_cli src/main.cpp)
    target_link_libraries(cpp_lib_cli PRIVATE cpp_lib)
endif()


######################################################################
# TESTS
######################################################################
if(BUILD_TESTING)
    file(GLOB_RECURSE TEST_SRC_FILES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
    )

    if(TEST_SRC_FILES)
        add_executable(cpp_lib_test ${TEST_SRC_FILES})

        target_include_directories(cpp_lib_test PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/tests"
        )

        target_link_libraries(cpp_lib_test PRIVATE
            cpp_lib
            GTest::gtest_main
        )

        include(GoogleTest)
        gtest_discover_tests(cpp_lib_test)
    endif()
endif()
