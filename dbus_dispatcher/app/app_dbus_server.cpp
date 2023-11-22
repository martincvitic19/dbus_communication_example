/**
* @file app_dbus_server.cpp
*
* @brief This app defines usage dbus_server's methods to implement handling 
         received messages from a client.
*/

//--------------------------------- INCLUDES ----------------------------------
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <sdbus-c++/sdbus-c++.h>
#include "message-dispatcher-server-glue.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief Callback to notify the user that the server has successfully received
 *        the method call message from the client.
 * @param call - the incoming method call message.
*/
void notifyMessageArrivalCb(sdbus::MethodCall call);

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------
sdbus::IObject* g_nessage_dispatcher{};

//------------------------------ PUBLIC FUNCTIONS -----------------------------

//---------------------------- PRIVATE FUNCTIONS ------------------------------
int main(int argc, char *argv[])
{
    //TODO: add error checking

    printf("Hello from DBusServer app.\n");

    // Establish D-Bus connection to the session bus and request a name on it.
    // This name will be used by D-Bus clients to find the service.
    const char* serviceName = "org.sdbuscpp.messageDispatcher";
    auto connection = sdbus::createSessionBusConnection(serviceName);

    // Create a corresponding D-Bus object.
    const char* objectPath = "/org/sdbuscpp/messageDispatcher";
    auto message = sdbus::createObject(*connection, objectPath);

    g_nessage_dispatcher = message.get();

    // Register D-Bus methods and signals on the message object.
    const char* interfaceName = "org.sdbuscpp.DBusDispatcherInterface";
    message->registerMethod(interfaceName, "messageDispatcherMethod",
                                             "ais", "s", &notifyMessageArrivalCb);
    message->registerSignal(interfaceName, "messageDispatcherSignal", "s");
    // Export the object - this makes the object visible to the clients on the bus
    message->finishRegistration();

    // Run the I/O event loop on the bus connection - this handles all incoming,
    //  outgoing and other requests.
    connection->enterEventLoop();

    return 0;
}
//---------------------------- INTERRUPT HANDLERS -----------------------------
void notifyMessageArrivalCb(sdbus::MethodCall call)
{
    //TODO: add error checking

    // This methods logic:
    std::cout << "The message was successfully received. " << std::endl;

    // Reply to the caller by creating a reply message for a given call.
    auto reply = call.createReply();
    // Since this is a void-returning method, just send an empty reply
    // back to the caller.
    reply.send();

    // Emit the 'message_received' signal.
    const char* interfaceName = "org.sdbuscpp.messagDispatcher";
    auto signal = g_nessage_dispatcher->createSignal(interfaceName,
                                         "notifyMessageArrivalCb");
    g_nessage_dispatcher->emitSignal(signal);
}