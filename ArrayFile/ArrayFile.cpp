#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

/////////////////////////////////////////////////////
// 3.1 Ввід масиву з консолі + запис у текстовий файл
/////////////////////////////////////////////////////

void inputArrayConsole(double*& arr, int& n)
{
    cout << "Enter array size: ";
    cin >> n;

    arr = new double[n];

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void writeArrayText(double* arr, int n, string filename)
{
    ofstream fout(filename);

    fout << n << endl;

    for (int i = 0; i < n; i++)
        fout << arr[i] << " ";

    fout.close();
}

/////////////////////////////////////////////////////
// читання масиву з текстового файлу
/////////////////////////////////////////////////////

double* readArrayText(string filename, int& n)
{
    ifstream fin(filename);

    fin >> n;

    double* arr = new double[n];

    for (int i = 0; i < n; i++)
        fin >> arr[i];

    fin.close();

    return arr;
}

/////////////////////////////////////////////////////
// 3.2 випадковий масив + бінарний файл
/////////////////////////////////////////////////////

void randomArrayBinary(string filename)
{
    int n;

    cout << "Enter size: ";
    cin >> n;

    double* arr = new double[n];

    srand(time(0));

    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100 - 50;

    ofstream fout(filename, ios::binary);

    fout.write((char*)&n, sizeof(int));
    fout.write((char*)arr, n * sizeof(double));

    fout.close();

    delete[] arr;
}

/////////////////////////////////////////////////////
// TASK 1
// максимальний серед від’ємних + індекс
/////////////////////////////////////////////////////

void task1(double* arr, int n)
{
    double maxNeg = -1e9;
    int index = -1;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < 0 && arr[i] > maxNeg)
        {
            maxNeg = arr[i];
            index = i;
        }
    }

    ofstream fout("result1.txt");

    if (index == -1)
    {
        cout << "No negative elements\n";
        fout << "No negative elements";
    }
    else
    {
        cout << "Max negative = " << maxNeg << endl;
        cout << "Index = " << index << endl;

        fout << "Max negative = " << maxNeg << endl;
        fout << "Index = " << index;
    }

    fout.close();
}

/////////////////////////////////////////////////////
// TASK 2
/////////////////////////////////////////////////////

void task2(double* arr, int n)
{
    double B, A1;

    cout << "Enter B: ";
    cin >> B;

    cout << "Enter A1: ";
    cin >> A1;

    int limit = n;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > A1)
        {
            limit = i;
            break;
        }
    }

    double minVal = 1e9;
    bool found = false;

    for (int i = 0; i < limit; i++)
    {
        if (arr[i] < B && arr[i] < minVal)
        {
            minVal = arr[i];
            found = true;
        }
    }

    ofstream fout("result2.txt");

    if (!found)
    {
        cout << "Element not found\n";
        fout << "Element not found";
    }
    else
    {
        cout << "Min element = " << minVal << endl;
        fout << "Min element = " << minVal;
    }

    fout.close();
}

/////////////////////////////////////////////////////
// TASK 3
// точки всередині кола
/////////////////////////////////////////////////////

void task3(double* arr, int n)
{
    double r;

    cout << "Enter radius r: ";
    cin >> r;

    int count = 0;

    for (int i = 0; i < n - 1; i += 2)
    {
        double x = arr[i];
        double y = arr[i + 1];

        if (x * x + y * y <= r * r)
            count++;
    }

    ofstream fout("result3.txt");

    cout << "Points inside circle = " << count << endl;
    fout << "Points inside circle = " << count;

    fout.close();
}

/////////////////////////////////////////////////////
// 3.4 читання у vector
/////////////////////////////////////////////////////

void readToVector(string filename)
{
    ifstream fin(filename);

    int n;
    fin >> n;

    vector<double> v(n);

    for (int i = 0; i < n; i++)
        fin >> v[i];

    cout << "Vector elements:\n";

    for (double x : v)
        cout << x << " ";

    cout << endl;

    fin.close();
}

/////////////////////////////////////////////////////
// MENU
/////////////////////////////////////////////////////

int main()
{
    double* arr = nullptr;
    int n = 0;

    int choice;

    do
    {
        cout << "\nMENU\n";
        cout << "1 - Input array -> text file\n";
        cout << "2 - Random array -> binary file\n";
        cout << "3 - Task 1\n";
        cout << "4 - Task 2\n";
        cout << "5 - Task 3\n";
        cout << "6 - Read file to vector\n";
        cout << "0 - Exit\n";

        cin >> choice;

        switch (choice)
        {

        case 1:
            inputArrayConsole(arr, n);
            writeArrayText(arr, n, "array.txt");
            break;

        case 2:
            randomArrayBinary("array.bin");
            break;

        case 3:
            arr = readArrayText("array.txt", n);
            task1(arr, n);
            break;

        case 4:
            arr = readArrayText("array.txt", n);
            task2(arr, n);
            break;

        case 5:
            arr = readArrayText("array.txt", n);
            task3(arr, n);
            break;

        case 6:
            readToVector("array.txt");
            break;

        }

    } while (choice != 0);

    delete[] arr;

    return 0;
}