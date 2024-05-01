#include "botmanager.h"
#include "dylanTools.h"

using namespace mssm;
using namespace std;

int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"

double temp;
double netDist;

Array<Vec2d> wallPos;

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
    Move
    Turn
    Scan
    Fire
    Heal
    Block

*/

class MyBotAI : public BotAI
{
    // Feel free to add fields and methods as needed
public:
    MyBotAI(std::string name);
    virtual BotCmd handleEvents( BotEvent& event);
    virtual void logEvent(std::string event);
    virtual void logCommand(std::string command);
};

MyBotAI::MyBotAI(string name)
{
    setName(name);
}
int a = 0;
bool justScannedBot = false;
double netRot;

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
        a++;
        //system("./scitp.sh");
        netRot += event.angleTurned;
        if(justScannedBot == true){
            return Fire();
        }
        else{
            return MoveForward(0.1);
        }
    case BotEventType::MoveComplete:      // Finished moving
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // valid for this event;
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        netDist += event.travelDistance;
        if(event.health < 3){
            return BotAI::Block();
        }
        else if(justScannedBot == true){
            return BotAI::Fire();
        }
        else if(a % 2 == 0){
            return MoveForward(0.3);
            a++;
        }
        else{
            return Scan(0.9);
        }
    case BotEventType::MoveBlockedByBot:  // you ran into a bot
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // valid for this event;
        // event.travelDistance;  // valid for this event;
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        netDist += event.travelDistance;
        a++;
        return Turn(M_PI + randomDouble(-0.1, 0.1));
    case BotEventType::MoveBlockedByWall: // you ran into a wall
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // valid for this event;
        // event.travelDistance;  // valid for this event;
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        netDist += event.travelDistance;
        
        return Turn(event.collisionAngle + (M_PI / 2));
    case BotEventType::FireComplete:   // bullet launched
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        //system("ping 192.168.6.199");
        return Block();
    case BotEventType::NoEnergy:       // Last command failed due to lack of energy
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        //return BotAI::Resign();
        return BotAI::Heal();
    case BotEventType::BlockComplete:  // Finished blocking
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        return Turn(1);
    case BotEventType::HealComplete:   // Finished healing
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        return Scan(0.9);
    case BotEventType::ScanComplete:   // Finished scanning
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        {
        double grinch = calcDist(event.scanData, 0.9);
        a++;
        for(int i = 0; i < event.scanData.size(); i++){
            double increment{0.9 / event.scanData.size()};
            if(event.scanData[i] > 0){
                justScannedBot = true;
                return Turn(0.45 - (increment * i));
            }
            justScannedBot = false;
        }
        if(grinch == 0 && a % 4 == 0){
            return Turn(0.9);
        }
        return BotAI::MoveForward(grinch / 50);
        }

        // the following events may be ignored if you choose
    case BotEventType::ShotSelf:       // Your own bullet hit you
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // valid for this event
        // event.travelDistance;  // valid for this event
        // event.angleTurned;     // valid for this event
        // event.scanData;        // N/A
        netDist += event.travelDistance;
        netRot += event.angleTurned;
        return MoveForward(event.health);
    case BotEventType::BulletHitBot:   // Your bullet hit another bot
        // event.eventTime;       // valid for this event
        // event.health;          // OTHER bot's health
        // event.energy;          // 1 if hit successfully, 0 if blocked by other bot
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        return Fire();
    case BotEventType::HitByBot:       // A bot collided with you
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // valid for this event
        // event.travelDistance;  // valid for this event
        // event.angleTurned;     // valid for this event
        // event.scanData;        // N/A

        netRot += event.angleTurned;
        netDist += event.travelDistance;
        if(event.health < 3){
            return BotAI::Block();
        }
        else{
            return Scan(0.9);
        }
    case BotEventType::HitByBullet:    // A bullet hit you
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // valid for this event
        // event.travelDistance;  // valid for this event
        // event.angleTurned;     // valid for this event
        // event.scanData;        // N/A
        netDist += event.travelDistance;
        netRot += event.angleTurned;
        return MoveForward(event.health);
        case BotEventType::PowerUp:        // you ran over an energy pellet
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // valid for this event
        // event.travelDistance;  // valid for this event
        // event.angleTurned;     // valid for this event
        // event.scanData;        // N/A
        netRot += event.angleTurned;
        netDist += event.travelDistance;
        return Ignore();
    }

    cout << "Oops!  You forgot to return a command!" << endl;
    return Ignore();
}

void MyBotAI::logEvent(std::string event)
{
    cout << "EVENT: " << event << endl;
}

void MyBotAI::logCommand(std::string command)
{
    cout << "CMD:   " << command << endl;
}

void botBrainLoop(Graphics& g)
{
    BotManager botManager(1235, "192.168.6.199"); // "192.168.6.199");
        
    botManager.setBot(std::make_unique<MyBotAI>("john"));
    
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
        g.ellipse(Vec2d{netDist, 0}.rotated(netRot), 40, 40, WHITE);
    }
}



int main()
{
    Graphics g("Bot Battle Client", 1000, 800);
    temp = 0;
    netRot = 0;
    netDist = 0;
    cout << "test";

    // Graphics m("BattleMapper", 1000, 800);

    // while(m.draw()){
    //     if(m.isKeyPressed(Key::Up)){
    //         temp += 0.1;
    //     }
    //     if(m.isKeyPressed(Key::Down)){
    //         temp -= 0.1;
    //     }
    //     for (int i = 0; netRot > 0; i++){
    //         netRot -= (M_PI * 2);
    //     }
    //     m.println("{}", Vec2d{netDist, 0}.rotated(netRot));
    //     m.ellipse(Vec2d{netDist, 0}.rotated(netRot), 100, 100, WHITE, WHITE);
    // }

    //dylanBot();
    // int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // sockaddr_in serverAddress;
    // serverAddress.sin_family = AF_INET;
    // serverAddress.sin_port = htons(8080);
    // serverAddress.sin_addr.s_addr = INADDR_ANY;

    // connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // const char* message = "F";
    // send(clientSocket, message, strlen(message), 0);

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

