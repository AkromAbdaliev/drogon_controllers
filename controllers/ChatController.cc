#include "ChatController.h"

void ChatController::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    // write your application logic here
    wsConnPtr->send("Server also says: " + message);
}

void ChatController::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    wsConnPtr->send("Welcome to the chat server!");
}

void ChatController::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    LOG_INFO << "Connection closed";
}
