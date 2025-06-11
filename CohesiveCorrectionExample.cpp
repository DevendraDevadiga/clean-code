
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class TemperatureMonitor {
public:
    void updateTemperature(float valueCelsius) {
        if (valueCelsius > 35.0) {
            cout << "ALERT: High temperature detected (Environment)" << endl;
        }
    }
};


class DimentionMonitor {
public:
    void updateDimensionVariation(float variationMM) {
        if (variationMM > 0.05) {
            cout << "ALERT: Part-dimension variation too high (Machine)" << endl;
        }
    }
};


class ContinousOperationMonitor {
public:
    void updateContinuousOperation(int minutes) {
        if (minutes > 360) {
            cout << "ALERT: Continuous operation exceeded 6 hours (Machine)" << endl;
        }
    }
};


class SelfTestCodeReporter {
public:
    void checkSelfTestCode(int code) {
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

class CNCMachineMonitor {
private:
    TemperatureMonitor tempMonitor;
    DimensionMonitor dimMonitor;
    OperationMonitor opMonitor;
    SelfTestReporter testReporter;
public:
    void process(float temperature, float variation, int minutes, int code) {
        tempMonitor.updateTemperature(temperature);
        dimMonitor.updateDimensionVariation(variation);
        opMonitor.updateContinuousOperation(minutes);
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

/*
Example input file (cnc_data.txt):
38.5 0.06 400 0x01
34.0 0.03 200 0xFF
36.0 0.04 300 0x00
*/
