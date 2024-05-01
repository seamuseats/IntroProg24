#include "botmanager.h"

using namespace mssm;
using namespace std;

#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"

/*
 *
 * Bot Event Types

 Not-Ignorable  (If you ignore these, you'll go to "sleep"
                 until someone hits you or shoots you... not good)

    case BotEventType::TurnComplete:      // Finished turning
    case BotEventType::MoveComplete:      // Finished moving
    case BotEventType::MoveBlockedByBot:  // you ran into a bot
    case BotEventType::MoveBlockedByWall: // you ran into a wall
    case BotEventType::FireComplete:   // bullet launched
    case BotEventType::NoEnergy:       // Last command failed due to lack of energy
    case BotEventType::ScanComplete:   // Finished scanning
    case BotEventType::BlockComplete:  // Finished blocking
    case BotEventType::HealComplete:   // Finished healing

  Ignorable events:
    These are "interrupt" points, where you can either issue a new command (canceling
    your last command, or you can Ignore to allow your previous command to finish

    case BotEventType::ShotSelf:       // Your own bullet hit you
    case BotEventType::BulletHitBot:   // Your bullet hit another bot
    case BotEventType::HitByBot:       // A bot collided with you
    case BotEventType::HitByBullet:    // A bullet hit you
    case BotEventType::PowerUp:        // you ran over an energy pellet

    For any of the Not-Ignorable events, you should return one of these commands

    Ignore
    MoveForward
    Turn
    Scan
    Fire
    Heal
    Block

*/

class MyBotAI : public BotAI
{
    Graphics& g;
    Array<string> messageLog;
    // Feel free to add fields and methods as needed
public:
    MyBotAI(Graphics& g, std::string name);
    virtual BotCmd handleEvents( BotEvent& event);
    virtual void logEvent(std::string event);
    virtual void logCommand(std::string command);
    void draw() override;
};

void MyBotAI::draw()
{
    while (messageLog.size() > 10) {
        messageLog.removeAtIndex(0);
    }
    for (auto& msg : messageLog) {
        g.println("{}", msg);
    }

}

MyBotAI::MyBotAI(Graphics& g, string name) : g{g}
{
    setName(name);
}

BotCmd MyBotAI::handleEvents(BotEvent& event)
{
    // This is where you'll implement your bot "AI"

    switch (event.eventType)
    {
    case BotEventType::TurnComplete:      // Finished turning
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // valid for this event;
        // event.scanData;        // N/A
        return MoveForward(5);
    case BotEventType::MoveComplete:      // Finished moving
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // valid for this event;
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        return MoveForward(5);
    case BotEventType::MoveBlockedByBot:  // you ran into a bot
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // valid for this event;
        // event.travelDistance;  // valid for this event;
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        return Turn(M_PI-event.collisionAngle);
    case BotEventType::MoveBlockedByWall: // you ran into a wall
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // valid for this event;
        // event.travelDistance;  // valid for this event;
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A       
        if (event.collisionAngle > 0) {
            double adjust = 1;
            return Turn(-M_PI+event.collisionAngle+adjust);
        }
        else {
            double adjust = 1;
            return Turn(M_PI+event.collisionAngle-adjust);
        }
    case BotEventType::FireComplete:   // bullet launched
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        return MoveForward(1);
    case BotEventType::NoEnergy:       // Last command failed due to lack of energy
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        return MoveForward(1);
    case BotEventType::BlockComplete:  // Finished blocking
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        return MoveForward(1);
    case BotEventType::HealComplete:   // Finished healing
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        return MoveForward(1);
    case BotEventType::ScanComplete:   // Finished scanning
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        // event.scanData;        // valid for this event
        return MoveForward(1);

        // the following events may be ignored if you choose
    case BotEventType::ShotSelf:       // Your own bullet hit you
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // valid for this event
        // event.travelDistance;  // valid for this event
        // event.angleTurned;     // valid for this event
        // event.scanData;        // N/A
        return Ignore();
    case BotEventType::BulletHitBot:   // Your bullet hit another bot
        // event.eventTime;       // valid for this event
        // event.health;          // OTHER bot's health
        // event.energy;          // 1 if hit successfully, 0 if blocked by other bot
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        return Ignore();
    case BotEventType::HitByBot:       // A bot collided with you
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // valid for this event
        // event.travelDistance;  // valid for this event
        // event.angleTurned;     // valid for this event
        // event.scanData;        // N/A
        return Ignore();
    case BotEventType::HitByBullet:    // A bullet hit you
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // valid for this event
        // event.travelDistance;  // valid for this event
        // event.angleTurned;     // valid for this event
        // event.scanData;        // N/A
        return Ignore();
    case BotEventType::PowerUp:        // you ran over an energy pellet
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // valid for this event
        // event.travelDistance;  // valid for this event
        // event.angleTurned;     // valid for this event
        // event.scanData;        // N/A
        return Ignore();
    }

    cout << "Oops!  You forgot to return a command!" << endl;
    return Ignore();
}

void MyBotAI::logEvent(std::string event)
{
    messageLog.append(event);
    cout << "EVENT: " << event << endl;
}

void MyBotAI::logCommand(std::string command)
{
    messageLog.append(command);
    cout << "CMD:   " << command << endl;
}

void botBrainLoop(Graphics& g)
{
    BotManager botManager(1235, "localhost"); // "192.168.6.199");

    botManager.setBot(std::make_unique<MyBotAI>(g, "Bouncer"));

    while (g.draw() && !botManager.isDead())
    {
        botManager.update();
    }
}


void prompt(Graphics& g, string msg)
{
    while (g.draw())
    {
        g.text({50,g.height()/2-10},20,msg);
        if (g.onKeyPress(' ')) {
            return;
        }
    }
}



int main()
{
    Graphics g("Bot Battle Client", 1000, 800);

    try {
        while (g.draw()) {
            botBrainLoop(g);
            prompt(g, "Disconnected: Press space to reconnect to server");
        }
    }
    catch (const std::exception& ex) {
        prompt(g, string{"Exception: "} + ex.what());
    }
    catch (...) {
        prompt(g, "Unknown exception thrown!");
    }
}

