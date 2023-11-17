cmake_minimum_required(VERSION 3.12)
project(dbus_dispatcher_app)

# Find sdbus-c++
find_package(sdbus-c++ REQUIRED)

add_executable(DBusClient app_dbus_client.cpp)
# Use the sdbus-c++ target in SDBusCpp namespace
target_link_libraries(DBusClient PRIVATE SDBusCpp::sdbus-c++)

add_executable(DBusServer app_dbus_server.cpp)
# Use the sdbus-c++ target in SDBusCpp namespace
target_link_libraries(DBusServer PRIVATE SDBusCpp::sdbus-c++)