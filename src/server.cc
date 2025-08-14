// src/server.cc (گزیده)
#include "mcpp/server.hpp"
#include "mcpp/rpc.hpp"
using nlohmann::json;
using namespace mcpp;

void Server::registerTool(const ToolSpec &spec)
{
    registry_[spec.name] = spec;
}

json Server::handleJsonRpc(const json &req)
{
    if (req.value("jsonrpc", "") != "2.0" || !req.contains("id") || !req.contains("method"))
        return err(req.value("id", 0), -32600, "Invalid Request");

    const int id = req["id"].get<int>();
    const std::string method = req["method"].get<std::string>();
    const json params = req.value("params", json::object());

    try
    {
        if (method == "initialize")
            return ok(id, onInitialize(params));
        if (method == "tools/list")
            return ok(id, onToolsList(params));
        if (method == "tools/call")
            return ok(id, onToolsCall(params));
        if (method == "resources/list")
            return ok(id, onResourcesList(params)); // اختیاری
        if (method == "prompts/list")
            return ok(id, onPromptsList(params)); // اختیاری
        return err(id, -32601, "Method not found");
    }
    catch (const std::exception &e)
    {
        return err(id, -32603, "Internal error", {{"what", e.what()}});
    }
}

json Server::onInitialize(const json &)
{
    return json{
        {"serverInfo", {{"name", "mcpp"}, {"version", "0.1.0"}}},
        {"capabilities", {{"tools", {{"listChanged", true}}}, {"resources", {{"subscribe", false}, {"listChanged", true}}}, {"prompts", {{"listChanged", true}}}}}};
}

json Server::onToolsList(const json &)
{
    json tools = json::array();
    for (auto &[name, spec] : registry_)
    {
        tools.push_back({{"name", spec.name},
                         {"description", spec.description},
                         {"inputSchema", spec.inputSchema}});
    }
    return {{"tools", tools}, {"nextCursor", nullptr}};
}

json Server::onToolsCall(const json &p)
{
    const std::string name = p.at("name").get<std::string>();
    const json args = p.value("arguments", json::object());
    auto it = registry_.find(name);
    if (it == registry_.end())
        return {{"content", {{{"type", "text"}, {"text", "Unknown tool"}}}}, {"isError", true}};
    // TODO: validate args with inputSchema (اختیاری)
    ToolResult r = it->second.handler(args);
    return {{"content", r.content}, {"isError", r.isError}};
}

// اختیاری: منابع/پرامپت‌ها
json Server::onResourcesList(const json &) { return {{"resources", json::array()}, {"nextCursor", nullptr}}; }
json Server::onPromptsList(const json &) { return {{"prompts", json::array()}, {"nextCursor", nullptr}}; }
