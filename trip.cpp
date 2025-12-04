#include <iostream>
#include <cstring>
#include <cstdlib>
#include "trip.h"

using namespace std;

int currentId = 1;

double safeInputDouble() {
    double value;
    while (true) {
        if (cin >> value) {
            cin.ignore(); 
            return value;
        } else {
            cout << "Ошибка: Введите число: ";
            cin.clear(); 
            cin.ignore(1000, '\n'); 
        }
    }
}

bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

bool isAllDigits(const char* str, int len) {
    for (int i = 0; i < len; i++) {
        if (!isDigit(str[i])) return false;
    }
    return true;
}

bool checkMonth(int month) {
    return (month >= 1 && month <= 12);
}

bool checkDayForMonth(int day, int month, int year) {
    if (day < 1 || day > 31) return false;
    
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeap && day > 29) return false;
        if (!isLeap && day > 28) return false;
    }
    
    return true;
}

bool checkDate(char* date) {
    if (strlen(date) != 10) {
        cout << "Ошибка: Должно быть 10 символов (ДД.ММ.ГГГГ)" << endl;
        return false;
    }
    
    if (date[2] != '.' || date[5] != '.') {
        cout << "Ошибка: Формат ДД.ММ.ГГГГ" << endl;
        return false;
    }
    
    char dayStr[3] = {date[0], date[1], '\0'};
    char monthStr[3] = {date[3], date[4], '\0'};
    char yearStr[5] = {date[6], date[7], date[8], date[9], '\0'};
    
    if (!isAllDigits(dayStr, 2) || !isAllDigits(monthStr, 2) || !isAllDigits(yearStr, 4)) {
        cout << "Ошибка: Только цифры" << endl;
        return false;
    }



    int day = atoi(dayStr);
    int month = atoi(monthStr);
    int year = atoi(yearStr);
    
    if (year < 2020 || year > 2030) {
        cout << "Ошибка: Год 2020-2030" << endl;
        return false;
    }
    
    if (!checkMonth(month)) {
        cout << "Ошибка: Месяц 01-12" << endl;
        return false;
    }
    
    if (!checkDayForMonth(day, month, year)) {
        cout << "Ошибка: Неправильный день" << endl;
        return false;
    }
    
    return true;
}
bool checkFIO(char* fio) {
    int len = strlen(fio);
    if (len < 5 || len > 60) {
        cout << "Ошибка: 5-60 символов" << endl;
        return false;
    }
    
    bool hasSpace = false;
    for (int i = 0; i < len; i++) {
        if (fio[i] == ' ') {
            hasSpace = true;
            break;
        }
    }
    
    if (!hasSpace) {
        cout << "Ошибка: Введите Фамилию Имя" << endl;
        return false;
    }
    
    return true;
}

bool checkMoney(double money) {
    if (money < 0.0 || money > 100000.0) {
        cout << "Ошибка: 0-100000" << endl;
        return false;
    }
    return true;
}


bool checkDatesOrder(char* departure, char* returnDate) {
    for (int i = 6; i <= 9; i++) {
        if (returnDate[i] < departure[i]) {
            cout << "Ошибка: Возвращение раньше выезда" << endl;
            return false;
        }
        if (returnDate[i] > departure[i]) {
            return true;
        }
    }
    

    for (int i = 3; i <= 4; i++) {
        if (returnDate[i] < departure[i]) {
            cout << "Ошибка: Возвращение раньше выезда" << endl;
            return false;
        }
        if (returnDate[i] > departure[i]) {
            return true;
        }
    }

    for (int i = 0; i <= 1; i++) {
        if (returnDate[i] < departure[i]) {
            cout << "Ошибка: Возвращение раньше выезда" << endl;
            return false;
        }
        if (returnDate[i] > departure[i]) {
            return true;
        }
    }
    
    return true; 
}

void copyString(char* &dest, const char* source) {
    if (dest != nullptr) {
        delete[] dest;
    }
    
    int len = strlen(source);
    dest = new char[len + 1];
    strcpy(dest, source);
}

Trip* addTrip(Trip* head) {
    Trip* newTrip = new Trip;
    
    newTrip->fio = nullptr;
    newTrip->departureDate = nullptr;
    newTrip->returnDate = nullptr;
    newTrip->destination = nullptr;
    newTrip->purpose = nullptr;
    newTrip->next = nullptr;
    
    cout << "\nНовая командировка:" << endl;
    
    char buffer[100];
    char departureBuffer[20];
    char returnBuffer[20];
    
    do {
        cout << "ФИО (5-60 букв, через пробел): ";
        cin.getline(buffer, 100);
    } while (!checkFIO(buffer));
    copyString(newTrip->fio, buffer);
    
    do {
        cout << "Дата выезда (ДД.ММ.ГГГГ, 2020-2030): ";
        cin.getline(departureBuffer, 20);
    } while (!checkDate(departureBuffer));
    
    bool datesOk = false;
    do {
        cout << "Дата возвращения (ДД.ММ.ГГГГ, 2020-2030): ";
        cin.getline(returnBuffer, 20);
        
        if (checkDate(returnBuffer)) {
            if (checkDatesOrder(departureBuffer, returnBuffer)) {
                datesOk = true;
            }
        }
    } while (!datesOk);
    
    copyString(newTrip->departureDate, departureBuffer);
    copyString(newTrip->returnDate, returnBuffer);
    
    do {
        cout << "Место назначения: ";
        cin.getline(buffer, 100);
        if (strlen(buffer) == 0) {
            cout << "Ошибка: Не может быть пустым" << endl;
        }
    } while (strlen(buffer) == 0);
    copyString(newTrip->destination, buffer);

    do {
        cout << "Цель поездки: ";
        cin.getline(buffer, 100);
        if (strlen(buffer) == 0) {
            cout << "Ошибка: Не может быть пустым" << endl;
        }
    } while (strlen(buffer) == 0);
    copyString(newTrip->purpose, buffer);
    
    do {
        cout << "Суточные (0-100000): ";
        newTrip->dailyAllowance = safeInputDouble();
        
        if (!checkMoney(newTrip->dailyAllowance)) {
            cout << "Ошибка: Должно быть 0-100000" << endl;
        }
    } while (!checkMoney(newTrip->dailyAllowance));
    
    newTrip->id = currentId;
    currentId++;
    
    cout << "Запись №" << newTrip->id << " добавлена" << endl;

    if (head == nullptr) {
        return newTrip;
    }
    

    Trip* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    

    temp->next = newTrip;
    return head;
}

void printAll(Trip* head) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }
    
    cout << "\n=== ВСЕ КОМАНДИРОВКИ ===" << endl;
    
    Trip* current = head;
    int count = 0;
    
    while (current != nullptr) {
        // Первая строка: ID и ФИО
        cout << "ID: " << current->id << " | " << current->fio << endl;
        
        // Вторая строка: всё остальное
        cout << "   Даты: " << current->departureDate << " - " << current->returnDate;
        cout << " | Куда: " << current->destination;
        cout << " | Деньги: " << current->dailyAllowance << " руб." << endl;
        
        cout << "   Цель: " << current->purpose << endl;
        cout << "   ---" << endl;
        
        current = current->next;
        count++;
    }
    
    cout << "\nВсего записей: " << count << endl;
}
void findTrip(Trip* head) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }
    
    char name[100];
    cout << "Введите ФИО для поиска: ";
    cin.getline(name, 100);
    
    Trip* current = head;
    int found = 0;
    int comparisons = 0;
    
    cout << "\nРезультаты поиска \"" << name << "\":" << endl;
    
    while (current != nullptr) {
        comparisons++;
        
        if (strcmp(current->fio, name) == 0) {
            cout << "\nНайдено:" << endl;
            cout << "ID: " << current->id << endl;
            cout << "ФИО: " << current->fio << endl;
            cout << "Даты: " << current->departureDate << " - " << current->returnDate << endl;
            cout << "Куда: " << current->destination << endl;
            cout << "Цель: " << current->purpose << endl;
            cout << "Суточные: " << current->dailyAllowance << endl;
            found++;
        }
        
        current = current->next;
    }
    
    cout << "\nНайдено записей: " << found << endl;
    cout << "Сравнений: " << comparisons << endl;
}


Trip* deleteTrip(Trip* head) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return head;
    }
    
    char name[100];
    cout << "Введите ФИО для удаления: ";
    cin.getline(name, 100);
    
    if (strcmp(head->fio, name) == 0) {
        Trip* toDelete = head;
        head = head->next;
        
        cout << "Удалена запись id " << toDelete->id << endl;
        
        delete[] toDelete->fio;
        delete[] toDelete->departureDate;
        delete[] toDelete->returnDate;
        delete[] toDelete->destination;
        delete[] toDelete->purpose;
        delete toDelete;
        
        return head;
    }
    

    Trip* current = head;
    while (current->next != nullptr) {
        if (strcmp(current->next->fio, name) == 0) {
            Trip* toDelete = current->next;
            current->next = toDelete->next;
            
            cout << "Удалена запись id " << toDelete->id << endl;
            
            delete[] toDelete->fio;
            delete[] toDelete->departureDate;
            delete[] toDelete->returnDate;
            delete[] toDelete->destination;
            delete[] toDelete->purpose;
            delete toDelete;
            
            return head;
        }
        current = current->next;
    }
    
    cout << "Запись не найдена" << endl;
    return head;
}

void sortByFIO(Trip* head) {
    if (head == nullptr || head->next == nullptr) {
        cout << "Нечего сортировать" << endl;
        return;
    }
    
    bool swapped;
    do {
        swapped = false;
        Trip* current = head;
        
        while (current->next != nullptr) {
            if (strcmp(current->fio, current->next->fio) > 0) {
                char* temp;
                double tempMoney;
                int tempId;
                
                temp = current->fio;
                current->fio = current->next->fio;
                current->next->fio = temp;

                temp = current->departureDate;
                current->departureDate = current->next->departureDate;
                current->next->departureDate = temp;
                
                temp = current->returnDate;
                current->returnDate = current->next->returnDate;
                current->next->returnDate = temp;
                
                temp = current->destination;
                current->destination = current->next->destination;
                current->next->destination = temp;
                
                temp = current->purpose;
                current->purpose = current->next->purpose;
                current->next->purpose = temp;

                tempMoney = current->dailyAllowance;
                current->dailyAllowance = current->next->dailyAllowance;
                current->next->dailyAllowance = tempMoney;
                
                tempId = current->id;
                current->id = current->next->id;
                current->next->id = tempId;
                
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
    
    cout << "Список отсортирован по ФИО" << endl;
}


void clearMemory(Trip* head) {
    Trip* current = head;
    
    while (current != nullptr) {
        Trip* nextOne = current->next;
        
        delete[] current->fio;
        delete[] current->departureDate;
        delete[] current->returnDate;
        delete[] current->destination;
        delete[] current->purpose;
        
        delete current;
        
        current = nextOne;
    }
    
    cout << "Память очищена" << endl;
}
