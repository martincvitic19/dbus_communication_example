/**
* @file app_dbus_server.cpp
*
* @brief This app defines usage dbus_server's methods to implement receiving
         messages from a client.
*/

//--------------------------------- INCLUDES ----------------------------------
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <sdbus-c++/sdbus-c++.h>

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------
sdbus::IObject* g_dbus_dispatcher{};

//------------------------------ PUBLIC FUNCTIONS -----------------------------

//---------------------------- PRIVATE FUNCTIONS ------------------------------
void message_received(sdbus::MethodCall call)
{
    std::cout << "The test message was received. " << std::endl;
}

int main(int argc, char *argv[])
{
    printf("Hello from DBusServer app.\n");

    // Create D-Bus connection to the session bus and request a name on it.
    const char* serviceName = "org.sdbuscpp.dbus_dispatcher";
    auto connection = sdbus::createSessionBusConnection(serviceName);

    // Create a corresponding D-Bus object.
    const char* objectPath = "/org/sdbuscpp/dbus_dispatcher";
    auto message = sdbus::createObject(*connection, objectPath);

    g_dbus_dispatcher = message.get();

    // Register D-Bus methods and signals on the message object, and export the object.
    const char* interfaceName = "org.sdbuscpp.DBusDispatcherInterface";
    message->registerMethod(interfaceName, "dbus_dispatcher_method", "ais", "s", &message_received);
    message->registerSignal(interfaceName, "dbus_dispatcher_signal", "s");
    message->finishRegistration();

    // Run the I/O event loop on the bus connection.
    connection->enterEventLoop();
}
//---------------------------- INTERRUPT HANDLERS -----------------------------