#include "iostream"
using namespace std;

class Rupee{
    private:
        long value;
    public:
        Rupee(long value = 0) : value(value){}
        Rupee operator +(const Rupee& R){
            return Rupee(value + R.value);
        }
        Rupee operator ==(const Rupee& R){
            return value == R.value;
        }

        friend ostream& operator <<(ostream& os, const Rupee& R);
};

ostream& operator <<(ostream& os, const Rupee& R){
    os<<" "<<R.value<<endl;
    return os;
}

int main(){
    Rupee R(483232200);
    cout<<"Addition: "<<endl;
    Rupee R2(12222222);
    Rupee R3 = R + R2;
    cout<<"Sum of R3: Rs."<<R3;
    cout<<endl;
    
    cout<<"Comparison: "<<endl;
    Rupee R4(483232200);
    Rupee R5 = R == R4;
    cout<<"Comparing R with R4: "<<R5<<endl;
    cout<<"R5 is equal to R1: "<<R5;
    
    cout<<endl;
    cout<<"Printing: "<<endl;
    cout<<R3;
    cout<<R5;
   
    return 0;


}