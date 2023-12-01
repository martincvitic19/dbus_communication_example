cmake_minimum_required(VERSION 3.12)
project(message_dispatcher_app)

# Find sdbus-c++
find_package(sdbus-c++ REQUIRED)

add_executable(DBusClientListener app_dbus_client_listener.cpp)
# Use the sdbus-c++ target in SDBusCpp namespace
target_link_libraries(DBusClientListener PRIVATE SDBusCpp::sdbus-c++)

add_executable(DBusServerDaemon app_dbus_server_daemon.cpp)
# Use the sdbus-c++ target in SDBusCpp namespace
target_link_libraries(DBusServerDaemon PRIVATE SDBusCpp::sdbus-c++)