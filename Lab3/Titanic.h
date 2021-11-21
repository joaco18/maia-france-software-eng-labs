#ifndef TITANIC_H
#define TITANIC_H

#include "Passager.h"
#include <bits/stdc++.h>
#include <fstream>
#include <cstring>

using namespace std;

class Titanic{
    private:
        void split(string str, char separator, string *strings);
        int contingency[3][7]={};
        vector<Passager> passagers;
    public:
        Titanic(string pathTitanic);
        Passager createPassager(string rawPassager);
        void createContingencyTable();
        void printPassager();
        void printOnePassager(int index);
        void printContingencyMatrix();
        float survivalGivenSexClass(string passSex, int passClass, bool survived);
        float survivalGivenAgeClassFrequentist(int passAge, int passClass, bool survived);
        float survivalGivenAgeClassBayesian(int passAge, int passClass, bool survived);
        float expectation(int passClass);
};

#endif