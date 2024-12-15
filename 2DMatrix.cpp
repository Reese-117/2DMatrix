
#include<iostream>
using namespace std;

class SparseRow {
protected:
    int row; // Row#
    int col; // Column#
    int value; // We assume all values are integers

public:
    SparseRow();
    // Parameterized constructor
    SparseRow(int r, int c, int v);

    // Getter methods
    int getRow();
    int getCol();
    int getValue();

    // Setter methods
    void setRow(int r);
    void setCol(int c);
    void setValue(int v);

    // Display method
    void display();

    friend ostream& operator<<(ostream& os, const SparseRow& sr) {
        os << " " << sr.row << ", " << sr.col << ", " << sr.value;
        return os;
    }
};
SparseRow::SparseRow()
    {
        row = -1;
        col = -1;
        value = 0;
    }
SparseRow:: SparseRow(int r, int c, int v)
    {
        row = r;
        col = c;
        value = v;


    }
int SparseRow:: getRow(){
        return row;
    }
int SparseRow:: getCol(){ 
        return col;
    }
int SparseRow:: getValue(){
        return value;
    }
void SparseRow:: setRow(int r) {
         row = r; 
    }
void SparseRow:: setCol(int c) { 
        col = c; 
    }
void SparseRow:: setValue(int v) { 
        value = v; 
        }
void SparseRow:: display() {
        cout << "" << row << ", " << col << ", " << value << endl;
    }
class SparseMatrix {
public:
    int noRows;               // Number of rows of the original matrix
    int noCols;               // Number of columns of the original matrix
    int commonValue;          // The value considered as "common" (usually 0)
    int noNonSparseValues;    // Number of non-zero values
    SparseRow* myMatrix;      // Array of SparseRow objects

public:
    SparseMatrix ();
    // Default constructor
    
    // Parameterized constructor
    SparseMatrix(int n, int m, int cv, int noNSV);
    
    // Destructor to free memory
    ~SparseMatrix();

    // Getter methods
    int getNoRows();
    int getNoCols();
    int getCommonValue();
    int getNoNonSparseValues();
 

    // Setter methods
    void setNoRows(int n);
    void setNoCols(int m);
    void setCommonValue(int cv);
    void setNoNonSparseValues(int noNSV);
    void setSparseRow(int index, int row, int col, int value);
    // Display the matrix in matrix format
    void displayMatrix();
    // Overload the << operator to display sparse matrix format
    friend ostream& operator<<(ostream& os, const SparseMatrix& sm) {
        for (int i = 0; i < sm.noNonSparseValues; ++i) {
            os << sm.myMatrix[i] << endl;
        }
        return os;

    }
    // Transpose method
    SparseMatrix* Transpose();
    SparseMatrix* Add(SparseMatrix& M);
    SparseMatrix* Multiply(SparseMatrix& M);

};

SparseMatrix::SparseMatrix() {
        noRows = 0;
        noCols = 0;
        commonValue = 0;
        noNonSparseValues = 0;
        }
SparseMatrix::SparseMatrix(int n, int m, int cv, int noNSV) {
        noRows = n;
        noCols = m;
        commonValue = cv;
        noNonSparseValues = noNSV;
        myMatrix = new SparseRow[noNonSparseValues];
}
SparseMatrix::~SparseMatrix() {
        delete[] myMatrix;
    }
int SparseMatrix::getNoRows() 
    { 
        return noRows; 
    }
int SparseMatrix:: getNoCols() 
    { 
        return noCols; 
    }
int SparseMatrix:: getCommonValue() 

    { 
        return commonValue; 
    }
int SparseMatrix:: getNoNonSparseValues() 
    { 
        return noNonSparseValues; 
    }
void SparseMatrix:: setNoRows(int n) 
    { 
        noRows = n; 
    }
void SparseMatrix::setNoCols(int m) 
    { 
        noCols = m; 
    }
void SparseMatrix:: setCommonValue(int cv)
    {
         commonValue = cv; 
    }
void SparseMatrix::setNoNonSparseValues(int noNSV) 
    { 
        noNonSparseValues = noNSV; 
    }
void SparseMatrix:: setSparseRow(int index, int row, int col, int value) {
        if (index >= 0 && index < noNonSparseValues) {
            myMatrix[index] = SparseRow(row, col, value);
        }
    }
void SparseMatrix:: displayMatrix(){
       // Display the matrix in matrix format
        for (int i = 0; i < noRows; ++i) {
            for (int j = 0; j < noCols; ++j) {
                bool found = false;
                for (int k = 0; k < noNonSparseValues; ++k) {
                    if (myMatrix[k].getRow() == i && myMatrix[k].getCol() == j) {
                        cout << myMatrix[k].getValue() << " ";
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << commonValue << " ";
                }
            }
            cout << endl;
        }
    }
SparseMatrix* SparseMatrix::Transpose() {
    SparseMatrix* transposed = new SparseMatrix(noCols, noRows, commonValue, noNonSparseValues);
    for (int i = 0; i < noNonSparseValues; ++i) {
        transposed->myMatrix[i].setRow(myMatrix[i].getCol());
        transposed->myMatrix[i].setCol(myMatrix[i].getRow());
        transposed->myMatrix[i].setValue(myMatrix[i].getValue());
    }
    return transposed;
}
SparseMatrix* SparseMatrix::Add(SparseMatrix &M) {
    if (noRows != M.noRows || noCols != M.noCols) {
        cout << "Matrix addition is not possible" << endl;
        return nullptr;
    }

    SparseMatrix* result = new SparseMatrix(noRows, noCols, commonValue, noNonSparseValues + M.noNonSparseValues);

    int index = 0;

    for (int i = 0; i < noNonSparseValues; ++i) {
        result->setSparseRow(index++, myMatrix[i].getRow(), myMatrix[i].getCol(), myMatrix[i].getValue());
    }

    for (int i = 0; i < M.noNonSparseValues; ++i) {
        int r = M.myMatrix[i].getRow();
        int c = M.myMatrix[i].getCol();
        int v = M.myMatrix[i].getValue();

        bool found = false;
        for (int j = 0; j < index; ++j) {
            if (result->myMatrix[j].getRow() == r && result->myMatrix[j].getCol() == c) {
                result->myMatrix[j].setValue(result->myMatrix[j].getValue() + v);
                found = true;
                break;
            }
        }

        if (!found) {
            result->setSparseRow(index++, r, c, v);
        }
    }

    result->noNonSparseValues = index;

    return result;
}

SparseMatrix* SparseMatrix::Multiply(SparseMatrix &M) {
    // Check if matrices are compatible for multiplication
    if (noCols != M.noRows) {
        cout << "Matrix multiplication is not possible" << endl;
        return nullptr;
    }

    // Create a temporary matrix to store intermediate results
    int** temp = new int*[noRows];
    for (int i = 0; i < noRows; ++i) {
        temp[i] = new int[M.noCols]();
    }

    // Populate the temp matrix with multiplication results
    for (int i = 0; i < noRows; ++i) {
        for (int j = 0; j < M.noCols; ++j) {
            for (int k = 0; k < noCols; ++k) {
                int value1 = commonValue;
                int value2 = commonValue;

                // Retrieve value1 from the first matrix
                for (int l = 0; l < noNonSparseValues; ++l) {
                    if (myMatrix[l].getRow() == i && myMatrix[l].getCol() == k) {
                        value1 = myMatrix[l].getValue();
                        break;
                    }
                }

                // Retrieve value2 from the second matrix
                for (int l = 0; l < M.noNonSparseValues; ++l) {
                    if (M.myMatrix[l].getRow() == k && M.myMatrix[l].getCol() == j) {
                        value2 = M.myMatrix[l].getValue();
                        break;
                    }
                }

                // Accumulate the product
                temp[i][j] += value1 * value2;
            }
        }
    }

    // Count non-zero values for the result matrix
    int nonZeroCount = 0;
    for (int i = 0; i < noRows; ++i) {
        for (int j = 0; j < M.noCols; ++j) {
            if (temp[i][j] != commonValue) {
                ++nonZeroCount;
            }
        }
    }

    // Create the result matrix with the correct number of non-zero values
    SparseMatrix* result = new SparseMatrix(noRows, M.noCols, commonValue, nonZeroCount);

    // Set the result values in the sparse matrix
    int index = 0;
    for (int i = 0; i < noRows; ++i) {
        for (int j = 0; j < M.noCols; ++j) {
            if (temp[i][j] != commonValue) {
                result->setSparseRow(index++, i, j, temp[i][j]);
            }
        }
    }

    // Clean up the temporary matrix
    for (int i = 0; i < noRows; ++i) {
        delete[] temp[i];
    }
    delete[] temp;

    return result;
}
 

int main() {
    int n, m, cv, noNSV;
    SparseMatrix* temp;

    // Read the first matrix from the input
    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* firstOne = new SparseMatrix(n, m, cv, noNSV);
    int index = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int value;
            cin >> value;
            if (value != cv) {
                firstOne->setSparseRow(index++, i, j, value);
            }
        }
    }

    // Read the second matrix from the input
    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* secondOne = new SparseMatrix(n, m, cv, noNSV);
    int index2 = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int value;
            cin >> value;
            if (value != cv) {
                secondOne->setSparseRow(index2++, i, j, value);
            }
        }
    }
    // Display matrices

    cout << "First one in sparse matrix format" << endl;
    cout << *firstOne; // This uses the overloaded << operator


    cout << "After transpose" << endl;
    cout << (*(*firstOne).Transpose());




    cout << "First one in matrix format" << endl;
    firstOne->displayMatrix();


    cout << "Second one in sparse matrix format" << endl;
    cout << *secondOne; // This uses the overloaded << operator


    
    //transpose secondOne
    cout << "After transpose" << endl;
    cout << (*(*secondOne).Transpose());
    
    cout << "Second one in matrix format" << endl;
    secondOne->displayMatrix();

    

    
   


    
    cout << "Matrix addition result" << endl;
    SparseMatrix* addResult = firstOne->Add(*secondOne);
    if (addResult) {
        addResult->displayMatrix(); // Display in matrix format
        delete addResult; // Clean up
    }

    cout << "Matrix multiplication result" << endl;
    SparseMatrix* mulResult = firstOne->Multiply(*secondOne);
    if (mulResult) {
        mulResult->displayMatrix(); // Display in matrix format
        delete mulResult; // Clean up
    }
    return 0;
};