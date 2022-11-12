#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vl vector<ll>
#define fl double

struct Car {
    string model;
    fl chargingRate; 
    fl battery;
}; 

vector<Car> cars;
int totalCars = 1000;

vector<fl> MOER;

vector<fl> weekdayPri;
vector<fl> weekdayPub;
vector<fl> workplace;
vector<fl> weekendPri;
vector<fl> weekendPub;
int n = 96;

vector<vector<fl>> week;

fl sim(int day, fl min15, fl activeCars) {
    fl CE = 0; //carbon emission = MOER * charging rate
    int numCars = ceil(activeCars * totalCars);
    for (int i = 0; i < numCars; i ++) {
        int randCar = rand()%(totalCars);
        fl battery;
        battery = (cars[randCar].battery + min15 > 96) ? cars[randCar].battery - min15 : cars[randCar].battery; //6 * 15min = 90 min
        fl carCE;
        for (int j = min15; j < battery; j ++) { //ie 5 hours to charge
            carCE = (cars[randCar].chargingRate * MOER[j]) / 1000;  //MOER data is every 5 mins so 5 * 3 = 15 min
            
            CE += carCE; //lbs CO2
            //cout << CE << '\t';
            week[day][j] += carCE; 
            cout << week[day][j] << '\t';
        }
    }
    return CE; 
}

int main() {
    cars.resize(totalCars);
    MOER.resize(n);
    weekdayPri.resize(n);
    weekdayPub.resize(n);
    weekendPri.resize(n);
    weekendPub.resize(n);
    workplace.resize(n);
    week.resize(7, vector<fl>(n)); //7 days, 96 * 15 min intervals

    ifstream input1 ("carData.in");
    for (int i = 0; i < totalCars; i ++) {
        input1 >> cars[i].model; 
    }
        

    input1.close();

    ifstream input2 ("battery.in");
    for (int i = 0; i < totalCars; i ++) 
        input2 >> cars[i].battery; 
    input2.close();

    ifstream input3 ("chargingRate.in");
    for (int i = 0; i < totalCars; i ++) 
        input3 >> cars[i].chargingRate; 
    input3.close();

    ifstream input4 ("MOER.in");
    for (int i = 0; i < n; i ++) 
        input4 >> MOER[i]; 
    input4.close();

    ifstream input5 ("pubATDay.in");
    for (int i = 0; i < totalCars; i ++) 
        input5 >> weekdayPub[i]; 
    input5.close();

    ifstream input6 ("priATDay.in");
    for (int i = 0; i < totalCars; i ++) 
        input6 >> weekdayPri[i]; 
    input6.close();

    ifstream input7 ("workplace.in");
    for (int i = 0; i < totalCars; i ++) 
        input7 >> weekendPri[i]; 
    input7.close();

    ifstream input8 ("pubATEnd.in");
    for (int i = 0; i < totalCars; i ++) 
        input8 >> weekendPub[i]; 
    input8.close();

    ifstream input9 ("priATEnd.in");
    for (int i = 0; i < totalCars; i ++) 
        input9 >> weekendPri[i]; 
    input9.close();

    ofstream output("carData.out");
    fl CE = 0;

    for (int day = 0; day < 7; day ++) { //weekday
        if (day < 5) { //weekday
            for (fl min15 = 0; min15 < n; min15 ++) { //0 - 96
                CE += sim (day, min15, weekdayPri[min15]);
                CE += sim (day, min15, weekdayPub[min15]);
                CE += sim (day, min15, workplace[min15]);
                output << week[day][min15] << " ";
            }
        }
        else { //weekend
            for (fl min15 = 0; min15 < n; min15 ++) { //15 min increment
                CE += sim (day, min15, weekendPri[min15]);
                CE += sim (day, min15, weekendPub[min15]);
                output << week[day][min15] << " ";
            }
        }
        
        output << endl;
    }
    output << endl << CE;
    output.close();
}
