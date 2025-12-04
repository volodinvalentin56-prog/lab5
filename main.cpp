#include <iostream>
#include "trip.h"
#include "screens.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    
    Trip* head = nullptr;
    int choice;
    
    do {
        showMenu();
        cin >> choice;
        cin.ignore(); 
        
        switch (choice) {
            case 1: head = addTrip(head); break;
            case 2: printAll(head); break;
            case 3: findTrip(head); break;
            case 4: head = deleteTrip(head); break;
            case 5: sortByFIO(head); break; 
            case 0: cout << "Выход..." << endl; break;
            default: cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);
    
    clearMemory(head);
    return 0;
}