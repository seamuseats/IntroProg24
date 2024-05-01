#ifndef CONNECTEDBOT_H
#define CONNECTEDBOT_H

#include "graphics.h"
//#include "vec2d.h"
#include "bot.h"
#include "../comm/tcpserver.h"
#include <memory>

class ConnectedBot {
private:
    Bot bot;
    std::unique_ptr<TCPConnection> connection;
public:
    ConnectedBot(std::unique_ptr<BotAI> brain, std::unique_ptr<TCPConnection> connection);
    ConnectedBot(ConnectedBot&& other);
    void update();
    bool isDead();
    void draw();
};


#endif // CONNECTEDBOT_H
