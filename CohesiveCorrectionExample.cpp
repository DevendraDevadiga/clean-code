
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class TemperatureMonitor {
private:
    float temperature;
public:
    void updateTemperature(float valueCelsius) {
        temperature = valueCelsius;
        if (temperature > 35.0) {
            cout << "ALERT: High temperature detected (Environment)" << endl;
        }
    }
};


class DimentionMonitor {
private:
    float dimensionVariation;

public:
    void updateDimensionVariation(float variationMM) {
        dimensionVariation = variationMM;
        if (dimensionVariation > 0.05) {
            cout << "ALERT: Part-dimension variation too high (Machine)" << endl;
        }
    }
};


class ContinousOperationMonitor {
private:
    int continuousOperationMinutes;

public:
    void updateContinuousOperation(int minutes) {
        continuousOperationMinutes = minutes;
        if (continuousOperationMinutes > 360) {
            cout << "ALERT: Continuous operation exceeded 6 hours (Machine)" << endl;
        }
    }
};


class SelfTestCodeReporter {
private:
    int selfTestCode;

public:
    void checkSelfTestCode(int code) {
        selfTestCode = code;
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
public:

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
        monitor.updateTemperature(temp);
        monitor.updateDimensionVariation(variation);
        monitor.updateContinuousOperation(minutes);
        monitor.checkSelfTestCode(selfTest);
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
