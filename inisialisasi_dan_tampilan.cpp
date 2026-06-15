#include <iostream>  
#include <conio.h>   
using namespace std;



char navigasi;

void efekLoading(string proses) {
    cout << proses;
    for (int i = 0; i < 3; i++) {
        cout << ". ";
        sleep(1);
    }
    cout << endl;
}

void banner() {
    for (int i = 0; i < 105; i++) cout << "="; cout << endl;
    cout << "\033[36m" << R"(

ooooooooo.   oooo                         oooooooooo.                        oooo        
`888   `Y88. `888                        `888'   `Y8b                       `888        
 888   .d88'  888   .oooo.   oooo    ooo  888     888  .ooooo.   .ooooo.      888  oooo  
 888ooo88P'   888  `P  )88b   `88b..8P'   888oooo888' d88' `88b d88' `88b     888 .8P'  
 888          888   .oP"888     Y888'     888    `88b 888   888 888   888     888888.    
 888          888  d8(  888   .o8"'       888    .88P 888   888 888   888     888 `88b.  
o888o        o888o `Y888""8o o88'         o888bood8P'  `Y8bod8P' `Y8bod8P'   o888o o888o 

)" << "\033[0m";
    for (int i = 0; i < 105; i++) cout << "="; cout << endl;
}

void tengah(string teks, int kolom) {
    int totalSpasi = kolom - 2 - (int)teks.length();
    int spasiKiri  = max(0, totalSpasi / 2);
    int spasiKanan = max(0, totalSpasi - spasiKiri);
    cout << "|" << string(spasiKiri, ' ') << teks << string(spasiKanan, ' ') << "|\n";
}

void garis() {
    for (int i = 0; i < 105; i++) cout << "="; cout << endl;
}

void garisBatas() {
    cout << "|";
    for (int i = 0; i < 103; i++) cout << "=";
    cout << "|" << endl;
}

string select(string teks) {
    return "\033[36m" + teks + "\033[0m";
}

void bersihkanBuffer() {
    cin.clear();
    cin.ignore(1000, '\n');
}

string inputString() {
    string hasil;
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, hasil);
    return hasil;
}

struct dataMember {
    string username[50];
    string name[50];
    string email[50];
    string pass[50];
    string noTelp[50];         
    int    umur[50];
    int    poin[50];           
    int    pemasukanPoin[50];  
    int    pengeluaranPoin[50];
} daftarMember;
int jumlahMember = 0; 

struct dataOperator {
    string username[20];
    string name[20];
    string pass[20];
    int count = 0;
} daftarOperator;
int operatorLoginIdx = -1; 

struct UnitPS {
    int    id;
    string tipe;         
    string status;       
    int    hargaPerJam;
};

UnitPS daftarUnit[10] = {
    {1,  "PS4 Reguler", "Tersedia", 8000 },
    {2,  "PS4 Reguler", "Tersedia", 8000 },
    {3,  "PS4 Reguler", "Tersedia", 8000 },
    {4,  "PS4 VIP    ", "Tersedia", 12000},
    {5,  "PS4 VIP    ", "Tersedia", 12000},
    {6,  "PS4 VIP    ", "Tersedia", 12000},
    {7,  "PS5 Reguler", "Tersedia", 15000},
    {8,  "PS5 Reguler", "Tersedia", 15000},
    {9,  "PS5 VIP    ", "Tersedia", 20000},
    {10, "PS5 VIP    ", "Tersedia", 20000}
};

struct Booking {
    string memberUsername; 
    string memberName;     
    int    unitId;         
    string tipePS;         
    int    durasi;        
    int    totalHarga;     
    int    poinDapat;     
    string status;         
};
Booking daftarBooking[100]; 
int jumlahBooking = 0;      

struct BarangRedeem {
    string nama;
    int    hargaPoin;
};

BarangRedeem daftarBarang[] = {
    {"Snack Gratis        ", 20 },
    {"Minuman Gratis      ", 15 },
    {"Extend 30 Menit     ", 25 },
    {"Gratis 1 Jam PS4    ", 50 },
    {"Gratis 1 Jam PS5    ", 80 },
    {"Merchandise PlayBook", 100}
};
const int jumlahBarang = 6; 

string historyRedeem[100]; 
int    jumlahHistory   = 0; 
int    totalPendapatan = 0; 

string currentUsername = "";
string currentRole     = "";
int    memberLoginIdx  = -1;