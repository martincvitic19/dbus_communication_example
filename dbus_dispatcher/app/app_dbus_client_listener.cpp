/**
* @file app_dbus_client_listener.cpp
*
* @brief This app defines usage dbus_client's methods to implement sending
         messages to a server.
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

//------------------------------ PUBLIC FUNCTIONS -----------------------------

//---------------------------- PRIVATE FUNCTIONS ------------------------------
int main(void)
{
   printf("Hello from DBusClientListener app.\n");

    // Create a proxy object - view of the object from the client side
    const char* destinationName = "org.sdbuscpp.messageDispatcher";
    const char* objectPath = "/org/sdbuscpp/messageDispatcher";
    auto testMessageProxy = sdbus::createProxy(destinationName, objectPath);

    const char* interfaceName = "org.sdbuscpp.messageDispatcherInterface1";
    testMessageProxy->finishRegistration();

     std::string testMessage = "This is a test message.";

    // Invoke sending a test message on given interface of the object
    {
        auto method = testMessageProxy->createMethodCall(interfaceName, "notifyMessageArrival");
        method << testMessage;
        auto reply = testMessageProxy->callMethod(method);
        std::string result;
        reply >> result;
    }

    sleep(1);

    return 0;
}
//---------------------------- INTERRUPT HANDLERS -----------------------------
