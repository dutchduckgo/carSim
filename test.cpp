#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vl vector<ll>
#define fl float


struct Car {
    string model;
    fl chargingTime; //write funciton for charging time per car
    int startTime;
    fl EC;
    fl carbon;
    
}; 
vector<Car> cars;
int totalCars = 1000;

vector<fl> privAT;
int totalAT = 96;
int main() {
    cars.resize(totalCars);
    privAT.resize(totalAT);
    std::ifstream carData ("carData.in");
    for (int i = 0; i < totalCars; i ++) {
        carData >> cars[i].model; 
    }
    carData.close();

    std::ofstream output ("carData.out");
    for (int i = 0; i < totalCars; i ++) {
        output << cars[i].model;
    }
    output.close();

}