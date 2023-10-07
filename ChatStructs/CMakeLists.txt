cmake_minimum_required(VERSION 3.14)

project(ChatStructs LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

#########################
set(LIB_NAME ChatStructs)
#########################

add_library(ChatStructs SHARED
    ChatStructs_global.h
    user.h user.cpp
    message.h message.cpp
    ../Misc/SHA1.cpp ../Misc/SHA1.h
    ../Misc/flags.h
    ../Misc/misc.h ../Misc/misc.cpp
)

target_link_libraries(ChatStructs PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(ChatStructs PRIVATE CHATSTRUCTS_LIBRARY)

##############################################################################################
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(BUILD_PREFIX "debug")
endif()
if(CMAKE_BUILD_TYPE MATCHES "Release")
    set(BUILD_PREFIX "release")
endif()

# создаем директории
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/${BUILD_PREFIX})
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Указываем папку для выходных файлов библиотеки
set_target_properties(${LIB_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/${BUILD_PREFIX}
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/${BUILD_PREFIX}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/${BUILD_PREFIX}
)

# Задаем маску для заголовочных файлов во всех вложенных папках
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Копируем заголовочные файлы в папку include
foreach(header_file ${HEADER_FILES})
    get_filename_component(header_name ${header_file} NAME)
    configure_file(${header_file} ${CMAKE_CURRENT_SOURCE_DIR}/include/${header_name} COPYONLY)
endforeach()
##############################################################################################

###### Misc ######
include_directories(../Misc)
##################
