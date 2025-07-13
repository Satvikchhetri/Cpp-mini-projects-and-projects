#include<iostream>
#include<string.h>
using namespace std;

struct future {
    float age;
    char name[50];
    char rashi[25];
    char ratan[25];
    char day[25];
    char dhatu[25];
    char quantity[25];

    void enter() {
        cout << "\n==============================\n";
        cout << "        Future Calculator" << endl;
        cout << "==============================\n";
        cout << "For seeing your future, please provide the following details:\n";
        cout << "Enter your Age: ";
        cin >> age;
        cout << "Enter your Name: ";
        cin >> name;
        cout << "\nCalculating your future...\n\n";
    }

    void display() {
        cout << "Your rashi/horoscope is: " << rashi << endl;
        cout << "Your lucky day is: " << day << endl;
        cout << "Your lucky metal is: " << dhatu << endl;
        cout << "Your lucky gemstone is: " << ratan << endl;
        cout << "Your lucky gemstone weight: " << quantity << endl;
    }

    void getcalc();
};

void future::getcalc() {
    int x = strlen(name);
    for (int i = 0; i <= x; i++) {
        
        else {
            strcpy(rashi, "No details found !");
            strcpy(ratan, "No details found !");
            strcpy(day, "No details found !");
            strcpy(dhatu, "No details found !");
            strcpy(quantity, "No details found !");
        }
    }
}

int main() {
    int x = 1;
    while (x != 0) {
        future f;
        f.enter();
        f.getcalc();
        f.display();

        cout << "\n============================================\n";
        cout << ".... Press 0 to exit or any number to retry ....\n";
        cout << "============================================\n";
        cin >> x;
    }
    return 0;
}
