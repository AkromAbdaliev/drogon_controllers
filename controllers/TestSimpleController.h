#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class TestSimpleController : public drogon::HttpSimpleController<TestSimpleController>
{
  public:
    void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override
      {
          if (req->method() == HttpMethod::Get)
          {
              Json::Value jsonArr;
              jsonArr["name"] = "John Doe";
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
                  response["message"] = "Invalid or missing JSON body.";
              }

              auto res = HttpResponse::newHttpJsonResponse(response);
              callback(res);
          }
          else
          {
              auto res = HttpResponse::newHttpResponse();
              res->setStatusCode(k405MethodNotAllowed);
              callback(res);
          }
      }
    PATH_LIST_BEGIN
    // list path definitions here;
    // PATH_ADD("/path", "filter1", "filter2", HttpMethod1, HttpMethod2...);
    PATH_ADD("/simple", Get, Post);
    PATH_LIST_END

};
