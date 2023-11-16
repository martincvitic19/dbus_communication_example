cmake_minimum_required(VERSION 3.12)
project(dbus_dispatcher)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Find sdbus-c++
find_package(sdbus-c++ REQUIRED)

add_executable(DBusClient app/app_dbus_client.cpp)
# Use the sdbus-c++ target in SDBusCpp namespace
target_link_libraries(DBusClient PRIVATE SDBusCpp::sdbus-c++)

add_executable(DBusServer app/app_dbus_server.cpp)
# Use the sdbus-c++ target in SDBusCpp namespace
target_link_libraries(DBusServer PRIVATE SDBusCpp::sdbus-c++)