// include/mcpp/stdio_transport.hpp
#pragma once
#include "server.hpp"

namespace mcpp
{

    class StdioTransport
    {
    public:
        explicit StdioTransport(Server &server) : server_(server) {}
        int run(); // loop: read line -> parse -> server.handleJsonRpc -> write line

    private:
        Server &server_;
    };

} // namespace mcpp
