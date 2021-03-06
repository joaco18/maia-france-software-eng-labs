#include <iostream>
#include "Titanic.h"
#include <string>

using namespace std;

int main(){
    // Problem 1:
    // Read titanic.csv and generate vector of passagers.
    Titanic titanic("titanic.csv");
    // Show an example of passager.
    titanic.printOnePassager(5);
    
    //Problem 2: Get the desired conditional probabilities.
    cout << endl << "Given the computed contingency table: " << endl;
    cout << endl;

    titanic.createContingencyTable();
    titanic.printContingencyMatrix();
    
    cout << endl << "The requested probabilities are: " << endl;
    cout << endl;
    
    cout << "P(S= true | G=female,C=1): "
         << titanic.survivalGivenSexClass("female", 1, true) << endl;
    cout << "P(S= true | G=female,C=2): "
         << titanic.survivalGivenSexClass("female", 2, true) << endl;
    cout << "P(S= true | G=female,C=3): "
         << titanic.survivalGivenSexClass("female", 3, true) << endl;
    cout << "P(S= true | G=male,C=1): "
         << titanic.survivalGivenSexClass("male", 1, true) << endl;
    cout << "P(S= true | G=male,C=2): "
         << titanic.survivalGivenSexClass("male", 2, true) << endl;
    cout << "P(S= true | G=male,C=3): "
         << titanic.survivalGivenSexClass("male", 3, true) << endl;
    
    //Problem 3: Probability that a child who is in third class and
    //           is 10 years old or younger survives.
    // FREQUENTIST APROACH:
    cout << endl << "Not bayesian aproach to get the probability of being a "
         << "kid in 3rd class and survive:" << endl;
    cout << "P(S= true | A<=10,C=3): " 
         << titanic.survivalGivenAgeClassFrequentist(10, 3, true) << endl;
    // BAYESIAN APROACH:
    cout << endl << "Bayesian aproach to get the probability of being a "
         << "kid in 3rd class and survive:" << endl;
    cout << "P(S= true | A<=10,C=3): " 
         << titanic.survivalGivenAgeClassBayesian(10, 3, true) << endl;

    // Problem 4: How much did people pay to be on the ship? Calculate the 
    //            expectation of fare conditioned on passenger-class:

    cout << endl << "Fare expectation for first class:" << endl;
    cout << "E[X|C1]= " << titanic.expectation(1) << endl;
    cout << endl << "Fare expectation for second class:" << endl;
    cout << "E[X|C2]= " << titanic.expectation(2) << endl;
    cout << endl << "Fare expectation for third class:" << endl;
    cout << "E[X|C3]= " << titanic.expectation(3) << endl;
    cout << endl;

    return 0;
}