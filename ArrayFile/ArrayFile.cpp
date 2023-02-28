// ArrayFile.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <ios>
#include <vector>
#include <algorithm>
#include <time.h>



using namespace std;

typedef double* pDouble;
const int MAX_SIZE = 200;

int y;
/*
*   ConsoleInputArrayDouble
*
*/
int ConsoleInputSizeArray(const int sizeMax)
{
    int size = 0;
    do {
        cout << " Input size Array ( 0< 1 < " << sizeMax << " ) ";
        cin >> size;
    } while (size <= 0 || size >= sizeMax);
    return size;
}
/*
*   ConsoleInputArrayDouble
*
*/
int ConsoleInputArray(int sizeMax, double A[])
{
    int size = ConsoleInputSizeArray(sizeMax);
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> A[i];
    }
    return size;
}

/*
*   RndInputArrayDouble
*
*/
int RndInputArray(int sizeMax, vector<int>& A)
{
    int size = ConsoleInputSizeArray(sizeMax);
    int r1 = 0, r2 = 0;
    srand(size);

    for (int i = 0; i < size; i++, cout << endl) {
        r1 = rand();
        r2 = rand() % 1;
        A.push_back((r2) ? r1 : -r1);
        cout << A[i] << ' ';
    }
    return size;
}
int RndInputArray(int sizeMax, vector<double>& A)
{
    int size = ConsoleInputSizeArray(sizeMax);
    int r1 = 0, r2 = 0;
    srand(size);

    for (int i = 0; i < size; i++, cout << endl) {
        r1 = rand();
        r2 = rand() % 1;
        A.push_back((r2) ? r1 : -r1);
        cout << A[i] << ' ';
    }
    return size;
}

int ConsoleInputDynamicArrayNew(int sizeMax, pDouble& pA)
{
    int size = ConsoleInputSizeArray(sizeMax);
    pA = new double[size];
    if (pA == nullptr) { return 0; }
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> pA[i];
    }
    return size;
}

int ConsoleInputDynamicArray_calloc(int sizeMax, pDouble& pA)
{
    int size = ConsoleInputSizeArray(sizeMax);
    pA = (double*)calloc(size, sizeof(double));      // pA = (double*)malloc(size * sizeof(double)); 
    if (pA == nullptr) { return 0; }
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> pA[i];
    }
    return size;
}

void ConsoleInputVector(int sizeMax, vector<double>& A)
{
    int size = ConsoleInputSizeArray(sizeMax);
    double d;
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> d; A.push_back(d);
    }
    return;
}

void ConsoleInputVector(int sizeMax, vector<int>& A)
{
    int size = ConsoleInputSizeArray(sizeMax);
    int d;
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> d; A.push_back(d);
    }
    return;
}



/*
*  WriteArrayTextFile
*
*/

void WriteArrayTextFile(int n, double* arr, const char* fileName)
{
    ofstream fout(fileName, ios::app);
    if (fout.fail())
    {
        cout << "Erorr"; return;
    }
    fout << n << endl;
    for (int i = 0; i < n; i++)
        fout << arr[i] << "   ";
    fout.close();
}
void WriteArrayTextFile(int n, vector<int>& arr, const char* fileName)
{
    ofstream fout(fileName, ios::app);
    if (fout.fail())
    {
        cout << "Erorr"; return;
    }
    fout << n << endl;
    for (int i = 0; i < n; i++)
        fout << arr[i] << "   ";
    fout.close();
}
void WriteArrayTextFile(int n, vector<double>& arr, const char* fileName)
{
    ofstream fout(fileName, ios::app);
    if (fout.fail())
    {
        cout << "Erorr"; return;
    }
    fout << n << endl;
    for (int i = 0; i < n; i++)
        fout << arr[i] << "   ";
    fout << '\n';
    fout.close();
}

/*
*  ReadArrayTextFile
*
*/


int ReadArrayTextFile(double* arr, const char* fileName)
{
    int size;
    ifstream fin(fileName);
    if (!fin.is_open())
    {
        cout << "Erorr text"; return 0;
    }
    fin >> size;
    if (size <= 0) return 0;
    for (int i = 0; i < size; i++)
        fin >> arr[i];
    fin.close();
    return size;
}
int ReadArrayTextFile(vector<int>& arr, const char* fileName)
{
    int size;
    double buff = 0;
    ifstream fin(fileName);
    if (!fin.is_open())
    {
        cout << "Erorr text"; return 0;
    }
    fin >> size;
    if (size <= 0) return 0;
    for (int i = 0; i < size; i++)
    {
        fin >> buff;
        arr.push_back(buff);
    }
    fin.close();
    return size;
}
int ReadArrayTextFile(vector<double>& arr, const char* fileName)
{
    int size;
    double buff = 0;
    ifstream fin(fileName);
    if (!fin.is_open())
    {
        cout << "Erorr text"; return 0;
    }
    fin >> size;
    if (size <= 0) return 0;
    for (int i = 0; i < size; i++)
    {
        fin >> buff;
        arr.push_back(buff);
    }
    fin.close();
    return size;
}


void WriteArrayBinFile(int n, vector<double>& arr, const char* fileName)
{
    //ios_base
    ofstream bfout(fileName, ios::binary | ios::app);
    if (bfout.fail()) return;
    bfout.write((char*)&n, sizeof(int));
    bfout.write((char*)arr.data(), n * sizeof(arr[0]));
    bfout.close();
}

int ReadArrayBinFile(int n, vector<double>& arr, const char* fileName)
{
    int size = 0;
    ifstream bfin(fileName, ios_base::binary);
    if (bfin.fail()) return 0;
    bfin.read((char*)&size, sizeof(int));
    if (size <= 0) return 0;
    if (size > n) size = n;
    bfin.read((char*)&arr, n * sizeof(double));
    bfin.close();
    // ssdhs
    return size;
}

void ShowMainMenu()
{
    cout << "    Main Menu  \n";
    cout << "    1.  Task 1  \n";
    cout << "    2.  Task 2  \n";
    cout << "    3.  Task 3  \n";
    cout << "    4.  Exit  \n";
}

void MenuTask()
{
    cout << "     Menu Task   \n";
    cout << "    1.  Local array  \n";
    cout << "    2.  Dynamic array 1 \n";
    cout << "    3.  Dynamic array 2  new \n";
    cout << "    4.  Dynamic array : vector \n";
    cout << "    5.  Exit \n";
}

void MenuInput()
{
    cout << "     Menu Input   \n";
    cout << "    1.  Console all \n";
    cout << "    2.  Console - size, array - random \n";
    cout << "    3.  File 1.txt \n";
    cout << "    4.  Exit \n";
}


void Task1()
{
    vector<double> a, b;
    if (y == 1) ConsoleInputVector(MAX_SIZE, a);
    else if (y == 2) RndInputArray(MAX_SIZE, a);
    else if (y == 3) ReadArrayTextFile(a, "1.txt");
    else
    {
        cout << "Error" << endl;
        return;
    }
    copy_if(a.begin(), a.end(), back_inserter(b), [](double i) {return i < 0; });
    for (int i = 0; i < b.size(); i++) cout << "B = " << b[i] << ' ';
    WriteArrayTextFile(b.size(), b, "rez.txt");
    WriteArrayBinFile(b.size(), b, "BinaryRez.bin");
    cout << endl;
    return;
}
void Task2()
{
    vector<double> a, b;
    if (y == 1) ConsoleInputVector(MAX_SIZE, a);
    else if (y == 2) RndInputArray(MAX_SIZE, a);
    else if (y == 3) ReadArrayTextFile(a, "1.txt");
    else
    {
        cout << "Error" << endl;
        return;
    }
    copy_if(a.begin(), a.end(), back_inserter(b), [](double i) {return i < 0; });
    double T;
    cout << "Enter T: "; cin >> T;
    auto iter = find(b.begin(), b.end(), T);
    ofstream file("rez.txt", ios::app);
    double rez = *max_element(b.begin(), iter);
    cout << rez << endl;
    file << rez << '\n';
    file.close();
    WriteArrayBinFile(b.size(), b, "BinaryRez.bin");
    cout << endl;
    return;
}
void Task3()
{
    vector<double> A, B;
    if (y == 1) ConsoleInputVector(MAX_SIZE, A);
    else if (y == 2) RndInputArray(MAX_SIZE, A);
    else if (y == 3) ReadArrayTextFile(A, "1.txt");
    else
    {
        cout << "Error" << endl;
        return;
    }
    copy_if(A.begin(), A.end(), back_inserter(B), [A](double i) {return (bool)(count(A.begin(), A.end(), i) - 1); });
    sort(B.begin(), B.end());
    auto last = unique(B.begin(), B.end());
    B.erase(last, B.end());
    for (int i = 0; i < B.size(); i++, cout << ((i % 5 == 0 ? '\n' : ' '))) cout << B[i];
    WriteArrayTextFile(B.size(), B, "rez.txt");
    WriteArrayBinFile(B.size(), B, "BinaryRez.bin");
    cout << endl;
    return;
}

void Menu()
{
    int x;
    ShowMainMenu();
    cin >> x;
    if (x == 1)
    {
        MenuInput();
        cin >> y;
        Task1();
        Menu();
    }
    else if (x == 2)
    {
        MenuInput();
        cin >> y;
        Task2();
        Menu();
    }
    else if (x == 3)
    {
        MenuInput();
        cin >> y;
        Task3();
        Menu();
    }
    else if (x == 4) { return; }
    else Menu();
}

int main()
{
    Menu();
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
