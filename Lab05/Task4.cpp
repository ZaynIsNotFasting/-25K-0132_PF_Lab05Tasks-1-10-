#include "iostream"
using namespace std;

class  Device{
    private:
        string deviceName;
        string brand;
    public:
        Device(string deviceName, string brand) : deviceName(deviceName), brand(brand) {}
        void displayDevice(){
            cout<<"Device Name: "<<deviceName<<endl;
            cout<<"Brand: "<<brand<<endl;
        }
};

class Connectivity{
    private:
        bool wifiStatus;
        bool bluetoothStatus;
    public:
        Connectivity(bool wifiStatus, bool bluetoothStatus) : wifiStatus(wifiStatus), bluetoothStatus(bluetoothStatus) {}
        void displayConnect(){
            cout<<"Wifi Status: "<<wifiStatus<<endl;
            cout<<"Bluetooth Status: "<<bluetoothStatus<<endl;
        }
};

class SmartWatch : public Device, public Connectivity {
    private:
        int heartRate;
        int stepCount;
    public:
        SmartWatch(string deviceName, string brand, bool wifiStatus, bool bluetoothStatus, int heartRate, int stepCount) 
        : Device(deviceName, brand), Connectivity(wifiStatus, bluetoothStatus), heartRate(heartRate), stepCount(stepCount) {}

        void show(){
            displayDevice();
            displayConnect();
            cout<<"Heart Rate: "<<heartRate<<endl;
            cout<<"Step Count: "<<stepCount<<endl;
        }

};

int main(){
    SmartWatch SW("Stornmaker", "Sveston", true, false, 84, 13445);
    SW.show();
    return 0;
}