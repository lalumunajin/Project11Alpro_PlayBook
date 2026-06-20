#include<iostream>
#include <conio.h> 
using namespace std;

#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define CYAN   "\033[36m"
#define RESET  "\033[0m"

string pad(string teks, int lebar, bool kiri = true) {
    if ((int)teks.length() >= lebar) return teks;
    string spasi(lebar - (int)teks.length(), ' ');
    return kiri ? teks + spasi : spasi + teks;
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

void garis()      { for (int i = 0; i < 105; i++) cout << "="; cout << endl; }
void garisBatas() { cout << "|"; for (int i = 0; i < 103; i++) cout << "="; cout << "|" << endl; }
string select(string teks) { return string(CYAN) + teks + RESET; }

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

string formatRupiah(int angka) {
    string hasil = to_string(angka);
    int pos = (int)hasil.length() - 3;
    while (pos > 0) { hasil.insert(pos, "."); pos -= 3; }
    return "Rp " + hasil;
}

void baris5(string k1, int w1, string k2, int w2, string k3, int w3,
            string warnaK3, string k4, int w4, string k5, int w5) {
    cout << "| " << pad(k1, w1) << "| " << pad(k2, w2) << "| "
         << warnaK3 << pad(k3, w3) << RESET << "| "
         << pad(k4, w4, false) << "| " << pad(k5, w5) << "|" << endl;
}

void cetakStatistik(string label, string nilai) {
    string titik(48, '.');
    cout << "|  " << pad(label, 25) << titik << " " << pad(nilai, 24) << "|" << endl;
}

struct dataMember {
    string username[50];
    string name[50];
    string email[50];
    string pass[50];
    string noTelp[50];         
    int    umur[50];
    int    poin[50];           
    int    totalJamSewa[50];   
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

string currentUsername = "";
string currentRole = "";
int memberLoginIdx = -1;

void tambahPoin(int *poin, int *pemasukanPoin, int *totalJam, int jumlahPoin, int jam) {
    *poin += jumlahPoin; *pemasukanPoin += jumlahPoin; *totalJam += jam;
}

void updateStatusUnit(UnitPS *unit, string statusBaru) { unit->status = statusBaru; }

void editProfilMember(string *nama, string *noTelp) {
    cout << "  Nama baru    : "; *nama   = inputString();
    cout << "  No. HP baru  : "; *noTelp = inputString();
}

bool gantiPassword(string *pass) {
    string oldPass, newPass, konfirm;
    cout << "  Password lama       : "; cin >> oldPass; bersihkanBuffer();
    if (oldPass != *pass) { cout << RED << "  Password salah!\n" << RESET; return false; }
    cout << "  Password baru       : "; cin >> newPass; bersihkanBuffer();
    cout << "  Konfirmasi password : "; cin >> konfirm; bersihkanBuffer();
    if (newPass != konfirm) { cout << RED << "  Konfirmasi tidak cocok!\n" << RESET; return false; }
    *pass = newPass;
    return true;
}

void simpanBooking(Booking *arr, int *jumlah, string uname, string nama,
                    int unitId, string tipe, int durasi, int harga, int poin) {
    int idx = *jumlah;
    arr[idx] = {uname, nama, tipe, "Menunggu", unitId, durasi, harga, poin};
    (*jumlah)++;
}

void hapusBooking(Booking *arr, int *jumlah, int index) {
    for (int i = index; i < (*jumlah) - 1; i++) arr[i] = arr[i + 1];
    (*jumlah)--;
}

void menuMemberLandscape() {
    cout << "Masuk Menu Member\n";
}

void menuOperatorLandscape() {
    cout << "Masuk Menu Operator\n";
}

void login() {
    system("cls"); banner();
    tengah("MASUK KE AKUN", 105);
    garisBatas();
    if (jumlahMember == 0 && daftarOperator.count == 0) {
        tengah("Belum ada akun! Silakan daftar terlebih dahulu.", 105);
        garisBatas(); system("pause"); return;
    }
    string uname, pass;
    cout << "  Username : "; cin >> uname; bersihkanBuffer();
    cout << "  Password : "; cin >> pass;  bersihkanBuffer();

    for (int i = 0; i < jumlahMember; i++) {
        if (daftarMember.username[i] == uname && daftarMember.pass[i] == pass) {
            currentUsername = uname; currentRole = "Member"; memberLoginIdx = i;
            cout << GREEN << "\n  Login berhasil! Selamat datang, " << daftarMember.name[i] << "!\n" << RESET;
            system("pause");
            menuMemberLandscape();
            return;
        }
    }
    for (int i = 0; i < daftarOperator.count; i++) {
        if (daftarOperator.username[i] == uname && daftarOperator.pass[i] == pass) {
            currentUsername = uname; currentRole = "Operator"; operatorLoginIdx = i;
            cout << GREEN << "\n  Login berhasil! Selamat datang, Operator " << daftarOperator.name[i] << "!\n" << RESET;
            system("pause");
            menuOperatorLandscape();
            return;
        }
    }
    cout << RED << "\n  Username atau password salah!\n" << RESET;
    system("pause");
}

void signUp() {
    int pilihan = 1;
    char nav;
    while (true) {
        system("cls"); banner();
        tengah("DAFTAR AKUN BARU", 105);
        garisBatas();
        tengah("Daftar Sebagai:", 105);
        tengah("", 105);
        tengah(pilihan == 1 ? select("Member  ") : "Member  ", pilihan == 1 ? 114 : 105);
        tengah(pilihan == 2 ? select("Operator") : "Operator", pilihan == 2 ? 114 : 105);
        tengah("", 105);
        garis();

        nav = getch();
        switch (nav) {
            case 72: if (pilihan == 1) pilihan = 2; else pilihan--; break;
            case 80: if (pilihan == 2) pilihan = 1; else pilihan++; break;
            case 13:
                if (pilihan == 1) {
                    system("cls"); banner();
                    tengah("DAFTAR SEBAGAI MEMBER", 105);
                    garisBatas();
                    int i = jumlahMember;
                    daftarMember.name[i]     = inputValidasi("  Nama Lengkap : ", hanyaHuruf, "Nama hanya boleh huruf!");
                    daftarMember.username[i] = inputValidasi("  Username     : ", hanyaHuruf, "Username hanya boleh huruf!");
                    daftarMember.umur[i]     = inputUmur("  Umur         : ");
                    daftarMember.noTelp[i]   = inputValidasi("  No. HP       : ", hanyaAngka, "No. HP harus berupa angka!");
                    cout << "  Email        : "; cin >> daftarMember.email[i]; bersihkanBuffer();
                    cout << "  Password     : "; cin >> daftarMember.pass[i];  bersihkanBuffer();
                    daftarMember.poin[i] = daftarMember.totalJamSewa[i] = 0;
                    daftarMember.pemasukanPoin[i] = daftarMember.pengeluaranPoin[i] = 0;
                    jumlahMember++;
                    cout << GREEN << "\n  Pendaftaran berhasil sebagai Member!\n" << RESET;
                    system("pause"); return;
                } else if (pilihan == 2) {
                    system("cls"); banner();
                    tengah("DAFTAR SEBAGAI OPERATOR", 105);
                    garisBatas();
                    int idx = daftarOperator.count;
                    daftarOperator.name[idx]     = inputValidasi("  Nama Lengkap : ", hanyaHuruf, "Nama hanya boleh huruf!");
                    daftarOperator.username[idx] = inputValidasi("  Username     : ", hanyaHuruf, "Username hanya boleh huruf!");
                    cout << "  Password     : "; cin >> daftarOperator.pass[idx]; bersihkanBuffer();
                    daftarOperator.count++;
                    cout << GREEN << "\n  Pendaftaran berhasil sebagai Operator!\n" << RESET;
                    system("pause"); return;
                }
                break;
        }
    }
}

int main() {
    int pilihan = 1;
    char nav;
    while (true) {
        system("cls"); banner();
        tengah("Selamat Datang di PlayBook!", 105);
        tengah("~ Your Gaming Zone, Anytime ~", 105);
        garisBatas();
        tengah("", 105);
        tengah(pilihan == 1 ? select("Sign Up") : "Sign Up", pilihan == 1 ? 114 : 105);
        tengah(pilihan == 2 ? select("Sign In") : "Sign In", pilihan == 2 ? 114 : 105);
        tengah(pilihan == 3 ? select("Exit   ") : "Exit   ", pilihan == 3 ? 114 : 105);
        tengah("", 105);
        garis();

        nav = getch();
        switch (nav) {
            case 72: if (pilihan == 1) pilihan = 3; else pilihan--; break;
            case 80: if (pilihan == 3) pilihan = 1; else pilihan++; break;
            case 13:
                if (pilihan == 1) signUp();
                else if (pilihan == 2) login();
                else if (pilihan == 3) {
                    system("cls");
                    cout << GREEN << "Terima kasih telah menggunakan PlayBook!\n" << RESET;
                    return 0;
                }
                break;
        }
    }
    return 0;
}
