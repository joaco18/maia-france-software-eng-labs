/*
    Software Engineering
    16 November 2021
    Joaquin Seia
    Emily Caravajal

    Task:
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
    // Transposes the matrix and stores the result in a different memory
    // position.
    for (int i=0; i < column; i++){
        for (int j=0; j < row; j++){
            transposed[i][j] = matrix[j][i];
        }
    }
}

void stringToArray(float *row, string line, string delimiter, int column){
    // Extract each of the substrings separated by the delimiter 
    // from the line and stores the in the indicated array.
    int pos, k = 0;
    string token;
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        row[k] = stof(token);
        line.erase(0, pos + delimiter.length());
        k++;
    }
}

float** initialise(int row ,int column){
    // Initializes a 2D array with the indicated number of rows and columns.
    float** matrix = new float*[row];   
    for(int i=0; i < row ; i++){
        matrix[i] = new float[column];
    }
    return matrix;
}

void printMonoArray(int elements, float *monomatrix){
    // Prints a 1D array nicely.
    for(int j=0; j < elements; j++){
        cout << monomatrix[j] << " ";
    }
    cout << endl;
}

void printMatrix(int row, int column, float **matrix){
    // Prints a 2D array nicely.
    for(int i=0; i < row; i++){
        printMonoArray(column, matrix[i]);
    }
}

void monoDimMatrix(int row, int column, float **matrix, float *monoMatrix){
    // Transforms a 2D array in a monodimensional array.
    int k=0;
    for(int i=0; i < row; i++){
        for(int j=0; j < column; j++){
            monoMatrix[k] = matrix[i][j];
            k++;    
        }
    }
}

void fillMatrix(float **matrix, int row, int column){
    // Gets values to fill the matrix from the user
    cout << "Let's enter the matrix! :)" << endl;
    for (int i=0; i < row; i++){
        cout << "Please enter the data for the " << i << " row. "
             << "Separating each of the elements by a space" << endl;
        getline(cin, line);
        line = line + " ";
        stringToArray(matrix[i], line, " ", column);
    }
}

void getMatrixDimensions(int *row, int *column){
    // Asks the user to input the desired number of rows and columns for the
    // matrix. If the selected number exceeds 8 asks again until succed.
    bool flag = true;
    string line = "";
    
    while(flag){
        //Ex 1. Get size of matrix as an input from the user
        cout << "Enter the number of rows for the matrix: ";
        cin >> * row;
        cout << "Enter the number of columns for the matrix: ";
        cin >> * column;
        
        // Clean the cin cache
        cin.clear();
        cin.ignore(100, '\n');
        
        //Ex 2. Size should be less than 8 in each direction (row, column)
        flag = false;
        if ((* row >= 8) && (* column >= 8)){
            cout << "The number of rows or columns are greater or equal"
                 << " that 8.\nTry again."
                 << endl;
            flag = true;
        }
    }
}


int main(){
    //1. Get size of matrix as an input from the user
    //2. Size should be less than 8 in each direction (row, column)
    int row, column = 0;
    getMatrixDimensions(&row, &column);
    
    //3. Get values to fill the matrix from the user
    float **matrix = initialise(row, column);
    fillMatrix(matrix, row, column);

    //4. Transpose matrix
    float **transposed = initialise(column, row);
    transpose(matrix, transposed, row, column);

    //5. Print original matrix
    cout << "Original matrix:" << endl;
    printMatrix(row, column, matrix);
    
    //6. Print transposed matrix
    cout << "Transpose matrix: " << endl;
    printMatrix(column, row, transposed);

    //7. Transform the original matrix in a mono dimensional array
    float monomatrix[row*column];
    monoDimMatrix(row, column, matrix, monomatrix);

    cout << "Mono dimensional matrix" << endl;
    printMonoArray(row*column, monomatrix);

    return 0;
}