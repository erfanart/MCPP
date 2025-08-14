#include "mcpp/server.hpp"
#include "mcpp/stdio_transport.hpp"
#include "mcpp/json.hpp"

using namespace mcpp;
using nlohmann::json;

int main()
{
    Server server;

    server.registerTool(ToolSpec{
        .name = "entity.search",
        .description = "Search sensors by label",
        .inputSchema = json{
            {"type", "object"},
            {"properties", {{"query", {{"type", "string"}}}, {"limit", {{"type", "integer"}, {"default", 5}}}}},
            {"required", {"query"}}},
        .handler = [](const json &args) -> ToolResult
        {
            std::string q = args.value("query", "");
            json results = json::array({{{"resource_uri", "simop:/plants/p1/y1/e3/s10"}, {"label", "Air Temperature - Turbine Hall"}, {"unit", "°C"}, {"capabilities", {"read"}}},
                                        {{"resource_uri", "simop:/plants/p2/y1/e1/s7"}, {"label", "Outside Air Temp - Gate"}, {"unit", "°C"}, {"capabilities", {"read"}}}});
            json content = json::array({{{"type", "text"}, {"text", "Found sensors for query: " + q}},
                                        {{"type", "resource"}, {"resource", {{"uri", "resource://search-results"}, {"mimeType", "application/json"}, {"text", results.dump()}}}}});
            return {.content = content, .isError = false};
        }});

    server.registerTool(ToolSpec{
        .name = "entity.read",
        .description = "Read last value from a sensor",
        .inputSchema = json{
            {"type", "object"},
            {"properties", {{"resource_uri", {{"type", "string"}}}}},
            {"required", {"resource_uri"}}},
        .handler = [](const json &args) -> ToolResult
        {
            std::string uri = args.value("resource_uri", "");
            double value = 28.4;
            std::string unit = "°C";
            std::string ts = "2025-08-14T10:14:12Z";
            json content = json::array({{{"type", "text"}, {"text", uri + ": " + std::to_string(value) + " " + unit + " @ " + ts}},
                                        {{"type", "resource"}, {"resource", {{"uri", uri}, {"mimeType", "application/json"}, {"text", json({{"value", value}, {"unit", unit}, {"timestamp", ts}, {"quality", "good"}}).dump()}}}}});
            return {.content = content, .isError = false};
        }});

    StdioTransport transport(server);
    return transport.run();
}
