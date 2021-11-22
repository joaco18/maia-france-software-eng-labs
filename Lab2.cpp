/*

    Software Engineering
    16 November 2021
    Joaquin
    Emily

    Write the following functions :
    • Caesar cipher https://en.wikipedia.org/wiki/Caesar_cipher
    • Vigenere cipher https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher
    In the main file add the necessary code to test and validate your encryption

*/
#include <iostream>
#include <functional>
#include <string>

using namespace std;

/*
    caesarCipher(string, string, int) -> string
*/
string caesarCipher(string text, string direction, int step){
    string output = "";
    function<int(int, int)> op;
    if (direction.compare("R") == 0){
        op = plus<int>();
    }else if(direction.compare("L") == 0){
        op = minus<int>();
    }
    for(char& c: text){
        c = toupper(c);
        int coded_pos = op(int(c) - int('A'), step);
        coded_pos = (coded_pos < 0) ? 26 + coded_pos : coded_pos;
        output = output + char((coded_pos % 26) + int('A'));
    }
    return output;
}

/*
        caesarDesipher(string, string, int) -> string
*/
string caesarDesipher(string text, string direction, int step){
    return caesarCipher(text, (direction.compare("R")==0 ? "L" : "R"), step);
}

/*
        vigenereCipher(string, string, string) -> string
*/
string vigenereCipher (string text, string direction, string key){
    int text_lenght = text.length();
    int equal_key[text_lenght];
    for (int i=0; i < text_lenght; i++){
        equal_key[i] = int(key[i % key.length()]) - int('A');
    }
    string output = "";
    int counter = 0;
    for(char& c: text){
        c = toupper(c);
        string s = "";
        s+=c;
        output = output + caesarCipher(s, direction, equal_key[counter]);
        counter++;
    }
    return output;
}

/*
        vigenereDesipher(string, string, string) -> string
*/
string vigenereDesipher(string text, string direction, string key){
    return vigenereCipher(text, (direction.compare("R")==0 ? "L" : "R"), key);
}

/*
        testEncription(string, string) -> void
*/
void testEncription(string result, string expected_result){
    bool test_passed = !(result).compare(expected_result);
    cout << "The test " << (test_passed ? "passed! :)" : "didnt passed :(") << endl;  
}

int main(){
    // Ask for a step between 1 and 25
    string expected_result = "DEBC";
    string result = caesarCipher("AbYz", "R", 3);
    cout << "We are chiphering this string " << "\'AbYz\'" << " with Caesar Cipher, with step 3 and to the right: "  << endl;
    cout << "We are expecting this chiphered string: " << "DEBC" << endl;
    cout << "The chiphered string that we receive is: " << result << endl;
    testEncription(expected_result, result);
    cout << endl;
    
    expected_result = "ABYZ";
    result = caesarDesipher("DEBC", "R", 3);
    cout << "We are dechiphering this string " << "\'ABYZ\'" <<  " Ciphered with Caesar Cipher, with step 3 and to the right" << endl;
    cout << "We are expecting this dechiphered string: " << "ABYZ" << endl;
    cout << "The dechiphered string that we receive is: " << result << endl;
    testEncription(expected_result, result);
    cout << endl;

    expected_result = "EPQC";
    result = vigenereCipher("MaIA", "R", "SPICE");
    cout << "We are chiphering this string " << "\'MaIA\'" << " with Vigenere Cipher, with key word SPICE: "  << endl;
    cout << "We are expecting this chiphered string: " << "EPQC" << endl;
    cout << "The chiphered string that we receive is: " << result << endl;
    testEncription(expected_result, result);
    cout << endl;

    expected_result = "MAIA";
    result = vigenereDesipher("EPQC", "R", "SPICE");
    cout << "We are dechiphering this string " << "\'EPQC\'" <<  " Ciphered with Vigenere Cipher, with key word SPICE" << endl;
    cout << "We are expecting this dechiphered string: " << "MAIA" << endl;
    cout << "The dechiphered string that we receive is: " << result << endl;
    testEncription(expected_result, result);
    cout << endl;

    return 0;
}