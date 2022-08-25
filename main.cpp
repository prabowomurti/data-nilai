#include <iostream>
#include <map>
#include "table.h"

using namespace std;

char choice;

struct Mahasiswa {
    string nim;
    string nama;
    string jurusan;
};

struct MataKuliah {
    string kode;
    string nama;
    int sks;
};

struct Nilai {
    string nim;
    string kodeMataKuliah;
    int nilaiUTS;
    int nilaiTugas;
    int nilaiUAS;
    int nilaiAkhir;
    char grade;
};

Mahasiswa listMahasiswa[1000];
int numOfMahasiswa = 0;
MataKuliah listMataKuliah[100];
int numOfMataKuliah = 0;
Nilai listNilai[1000];
int numOfNilai = 0; // hold the number(count) of nilai data rows

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

// display menu to input data Mahasiswa
void inputMahasiswa()
{   
    char subMenuChoice;

    do {
        tulisHeader("INPUT DATA MAHASISWA");

        cout << "Input Nilai Mahasiswa: " + to_string(numOfMahasiswa + 1) << endl;
        cout << "NIM : ";
        cin >> listMahasiswa[numOfMahasiswa].nim;
        cout << "Nama : ";
        getline(cin >> ws, listMahasiswa[numOfMahasiswa].nama);
        cout << "Jurusan : ";
        getline(cin >> ws, listMahasiswa[numOfMahasiswa].jurusan);

        numOfMahasiswa++;

        cout << "Tambahkan Mahasiswa Lagi? [y/n] : ";
        cin >> subMenuChoice;

    } while (subMenuChoice != 'n');

}

// display menu to input MataKuliah
void inputMataKuliah()
{
    char subMenuChoice;

    do {
        tulisHeader("INPUT DATA MATA KULIAH");
        cout << "Input Mata Kuliah: " + to_string(numOfMataKuliah + 1) << endl;
        cout << "Kode Mata Kuliah : ";
        cin >> listMataKuliah[numOfMataKuliah].kode;
        cout << "Nama Mata Kuliah : ";
        getline(cin >> ws, listMataKuliah[numOfMataKuliah].nama);
        cout << "Bobot SKS : ";
        cin >> listMataKuliah[numOfMataKuliah].sks;
        
        numOfMataKuliah++;

        cout << "Tambahkan Mata Kuliah Lagi? [y/n] : ";
        cin >> subMenuChoice;
    } while (subMenuChoice != 'n');
}

// calculate nilaiAkhir based on UTS, Tugas, and UAS
int calculateNilaiAkhir(int nilaiUTS, int nilaiTugas, int nilaiUAS)
{
    return (nilaiUTS * 30 / 100) + (nilaiTugas * 30 / 100) + (nilaiUAS * 40 / 100);
}

// calculate grade based on nilaiAkhir
char calculateGrade(int nilaiAkhir) {
    if (nilaiAkhir >= 85) {
        return 'A';
    } else if (nilaiAkhir >= 75) {
        return 'B';
    } else if (nilaiAkhir >= 60) {
        return 'C';
    } else if (nilaiAkhir >= 40) {
        return 'D';
    }

    return 'E';
}

// show data input menu for Nilai Mahasiswa
void inputNilaiMahasiswa()
{
    char subMenuChoice;
    string nim;
    string kodeMataKuliah;

    do {
        tulisHeader("INPUT DATA NILAI MAHASISWA");
        cout << "Input Nilai Mahasiswa : " + to_string(numOfNilai + 1) << endl;
        
        cout << "Input NIM : ";
        cin >> nim;

        // search Mahasiswa by NIM
        // TODO: move search to a function
        for (int i = 0; i < numOfMahasiswa; i++) {
            if (nim == listMahasiswa[i].nim) {
                cout << "Nama : " << listMahasiswa[i].nama << endl;
                cout << "Jurusan : " << listMahasiswa[i].jurusan << endl;

                listNilai[numOfNilai].nim = nim;
            }
        }

        if (listNilai[numOfNilai].nim == "") {
            cout << "NIM tidak ditemukan" << endl;
            continue;
        }
        
        cout << "Kode Mata Kuliah : ";
        cin >> kodeMataKuliah;

        // search Mata Kuliah by Kode Mata Kuliah
        // TODO: move search to a function
        for (int i = 0; i < numOfMataKuliah; i++) {
            if (kodeMataKuliah == listMataKuliah[i].kode) {
                cout << "Nama Mata Kuliah : " << listMataKuliah[i].nama << endl;
                cout << "Bobot SKS : " << listMataKuliah[i].sks << endl;
                listNilai[numOfNilai].kodeMataKuliah = kodeMataKuliah;
            }
        }

        if (listNilai[numOfNilai].kodeMataKuliah == "") {
            cout << "Kode Mata Kuliah tidak ditemukan" << endl;
            listNilai[numOfNilai].nim = "";
            continue;
        }

        cout << "Nilai UTS : ";
        cin >> listNilai[numOfNilai].nilaiUTS;
        cout << "Nilai Tugas : ";
        cin >> listNilai[numOfNilai].nilaiTugas;
        cout << "Nilai UAS : ";
        cin >> listNilai[numOfNilai].nilaiUAS;

        listNilai[numOfNilai].nilaiAkhir = calculateNilaiAkhir(
            listNilai[numOfNilai].nilaiUTS,
            listNilai[numOfNilai].nilaiTugas,
            listNilai[numOfNilai].nilaiUAS);

        cout << "Nilai Akhir : " + to_string(listNilai[numOfNilai].nilaiAkhir) << endl;

        listNilai[numOfNilai].grade = calculateGrade(listNilai[numOfNilai].nilaiAkhir);
        cout << "Grade : " + string (1, listNilai[numOfNilai].grade) << endl;
        
        // success input nilai mahasiswa, increment the counter
        numOfNilai++;
        
        cout << "Tambahkan Nilai Lagi? [y/n] : ";
        cin >> subMenuChoice;
    } while (subMenuChoice != 'n');
}

int tampilkanDaftarNilaiMahasiswa()
{
    clitable::Table table;
    clitable::Column c[12] = {
        clitable::Column("NO", clitable::Column::CENTER_ALIGN, clitable::Column::LEFT_ALIGN, 1,4,clitable::Column::RESIZABLE),
        clitable::Column("NIM", clitable::Column::CENTER_ALIGN, clitable::Column::LEFT_ALIGN, 1,7,clitable::Column::RESIZABLE),
        clitable::Column("NAMA", clitable::Column::CENTER_ALIGN, clitable::Column::LEFT_ALIGN, 1,10,clitable::Column::RESIZABLE),
        clitable::Column("JURUSAN", clitable::Column::CENTER_ALIGN, clitable::Column::LEFT_ALIGN, 1,10,clitable::Column::RESIZABLE),
        clitable::Column("KODE MTK", clitable::Column::CENTER_ALIGN, clitable::Column::LEFT_ALIGN, 1,8,clitable::Column::RESIZABLE),
        clitable::Column("NAMA MTK", clitable::Column::CENTER_ALIGN, clitable::Column::LEFT_ALIGN, 1,10,clitable::Column::RESIZABLE),
        clitable::Column("SKS", clitable::Column::CENTER_ALIGN, clitable::Column::LEFT_ALIGN, 1,4,clitable::Column::RESIZABLE),
        clitable::Column("UTS", clitable::Column::CENTER_ALIGN, clitable::Column::LEFT_ALIGN, 1,4,clitable::Column::RESIZABLE),
        clitable::Column("TUGAS", clitable::Column::CENTER_ALIGN, clitable::Column::LEFT_ALIGN, 1,4,clitable::Column::RESIZABLE),
        clitable::Column("UAS", clitable::Column::CENTER_ALIGN, clitable::Column::LEFT_ALIGN, 1,4,clitable::Column::RESIZABLE),
        clitable::Column("AKHIR", clitable::Column::CENTER_ALIGN, clitable::Column::LEFT_ALIGN, 1,4,clitable::Column::RESIZABLE),
        clitable::Column("GRADE", clitable::Column::CENTER_ALIGN, clitable::Column::LEFT_ALIGN, 1,4,clitable::Column::RESIZABLE)
    };

    string r[numOfNilai][12];

    table.addTitle("DAFTAR NILAI MAHASISWA");

    for (int i = 0; i < 12; i++) table.addColumn(c[i]);

    for (int i = 0; i < numOfNilai; i++) {
        r[i][0] = to_string(i + 1);
        r[i][1] = listNilai[i].nim;

        // search nama and jurusan by NIM
        for (int j = 0; j < numOfMahasiswa; j++) {
            if (listNilai[i].nim == listMahasiswa[j].nim) {
                r[i][2] = listMahasiswa[j].nama;
                r[i][3] = listMahasiswa[j].jurusan;
            }
        }

        r[i][4] = listNilai[i].kodeMataKuliah;

        // search nama and sks by Kode Mata Kuliah
        for (int j = 0; j < numOfMataKuliah; j++) {
            if (listNilai[i].kodeMataKuliah == listMataKuliah[j].kode) {
                r[i][5] = listMataKuliah[j].nama;
                r[i][6] = to_string(listMataKuliah[j].sks);
            }
        }

        r[i][7] = to_string(listNilai[i].nilaiUTS);
        r[i][8] = to_string(listNilai[i].nilaiTugas);
        r[i][9] = to_string(listNilai[i].nilaiUAS);
        r[i][10] = to_string(listNilai[i].nilaiAkhir);
        r[i][11] = string (1, listNilai[i].grade);

        table.addRow(r[i]);
    }

    cout << table.draw();
    cout << "Tekan Enter untuk kembali ke Menu Utama... " << endl;
    
    // TODO: find a better way
    system("read");

    return 0;
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
        case '1':
            inputMahasiswa();
            break;
        case '2':
            inputMataKuliah();
            break;
        case '3': 
            inputNilaiMahasiswa();
            break;
        case '4':
            tampilkanDaftarNilaiMahasiswa();
            break;
        
        case '5': 
            cout << "Terima Kasih" << endl;
            break;
        
        default:
            cout << "Pilihan tidak tersedia" << endl;
        }

    } while (choice != '5');
    
    return EXIT_SUCCESS;
}

