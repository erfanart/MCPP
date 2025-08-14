// include/mcpp/server.hpp
#pragma once
#include "tool.hpp"
#include <unordered_map>

namespace mcpp
{

    class Server
    {
    public:
        void registerTool(const ToolSpec &spec);
        nlohmann::json handleJsonRpc(const nlohmann::json &req); // ورودی/خروجی JSON-RPC

    private:
        nlohmann::json onInitialize(const nlohmann::json &params);
        nlohmann::json onToolsList(const nlohmann::json &params);
        nlohmann::json onToolsCall(const nlohmann::json &params);

        // اختیاری:
        nlohmann::json onResourcesList(const nlohmann::json &params);
        nlohmann::json onPromptsList(const nlohmann::json &params);

        std::unordered_map<std::string, ToolSpec> registry_;
    };

} // namespace mcpp
