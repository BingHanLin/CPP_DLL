cmake_minimum_required(VERSION 3.18.0)

project(client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/client/main.cpp
)

if(MSVC)
    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
        set_target_properties( ${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_BINARY_DIR}/bin )
        set_target_properties( ${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_BINARY_DIR}/lib )
        set_target_properties( ${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_BINARY_DIR}/archive )
    endforeach()
endif()

target_include_directories(${PROJECT_NAME} 
  PUBLIC
    ${PROJECT_SOURCE_DIR}/mathLibarary
)

target_link_libraries(${PROJECT_NAME} 
  PUBLIC
    ${PROJECT_SOURCE_DIR}/mathLibarary/build/archive/mathLibrary.lib
)


target_link_libraries(${PROJECT_NAME} PRIVATE delayimp) # maybe need for Ninja: https://discourse.cmake.org/t/delayload-inconsistency-between-visual-studio-and-ninja-generators/2719
target_link_options(${PROJECT_NAME} PRIVATE "/DELAYLOAD:mathLibrary.dll")

install(
  FILES 
    ${PROJECT_SOURCE_DIR}/mathLibarary/build/bin/mathLibrary.dll
  DESTINATION 
    ${PROJECT_BINARY_DIR}/bin
)


