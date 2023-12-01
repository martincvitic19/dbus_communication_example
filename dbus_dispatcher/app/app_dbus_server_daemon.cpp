/**
* @file app_dbus_server_daemon.cpp
*
* @brief This app defines usage of methods a D-Bus server daemon that
         implement sending messages to a client.
*/

//--------------------------------- INCLUDES ----------------------------------
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <sdbus-c++/sdbus-c++.h>

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief Callback to notify the user that the listener has successfully received
 *        the method call message from the daemon.
 * @param call - the incoming method call message.
*/
void notifyMessageArrival(sdbus::MethodCall call);

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------
sdbus::IObject* g_nessage_dispatcher{};

//------------------------------ PUBLIC FUNCTIONS -----------------------------

//---------------------------- PRIVATE FUNCTIONS ------------------------------
int main(int argc, char *argv[])
{

   printf("Hello from DBusServerDaemon app.\n");

    // Establish D-Bus connection to the session bus and request a name on it.
    // This name will be used by D-Bus clients to find the service.
    const char* serviceName = "org.sdbuscpp.messageDispatcher";
    auto connection = sdbus::createSystemBusConnection(serviceName);

    // Create a corresponding D-Bus object.
    const char* objectPath = "/org/sdbuscpp/messageDispatcher";
    auto message_parse = sdbus::createObject(*connection, objectPath);

    g_nessage_dispatcher = message_parse.get();

    // Register D-Bus methods and signals on the message object.
    const char* interfaceName = "org.sdbuscpp.messageDispatcherInterface1";
    message_parse->registerMethod(interfaceName, "notifyMessageArrival",
                                             "s", "s", &notifyMessageArrival);
    // Export the object - this makes the object visible to the clients on the bus
    message_parse->finishRegistration();

    // Run the I/O event loop on the bus connection - this handles all incoming,
    //  outgoing and other requests.
    connection->enterEventLoop();

    return 0;
}
//---------------------------- INTERRUPT HANDLERS -----------------------------
void notifyMessageArrival(sdbus::MethodCall call)
{
    // This methods logic:
    std::cout << "The message was successfully received. " << std::endl;
}
