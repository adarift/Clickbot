cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Clickbot VERSION 0.1.0)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    libraries/minhook/include
    libraries/gd.h/include
    libraries/gd.h
    libraries/Mega-Hack-Extensions/include
)

add_subdirectory(libraries/minhook)
add_subdirectory(libraries/cocos-headers)
add_subdirectory(libraries/fmod-headers)

target_link_libraries(${PROJECT_NAME}
    minhook
    cocos2d
    fmod
    ${CMAKE_CURRENT_LIST_DIR}/libraries/Mega-Hack-Extensions/bin/hackpro.lib
)