#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class TestSimpleController : public drogon::HttpSimpleController<TestSimpleController>
{
  public:
    void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override
    {
        Json::Value jsonArr;
        jsonArr["name"] = "John Doe";
        jsonArr["job"] = "Engineer";
        auto res = HttpResponse::newHttpJsonResponse(jsonArr);
        callback(res);
    }
    PATH_LIST_BEGIN
    // list path definitions here;
    // PATH_ADD("/path", "filter1", "filter2", HttpMethod1, HttpMethod2...);
    PATH_ADD("/simple", drogon::Get);
    PATH_LIST_END

};
