#include "tcpserver.h"
#include <asio.hpp>
#include <iostream>
#include <asio/error.hpp>

using asio::ip::tcp;

using namespace std;

TCPServer::TCPServer(TCPContext& context, int port, std::function<void (std::weak_ptr<TCPConnection>)> onConnect)
    : context{context},
      acceptor(context.io_context, tcp::endpoint(tcp::v4(), port)),
      onConnect{onConnect}
{
    doAccept();
}

TCPServer::~TCPServer()
{
    acceptor.cancel();
}

void TCPServer::doAccept()
{
    acceptor.async_accept([this](asio::error_code ec, tcp::socket socket)
    {
        if (!ec)
        {
            conns.push_back(std::make_shared<TCPConnection>(this, std::move(socket)));
            if (onConnect) {
                onConnect(conns.back());
            }
        }

        doAccept();
    });

}

void TCPContext::poll()
{
    io_context.poll();
}

std::unique_ptr<TCPConnection> TCPContext::connect(std::string server, int port)
{
    tcp::resolver resolver(io_context);

    tcp::resolver::results_type endpoints = resolver.resolve(server, to_string(port));

    tcp::socket socket(io_context);

    asio::connect(socket, endpoints);

    return std::make_unique<TCPConnection>(nullptr, std::move(socket));
}

void TCPServer::remove(TCPConnection *connection)
{
    conns.erase(std::remove_if(conns.begin(), conns.end(), [connection](auto& ptr) {
        return ptr.get() == connection;
    }), conns.end());
}

TCPConnection::TCPConnection(TCPServer* server, asio::ip::tcp::socket sock)
    : server{server}, sock{std::move(sock)}
{
    keepReadingAsync();
}

TCPConnection::~TCPConnection()
{
    sock.close();
}

void TCPConnection::write(std::string data)
{
    sock.async_send(asio::buffer(data), [this](asio::error_code ec, std::size_t length) {
        if (ec) {
            if ((asio::error::eof == ec) ||
                (asio::error::connection_reset == ec))
            {
                // handle the disconnect.
                cout << "Write Failed.  Connection closed" << endl;
            }
            else
            {
                // read the data
                cout << "Write Failed.  Unexpected Error: " << ec.message() << " " << ec.value() <<  " " << ec.category().name() << endl;
            }
            sock.close();
            sock.close();

            if (server) {
                server->remove(this);
            }
            return;
        }
        //cout << "Write Completed.  Sent: " << length << endl;
    });
}

std::string TCPConnection::read()
{
    return std::exchange(data, {});
}

bool TCPConnection::isClosed()
{
    return !sock.is_open();
}

void TCPConnection::close()
{
    sock.close();
    if (server) {
        server->remove(this);
    }
}

void TCPConnection::keepReadingAsync()
{
    this->sock.async_read_some(asio::buffer(buffer),  [this](asio::error_code ec, std::size_t length) {
        if (ec) {
            if ((asio::error::eof == ec) ||
                (asio::error::connection_reset == ec))
            {
                // handle the disconnect.
                cout << "Read Some Failed.  Connection closed" << endl;


            }
            else
            {
                // read the data
                cout << "Read Some Failed.  Unexpected Error: " << ec.message() << " " << ec.value() <<  " " << ec.category().name() << endl;
            }

            sock.close();

            if (server) {
                server->remove(this);
            }

            return;
        }
        data.append(buffer.data(), length);
        //cout << "Data: '" << data << "'" << endl;
        keepReadingAsync();
    });
}




