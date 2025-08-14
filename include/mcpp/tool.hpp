// include/mcpp/tool.hpp
#pragma once
#include <string>
#include <functional>
#include "json.hpp"

namespace mcpp
{

    // نتیجهٔ استاندارد tools/call
    struct ToolResult
    {
        nlohmann::json content; // آرایه‌ای از قطعات: [{type:"text",...}, {type:"resource",...}]
        bool isError{false};
    };

    using ToolHandler = std::function<ToolResult(const nlohmann::json &args)>;

    struct ToolSpec
    {
        std::string name;
        std::string description;
        nlohmann::json inputSchema; // JSON Schema
        ToolHandler handler;
    };

} // namespace mcpp
