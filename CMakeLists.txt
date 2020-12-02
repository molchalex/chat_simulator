cmake_minimum_required(VERSION 3.16.0)
project(ChatSimulator)
set(PROJECT_NAME ChatSimulator)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set( CMAKE_INCLUDE_CURRENT_DIR ON )

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

file(GLOB_RECURSE HEADERS_FILES source/*.h source/ServerSide/*.h source/ClientSide/*.h)
file(GLOB_RECURSE SOURCE_FILES source/*.cpp source/ServerSide/*.cpp source/ClientSide/*.cpp)
file(GLOB_RECURSE UI source/*.ui source/ClientSide/*.ui source/ServerSide/*.ui)

qt5_wrap_ui(UI_HEADERS ${UI})

add_executable(${PROJECT_NAME} ${HEADERS_FILES} ${SOURCE_FILES} ${UI_HEADERS})

# source_group("Server" FILES ${SERVER_SOURCE_FILES})
# source_group("Client" FILES ${CLIENT_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Network)
