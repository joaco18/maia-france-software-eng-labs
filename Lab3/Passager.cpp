
#include "Passager.h"

Passager::Passager(bool isurvived, int ipassagerClass, string iname, string isex,  int iage, int isiblings, int ichildren, float ipaid){ 
    this->survived = isurvived;
    this->passagerClass = ipassagerClass;
    this->name = iname;
    this->sex = isex;
    this->age = iage;
    this->siblings = isiblings;
    this->children = ichildren;
    this->paid = ipaid;
}

bool Passager::getSurvived(){
    return this->survived;
}

int Passager::getAge(){
    return this->age;
}

int Passager::getPassagerClass(){
    return this->passagerClass;
}

string Passager::getSex(){
    return this->sex;
}

float Passager::getPaid(){
    return this->paid;
}

string Passager::getName(){
    return this->name;
}

int Passager::getSiblings(){
    return this->siblings;
}

int Passager::getChildren(){
    return this->children;
}
