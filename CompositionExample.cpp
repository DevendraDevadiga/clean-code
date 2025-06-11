#include <iostream>
using namespace std;

class TemperatureMonitor {
    float temperature;
public:
    void updateTemperature(float valueCelsius) {
        temperature = valueCelsius;
        if (temperature > 35.0)
            cout << "ALERT: High temperature detected\n";
    }
    ~TemperatureMonitor() {
        cout << "TemperatureMonitor destroyed\n";
    }
};

class DimentionVariationMonitor {
    float dimensionVariation;
public:
    void updateDimensionVariation(float variationMM) {
        dimensionVariation = variationMM;
        if (dimensionVariation > 0.05)
            cout << "ALERT: Dimension variation too high\n";
    }
    ~DimentionVariationMonitor() {
        cout << "DimentionVariationMonitor destroyed\n";
    }
};

class OperationMonitor {
    int continuousOperationMinutes;
public:
    void updateContinuousOperation(int minutes) {
        continuousOperationMinutes = minutes;
        if (continuousOperationMinutes > 360)
            cout << "ALERT: Operation exceeded 6 hours\n";
    }
    ~OperationMonitor() {
        cout << "OperationMonitor destroyed\n";
    }
};

class SelfTestReporter {
    int selfTestCode;
public:
    void checkSelfTestCode(int code) {
        selfTestCode = code;
        switch (code) {
            case 0xFF: cout << "Self-test OK\n"; break;
            case 0x00: cout << "ALERT: No data from machine\n"; break;
            case 0x01: cout << "ALERT: Controller failure\n"; break;
            default:   cout << "ALERT: Unknown self-test code\n"; break;
        }
    }
    ~SelfTestReporter() {
        cout << "SelfTestReporter destroyed\n";
    }
};

class CNCMachineMonitor {
    TemperatureMonitor tempMonitor;
    DimentionVariationMonitor dimMonitor;
    OperationMonitor opMonitor;
    SelfTestReporter testReporter;

public:
    void monitor(float temp, float dimVar, int mins, int code) {
        tempMonitor.updateTemperature(temp);
        dimMonitor.updateDimensionVariation(dimVar);
        opMonitor.updateContinuousOperation(mins);
        testReporter.checkSelfTestCode(code);
    }

    ~CNCMachineMonitor() {
        cout << "CNCMachineMonitor destroyed\n";
    }
};

int main() {
    {
        CNCMachineMonitor monitor;
        monitor.monitor(38.0, 0.06, 400, 0x01);
    } // end of scope: destructor calls happen here

    return 0;
}
