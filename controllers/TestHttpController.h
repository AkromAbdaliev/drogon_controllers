#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class TestHttpController : public drogon::HttpController<TestHttpController>
{
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(TestHttpController::userInfo, "/normal", Get);
    METHOD_LIST_END

        void userInfo(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback);
};
