#include "FibLFSR.hpp"

int main(){

    string seed("1011010000000000");
    FibLFSR A(seed);
    cout << A << endl;
    cout << "Step result : " << A.step() << endl;
    cout << A << endl;
    cout << "Step result : " << A.step() << endl;
    cout << A << endl;

    FibLFSR abc("1100011011000011");

    for(int i = 0; i < 7; i++) cout << abc.generate(5) << endl;


    return 0;
}
