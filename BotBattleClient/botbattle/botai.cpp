#include "botai.h"
#include <iostream>
#include <cmath>

using namespace std;

int BotAI::botCount = 0;

BotAI::BotAI()
{
    botNum = ++botCount;
    setName("Unnamed");
}

BotAI::~BotAI()
{
}

void BotAI::setName(const std::string& botName)
{
    string newName = botName;
    if (name != newName) {
        name = newName;
        nameChanged = true;
    }
}

std::string BotAI::getName()
{
    return name;
}

void BotAI::checkCommandIssued()
{
    if (commandIssued) {
        throw runtime_error("Only one command (Move, Fire, Turn, Scan, Ignore) may be sent per event");
    }
    commandIssued = true;
}


BotCmd BotAI::Turn(double angle)
{
    checkCommandIssued();
    return BotCmd{BotCmdType::Turn, angle, 0};
}

BotCmd BotAI::MoveForward(double time)
{
    checkCommandIssued();
    return BotCmd{BotCmdType::Move, 50, time};
}

BotCmd BotAI::MoveBackward(double time)
{
    checkCommandIssued();
    return BotCmd{BotCmdType::Move, -50, time};
}

BotCmd BotAI::Fire()
{
    checkCommandIssued();
    return BotCmd{BotCmdType::Fire, 0, 0};
}

BotCmd BotAI::Scan(double fieldOfView)
{
    checkCommandIssued();
    return BotCmd{BotCmdType::Scan, fieldOfView, 0};
}

BotCmd BotAI::Resign()
{
    checkCommandIssued();
    return BotCmd{BotCmdType::Resign, 0, 0};
}

BotCmd BotAI::Block()
{
    checkCommandIssued();
    return BotCmd{BotCmdType::Block, 0, 0};
}

BotCmd BotAI::Heal()
{
    checkCommandIssued();
    return BotCmd{BotCmdType::Heal, 0, 0};
}

BotCmd BotAI::Ignore()
{
    checkCommandIssued();
    return BotCmd{BotCmdType::Ignore, 0, 0};
}
