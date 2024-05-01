#include "connectedbot.h"

using namespace std;
using namespace mssm;

//ConnectedBot::ConnectedBot(ConnectedBot&& other)
//  : g{other.g}, bot{std::move(other.bot.brain)}, connection{other.connection}
//{
//}

ConnectedBot::ConnectedBot(std::unique_ptr<BotAI> brain, std::unique_ptr<TCPConnection> connection)
    : bot{std::move(brain)}, connection{std::move(connection)}
{
    if (connection) {
        connection->write("Name " + bot.name() + "\n");
    }
}

bool ConnectedBot::isDead()
{
    if (connection) {
        return connection->isClosed();
    }
    return true;
}

void ConnectedBot::draw()
{
    bot.draw();
}

void ConnectedBot::update()
{
    if (connection) {
        if (connection->isClosed()) {
            return;
        }
        if (connection->hasData()) {
            string data = connection->read();
            bot.handleReceivedData(data);
        }
        if (bot.hasOutgoingData()) {
            connection->write(bot.getOutgoingData());
        }
    }
}



