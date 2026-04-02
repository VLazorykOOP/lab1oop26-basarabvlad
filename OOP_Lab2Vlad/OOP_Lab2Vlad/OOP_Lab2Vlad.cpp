#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

using namespace std;

// ================= TASK 1 =================
int calculateExpression(int a, int b, int c, int d)
{
    int part1 = (a << 3) + (a << 2);              // 12*a
    int part2 = ((d << 4) - d) + ((b << 3) + (b << 2)); // d*15 + 12*b
    int part3 = part2 >> 10;                     // /1024
    int part4 = (c << 3) + (c << 2);             // 12*c
    int part5 = (d << 4) - d;                    // d*15

    return part1 + part3 - part4 + part5;
}

// ================= TASK 2 =================
void encryptToFile()
{
    ofstream fout("data.bin", ios::binary);
    if (!fout)
    {
        cout << "Помилка відкриття файлу!\n";
        return;
    }

    string lines[4];

    cout << "Введіть 4 рядки (до 32 символів):\n";
    for (int i = 0; i < 4; i++)
    {
        getline(cin, lines[i]);
        lines[i].resize(32, ' ');
    }

    for (int row = 0; row < 4; row++)
    {
        for (int pos = 0; pos < 32; pos++)
        {
            uint16_t word = 0;
            unsigned char ch = static_cast<unsigned char>(lines[row][pos]);

            word |= (pos & 0x1F);          // 0-4
            word |= (row & 0x03) << 5;     // 5-6
            word |= ch << 7;               // 7-14

            // parity bit
            int parity = 0;
            for (int i = 0; i < 15; i++)
                parity ^= (word >> i) & 1;

            word |= parity << 15;

            fout.write(reinterpret_cast<char*>(&word), sizeof(word));
        }
    }

    fout.close();
    cout << "Шифрування завершено.\n";
}

void decryptFromFile()
{
    ifstream fin("data.bin", ios::binary);
    if (!fin)
    {
        cout << "Файл не знайдено!\n";
        return;
    }

    uint16_t word;

    cout << "\nРозшифрований текст:\n";

    while (fin.read(reinterpret_cast<char*>(&word), sizeof(word)))
    {
        int pos = word & 0x1F;
        char ch = static_cast<char>((word >> 7) & 0xFF);

        cout << ch;

        if (pos == 31)
            cout << endl;
    }

    fin.close();
}

// ================= TASK 3 =================
union PackedData
{
    uint16_t value;

    struct
    {
        uint16_t pos : 5;
        uint16_t row : 2;
        uint16_t ch : 8;
        uint16_t parity : 1;
    } bits;
};

void encryptUsingStruct()
{
    ofstream fout("data_struct.bin", ios::binary);
    if (!fout)
    {
        cout << "Помилка файлу!\n";
        return;
    }

    string line;

    cout << "Введіть 4 рядки:\n";

    for (int row = 0; row < 4; row++)
    {
        getline(cin, line);
        line.resize(32, ' ');

        for (int pos = 0; pos < 32; pos++)
        {
            PackedData data{};
            data.bits.pos = pos;
            data.bits.row = row;
            data.bits.ch = static_cast<unsigned char>(line[pos]);

            int parity = 0;
            for (int i = 0; i < 15; i++)
                parity ^= (data.value >> i) & 1;

            data.bits.parity = parity;

            fout.write(reinterpret_cast<char*>(&data.value), sizeof(data.value));
        }
    }

    fout.close();
    cout << "Struct-шифрування завершено.\n";
}

// ================= TASK 4 =================
void checkCRC()
{
    ifstream fin("data.bin", ios::binary);
    if (!fin)
    {
        cout << "Файл не знайдено!\n";
        return;
    }

    uint16_t word;

    cout << "\nПеревірка CRC:\n";

    while (fin.read(reinterpret_cast<char*>(&word), sizeof(word)))
    {
        int odd = 0;
        int even = 0;

        for (int i = 0; i < 14; i++)
        {
            if (i % 2 == 0)
                even ^= (word >> i) & 1;
            else
                odd ^= (word >> i) & 1;
        }

        int crc_odd = (word >> 14) & 1;
        int crc_even = (word >> 15) & 1;

        if (crc_odd != odd || crc_even != even)
            cout << "Помилка передачі!\n";
        else
            cout << "OK\n";
    }

    fin.close();
}

// ================= MENU =================
void menu()
{
    int choice;

    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1
            - Обчислення виразу\n";
            cout << "2 - Шифрування (файл)\n";
        cout << "3 - Дешифрування\n";
        cout << "4 - Шифрування через struct\n";
        cout << "5 - Перевірка CRC\n";
        cout << "0 - Вихід\n";
        cout << "Вибір: ";

        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            int a, b, c, d;
            cout << "Введіть a b c d: ";
            cin >> a >> b >> c >> d;
            cout << "Результат: "
                << calculateExpression(a, b, c, d) << endl;
            break;
        }
        case 2:
            encryptToFile();
            break;
        case 3:
            decryptFromFile();
            break;
        case 4:
            encryptUsingStruct();
            break;
        case 5:
            checkCRC();
            break;
        }

    } while (choice != 0);
}

int main()
{
    menu();
    return 0;
}