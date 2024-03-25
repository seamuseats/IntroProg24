#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <asio.hpp>
#include <array>

//// USAGE
////vector<weak_ptr<TCPConnection>> connections;

//TCPContext context;
//TCPServer server(context, 1234); // , [&connections](std::weak_ptr<TCPConnection> conn) {
////        cout << "Client Connected" << endl;
////        connections.push_back(conn);
////    });

//unique_ptr<TCPConnection> client{context.connect("localhost", 1234)};

//while (true) {
//    context.poll();

//    for (auto& c : server.connections()) {
//        if (c->hasData()) {
//            g.cout << "Got Data: '" << c->read() << "'" << endl;
//            c->write("Ping");
//        }
//        else {
//            g.cout << "Waiting" << endl;
//        }
//    }

//    if (client->hasData()) {
//        g.cerr << client->read() << endl;
//    }
//}

class TCPServer;
class TCPConnection;

class TCPContext {
private:
    asio::io_context io_context;
public:
    void poll();
    std::unique_ptr<TCPConnection> connect(std::string server, int port);
    friend class TCPServer;
};

class TCPConnection
{
private:
    TCPServer*  server;
    asio::ip::tcp::socket sock;
    std::array<char, 20> buffer;
    std::string data;
public:
    TCPConnection(TCPServer* server, asio::ip::tcp::socket sock);
    virtual ~TCPConnection();
    void write(std::string data);
    std::string read();
    bool hasData() const { return !data.empty(); }
    bool isClosed();
    void close();
private:
    void keepReadingAsync();
};

class TCPServer
{
    TCPContext& context;
    asio::ip::tcp::acceptor acceptor;
    std::vector<std::shared_ptr<TCPConnection>> conns;
    std::function<void (std::weak_ptr<TCPConnection>)> onConnect;
public:
    TCPServer(TCPContext& context, int port, std::function<void(std::weak_ptr<TCPConnection>)> onConnect = {});
    virtual ~TCPServer();
    const std::vector<std::shared_ptr<TCPConnection>>& connections() { return conns; };
    void doAccept();

    void remove(TCPConnection* connection);
};

#endif // TCPSERVER_H
