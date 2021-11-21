#ifndef PASSAGER_H
#define PASSAGER_H

#include <iostream>
#include <string>

using namespace std;

class Passager{
    private:
        bool survived;
        int passagerClass;
        string name;
        string sex;
        int age;
        int siblings;
        int children;
        float paid;
    
    public:
        Passager(bool isurvived, int ipassagerClass, string iname, string isex, int age, int isiblings, int ichildren, float ipaid);
        bool getSurvived();
        int getAge();
        int getPassagerClass();
        string getSex();
        float getPaid();
        string getName();
        int getSiblings();
        int getChildren();
};

#endif