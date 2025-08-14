// include/mcpp/rpc.hpp
#pragma once
#include "json.hpp"

namespace mcpp
{
    inline nlohmann::json ok(int id, nlohmann::json result)
    {
        return nlohmann::json{{"jsonrpc", "2.0"}, {"id", id}, {"result", std::move(result)}};
    }
    inline nlohmann::json err(int id, int code, std::string msg, nlohmann::json data = {})
    {
        return nlohmann::json{
            {"jsonrpc", "2.0"}, {"id", id}, {"error", {{"code", code}, {"message", std::move(msg)}, {"data", std::move(data)}}}};
    }
} // namespace mcpp
