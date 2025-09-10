cmake_minimum_required(VERSION 3.14)
project(ImageViewerApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt (change 6 to 5 if you installed Qt5)

find_package(Qt6 COMPONENTS Widgets REQUIRED)


set(SOURCES
    main.cpp
    window.cpp
)

set(HEADERS
    window.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
