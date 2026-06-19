#include<iostream>
#include <conio.h> 
using namespace std;

char navigasi;
void efekLoading(string proses) {
    cout << proses;
    for (int i = 0; i < 3; i++) {
        cout << ". ";
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
        garisBatas();
        system("pause"); efekLoading("Loading"); return;
    }

    string uname, pass;
    cout << "  Username : "; cin >> uname; bersihkanBuffer();
    cout << "  Password : "; cin >> pass;  bersihkanBuffer();
    bool found = false;

    for (int i = 0; i < jumlahMember; i++) {
        if (daftarMember.username[i] == uname && daftarMember.pass[i] == pass) {
            currentUsername = uname;
            currentRole     = "Member";
            memberLoginIdx  = i;
            cout << "\n  Login berhasil! Selamat datang, " << daftarMember.name[i] << "!\n";
            found = true;
            system("pause"); efekLoading("Loading");
            menuMemberLandscape();
            return;
        }
    }

    for (int i = 0; i < daftarOperator.count; i++) {
        if (daftarOperator.username[i] == uname && daftarOperator.pass[i] == pass) {
            currentUsername  = uname;
            currentRole      = "Operator";
            operatorLoginIdx = i;
            cout << "\n  Login berhasil! Selamat datang, Operator " << daftarOperator.name[i] << "!\n";
            found = true;
            system("pause"); efekLoading("Loading");
            menuOperatorLandscape();
            return;
        }
    }

    if (!found) {
        cout << "\n  Username atau password salah!\n";
        system("pause"); efekLoading("Loading");
    }
}

void signUp() {
    int  pilihan = 1;
    char nav;

    while (true) {
        system("cls"); banner();
        tengah("DAFTAR AKUN BARU", 105);
        garisBatas();
        tengah("Daftar Sebagai:", 105);
        tengah("", 105);
        if (pilihan == 1) tengah(select("Member  "), 114);
        else              tengah("Member  ", 105);
        if (pilihan == 2) tengah(select("Operator"), 114);
        else              tengah("Operator", 105);
        tengah("", 105);
        garis();

        nav = getch();
        switch (nav) {
            case 72: 
                if (pilihan == 1) pilihan = 2; else pilihan--;
                break;
            case 80: 
                if (pilihan == 2) pilihan = 1; else pilihan++;
                break;
            case 13: 
                if (pilihan == 1) {
                    
                    efekLoading("Loading");
                    system("cls"); banner();
                    tengah("DAFTAR SEBAGAI MEMBER", 105);
                    garisBatas();
                    int i = jumlahMember;
                    
                    cout << "  Nama Lengkap : "; daftarMember.name[i]     = inputString();
                    cout << "  Username     : "; cin >> daftarMember.username[i]; bersihkanBuffer();
                    cout << "  Umur         : "; cin >> daftarMember.umur[i];     bersihkanBuffer();
                    cout << "  No. HP       : "; daftarMember.noTelp[i]   = inputString();
                    cout << "  Email        : "; cin >> daftarMember.email[i];    bersihkanBuffer();
                    cout << "  Password     : "; cin >> daftarMember.pass[i];     bersihkanBuffer();

                    
                    daftarMember.poin[i]            = 0;
                    daftarMember.totalJamSewa[i]    = 0;
                    daftarMember.pemasukanPoin[i]   = 0;
                    daftarMember.pengeluaranPoin[i] = 0;
                    jumlahMember++;

                    cout << "\n  Pendaftaran berhasil sebagai Member!\n";
                    system("pause"); efekLoading("Loading"); return;

                } else if (pilihan == 2) {
                    
                    efekLoading("Loading");
                    system("cls"); banner();
                    tengah("DAFTAR SEBAGAI OPERATOR", 105);
                    garisBatas();
                    int idx = daftarOperator.count;
                    cout << "  Nama Lengkap : "; daftarOperator.name[idx]     = inputString();
                    cout << "  Username     : "; cin >> daftarOperator.username[idx]; bersihkanBuffer();
                    cout << "  Password     : "; cin >> daftarOperator.pass[idx];     bersihkanBuffer();
                    daftarOperator.count++;

                    cout << "\n  Pendaftaran berhasil sebagai Operator!\n";
                    system("pause"); efekLoading("Loading"); return;
                }
                break;
        }
    }
}

void mainMenu() { 
    int  pilihan = 1;
    char nav;

    while (true) {
        system("cls"); banner(); 
        tengah("Selamat Datang di PlayBook!", 105);
        tengah("~ Your Gaming Zone, Anytime ~", 105);
        garisBatas();
        tengah("", 105);
        if (pilihan == 1) tengah(select("Sign Up"), 114);
        else              tengah("Sign Up", 105);
        if (pilihan == 2) tengah(select("Sign In"), 114);
        else              tengah("Sign In", 105);
        if (pilihan == 3) tengah(select("Exit   "), 114);
        else              tengah("Exit   ", 105);
        tengah("", 105);
        garis();

        nav = getch();
        switch (nav) {
            case 72: 
                if (pilihan == 1) pilihan = 3; else pilihan--;
                break;
            case 80: 
                if (pilihan == 3) pilihan = 1; else pilihan++;
                break;
            case 13: 
                if (pilihan == 1) {
                    efekLoading("Loading");
                    signUp(); 
                } else if (pilihan == 2) {
                    efekLoading("Loading");
                    login();
                } else if (pilihan == 3) {
                    efekLoading("Terima kasih telah menggunakan PlayBook");
                    return;
                }
                break;
        }
    }
}
int main() {
    mainMenu();
    return 0;
}
