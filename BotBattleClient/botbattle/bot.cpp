#include <iostream>
#include <sstream>
#include "bot.h"

using namespace std;

Bot::Bot(std::unique_ptr<BotAI> brain)
    : brain{std::move(brain)}
{
}

Bot::~Bot()
{
}

string formatEvent(std::string name, const BotEvent& event)
{
    stringstream ss;
    ss << name << ": ";
    event.write(ss, false);
    return ss.str();
}

string formatCmd(std::string name, BotCmd cmd)
{
    std::stringstream ss;
    ss << name << ": ";
    cmd.write(ss, false);
    return ss.str();
}

BotCmd Bot::handleEvents(BotEvent& evt)
{
    brain->logEvent(formatEvent(brain->getName(), evt));
    brain->resetCommandIssued();
    BotCmd cmd = brain->handleEvents(evt);
    brain->logCommand(formatCmd(brain->getName(), cmd));
    return cmd;
}


void Bot::handleReceivedData(const std::string& incoming)
{
    receivedData.append(incoming);

    auto idx = receivedData.find_first_of('\n');

    if (idx != string::npos) {
        string commandString{receivedData.substr(0, idx)};
        receivedData = receivedData.substr(idx+1);
        //cout << "Received: '" << commandString << endl;

        std::stringstream evtStream(commandString);
        event = BotEvent::read(evtStream);

        BotCmd nextCommand = handleEvents(event);

        std::stringstream cmdStream;
        nextCommand.write(cmdStream, true);
        outgoingCommand = cmdStream.str();
        //cout << "Outgoing: ";
        //cout << outgoingCommand << endl;
    }
}

string Bot::getOutgoingData()
{
    std::string tmp = std::move(outgoingCommand);
    outgoingCommand.clear();
    if (brain->isNameChanged()) {
        tmp = "N " + brain->getName() + "\n" + tmp;
        brain->clearNameChanged();
    }
    return tmp;
}
