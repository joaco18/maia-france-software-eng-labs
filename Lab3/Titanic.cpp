#include "Titanic.h"
#include <math.h> 

Titanic::Titanic(string pathTitanic){
    string rawPassager;
    ifstream fileTitanic(pathTitanic);
    if (fileTitanic.is_open()){
        getline(fileTitanic, rawPassager);
        while ( getline (fileTitanic,rawPassager) ){
            Passager passager1 = createPassager(rawPassager);
            this->passagers.push_back(passager1);
        }
        fileTitanic.close();
    }
    else 
        cout << "Unable to read titanic file"; 
        fileTitanic.close();
}

Passager Titanic::createPassager(string rawPassager){
    string dataPassager[8] = {};
    split(rawPassager, ',', dataPassager);
    Passager passager(
        (dataPassager[0][0] == '1'),
        stoi(dataPassager[1]),
        dataPassager[2],
        dataPassager[3],
        stoi(dataPassager[4]),
        stoi(dataPassager[5]),
        stoi(dataPassager[6]),
        stof(dataPassager[7]));
    return passager;
}

void Titanic::split(string text, char separator, string *strings){  
    int currIndex = 0, i = 0, startIndex = 0, endIndex = 0;
    while (i <= text.length()){  
        if (text[i] == separator || i == text.length()){  
            endIndex = i;
            string subStr = "";  
            subStr.append(text, startIndex, endIndex - startIndex);  
            strings[currIndex] = subStr;
            startIndex = endIndex + 1;
            currIndex++;
        }  
        i++;  
    }
}

void Titanic::printPassager(){
    for (Passager p: this->passagers){
        cout << "Passager " << p.getSex() << endl;
    }
}

void Titanic::printOnePassager(int index){
    Passager p =  this->passagers[index];
    cout << "Passager Atributes: " << endl ;
    cout << "\t Survived: " << p.getSurvived() << endl;
    cout << "\t Class: " << p.getPassagerClass() << endl;
    cout << "\t Name : " << p.getName() << endl;
    cout << "\t Sex: " << p.getSex() << endl;
    cout << "\t Age: " << p.getAge() << endl;
    cout << "\t Siblings: " << p.getSiblings() << endl;
    cout << "\t Children: " << p.getChildren() << endl;
    cout << "\t Ticket Fee: " << p.getPaid() << endl;
}

void Titanic::printContingencyMatrix(){
    // Prints a 2D array nicely.
    string rowNames[3] = {"survived", "not-survived", "total    "};
    string columnNames[8] = {
        "           ", "male_c1", "male_c2", "male_c3",
        "fem_c1", "fem_c2", "fem_c3", "total"
    };
    for(int j=0; j < 8; j++){
        cout << columnNames[j] << "\t";
    }
    cout << endl;
    for(int i=0; i < 3; i++){
        cout << rowNames[i] << "\t";
        for(int j=0; j < 7; j++){
            cout << contingency[i][j] << "\t";
        }
        cout << endl;
    }
}

void Titanic::createContingencyTable(){
    // contigency:
    //              |male_c1|male_c2|male_c3|female_c1|female_c2|female_c3|total
    // suvived      |_______|_______|_______|_________|_________|_________|_____
    // not_survived |_______|_______|_______|_________|_________|_________|_____
    // total        |_______|_______|_______|_________|_________|_________|_____
    //
    for (Passager p: this->passagers){
        if (!(p.getSex()).compare("male")){
            switch (p.getPassagerClass()){
                case 1:
                    this->contingency[2][0]++;
                    if (p.getSurvived()) this->contingency[0][0]++;
                case 2:
                    this->contingency[2][1]++;
                    if (p.getSurvived()) this->contingency[0][1]++;
                case 3:
                    this->contingency[2][2]++;
                    if (p.getSurvived()) this->contingency[0][2]++;
                }
        }
        else{
            switch (p.getPassagerClass()){
                case 1:
                    this->contingency[2][3]++;
                    if (p.getSurvived()) this->contingency[0][3]++;
                case 2:
                    this->contingency[2][4]++;
                    if (p.getSurvived()) this->contingency[0][4]++;
                case 3:
                    this->contingency[2][5]++;
                    if (p.getSurvived()) this->contingency[0][5]++;
            }
        }
    }
    for (int i=0; i<6; i++){
        this->contingency[1][i] = this->contingency[2][i] - this->contingency[0][i];
        this->contingency[0][6] += this->contingency[0][i];
        this->contingency[1][6] += this->contingency[1][i];
        this->contingency[2][6] += this->contingency[2][i];
    }
}

float Titanic::survivalGivenSexClass(string passSex, int passClass, bool survived){
    int sex = (passSex.compare("male")==0 ? 0 : 3);
    passClass--;
    int column = sex + passClass;
    int row = (survived ? 0 : 1);
    float num = static_cast< float >(this->contingency[row][column]);
    float den = static_cast< float >(this->contingency[2][column]);
    return num/den;
}

float Titanic::survivalGivenAgeClassFrequentist(int passAge, int passClass, bool survived){
    float less10Survived, less10 = 0; 
    for (Passager p: this->passagers){
        if ((p.getAge() <= passAge) && (p.getPassagerClass() == passClass)){
            if (p.getSurvived()){
                less10Survived++;
            }
            less10++;
        }
    }
    return less10Survived/less10;
}


float Titanic::survivalGivenAgeClassBayesian(int passAge, int passClass, bool survived){
    // Given a uniform (not informative) prior:
    float alpha, beta = 1;
    for (Passager p: this->passagers){
        if ((p.getAge() <= passAge) && (p.getPassagerClass() == passClass)){
            alpha += static_cast< float > (p.getSurvived());
            beta = beta - static_cast< float > (p.getSurvived()) + 1;
        }
    }
    return alpha / (alpha + beta);
}

void Titanic::histogram(vector<float> fares,
                        vector<float> &fareHistoProbs,
                        vector<float> &fareHistoVals){
    sort(fares.begin(), fares.end());
    float arrSize = static_cast<float> (fares.size());
    int histIndex = 0;
    int i=0;
    while (i<arrSize){
        float counter = 1.;
        for (int j=1; j<arrSize; j++){
            if (fares[i+j] == fares[i]){
                counter++;
            }
        }
        i += static_cast<int> (counter);
        // don't consider outliers
        if ((0.5<fares[i]) && (fares[i]<100)){
            fareHistoProbs.push_back(counter/arrSize);
            fareHistoVals.push_back(fares[i]);
            histIndex++;
        }
    }
}

float Titanic::expectation(int passClass){
    vector<float> fares={};
    vector<float> fareHistoProbs={};
    vector<float> fareHistoVals={};
    for (Passager p: this->passagers){
        if (p.getPassagerClass() == passClass){
            fares.push_back(p.getPaid());
        }
    }
    histogram(fares, fareHistoProbs, fareHistoVals);
    float faresExpectation = 0.;
    for (int i=0; i<fareHistoVals.size(); i++){
        faresExpectation += fareHistoVals[i] * fareHistoProbs[i];
    }

    return faresExpectation;
}
