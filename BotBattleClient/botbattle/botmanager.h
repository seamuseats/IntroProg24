#ifndef BOTMANAGER_H
#define BOTMANAGER_H

#include "connectedbot.h"

class BotManager {
private:
    TCPContext context;
   // mssm::Graphics& g;
    int port;
    std::string host;
    std::unique_ptr<ConnectedBot> bot;
public:
    BotManager(int port, const std::string& host);
   ~BotManager();
    void setBot(std::unique_ptr<BotAI> brain);
    void update();
    bool isDead();
};

#endif // BOTMANAGER_H
