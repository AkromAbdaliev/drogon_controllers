#include "TestSimpleController.h"

void TestSimpleController::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    if (req->method() == HttpMethod::Get)
    {
        Json::Value jsonArr;
        jsonArr["name"] = "Jack Black";
        jsonArr["job"] = "Engineer";
        auto res = HttpResponse::newHttpJsonResponse(jsonArr);
        callback(res);
    }

    else if (req->method() == HttpMethod::Post)
    {
        auto json = req->getJsonObject();
        Json::Value response;

        if (json)
        {
            response["status"] = "success";
            response["received"] = *json;
        }
        else
        {
            response["status"] = "error";
            response["message"] = "Missing JSON body";
        }

        auto res = HttpResponse::newHttpJsonResponse(response);
        callback(res);
    }
}
