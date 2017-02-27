cmake_minimum_required(VERSION 3.1)

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)

if(COMMAND cmake_policy)
cmake_policy(SET CMP0003 NEW) # Required by CMake 2.7+
endif(COMMAND cmake_policy)

# Basic information about project
project(GSoC)

set(CMAKE_AUTOMOC ON)


set(SOURCE_FILES
    main.cpp
)

set(GUI_SOURCE_FILES
	CMainWindow.cpp
	CGraphicsScene.cpp
	CGraphicsView.cpp
)

find_package(Qt5Widgets REQUIRED)

FIND_PACKAGE( MRPT REQUIRED base maps slam)


set(GUI_APP_NAME ${PROJECT_NAME})

add_executable(${GUI_APP_NAME}
	 ${SOURCE_FILES}
	 ${GUI_SOURCE_FILES}
    ${UIS_HDRS}
)

qt5_use_modules(${GUI_APP_NAME} Widgets)

TARGET_LINK_LIBRARIES(${GUI_APP_NAME} ${MRPT_LIBS})

IF(CMAKE_COMPILER_IS_GNUCXX AND NOT CMAKE_BUILD_TYPE MATCHES "Debug")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
ENDIF(CMAKE_COMPILER_IS_GNUCXX AND NOT CMAKE_BUILD_TYPE MATCHES "Debug")
