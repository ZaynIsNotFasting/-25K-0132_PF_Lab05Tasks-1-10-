#include "iostream"
using namespace std;

class Radio {
    private:
    int volume;
    float frequency;
    public:
    
    void setVolume(int v)
    {
        volume = v;
    }

    void setFrequency(float f)
    {
        frequency = f;
    }

    void  displayStatus(){
        cout<<"Volume: "<<volume<<endl<<"Frequency: "<<frequency<<endl;
    }
};

int main(){
    Radio r;
    r.setVolume(10);
    r.setFrequency(100.23);
    r.displayStatus();
    return 0;
}