cmake_minimum_required(VERSION 3.5)

project(Server VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS LinguistTools)
set(TS_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/translations/qtChat_ru.ts)
file(GLOB_RECURSE TS_SOURCES "*.cpp" "*.h" ".ui")
add_custom_target(translations)
#по сути, при билде для каждого .ts файла вызывается
#утилита lupdate.exe
foreach(_ts_file ${TS_FILES})
    get_filename_component(_ts_name ${_ts_file} NAME_WE)
    execute_process(
        COMMAND lupdate -no-obsolete ${CMAKE_CURRENT_SOURCE_DIR} -ts ${_ts_file}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
add_custom_target(translate_${_ts_name} DEPENDS ${_ts_file})
add_dependencies(translations translate_${_ts_name})
endforeach()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/translations/qtChat_ru.qm ${CMAKE_BINARY_DIR}/translations/qtChat_ru.qm COPYONLY)

#подключаем файлы трансляции(переводов)
qt_add_translation(QM_FILES ${TS_FILES})

set(PROJECT_SOURCES
    MainWindow/main.cpp
    MainWindow/mainwindow.cpp
    MainWindow/mainwindow.h
    MainWindow/mainwindow.ui
)

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resources.rc")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Server
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Strings/strings.h Strings/strings.cpp
        DB/db.h DB/db.cpp
        ../Misc/SHA1.cpp ../Misc/SHA1.h
        ../Misc/misc.cpp ../Misc/misc.h
        resources.rc
        ${APP_ICON_RESOURCE_WINDOWS}
        resources.qrc

    )




# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Server APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Server SHARED
            ${PROJECT_SOURCES}
        )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
else()
    add_executable(Server
        ${PROJECT_SOURCES}
    )
endif()
endif()

target_link_libraries(Server PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Server)
endif()
set_target_properties(Server PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Server
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Server)
endif()

# префикс режима сборки
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(BUILD_PREFIX "debug")
endif()
if(CMAKE_BUILD_TYPE MATCHES "Release")
    set(BUILD_PREFIX "release")
endif()

###### Add library ChatStructs ######
file(GLOB_RECURSE CHAT_STRUCTS_LIBS "../ChatStructs/lib/${BUILD_PREFIX}/*.*")
# Copy the ChatStructs library files to the project build folder.
foreach(ChatStructs_lib_file ${CHAT_STRUCTS_LIBS})
    get_filename_component(header_name ${ChatStructs_lib_file} NAME)
    configure_file(${ChatStructs_lib_file} ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()

include_directories(../ChatStructs/include)
link_directories(../ChatStructs/lib/${BUILD_PREFIX})
target_link_libraries(Server PRIVATE ChatStructs)
#####################################

###### Misc ######
include_directories(../Misc)
##################

######## server.ini ########
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/server.ini ${CMAKE_BINARY_DIR} COPYONLY)
############################

