#include "botmanager.h"

using namespace std;
using namespace mssm;

BotManager::BotManager(int port, const std::string& host)
    : port{port}, host{host}
{
}

BotManager::~BotManager()
{
}

void BotManager::setBot(std::unique_ptr<BotAI> brain)
{
    bot = std::make_unique<ConnectedBot>(std::move(brain), context.connect(host, port));
}

void BotManager::update()
{
    context.poll();
    bot->update();
    bot->draw();
}

bool BotManager::isDead()
{
    return bot->isDead();
}
