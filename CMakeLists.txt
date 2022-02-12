cmake_minimum_required(VERSION 3.21)
project(BoostAwaitError)

set(CMAKE_CXX_STANDARD 20)
MESSAGE(STATUS "Compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

set(FETCHCONTENT_QUIET OFF)
set(CPM_USE_NAMED_CACHE_DIRECTORIES ON)
include(cmake/CPM.cmake)

CPMAddPackage(
        NAME Boost
        VERSION 1.78.0
        GITHUB_REPOSITORY "boostorg/boost"
        GIT_TAG "boost-1.78.0"
)

add_executable(BoostAwaitError main.cpp)
find_package (Threads REQUIRED)
target_link_libraries(BoostAwaitError PUBLIC Threads::Threads)
target_link_libraries(BoostAwaitError PUBLIC Boost::beast)
if(WIN32)
    target_link_libraries(BoostAwaitError PRIVATE wsock32 ws2_32)
endif()
