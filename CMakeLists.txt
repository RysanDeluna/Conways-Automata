cmake_minimum_required(VERSION 3.21)
project(LIFE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
## COMPILER FLAGS
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc" CACHE INTERNAL "" FORCE)
elseif(APPLE)
    message("hello apple")
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9 CACHE STRING "")
endif()

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set (SFML_INCS "${sfml_SOURCE_DIR}/include")

## MATHS LIBRARY
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" INTERFACE ${SFML_INCS})

## ENGINE
file(GLOB_RECURSE SOURCE_FILES engine/*.cpp engine/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/engine/")
target_link_libraries(lib_engine lib_maths)

## EXECUTABLES AND LINKS
add_executable(LIFE src/main.cpp
        src/classes/cell.cpp
        src/classes/cell.h
        src/classes/Matrix.cpp
        src/classes/Matrix.h
        src/scenes/scene_simulation.cpp
        src/scenes/scene_simulation.h)
target_link_libraries(LIFE PRIVATE sfml-graphics lib_engine)
target_compile_features(LIFE PRIVATE cxx_std_17)

## FOR WINDOWS
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET LIFE POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:LIFE> $<TARGET_FILE_DIR:LIFE> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS LIFE)