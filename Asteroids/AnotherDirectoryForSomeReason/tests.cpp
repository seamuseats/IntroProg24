#include <iostream>
#include "graphics.h"
#include "tcpserver.h"

//#include "vec2d.h"
//#include "paths.h"

using namespace std;
using namespace mssm;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif



int main(int argc, char* argv[])
{
    vector<weak_ptr<TCPConnection>> connections;

    TCPContext context;
    TCPServer server(context, 1234); // , [&connections](std::weak_ptr<TCPConnection> conn) {
//        cout << "Client Connected" << endl;
//        connections.push_back(conn);
//    });

    unique_ptr<TCPConnection> client{context.connect("localhost", 1234)};

    try
    {
        //   Paths::findAsset("skull.png");
        Graphics g("Test", 1024, 768);

        Image skull(g, "skull.png", true);
        Sound pew(g, "sounds/ShortLaser.wav");

        skull.setPixel(0,0,WHITE);
        skull.setPixel(1,1,WHITE);
        skull.setPixel(2,2,WHITE);

        skull.save("skullmod.png");

        SoundHandle handle = 0;

        while (g.draw()) {

            context.poll();

           // cout << "Before Poll" << endl;
            // cout << "After Poll" << endl;

            for (auto& c : server.connections()) {
                if (c->hasData()) {
                    g.cout << "Got Data: '" << c->read() << "'" << endl;
                    c->write("Ping");
                }
                else {
                    g.cout << "Waiting" << endl;
                }
            }

            if (client->hasData()) {
                g.cerr << client->read() << endl;
            }

            if (!g.isMusicPlaying()) {
                g.music("sounds/goldn-116392.mp3", 0.1);
            }

            g.image({100,100}, skull);

            if (g.onMousePress(MouseButton::Left)) {
                g.cerr << "Click" << endl;
                client->write("Hello");
            }

            if (g.onKeyPress(' ')) {
                g.play(pew);
            }

            if (g.isKeyPressed('c') && !g.isPlaying(handle)) {
                handle = g.play(pew, 0.5);
            }

            if (g.onKeyPress('1')) {
                g.setMusicVolume(0.1);
            }
            if (g.onKeyPress('2')) {
                g.setMusicVolume(0.2);
            }
            if (g.onKeyPress('3')) {
                g.setMusicVolume(0.3);
            }
            if (g.onKeyPress('4')) {
                g.setMusicVolume(0.4);
            }

        }

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }


    return 0;
}


