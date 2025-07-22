#include "UserController.h"
#include "drogon/drogon.h"
#include "../models/Users.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::drogon_controllers;

// Add definition of your processing function here
void UserController::getUsers(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto dbClient = app().getDbClient();
    Mapper<Users> mp(dbClient);

    mp.findAll(
        [callback](const std::vector<Users> &users) {
            Json::Value usersJson = Json::arrayValue;
            for (const auto &user : users)
                usersJson.append(user.toJson());

            auto resp = HttpResponse::newHttpJsonResponse(usersJson);
            callback(resp);
        },
        [callback](const DrogonDbException &e) {
            Json::Value error;
            error["error"] = e.base().what();
            auto resp = HttpResponse::newHttpJsonResponse(error);
            resp->setStatusCode(k500InternalServerError);
            callback(resp);
        }
        );

}
