#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Handles temperature-specific logic
class TemperatureMonitor {
public:
    void update(float valueCelsius) {
        if (valueCelsius > 35.0) {
            cout << "ALERT: High temperature detected (Environment)" << endl;
        }
    }
};

// Handles dimension variation logic
class DimensionMonitor {
public:
    void update(float variationMM) {
        if (variationMM > 0.05) {
            cout << "ALERT: Part-dimension variation too high (Machine)" << endl;
        }
    }
};

// Handles continuous operation logic
class OperationMonitor {
public:
    void update(int minutes) {
        if (minutes > 360) {
            cout << "ALERT: Continuous operation exceeded 6 hours (Machine)" << endl;
        }
    }
};

// Handles self-test reporting logic
class SelfTestReporter {
public:
    void report(int code) {
        switch (code) {
            case 0xFF:
                cout << "Self-test OK" << endl;
                break;
            case 0x00:
                cout << "ALERT: No data from machine (Environment)" << endl;
                break;
            case 0x01:
                cout << "ALERT: Controller board failure (Machine)" << endl;
                break;
            case 0x02:
                cout << "ALERT: Configuration data corrupted (Machine)" << endl;
                break;
            default:
                cout << "ALERT: Unknown self-test code (Machine)" << endl;
        }
    }
};

// Central class that delegates to specific monitors
class CNCMachineMonitor {
private:
    TemperatureMonitor tempMonitor;
    DimensionMonitor dimMonitor;
    OperationMonitor opMonitor;
    SelfTestReporter testReporter;

public:
    void process(float temperature, float variation, int minutes, int code) {
        tempMonitor.update(temperature);
        dimMonitor.update(variation);
        opMonitor.update(minutes);
        testReporter.report(code);
    }
};

int main() {
    CNCMachineMonitor monitor;
    ifstream infile("cnc_data.txt");

    if (!infile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    float temp, variation;
    int minutes, selfTest;

    while (infile >> temp >> variation >> minutes >> hex >> selfTest) {
        monitor.process(temp, variation, minutes, selfTest);
        cout << "---" << endl;
    }

    infile.close();
    return 0;
}
