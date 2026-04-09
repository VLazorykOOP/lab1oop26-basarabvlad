#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// =====================================================
//                    TASK 1. VECTORFLOAT
// =====================================================

class VectorFloat {
private:
    float* arr;
    int size;
    int codeError;

public:
    VectorFloat() {
        size = 1;
        arr = new float[1];
        arr[0] = 0.0f;
        codeError = 0;
    }

    VectorFloat(int n) {
        if (n <= 0) n = 1;
        size = n;
        arr = new float[size];
        for (int i = 0; i < size; i++) arr[i] = 0.0f;
        codeError = 0;
    }

    VectorFloat(int n, float value) {
        if (n <= 0) n = 1;
        size = n;
        arr = new float[size];
        for (int i = 0; i < size; i++) arr[i] = value;
        codeError = 0;
    }

    VectorFloat(const VectorFloat& other) {
        size = other.size;
        codeError = other.codeError;
        arr = new float[size];
        for (int i = 0; i < size; i++) arr[i] = other.arr[i];
    }

    ~VectorFloat() {
        delete[] arr;
    }

    int getSize() const {
        return size;
    }

    int getCodeError() const {
        return codeError;
    }

    void setCodeError(int code) {
        codeError = code;
    }

    void fillRandom(float minVal = -10.0f, float maxVal = 10.0f) {
        for (int i = 0; i < size; i++) {
            float r = minVal + static_cast<float>(rand()) / RAND_MAX * (maxVal - minVal);
            arr[i] = r;
        }
    }

    void fillFromKeyboard() {
        cout << "Enter " << size << " elements:\n";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
    }

    void fillFromFile(const string& filename) {
        ifstream fin(filename.c_str());
        if (!fin) {
            cout << "Cannot open file: " << filename << endl;
            codeError = 1;
            return;
        }
        for (int i = 0; i < size; i++) {
            if (!(fin >> arr[i])) {
                arr[i] = 0.0f;
            }
        }
        fin.close();
    }

    void saveToFile(const string& filename) const {
        ofstream fout(filename.c_str());
        if (!fout) {
            cout << "Cannot create file: " << filename << endl;
            return;
        }
        fout << size << endl;
        for (int i = 0; i < size; i++) fout << arr[i] << " ";
        fout << endl;
        fout.close();
    }

    VectorFloat& operator=(const VectorFloat& other) {
        if (this != &other) {
            delete[] arr;
            size = other.size;
            codeError = other.codeError;
            arr = new float[size];
            for (int i = 0; i < size; i++) arr[i] = other.arr[i];
        }
        return *this;
    }

    VectorFloat& operator++() {
        for (int i = 0; i < size; i++) arr[i] += 1.0f;
        return *this;
    }

    VectorFloat operator++(int) {
        VectorFloat temp(*this);
        for (int i = 0; i < size; i++) arr[i] += 1.0f;
        return temp;
    }

    VectorFloat& operator--() {
        for (int i = 0; i < size; i++) arr[i] -= 1.0f;
        return *this;
    }

    VectorFloat operator--(int) {
        VectorFloat temp(*this);
        for (int i = 0; i < size; i++) arr[i] -= 1.0f;
        return temp;
    }

    bool operator!() const {
        return size != 0;
    }

    VectorFloat operator-() const {
        VectorFloat temp(size);
        for (int i = 0; i < size; i++) temp.arr[i] = -arr[i];
        return temp;
    }

    VectorFloat& operator+=(const VectorFloat& other) {
        if (size != other.size) {
            codeError = 2;
            return *this;
        }
        for (int i = 0; i < size; i++) arr[i] += other.arr[i];
        return *this;
    }

    VectorFloat& operator-=(const VectorFloat& other) {
        if (size != other.size) {
            codeError = 2;
            return *this;
        }
        for (int i = 0; i < size; i++) arr[i] -= other.arr[i];
        return *this;
    }

    VectorFloat& operator*=(float value) {
        for (int i = 0; i < size; i++) arr[i] *= value;
        return *this;
    }

    VectorFloat& operator/=(float value) {
        if (value == 0) {
            codeError = 3;
            return *this;
        }
        for (int i = 0; i < size; i++) arr[i] /= value;
        return *this;
    }

    VectorFloat& operator%=(int value) {
        if (value == 0) {
            codeError = 3;
            return *this;
        }
        for (int i = 0; i < size; i++) arr[i] = static_cast<int>(arr[i]) % value;
        return *this;
    }

    float& operator[](int index) {
        if (index < 0 || index >= size) {
            codeError = 4;
            return arr[size - 1];
        }
        return arr[index];
    }

    const float& operator[](int index) const {
        if (index < 0 || index >= size) {
            return arr[size - 1];
        }
        return arr[index];
    }

    float operator()() const {
        float sum = 0;
        for (int i = 0; i < size; i++) sum += arr[i];
        return sum;
    }

    friend VectorFloat operator+(const VectorFloat& a, const VectorFloat& b) {
        if (a.size != b.size) {
            VectorFloat temp(1);
            temp.codeError = 2;
            return temp;
        }
        VectorFloat temp(a.size);
        for (int i = 0; i < a.size; i++) temp.arr[i] = a.arr[i] + b.arr[i];
        return temp;
    }

    friend VectorFloat operator-(const VectorFloat& a, const VectorFloat& b) {
        if (a.size != b.size) {
            VectorFloat temp(1);
            temp.codeError = 2;
            return temp;
        }
        VectorFloat temp(a.size);
        for (int i = 0; i < a.size; i++) temp.arr[i] = a.arr[i] - b.arr[i];
        return temp;
    }

    friend VectorFloat operator*(const VectorFloat& a, float value) {
        VectorFloat temp(a.size);
        for (int i = 0; i < a.size; i++) temp.arr[i] = a.arr[i] * value;
        return temp;
    }

    friend VectorFloat operator*(float value, const VectorFloat& a) {
        return a * value;
    }

    friend VectorFloat operator/(const VectorFloat& a, float value) {
        VectorFloat temp(a.size);
        if (value == 0) {
            temp.codeError = 3;
            return temp;
        }
        for (int i = 0; i < a.size; i++) temp.arr[i] = a.arr[i] / value;
        return temp;
    }

    friend VectorFloat operator%(const VectorFloat& a, int value) {
        VectorFloat temp(a.size);
        if (value == 0) {
            temp.codeError = 3;
            return temp;
        }
        for (int i = 0; i < a.size; i++) temp.arr[i] = static_cast<int>(a.arr[i]) % value;
        return temp;
    }

    friend bool operator==(const VectorFloat& a, const VectorFloat& b) {
        if (a.size != b.size) return false;
        for (int i = 0; i < a.size; i++) {
            if (a.arr[i] != b.arr[i]) return false;
        }
        return true;
    }

    friend bool operator!=(const VectorFloat& a, const VectorFloat& b) {
        return !(a == b);
    }

    friend ostream& operator<<(ostream& out, const VectorFloat& v) {
        out << "[ ";
        for (int i = 0; i < v.size; i++) out << v.arr[i] << " ";
        out << "]";
        return out;
    }

    friend istream& operator>>(istream& in, VectorFloat& v) {
        for (int i = 0; i < v.size; i++) in >> v.arr[i];
        return in;
    }
};

// =====================================================
//          TASK 2. ASSOCIATIVE CLASS COUNTRY-CAPITAL
// =====================================================

struct PairCC {
    string country;
    string capital;
};

class CountryCapitalMap {
private:
    PairCC* data;
    int size;
    int capacity;
    int codeError;

    void resize() {
        capacity *= 2;
        PairCC* temp = new PairCC[capacity];
        for (int i = 0; i < size; i++) temp[i] = data[i];
        delete[] data;
        data = temp;
    }

public:
    CountryCapitalMap() {
        capacity = 10;
        size = 0;
        codeError = 0;
        data = new PairCC[capacity];
    }

    CountryCapitalMap(const CountryCapitalMap& other) {
size = other.size;
        capacity = other.capacity;
        codeError = other.codeError;
        data = new PairCC[capacity];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
    }

    ~CountryCapitalMap() {
        delete[] data;
    }

    CountryCapitalMap& operator=(const CountryCapitalMap& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            codeError = other.codeError;
            data = new PairCC[capacity];
            for (int i = 0; i < size; i++) data[i] = other.data[i];
        }
        return *this;
    }

    void add(const string& country, const string& capital) {
        for (int i = 0; i < size; i++) {
            if (data[i].country == country) {
                data[i].capital = capital;
                return;
            }
        }
        if (size == capacity) resize();
        data[size].country = country;
        data[size].capital = capital;
        size++;
    }

    void fillRandom() {
        static string countries[] = {
            "Ukraine", "Poland", "France", "Germany", "Italy",
            "Spain", "Japan", "Canada", "Brazil", "Norway"
        };
        static string capitals[] = {
            "Kyiv", "Warsaw", "Paris", "Berlin", "Rome",
            "Madrid", "Tokyo", "Ottawa", "Brasilia", "Oslo"
        };
        size = 0;
        for (int i = 0; i < 5; i++) {
            int idx = rand() % 10;
            add(countries[idx], capitals[idx]);
        }
    }

    void fillFromKeyboard() {
        int n;
        cout << "Enter number of pairs: ";
        cin >> n;
        cin.ignore();

        for (int i = 0; i < n; i++) {
            string country, capital;
            cout << "Country: ";
            getline(cin, country);
            cout << "Capital: ";
            getline(cin, capital);
            add(country, capital);
        }
    }

    void fillFromFile(const string& filename) {
        ifstream fin(filename.c_str());
        if (!fin) {
            cout << "Cannot open file: " << filename << endl;
            codeError = 1;
            return;
        }

        size = 0;
        int n;
        fin >> n;
        fin.ignore();

        for (int i = 0; i < n; i++) {
            string country, capital;
            getline(fin, country);
            getline(fin, capital);
            if (!country.empty()) add(country, capital);
        }
        fin.close();
    }

    void saveToFile(const string& filename) const {
        ofstream fout(filename.c_str());
        if (!fout) {
            cout << "Cannot create file: " << filename << endl;
            return;
        }
        fout << size << endl;
        for (int i = 0; i < size; i++) {
            fout << data[i].country << endl;
            fout << data[i].capital << endl;
        }
        fout.close();
    }

    string& operator[](const string& country) {
        for (int i = 0; i < size; i++) {
            if (data[i].country == country) {
                return data[i].capital;
            }
        }
        codeError = 2;
        return data[size - 1].capital;
    }

    string operator()(const string& country) {
        for (int i = 0; i < size; i++) {
            if (data[i].country == country) {
                return data[i].capital;
            }
        }
        codeError = 2;
        return "NOT FOUND";
    }

    int getCodeError() const {
        return codeError;
    }

    friend ostream& operator<<(ostream& out, const CountryCapitalMap& obj) {
        out << "\nCountry -> Capital\n";
        for (int i = 0; i < obj.size; i++) {
            out << obj.data[i].country << " -> " << obj.data[i].capital << endl;
        }
        return out;
    }

    friend istream& operator>>(istream& in, CountryCapitalMap& obj) {
        int n;
        cout << "Enter number of pairs: ";
        in >> n;
        in.ignore();
        for (int i = 0; i < n; i++) {
            string country, capital;
            cout << "Country: ";
            getline(in, country);
            cout << "Capital: ";
getline(in, capital);
            obj.add(country, capital);
        }
        return in;
    }
};

// =====================================================
//                    TASK 3. MATRIXFLOAT
// =====================================================

class MatrixFloat {
private:
    VectorFloat* rows;
    int n, m;
    int codeError;
    static int countMatrix;

public:
    MatrixFloat() {
        n = 1;
        m = 1;
        rows = new VectorFloat[1];
        rows[0] = VectorFloat(1, 0.0f);
        codeError = 0;
        countMatrix++;
    }

    MatrixFloat(int size) {
        if (size <= 0) size = 1;
        n = size;
        m = size;
        rows = new VectorFloat[n];
        for (int i = 0; i < n; i++) rows[i] = VectorFloat(m, 0.0f);
        codeError = 0;
        countMatrix++;
    }

    MatrixFloat(int rowsCount, int colsCount) {
        if (rowsCount <= 0) rowsCount = 1;
        if (colsCount <= 0) colsCount = 1;
        n = rowsCount;
        m = colsCount;
        rows = new VectorFloat[n];
        for (int i = 0; i < n; i++) rows[i] = VectorFloat(m, 0.0f);
        codeError = 0;
        countMatrix++;
    }

    MatrixFloat(int rowsCount, int colsCount, float value) {
        if (rowsCount <= 0) rowsCount = 1;
        if (colsCount <= 0) colsCount = 1;
        n = rowsCount;
        m = colsCount;
        rows = new VectorFloat[n];
        for (int i = 0; i < n; i++) rows[i] = VectorFloat(m, value);
        codeError = 0;
        countMatrix++;
    }

    MatrixFloat(const MatrixFloat& other) {
        n = other.n;
        m = other.m;
        codeError = other.codeError;
        rows = new VectorFloat[n];
        for (int i = 0; i < n; i++) rows[i] = other.rows[i];
        countMatrix++;
    }

    ~MatrixFloat() {
        delete[] rows;
        countMatrix--;
    }

    static int getCountMatrix() {
        return countMatrix;
    }

    int getRows() const {
        return n;
    }

    int getCols() const {
        return m;
    }

    int getCodeError() const {
        return codeError;
    }

    void fillRandom(float minVal = -10.0f, float maxVal = 10.0f) {
        for (int i = 0; i < n; i++) rows[i].fillRandom(minVal, maxVal);
    }

    void fillFromKeyboard() {
        cout << "Enter matrix " << n << "x" << m << ":\n";
        for (int i = 0; i < n; i++) {
            cin >> rows[i];
        }
    }

    void fillFromFile(const string& filename) {
        ifstream fin(filename.c_str());
        if (!fin) {
            cout << "Cannot open file: " << filename << endl;
            codeError = 1;
            return;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fin >> rows[i][j];
            }
        }
        fin.close();
    }

    void saveToFile(const string& filename) const {
        ofstream fout(filename.c_str());
        if (!fout) {
            cout << "Cannot create file: " << filename << endl;
            return;
        }
        fout << n << " " << m << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) fout << rows[i][j] << " ";
            fout << endl;
        }
        fout.close();
    }

    MatrixFloat& operator=(const MatrixFloat& other) {
        if (this != &other) {
            delete[] rows;
            n = other.n;
            m = other.m;
            codeError = other.codeError;
            rows = new VectorFloat[n];
            for (int i = 0; i < n; i++) rows[i] = other.rows[i];
        }
        return *this;
    }

    MatrixFloat& operator++() {
        for (int i = 0; i < n; i++) ++rows[i];
        return *this;
    }

    MatrixFloat operator++(int) {
        MatrixFloat temp(*this);
        for (int i = 0; i < n; i++) rows[i]++;
        return temp;
    }

    MatrixFloat& operator--() {
        for (int i = 0; i < n; i++) --rows[i];
        return *this;
    }

    MatrixFloat operator--(int) {
        MatrixFloat temp(*this);
        for (int i = 0; i < n; i++) rows[i]--;
        return temp;
    }

    bool operator!() const {
        return (n != 0 && m != 0);
    }

    MatrixFloat operator-() const {
        MatrixFloat temp(n, m);
        for (int i = 0; i < n; i++) temp.rows[i] = -rows[i];
        return temp;
    }

    VectorFloat& operator[](int index) {
        if (index < 0 || index >= n) {
            codeError = 4;
            return rows[n - 1];
        }
        return rows[index];
    }

    const VectorFloat& operator[](int index) const {
        if (index < 0 || index >= n) {
            return rows[n - 1];
        }
        return rows[index];
    }

    float operator()() const {
        float sum = 0;
        for (int i = 0; i < n; i++) sum += rows[i]();
        return sum;
    }

    MatrixFloat& operator+=(const MatrixFloat& other) {
        if (n != other.n || m != other.m) {
            codeError = 2;
            return *this;
        }
        for (int i = 0; i < n; i++) rows[i] += other.rows[i];
        return *this;
    }

    MatrixFloat& operator-=(const MatrixFloat& other) {
        if (n != other.n || m != other.m) {
            codeError = 2;
            return *this;
        }
        for (int i = 0; i < n; i++) rows[i] -= other.rows[i];
        return *this;
    }

    MatrixFloat& operator*=(float value) {
        for (int i = 0; i < n; i++) rows[i] *= value;
        return *this;
    }

    MatrixFloat& operator/=(float value) {
        if (value == 0) {
            codeError = 3;
            return *this;
        }
        for (int i = 0; i < n; i++) rows[i] /= value;
        return *this;
    }

    MatrixFloat& operator%=(int value) {
        if (value == 0) {
            codeError = 3;
            return *this;
        }
        for (int i = 0; i < n; i++) rows[i] %= value;
        return *this;
    }

    friend MatrixFloat operator+(const MatrixFloat& a, const MatrixFloat& b) {
        if (a.n != b.n || a.m != b.m) {
            MatrixFloat temp(1, 1);
            return temp;
        }
        MatrixFloat temp(a.n, a.m);
        for (int i = 0; i < a.n; i++) temp.rows[i] = a.rows[i] + b.rows[i];
        return temp;
    }

    friend MatrixFloat operator-(const MatrixFloat& a, const MatrixFloat& b) {
        if (a.n != b.n || a.m != b.m) {
            MatrixFloat temp(1, 1);
            return temp;
        }
        MatrixFloat temp(a.n, a.m);
        for (int i = 0; i < a.n; i++) temp.rows[i] = a.rows[i] - b.rows[i];
        return temp;
    }

    friend MatrixFloat operator*(const MatrixFloat& a, float value) {
        MatrixFloat temp(a.n, a.m);
        for (int i = 0; i < a.n; i++) temp.rows[i] = a.rows[i] * value;
        return temp;
    }

    friend MatrixFloat operator*(float value, const MatrixFloat& a) {
        return a * value;
    }

    friend MatrixFloat operator/(const MatrixFloat& a, float value) {
        MatrixFloat temp(a.n, a.m);
        if (value == 0) return temp;
        for (int i = 0; i < a.n; i++) temp.rows[i] = a.rows[i] / value;
        return temp;
    }

    friend MatrixFloat operator%(const MatrixFloat& a, int value) {
        MatrixFloat temp(a.n, a.m);
        if (value == 0) return temp;
        for (int i = 0; i < a.n; i++) temp.rows[i] = a.rows[i] % value;
        return temp;
    }

    friend MatrixFloat operator*(const MatrixFloat& a, const MatrixFloat& b) {
        if (a.m != b.n) {
            MatrixFloat temp(1, 1);
            return temp;
        }

        MatrixFloat temp(a.n, b.m, 0.0f);
        for (int i = 0; i < a.n; i++) {
            for (int j = 0; j < b.m; j++) {
                float sum = 0;
                for (int k = 0; k < a.m; k++) {
                    sum += a.rows[i][k] * b.rows[k][j];
                }
                temp.rows[i][j] = sum;
            }
        }
        return temp;
    }

    friend MatrixFloat operator*(const MatrixFloat& a, const VectorFloat& v) {
        if (a.m != v.getSize()) {
            MatrixFloat temp(1, 1);
            return temp;
        }
        MatrixFloat temp(a.n, 1, 0.0f);
        for (int i = 0; i < a.n; i++) {
            float sum = 0;
            for (int j = 0; j < a.m; j++) {
sum += a.rows[i][j] * v[j];
            }
            temp.rows[i][0] = sum;
        }
        return temp;
    }

    friend bool operator==(const MatrixFloat& a, const MatrixFloat& b) {
        if (a.n != b.n || a.m != b.m) return false;
        for (int i = 0; i < a.n; i++) {
            if (a.rows[i] != b.rows[i]) return false;
        }
        return true;
    }

    friend bool operator!=(const MatrixFloat& a, const MatrixFloat& b) {
        return !(a == b);
    }

    friend bool operator>(const MatrixFloat& a, const MatrixFloat& b) {
        return a() > b();
    }

    friend bool operator<(const MatrixFloat& a, const MatrixFloat& b) {
        return a() < b();
    }

    friend bool operator>=(const MatrixFloat& a, const MatrixFloat& b) {
        return a() >= b();
    }

    friend bool operator<=(const MatrixFloat& a, const MatrixFloat& b) {
        return a() <= b();
    }

    friend ostream& operator<<(ostream& out, const MatrixFloat& mat) {
        for (int i = 0; i < mat.n; i++) {
            out << mat.rows[i] << endl;
        }
        return out;
    }

    friend istream& operator>>(istream& in, MatrixFloat& mat) {
        for (int i = 0; i < mat.n; i++) {
            in >> mat.rows[i];
        }
        return in;
    }
};

int MatrixFloat::countMatrix = 0;

// =====================================================
//                     TEST FUNCTIONS
// =====================================================

void testTask1() {
    cout << "\n================ TASK 1. VECTORFLOAT ================\n";

    VectorFloat a(5), b(5), c(5), d(5), e(5);

    a.fillRandom();
    b.fillRandom();
    c.fillRandom();
    d.fillRandom();
    e.fillRandom();

    cout << "A = " << a << endl;
    cout << "B = " << b << endl;
    cout << "C = " << c << endl;
    cout << "D = " << d << endl;
    cout << "E = " << e << endl;

    VectorFloat result1 = ((a + b) * 2.0f - c) / 2.0f + (d % 3);
    cout << "\nExpression 1 = ((A + B) * 2 - C) / 2 + (D % 3)\n";
    cout << "Result1 = " << result1 << endl;

    VectorFloat result2 = -((a - b) + c * 3.0f - d / 2.0f);
    cout << "\nExpression 2 = -((A - B) + C * 3 - D / 2)\n";
    cout << "Result2 = " << result2 << endl;

    cout << "\nPrefix ++A: " << ++a << endl;
    cout << "Postfix B++: " << b++ << endl;
    cout << "B after postfix: " << b << endl;

    cout << "\nA[2] = " << a[2] << endl;
    cout << "Sum of A elements A() = " << a() << endl;
    cout << "!A = " << (!a ? "true" : "false") << endl;

    a.saveToFile("vector_output.txt");
    cout << "\nVector A saved to vector_output.txt\n";
}

void testTask2() {
    cout << "\n================ TASK 2. COUNTRY-CAPITAL ================\n";

    CountryCapitalMap map;
    map.add("Ukraine", "Kyiv");
    map.add("Poland", "Warsaw");
    map.add("France", "Paris");
    map.add("Germany", "Berlin");
    map.add("Italy", "Rome");

    cout << map << endl;

    cout << "Capital of Ukraine: " << map["Ukraine"] << endl;
    cout << "Capital of France (operator()): " << map("France") << endl;
    cout << "Capital of Spain (operator()): " << map("Spain") << endl;

    map.saveToFile("countries_output.txt");
    cout << "\nMap saved to countries_output.txt\n";
}

void testTask3() {
    cout << "\n================ TASK 3. MATRIXFLOAT ================\n";

    MatrixFloat A(2, 2), B(2, 2), C(2, 2), D(2, 2);
    A.fillRandom();
    B.fillRandom();
    C.fillRandom();
    D.fillRandom();

    cout << "Matrix A:\n" << A << endl;
    cout << "Matrix B:\n" << B << endl;
    cout << "Matrix C:\n" << C << endl;
    cout << "Matrix D:\n" << D << endl;

    MatrixFloat result1 = ((A + B) * 2.0f - C) / 2.0f + (D % 3);
    cout << "Expression 1 = ((A + B) * 2 - C) / 2 + (D % 3)\n";
    cout << result1 << endl;

    MatrixFloat result2 = (A * B) + C - D * 2.0f;
    cout << "Expression 2 = (A * B) + C - D * 2\n";
    cout << result2 << endl;

    VectorFloat v(2);
    v.fillRandom();
    cout << "Vector V = " << v << endl;

    MatrixFloat result3 = A * v;
    cout << "Expression 3 = A * V\n";
    cout << result3 << endl;
cout << "A() = " << A() << endl;
    cout << "++A:\n" << ++A << endl;
    cout << "Number of existing matrix objects: " << MatrixFloat::getCountMatrix() << endl;

    A.saveToFile("matrix_output.txt");
    cout << "\nMatrix A saved to matrix_output.txt\n";
}

// =====================================================
//               INPUT DEMONSTRATION FUNCTIONS
// =====================================================

void demoVectorInputMethods() {
    cout << "\n--- Vector input methods ---\n";

    VectorFloat v1(5), v2(5), v3(5);

    cout << "1) Keyboard input:\n";
    // v1.fillFromKeyboard();   // розкоментуй, якщо треба вручну

    cout << "2) File input from vector_input.txt\n";
    v2.fillFromFile("vector_input.txt");
    cout << "V2 = " << v2 << endl;

    cout << "3) Random input:\n";
    v3.fillRandom();
    cout << "V3 = " << v3 << endl;
}

void demoCountryInputMethods() {
    cout << "\n--- Country-capital input methods ---\n";

    CountryCapitalMap m1, m2, m3;

    cout << "1) Keyboard input\n";
    // cin >> m1;   // розкоментуй, якщо треба вручну

    cout << "2) File input from countries_input.txt\n";
    m2.fillFromFile("countries_input.txt");
    cout << m2 << endl;

    cout << "3) Random input\n";
    m3.fillRandom();
    cout << m3 << endl;
}

void demoMatrixInputMethods() {
    cout << "\n--- Matrix input methods ---\n";

    MatrixFloat m1(2, 2), m2(2, 2), m3(2, 2);

    cout << "1) Keyboard input\n";
    // m1.fillFromKeyboard();   // розкоментуй, якщо треба вручну

    cout << "2) File input from matrix_input.txt\n";
    m2.fillFromFile("matrix_input.txt");
    cout << m2 << endl;

    cout << "3) Random input\n";
    m3.fillRandom();
    cout << m3 << endl;
}

// =====================================================
//                          MAIN
// =====================================================

int main() {
    srand(static_cast<unsigned int>(time(0)));

    cout << "LAB WORK: OPERATOR OVERLOADING\n";

    testTask1();
    testTask2();
    testTask3();

    cout << "\n================ INPUT METHODS DEMO ================\n";
    demoVectorInputMethods();
    demoCountryInputMethods();
    demoMatrixInputMethods();

    return 0;
}
