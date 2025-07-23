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
        });
}

void UserController::createUser(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    if (!json)
    {
        auto resp = HttpResponse::newHttpJsonResponse(Json::Value{
            {"error", "Invalid JSON input"}
        });
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    auto dbClient = app().getDbClient();
    Mapper<Users> mp(dbClient);
    Users newUser;
    if (json->isMember("name"))
    {
        newUser.setName((*json)["name"].asString());
    }
    if (json->isMember("email"))
    {
        newUser.setEmail((*json)["email"].asString());
    }
    if (json->isMember("is_active"))
    {
        newUser.setIsActive((*json)["is_active"].asBool());
    }

    mp.insert(newUser,
    [callback](const Users &user) {
      auto resp = HttpResponse::newHttpJsonResponse(user.toJson());
      callback(resp);
    },
    [callback](const DrogonDbException &e) {
      Json::Value error;
      error["error"] = e.base().what();
      auto resp = HttpResponse::newHttpJsonResponse(error);
      resp->setStatusCode(k500InternalServerError);
      callback(resp);
    });
}

// void UserController::updateUser(const HttpRequestPtr &req,
//                                 std::function<void(const HttpResponsePtr &)> &&callback,
//                                 int userId)
// {
//     auto json = req->getJsonObject();
//     if (!json || !json->isMember("name") || !json->isMember("email"))
//     {
//         auto resp = HttpResponse::newHttpJsonResponse(
//             Json::Value{{"error", "'name' and 'email' are required to update!"}});
//         resp->setStatusCode(k400BadRequest);
//         callback(resp);
//         return;
//     }

//     auto dbClient = app().getDbClient();
//     Mapper<Users> mp(dbClient);

//     Users user;
//     user.setId(userId);
//     user.setName((*json)["name"].asString());
//     user.setEmail((*json)["email"].asString());

//     if (json->isMember("is_active"))
//     {
//         user.setIsActive((*json)["is_active"].asBool());
//     }

//     mp.update(
//         user,
//         [callback](const Users &updatedUser) {
//             auto resp = HttpResponse::newHttpJsonResponse(updatedUser.toJson());
//             callback(resp);
//         },
//         [callback](const DrogonDbException &e) {
//             Json::Value error;
//             error["error"] = e.base().what();
//             auto resp = HttpResponse::newHttpJsonResponse(error);
//             resp->setStatusCode(k500InternalServerError);
//             callback(resp);
//     });
// }





