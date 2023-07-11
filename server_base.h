#ifndef SERVERBASE_H
#define SERVERBASE_H

#include <iostream>
#include <memory>
#include <grpcpp/grpcpp.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class serverBase
{
public:
    serverBase();

private:
    std::string serverAddrees;
};

#endif // SERVERBASE_H
