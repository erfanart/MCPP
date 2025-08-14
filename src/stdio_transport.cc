// src/stdio_transport.cc (گزیده)
#include "mcpp/stdio_transport.hpp"
#include <iostream>
#include <string>

using nlohmann::json;
using namespace mcpp;

int StdioTransport::run()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty())
            continue;
        json req;
        try
        {
            req = json::parse(line);
        }
        catch (...)
        {
            std::cout << R"({"jsonrpc":"2.0","id":null,"error":{"code":-32700,"message":"Parse error"}})" << std::endl;
            continue;
        }
        json resp = server_.handleJsonRpc(req);
        std::cout << resp.dump() << std::endl; // هر پاسخ روی یک خط
    }
    return 0;
}
