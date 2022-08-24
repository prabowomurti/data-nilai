#include <iostream>
#include <map>
#include "table.h"

using namespace std;

int choice;

// menuliskan header diapit separator
void tulisHeader(string title) {
    int length = title.length() + 10;
    cout << string(length, '=') + "\n";
    cout << string(5, ' ') + title + string(5, ' ') + "\n";
    cout << string(length, '=') << endl;
}

void tampilkanMenuUtama() {
    tulisHeader("DATA NILAI");
    cout << "1. Input Mahasiswa" << endl;
    cout << "2. Input Mata Kuliah" << endl;
    cout << "3. Input Nilai Mahasiswa" << endl;
    cout << "4. Tampilkan Daftar Nilai Mahasiswa" << endl;
    cout << "5. Keluar" << endl << endl;

    cout << "Masukkan Pilihan [1..5] : ";
}

void inputMahasiswa()
{
    tulisHeader("INPUT DATA MAHASISWA");
}

void inputMataKuliah()
{
    tulisHeader("INPUT MATA KULIAH");
}

void inputNilaiMahasiswa()
{
    tulisHeader("INPUT NILAI MAHASISWA");
}

void tampilkanDaftarNilaiMahasiswa()
{
    tulisHeader("TAMPILKAN DAFTAR NILAI MAHASISWA");
}

int main()
{
    do
    {
        tampilkanMenuUtama();
        cin >> choice;

        // Pilihan harus berupa angka 1..5
        while (cin.fail()) {
            cout << "PILIHAN HARUS BERUPA ANGKA" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            tampilkanMenuUtama();
            cin >> choice;
            continue;
        }

        // evaluate the choice
        switch (choice)
        {
        case 1:
            inputMahasiswa();
            break;
        case 2:
            inputMataKuliah();
            break;
        case 3: 
            inputNilaiMahasiswa();
            break;
        case 4:
            tampilkanDaftarNilaiMahasiswa();
            break;
        
        case 5: 
            cout << "Terima Kasih" << endl;
            break;
        
        default:
            cout << "Pilihan tidak tersedia" << endl;
        }

    } while (choice != 5);
    
    return EXIT_SUCCESS;
}

