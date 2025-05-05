cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 11)

project(main CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MANIFEST:NO")
endif()

find_library(
    WRITEWATCH_LIB
    NAMES WriteWatchDLL
    PATHS "C:/projects/MingW64-checked-pointer-vector/src"
    NO_DEFAULT_PATH
)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.hpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} ${WRITEWATCH_LIB} ${CMAKE_SOURCE_DIR}/src/WriteWatchDLL.a)
