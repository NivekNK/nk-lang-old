#============== Default Config ==================
cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_FILES_DIRECTORY "${CMAKE_HOME_DIRECTORY}/cmake")

include(${CMAKE_FILES_DIRECTORY}/compiler.cmake)
include(${CMAKE_FILES_DIRECTORY}/output.cmake)

project(nk-lang)

#============== Platform Specific ==================
add_compile_definitions(
    $<$<CONFIG:Debug>:NK_DEBUG>
    $<$<CONFIG:RelWithDebInfo>:NK_RELEASE_DEBUG_INFO>
    $<$<CONFIG:Release>:NK_RELEASE>
)

if (WIN32)
    add_compile_definitions(NK_PLATFORM_WINDOWS)
elseif (UNIX AND NOT APPLE)
    add_compile_definitions(NK_PLATFORM_LINUX)
endif()

#============== Project Config ==================
# add_subdirectory(vendor/tlsf)

add_executable(${PROJECT_NAME})

target_precompile_headers(${PROJECT_NAME} PUBLIC include/nkpch.h)

#================== Source Files ==================
set(SOURCES
    src/entry_point.cpp

    src/core/logging.cpp

    src/memory/allocator.cpp
    src/memory/malloc_allocator.cpp

    src/parser/report.cpp
    src/parser/lexer.cpp
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

#================== Include Files ==================
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    Threads::Threads
)

target_include_directories(${PROJECT_NAME}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>

    #Libraries
)
