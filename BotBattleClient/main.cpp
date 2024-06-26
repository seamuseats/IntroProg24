#include "botmanager.h"
#include "dylanTools.h"
#include <math.h>

using namespace mssm;
using namespace std;

#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"

double netRot;
double netDist;
bool starting{true};
Vec2d Pos;
double grinch;
Array<Vec2d> wallPoints;
World world;
bool aligned{false};
Vec2d viewTransform;
int mode{0};

int a;

bool justScannedBot;
bool inMiddle;
bool hitWall;
double evtTime;

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
        if(g.isKeyPressed('w')){
            viewTransform.y -= 1;
        }
        if(g.isKeyPressed('a')){
            viewTransform.x -= 1;
        }
        if(g.isKeyPressed('s')){
            viewTransform.y += 1;
        }
        if(g.isKeyPressed('d')){
            viewTransform.x += 1;
        }
        if(g.isKeyPressed('m')){
            mode = 1;
        }
        if(g.isKeyPressed('n')){
            mode = 0;
        }
        world.draw(g, viewTransform);
	    g.ellipse((Pos + viewTransform), 40, 40, WHITE, WHITE);
        while(world.GridCenters.size() > 60){
            world.GridCenters.removeAtIndex(0);
        }
        while(world.wallPoints.size() > 60){
            world.wallPoints.removeAtIndex(0);
        }
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
        a++;
        //system("./scitp.sh");
        if(starting){
            netRot = 0;
            starting = false;
        }
        else{
            netRot += event.angleTurned;
        }
        if(justScannedBot == true && event.energy > 0){
            justScannedBot = false;
            return Fire();
        }
        else if(hitWall == true){
            aligned = true;
            justScannedBot = false;
            return MoveForward(1.6);
        }
        else{
            justScannedBot = false;
            return MoveForward(0);
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
        Pos += Vec2d(event.travelDistance, 0).rotated(netRot);
        justScannedBot = false;
        // if(event.travelDistance >= 199 && event.travelDistance <= 201 && aligned == true){
        //     world.GridCenters.append(Pos);
        // }
        //world.clean();
        switch(mode){
        case(1):
            if(event.health <= 3 && event.energy >= 3){
                return BotAI::Heal();
            }
            else if(justScannedBot == true && event.energy >= 3){
                return BotAI::Fire();
            }
            else if(hitWall == true && aligned == true){
                hitWall = false;
                world.GridCenters.append(Pos);
                for(int i = 0; i < world.GridCenters.size(); i++){
                    int cardinalDirection = randomInt(-1, 1);
                    if(((Pos + Vec2d(200, 0).rotated(netRot + (M_PI * cardinalDirection))) - world.GridCenters[i]).magnitude() <= 0.1){
                        return Turn(M_PI * cardinalDirection);
                    }
                }
                return Turn((M_PI / 2) * randomInt(-1, 1));
            }
            else{
                return Scan(0.9);
            }
        case(0):
            if(event.health <= 3 && event.energy >= 3){
                return BotAI::Heal();
            }
            else if(justScannedBot == true && event.energy >= 3){
                return BotAI::Fire();
            }
            else if(hitWall == true && aligned == true){
                hitWall = false;
                world.GridCenters.append(Pos);
                return Turn((M_PI / 2) * randomInt(-1, 1));
            }
            else{
                return Scan(0.9);
            }
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
        Pos += Vec2d(event.travelDistance, 0).rotated(netRot);
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
        Pos += Vec2d(event.travelDistance, 0).rotated(netRot);
        if(aligned == true){
            world.wallPoints.append(Vec2d(Pos) + Vec2d(20, 0).rotated(event.collisionAngle + netRot));
            world.wallAngles.append(event.collisionAngle + netRot + (M_PI * 0.5));
        }
        hitWall = true;
        if(event.collisionAngle <= 0.01 && event.collisionAngle >= -0.01){
            return MoveForward(-1.6);
        }
        if(a % 2 == 0){
            a++;
            return Turn(event.collisionAngle + M_PI);
        }
        else{
            return Turn(event.collisionAngle - M_PI);
        }
    case BotEventType::FireComplete:   // bullet launched
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        //system("ping 192.168.6.199");
        return Scan(0.9);
    case BotEventType::NoEnergy:       // Last command failed due to lack of energy
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        //return BotAI::Resign();
        setName("AHHHHH");
        mode = 1;
        return BotAI::Scan(0.9);
    case BotEventType::BlockComplete:  // Finished blocking
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // N/A
        // event.travelDistance;  // N/A
        // event.angleTurned;     // N/A
        // event.scanData;        // N/A
        return Turn(M_PI);
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
        setName("pluh");
        {
        grinch = calcDist(event.scanData, 0.9); //distance from me to nearest bot
        a++;
        for(int i = 0; i < event.scanData.size(); i++){
            double increment{0.9 / event.scanData.size()};
            if(event.scanData[i] > 0){
                justScannedBot = true;
                BotAI::setName("I C U");
                aligned = false;
                return Turn(0.45 - (increment * i));
            }
            justScannedBot = false;
        }
        hitWall = true;
        return MoveForward(4);
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
        Pos += Vec2d(event.travelDistance, 0).rotated(netRot);
        return MoveForward(4);
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
        setName("SKDGHNLSKDJGNLSDJIGN");
        Pos += Vec2d(event.travelDistance, 0).rotated(netRot);
        return Scan(0.9);
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
        Pos += Vec2d(event.travelDistance, 0).rotated(netRot);
        return MoveForward(4);
        case BotEventType::PowerUp:        // you ran over an energy pellet
        // event.eventTime;       // valid for this event
        // event.health;          // valid for this event
        // event.energy;          // valid for this event
        // event.collisionAngle;  // valid for this event
        // event.travelDistance;  // valid for this event
        // event.angleTurned;     // valid for this event
        // event.scanData;        // N/A
        // netRot += event.angleTurned;
        // netDist += event.travelDistance;
        // Pos += Vec2d(event.travelDistance, 0).rotated(netRot);
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
    BotManager botManager(1235, "192.168.6.199"); // "192.168.6.199");

    botManager.setBot(std::make_unique<MyBotAI>(g, "Pluh"));

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
    Graphics g("Bot Battle Client", 3000, 2000);
    viewTransform = Vec2d(g.width() / 2, g.height() / 2);
    

    try {
        while (g.draw()) {
            botBrainLoop(g);
            world.wallAngles.clear();
            world.wallPoints.clear();
            world.GridCenters.clear();
        }
    }
    catch (const std::exception& ex) {
        prompt(g, string{"Exception: "} + ex.what());
    }
    catch (...) {
        prompt(g, "Unknown exception thrown!");
    }
}

