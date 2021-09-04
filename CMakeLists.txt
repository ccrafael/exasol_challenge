set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

cmake_minimum_required(VERSION 3.18)
project(exasol_challenge)

set(CMAKE_CXX_STANDARD 14)



add_executable(exasol main.cpp
        Client.cpp Client.h
        commands/Command.h
        NetworkConnection.cpp NetworkConnection.h
        Connection.h
        commands/HelloCommand.cpp commands/HelloCommand.h
        commands/PowCommand.cpp commands/PowCommand.h
        commands/EndCommand.cpp commands/EndCommand.h
        commands/SendDataCommand.cpp commands/SendDataCommand.h
        utils.h utils.cpp
        DummyConnection.cpp DummyConnection.h commands/Combinations.cpp commands/Combinations.h)

find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(
        exasol_chanllenge
        OpenSSL::SSL
        OpenSSL::Crypto
        ${CMAKE_THREAD_LIBS_INIT})
