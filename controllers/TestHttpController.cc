#include "TestHttpController.h"

void TestHttpController::userInfo(const HttpRequestPtr &req,
                               std::function<void(const HttpResponsePtr &)> &&callback)
{
    Json::Value jsonArr;
    jsonArr["fullname"] = "Mike Tyson";
    jsonArr["age"]  = 65;
    jsonArr["citizenship"] = "USA";
    auto res = HttpResponse::newHttpJsonResponse(jsonArr);
    callback(res);
}
