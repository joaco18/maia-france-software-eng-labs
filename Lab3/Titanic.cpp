#include "Titanic.h"

Titanic::Titanic(string pathTitanic){
  
    string rawPassager;
    ifstream fileTitanic (pathTitanic);
    if (fileTitanic.is_open()){
        getline(fileTitanic, rawPassager);
        while ( getline (fileTitanic,rawPassager) ){
            cout << "recibe linea" << endl;
            Passager passager1 = createPassager(rawPassager);
            cout << "crea pasajero" << endl;
            this->passagers.push_back(passager1);
            cout << "adiciona pasajero" << endl;
        }
        fileTitanic.close();
    }

    else cout << "Unable to read titanic file"; 

    fileTitanic.close();

}

Passager Titanic::createPassager(string rawPassager){
    string dataPassager[5] = {};
    //cout << "antes split" << endl;
    split(rawPassager, ',', dataPassager);
    //cout << "despues split" << endl;
    cout << dataPassager[0] << endl;
    cout << dataPassager[1] << endl;
    cout << dataPassager[2] << endl;
    cout << dataPassager[3] << endl;
    cout << dataPassager[4] << endl;
    cout << dataPassager[5] << endl;
    cout << dataPassager[6] << endl;
    cout << stof(dataPassager[7]) << endl;
    Passager passager((dataPassager[0][0] == '1'),
                       stoi(dataPassager[1]),
                       dataPassager[2],
                       dataPassager[3],
                       stoi(dataPassager[4]),
                       stoi(dataPassager[5]),
                       stoi(dataPassager[6]),
                       stof(dataPassager[7]));
    return passager;
}

void Titanic::split(string str, char separator, string *strings) {  
    int currIndex = 0, i = 0, startIndex = 0, endIndex = 0;
      
    while (i <= str.length()){  
        //cout << "split dentro while" << endl;
        if (str[i] == separator || i == str.length()){  
            //cout << "split dentro while dentro if" << endl;
            endIndex = i;  
            string subStr = "";  
            subStr.append(str, startIndex, endIndex - startIndex);  
            strings[currIndex] = subStr;  
            currIndex += 1;  
            startIndex = endIndex + 1;  
            cout << subStr << endl;
        }  
        i++;  
    }     
}  

void Titanic::printPassager(){
    cout << "holi " << endl;
    //for (Passager p: this->passagers){
        //cout << "Passager " << p.getName() << endl;
    //}
}