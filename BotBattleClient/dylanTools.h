#include "botmanager.h"

double calcDist(vector<int> scanData, double scanWidth) { // M_PI/scanWidth is the angle of the scan
    double anglePerRay =  scanWidth / scanData.size();
    int z;
    int y = 0;
    for (z = 0; z < scanData.size(); z++) {
        if (scanData[z] != 0 && y == 0)
        {
            y = z;
        }
        if (y != 0 && scanData[z] == 0) {
            break;
        }
        if(z == scanData.size() || y == 0){
            return 0;
        }
    }
    double angleA = anglePerRay * (z-y);
    double angleB = (M_PI-angleA)/2.0;
    double distB = (sin(angleB) * 40.0) / sin(angleA);

    cout << "AnglePerRay: " << anglePerRay << " z: " << z << " y: " << y << " angleA: " << angleA << " angleB: " << angleB << " Distance: " << distB << endl;
    return distB;
}

void dylanBot(){
    char cmd;
    cin >> cmd;
    system(fmt::format("telnet 192.168.6.199 1235 << EOF\n {}\n EOF", cmd).c_str());
}

