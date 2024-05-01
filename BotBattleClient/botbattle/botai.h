#ifndef BOTAI_H
#define BOTAI_H

#include "botcmd.h"
#include <vector>

namespace mssm {
class Graphics;
}

class BotAI
{
private:
    std::string name;
    static int  botCount;
    int         botNum;
    bool        commandIssued{false};
    bool        nameChanged{true};
public:
    BotAI();
    virtual ~BotAI();
    virtual BotCmd handleEvents(BotEvent& event) = 0;
    virtual std::string getName();
    bool isNameChanged() { return nameChanged; }
    void clearNameChanged() { nameChanged = false; }
    void resetCommandIssued() { commandIssued = false; }
    virtual void logEvent(std::string event) = 0;
    virtual void logCommand(std::string command) = 0;
    virtual void draw() = 0;
protected:
    void checkCommandIssued();
    void setName(const std::string& name);
    BotCmd Turn(double angle);
    BotCmd MoveForward(double timeInSeconds);
    BotCmd MoveBackward(double timeInSeconds);
    BotCmd Fire();
    BotCmd Scan(double fieldOfView);
    BotCmd Resign();
    BotCmd Block();
    BotCmd Heal();
    BotCmd Ignore();
};

#endif // BOTAI_H
