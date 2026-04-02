#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

// ================= VECTOR =================
class VectorFloat {
    float* data;
    int size;
    int codeError;
    static int count;

public:
    VectorFloat() : size(1), codeError(0) {
        data = new float[1] {0};
        count++;
    }

    VectorFloat(int n) : size(n), codeError(0) {
        data = new float[n] {0};
        count++;
    }

    VectorFloat(int n, float val) : size(n), codeError(0) {
        data = new float[n];
        for (int i = 0; i < n; i++) data[i] = val;
        count++;
    }

    VectorFloat(const VectorFloat& v) {
        size = v.size;
        codeError = v.codeError;
        data = new float[size];
        for (int i = 0; i < size; i++) data[i] = v.data[i];
        count++;
    }

    ~VectorFloat() {
        delete[] data;
        count--;
    }

    // ===== оператор =
    VectorFloat& operator=(const VectorFloat& v) {
        if (this != &v) {
            delete[] data;
            size = v.size;
            data = new float[size];
            for (int i = 0; i < size; i++) data[i] = v.data[i];
        }
        return *this;
    }

    // ===== []
    float& operator[](int i) {
        if (i < 0 || i >= size) {
            codeError = 1;
            return data[size - 1];
        }
        return data[i];
    }

    // ===== унарні
    VectorFloat operator-() {
        VectorFloat t(*this);
        for (int i = 0; i < size; i++) t.data[i] = -t.data[i];
        return t;
    }

    bool operator!() {
        return size != 0;
    }

    VectorFloat& operator++() {
        for (int i = 0; i < size; i++) data[i]++;
        return *this;
    }

    VectorFloat operator++(int) {
        VectorFloat temp(*this);
        for (int i = 0; i < size; i++) data[i]++;
        return temp;
    }

    // ===== арифметика
    VectorFloat operator+(const VectorFloat& v) {
        VectorFloat r(size);
        for (int i = 0; i < size; i++)
            r.data[i] = data[i] + v.data[i];
        return r;
    }

    VectorFloat operator-(const VectorFloat& v) {
        VectorFloat r(size);
        for (int i = 0; i < size; i++)
            r.data[i] = data[i] - v.data[i];
        return r;
    }

    VectorFloat operator*(float k) {
        VectorFloat r(size);
        for (int i = 0; i < size; i++)
            r.data[i] = data[i] * k;
        return r;
    }

    // ===== +=
    VectorFloat& operator+=(const VectorFloat& v) {
        for (int i = 0; i < size; i++)
            data[i] += v.data[i];
        return *this;
    }

    // ===== порівняння
    bool operator==(const VectorFloat& v) {
        for (int i = 0; i < size; i++)
            if (data[i] != v.data[i]) return false;
        return true;
    }

    bool operator!=(const VectorFloat& v) {
        return !(*this == v);
    }

    // ===== ()
    float operator()() {
        float s = 0;
        for (int i = 0; i < size; i++) s += data[i];
        return s;
    }

    // ===== введення/виведення
    friend ostream& operator<<(ostream& os, const VectorFloat& v) {
        for (int i = 0; i < v.size; i++)
            os << v.data[i] << " ";
        return os;
    }

    friend istream& operator>>(istream& is, VectorFloat& v) {
        for (int i = 0; i < v.size; i++)
            is >> v.data[i];
        return is;
    }

    static int getCount() { return count; }
};

int VectorFloat::count = 0;

// ================= ASSOCIATIVE =================
class CountryCapital {
    string country;
    string capital;

public:
    CountryCapital(string c = "", string cap = "")
        : country(c), capital(cap) {
    }

    string getCountry() { return country; }
    string getCapital() { return capital; }
};

class Map {
    CountryCapital arr[10];
    int size;
    int codeError;

public:
    Map() : size(0), codeError(0) {}

    void add(string c, string cap) {
        arr[size++] = CountryCapital(c, cap);
    }

    string operator[](string c) {
        for (int i = 0; i < size; i++)
            if (arr[i].getCountry() == c)
                return arr[i].getCapital();

        codeError = 1;
        return "Not found";
    }

    string operator()(string c) {
        return (*this)[c];
    }

    friend ostream& operator<<(ostream& os, Map& m) {
        for (int i = 0; i < m.size; i++)
            os << m.arr[i].getCountry() << " - "
            << m.arr[i].getCapital() << endl;
        return os;
    }
};

// ================= MATRIX =================
class MatrixFloat {
    float** data;
    int n, m;
    int codeError;

public:
    MatrixFloat(int r = 2, int c = 2) : n(r), m(c), codeError(0) {
        data = new float* [n];
        for (int i = 0; i < n; i++) {
            data[i] = new float[m] {0};
        }
    }

    ~MatrixFloat() {
        for (int i = 0; i < n; i++)
            delete[] data[i];
        delete[] data;
    }

    float& operator()(int i, int j) {
        if (i < 0 || j < 0 || i >= n || j >= m) {
            codeError = 1;
            return data[n - 1][m - 1];
        }
        return data[i][j];
    }

    MatrixFloat operator+(const MatrixFloat& mat) {
        MatrixFloat r(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                r.data[i][j] = data[i][j] + mat.data[i][j];
        return r;
    }

    friend ostream& operator<<(ostream& os, MatrixFloat& mat) {
        for (int i = 0; i < mat.n; i++) {
            for (int j = 0; j < mat.m; j++)
                os << mat.data[i][j] << " ";
            os << endl;
        }
        return os;
    }
};

// ================= TEST =================
void testVector() {
    VectorFloat v1(3, 2), v2(3, 1);

    VectorFloat res = (v1 + v2) * 2 - v2; // складний вираз
    cout << "Result: " << res << endl;
}

void testMap() {
    Map m;
    m.add("Ukraine", "Kyiv");
    m.add("France", "Paris");

    cout << m;
    cout << "Capital: " << m["Ukraine"] << endl;
}

void testMatrix() {
    MatrixFloat m1(2, 2), m2(2, 2);
    m1(0, 0) = 1; m2(0, 0) = 2;

    MatrixFloat m3 = m1 + m2;
    cout << m3;
}

// ================= MAIN =================
int main() {
    int choice;

    do {
        cout << "\n1-Vector\n2-Map\n3-Matrix\n0-Exit\n";
        cin >> choice;

        switch (choice) {
        case 1: testVector(); break;
        case 2: testMap(); break;
        case 3: testMatrix(); break;
        }

    } while (choice != 0);

    return 0;
}

// lab4 - це реалізація трьох класів: VectorFloat, Map та MatrixFloat, які демонструють різні аспекти об'єктно-орієнтованого програмування в C++. Клас VectorFloat реалізує вектор з плаваючою точкою, клас Map - асоціативний масив для зберігання країн та їх столиць, а клас MatrixFloat - матрицю з плаваючою точкою. У main() є меню для тестування кожного з цих класів.