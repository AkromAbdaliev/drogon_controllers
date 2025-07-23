#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class UserController : public drogon::HttpController<UserController>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(UserController::get, "/{2}/{1}", Get); // path is /UserController/{arg2}/{arg1}
    // METHOD_ADD(UserController::your_method_name, "/{1}/{2}/list", Get); // path is /UserController/{arg1}/{arg2}/list
    // ADD_METHOD_TO(UserController::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

    ADD_METHOD_TO(UserController::getUsers, "/users", Get);
    ADD_METHOD_TO(UserController::createUser, "/users", Post);
    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;

    void getUsers(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
    void createUser(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
};
