#ifndef TRIP_H
#define TRIP_H


struct Trip {
    char* fio;        
    char* departureDate; 
    char* returnDate;    
    char* destination;   
    char* purpose;       
    double dailyAllowance;
    int id;              
    Trip* next;          
};


Trip* addTrip(Trip* head);
void printAll(Trip* head);  
void findTrip(Trip* head);
Trip* deleteTrip(Trip* head);
void sortByFIO(Trip* head);  
void clearMemory(Trip* head);


bool checkDate(char* date);     
bool checkFIO(char* fio);        
bool checkMoney(double money);   
#endif