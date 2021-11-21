/*

    Software Engineering
    16 November 2021
    Joaquin
    Emily

    Array and Matrix
    1. Get size of matrix as an input from the user
    2. Size should be less than 8 in each direction (row, column)
    3. Get values to fill the matrix from the user
    4. Transpose matrix
    5. Print original matrix
    6. Print transposed matrix
    7. Transform the original matrix in a mono dimensional array

*/
#include <iostream>
#include <string>

using namespace std;


void transpose(float **matrix, float **transposed, int row, int column){
    for (int i=0; i < column; i++){
        for (int j=0; j < row; j++){
            transposed[i][j] = matrix[j][i];
        }
    }
}

void stringToArray(float *row, string line, string delimiter, int column){

    int pos, k = 0;
    string token;
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        row[k] = stof(token);
        line.erase(0, pos + delimiter.length());
        k++;
    }
}

float** initialise(int row ,int column)
{
    float** matrix = new float*[row];
    
    for(int i=0; i < row ; i++){
        matrix[i] = new float[column];
        
    }    
    return matrix;
    
}

void printMatrix(int row, int column, float **matrix){
    for(int i=0; i < row; i++){
        for(int j=0; j < column; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void monoDimMatrix(int row, int column, float **matrix, float **monoMatrix){
    int k=0;
    for(int i=0; i < row; i++){
        for(int j=0; j < column; j++){
            monoMatrix[0][k] = matrix[i][j];
            k++;    
        }
    }
}


int main(){

    bool flag = true;
    string line = "";
    int row, column = 0;

    while(flag){

        //1. Get size of matrix as an input from the user
        cout << "Enter the number of rows for the matrix: ";
        cin >> row;
        cout << "Enter the number of columns for the matrix: ";
        cin >> column;
        
        cin.clear();
        cin.ignore(100, '\n');

        flag = false;

        //2. Size should be less than 8 in each direction (row, column)
        if ((row >= 8) && (column >= 8)){
            cout << "The number of rows or columns are greater or equal that 8.\nTry again." << endl;
            flag = true;
        }
    }
    
    //3. Get values to fill the matrix from the user
    float **matrix = initialise(row, column);

    cout << "Let's enter the matrix! :)" << endl;
    for (int i=0; i < row; i++){
        cout << "Please enter the data for the " << i << " row. Separate each of the elements by a space" << endl;
        
        getline(cin, line);
        
        line = line + " "; 
        
        stringToArray(matrix[i], line," ",column);

    }

    //4. Transpose matrix
    float **transposed = initialise(column, row);

    //5. Print original matrix
    cout << "Original matrix" << endl;
    printMatrix(row, column, matrix);
    

    //6. Print transposed matrix
    transpose(matrix, transposed, row, column);
    cout << "Transpose matrix " << endl;

    printMatrix(column, row, transposed);


    //7. Transform the original matrix in a mono dimensional array
    float **monomatrix = initialise(1, row*column);
    monoDimMatrix(row, column, matrix, monomatrix);

    cout << "Mono dimensional matrix" << endl;
    printMatrix(1, row*column, monomatrix);

    return 0;
}