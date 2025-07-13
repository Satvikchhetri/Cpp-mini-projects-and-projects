#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;

class Hospital {
    int pid;
    char pname[50], fname[50], mname[50], hname[50];
    char ren[50], rer[50], gen[50];
    float age;
    char mob[50], status[50];

public:
    void input();
    void output() const;
    int getID() const { return pid; }
    void update();
};

void Hospital::input() {
    cout << "\nPlease enter the following details:\n";
    cout << "Patient ID: ";
    cin >> pid;
    cout << "Name: ";
    cin >> pname;
    cout << "Age: ";
    cin >> age;
    cout << "Gender: ";
    cin >> gen;
    cout << "Is the patient married? (yes/no): ";
    cin >> status;

    if (strcasecmp(gen, "female") == 0) {
        if (strcasecmp(status, "yes") == 0) {
            cout << "Husband's Name: ";
            cin >> hname;
        } else {
            cout << "Father's Name: ";
            cin >> fname;
            cout << "Mother's Name: ";
            cin >> mname;
        }
    } else {
        cout << "Father's Name: ";
        cin >> fname;
        cout << "Referred by (Name): ";
        cin >> ren;
        cout << "Referred by (Relation): ";
        cin >> rer;
        cout << "Mobile Number: ";
        cin >> mob;
    }
}

void Hospital::output() const {
    cout << "\n--- Patient Record ---\n";
    cout << "ID: " << pid << "\nName: " << pname << "\nAge: " << age << "\nGender: " << gen << "\nMarital Status: " << status << "\n";

    if (strcasecmp(gen, "female") == 0) {
        if (strcasecmp(status, "yes") == 0)
            cout << "Husband's Name: " << hname << endl;
        else {
            cout << "Father's Name: " << fname << "\nMother's Name: " << mname << endl;
        }
    } else {
        cout << "Father's Name: " << fname << "\nReferred By: " << ren << "\nRelation: " << rer << "\nMobile: " << mob << endl;
    }
}

void Hospital::update() {
    char choice[20], field[20], temp[50];
    cout << "Do you want to update this record? (yes/no): ";
    cin >> choice;

    if (strcasecmp(choice, "yes") == 0) {
        cout << "Which field do you want to update? (pname, fname, hname, mname, phone, status): ";
        cin >> field;

        cout << "Enter new value: ";
        cin >> temp;

        if (strcasecmp(field, "pname") == 0)
            strcpy(pname, temp);
        else if (strcasecmp(field, "fname") == 0)
            strcpy(fname, temp);
        else if (strcasecmp(field, "hname") == 0)
            strcpy(hname, temp);
        else if (strcasecmp(field, "mname") == 0)
            strcpy(mname, temp);
        else if (strcasecmp(field, "phone") == 0)
            strcpy(mob, temp);
        else if (strcasecmp(field, "status") == 0)
            strcpy(status, temp);
    }
}

Hospital h;

void add() {
    ofstream file("hospital.dat", ios::binary | ios::app);
    h.input();
    file.write((char*)&h, sizeof(h));
    file.close();
}

void show() {
    ifstream file("hospital.dat", ios::binary);
    while (file.read((char*)&h, sizeof(h)))
        h.output();
    file.close();
}

void search() {
    ifstream file("hospital.dat", ios::binary);
    int id;
    cout << "Enter patient ID to search: ";
    cin >> id;
    bool found = false;
    while (file.read((char*)&h, sizeof(h))) {
        if (h.getID() == id) {
            h.output();
            found = true;
        }
    }
    if (!found)
        cout << "Patient not found.\n";
    file.close();
}

void transpose() {
    ofstream temp("hos.dat", ios::binary);
    ifstream file("hospital.dat", ios::binary);
    int id1, id2;
    cout << "Enter ID range (start and end):\n";
    cin >> id1 >> id2;

    while (file.read((char*)&h, sizeof(h))) {
        if (h.getID() >= id1 && h.getID() <= id2)
            temp.write((char*)&h, sizeof(h));
    }
    file.close();
    temp.close();
}

void del() {
    ofstream temp("hos.dat", ios::binary);
    ifstream file("hospital.dat", ios::binary);
    int id;
    cout << "Enter patient ID to delete: ";
    cin >> id;

    while (file.read((char*)&h, sizeof(h))) {
        if (h.getID() != id)
            temp.write((char*)&h, sizeof(h));
    }
    file.close();
    temp.close();
    remove("hospital.dat");
    rename("hos.dat", "hospital.dat");
}

void shot() {
    ifstream file("hos.dat", ios::binary);
    while (file.read((char*)&h, sizeof(h)))
        h.output();
    file.close();
}

void erase() {
    char choice[10];
    cout << "Do you really want to erase all records? (yes/no): ";
    cin >> choice;
    if (strcasecmp(choice, "yes") == 0) {
        ofstream file("hospital.dat", ios::binary | ios::trunc);
        file.close();
        cout << "All records erased.\n";
    }
}

void modify() {
    fstream file("hospital.dat", ios::binary | ios::in | ios::out);
    int id;
    cout << "Enter patient ID to modify: ";
    cin >> id;

    while (file.read((char*)&h, sizeof(h))) {
        if (h.getID() == id) {
            h.update();
            file.seekp((int)file.tellg() - sizeof(h));
            file.write((char*)&h, sizeof(h));
            break;
        }
    }
    file.close();
}

int main() {
    char ch;
    do {
        cout << "\n--- Hospital Record System ---\n";
        cout << "1. Add Record\n";
        cout << "2. Display All Records\n";
        cout << "3. Search Record\n";
        cout << "4. Transpose Records (within ID range)\n";
        cout << "5. Show Transposed Records\n";
        cout << "6. Delete Record\n";
        cout << "7. Erase All Records\n";
        cout << "8. Modify Record\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch) {
            case '1': add(); break;
            case '2': show(); break;
            case '3': search(); break;
            case '4': transpose(); break;
            case '5': shot(); break;
            case '6': del(); break;
            case '7': erase(); break;
            case '8': modify(); break;
            case '9': exit(0);
            default: cout << "Invalid choice.\n";
        }
    } while (true);

    return 0;
}
