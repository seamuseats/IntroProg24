#ifndef BOTCMD
#define BOTCMD

#include <iostream>
#include <vector>

enum class BotCmdType
{
    Turn,
    Move,
    Fire,
    Scan,
    Ignore,
    Asleep,
    Resign,
    Block,
    Heal
};

class BotCmd
{
public:
    BotCmdType cmd;
    double arg1;
    double arg2;
public:
    void write(std::ostream& strm, bool includeCR = true);
};

enum class BotEventType
{
    TurnComplete,
    MoveComplete,
    ScanComplete,
    FireComplete,
    BlockComplete,
    HealComplete,
    NoEnergy,
    MoveBlockedByWall,
    MoveBlockedByBot,
    HitByBot,           // ignorable
    HitByBullet,        // ignorable
    ShotSelf,           // ignorable
    PowerUp,            // ignorable
    BulletHitBot,       // ignorable     Note:  health is target health, energy is 1 for hit, 0 if blocked
};

class BotEvent
{
public:
    BotEventType eventType;
    double       eventTime;
    int          health;
    int          energy;
    double       collisionAngle;  // angle with respect to the direction the bot is facing
    double       travelDistance;
    double       angleTurned;
    std::vector<int> scanData;

public:
    BotEvent(BotEventType eventType, double eventTime, int health, int energy);
    void write(std::ostream& strm, bool includeCr) const;
    static BotEvent read(std::istream& strm);  // note!  negative event time indicates an error reading from the stream!!
private:
    void write(std::ostream& strm, const std::string& typeName, bool includeCollisionAngle, bool includeDistance, bool includeAngleTurned, bool includeScanData) const;
    void read(std::istream& strm, bool includeCollisionAngle, bool includeDistance, bool includeAngleTurned, bool includeScanData);
};

#endif // BOTCMD

