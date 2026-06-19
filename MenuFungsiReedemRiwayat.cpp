#include <iostream>  
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

void tambahPoin(int *poin, int *pemasukanPoin, int *totalJam, int jumlahPoin, int jam) {
    *poin          += jumlahPoin;
    *pemasukanPoin += jumlahPoin;
    *totalJam      += jam;
}

void updateStatusUnit(UnitPS *unit, string statusBaru) {
    unit->status = statusBaru;
}

void editProfilMember(string *nama, string *noTelp) {
    cout << "  Nama baru    : "; *nama   = inputString();
    cout << "  No. HP baru  : "; *noTelp = inputString();
}

bool gantiPassword(string *pass) {
    string oldPass, newPass, konfirm;
    cout << "  Password lama       : "; cin >> oldPass; bersihkanBuffer();
    if (oldPass != *pass) {
        cout << "  Password salah!\n";
        return false;
    }
    cout << "  Password baru       : "; cin >> newPass; bersihkanBuffer();
    cout << "  Konfirmasi password : "; cin >> konfirm; bersihkanBuffer();
    if (newPass != konfirm) {
        cout << "  Konfirmasi tidak cocok!\n";
        return false;
    }
    *pass = newPass;
    return true;
}

void simpanBooking(Booking *arrBooking, int *jumlah,
                   string uname, string nama,
                   int unitId, string tipe,
                   int durasi, int harga, int poin) {
    int idx = *jumlah;
    arrBooking[idx].memberUsername = uname;
    arrBooking[idx].memberName     = nama;
    arrBooking[idx].unitId         = unitId;
    arrBooking[idx].tipePS         = tipe;
    arrBooking[idx].durasi         = durasi;
    arrBooking[idx].totalHarga     = harga;
    arrBooking[idx].poinDapat      = poin;
    arrBooking[idx].status         = "Menunggu";
    (*jumlah)++;
}

void menuProfilMember() {
    int pilih;
    while (true) {
        system("cls");
        banner();
        tengah("PROFIL MEMBER", 105);
        garisBatas();
        int i = memberLoginIdx;
        tengah("Nama Lengkap      : " + daftarMember.name[i], 105);
        tengah("Username          : " + daftarMember.username[i], 105);
        tengah("Email             : " + daftarMember.email[i], 105);
        tengah("No. HP            : " + daftarMember.noTelp[i], 105);
        tengah("Umur              : " + to_string(daftarMember.umur[i]) + " tahun", 105);
        garisBatas();
        tengah("=== STATISTIK AKUN ===", 105);
        tengah("Poin Saat Ini     : " + to_string(daftarMember.poin[i]) + " poin", 105);
        tengah("Pemasukan Poin    : " + to_string(daftarMember.pemasukanPoin[i]) + " poin", 105);
        tengah("Pengeluaran Poin  : " + to_string(daftarMember.pengeluaranPoin[i]) + " poin", 105);
        tengah("Total Jam Sewa    : " + to_string(daftarMember.totalJamSewa[i]) + " jam", 105);
        garisBatas();
        tengah("1. Edit Nama & No. HP", 105);
        tengah("2. Ganti Password    ", 105);
        tengah("3. Kembali           ", 105);
        garisBatas();
        cout << "  Pilih menu: ";
        cin >> pilih; bersihkanBuffer();

        if (pilih == 3) {
            break;
        } else if (pilih == 1) {
            system("cls"); banner();
            tengah("EDIT PROFIL", 105);
            garisBatas();
            cout << "  Nama lama   : " << daftarMember.name[i] << "\n";
            cout << "  No HP lama  : " << daftarMember.noTelp[i] << "\n";
            garisBatas();
            editProfilMember(&daftarMember.name[i], &daftarMember.noTelp[i]);
            cout << "  Profil berhasil diperbarui!\n";
            system("pause");
        } else if (pilih == 2) {
            system("cls"); banner();
            tengah("GANTI PASSWORD", 105);
            garisBatas();
            bool berhasil = gantiPassword(&daftarMember.pass[i]);
            if (berhasil) cout << "  Password berhasil diganti!\n";
            system("pause");
        }
    }
}

void menuLihatUnit() {
    system("cls"); banner();
    tengah("STATUS UNIT PLAYSTATION", 105);
    garisBatas();
    tengah("No  | Tipe          | Status      | Harga/Jam", 105);
    garisBatas();
    for (int i = 0; i < 10; i++) {
        string warna;
        if      (daftarUnit[i].status == "Tersedia")  warna = "\033[32m"; 
        else if (daftarUnit[i].status == "Dipakai")   warna = "\033[31m";
        else                                          warna = "\033[33m"; 

        string baris = "";
        baris += (daftarUnit[i].id < 10 ? " " : "");
        baris += to_string(daftarUnit[i].id);
        baris += "  | " + daftarUnit[i].tipe;
        baris += "  | " + warna + daftarUnit[i].status + "\033[0m";
        if      (daftarUnit[i].status == "Tersedia")  baris += "   ";
        else if (daftarUnit[i].status == "Dipakai")   baris += "    ";
        else                                           baris += " ";
        baris += "| Rp " + to_string(daftarUnit[i].hargaPerJam) + "/jam";
        tengah(baris, 105);
    }
    garisBatas();
    tengah("\033[32m[Hijau]\033[0m Tersedia   \033[31m[Merah]\033[0m Dipakai   \033[33m[Kuning]\033[0m Maintenance", 105);
    garisBatas();
    system("pause");
}

void menuBooking() {
    int pilih;
    while (true) {
        system("cls"); banner();
        tengah("BOOKING UNIT PS", 105);
        garisBatas();
        tengah("Unit Yang Tersedia:", 105);
        garisBatas();

        bool adaUnit = false;
        for (int i = 0; i < 10; i++) {
            if (daftarUnit[i].status == "Tersedia") {
                string info = "Unit " + to_string(daftarUnit[i].id) +
                              "  |  " + daftarUnit[i].tipe +
                              "  |  Rp " + to_string(daftarUnit[i].hargaPerJam) + "/jam";
                tengah(info, 105);
                adaUnit = true;
            }
        }
        if (!adaUnit) {
            tengah("Semua unit sedang dipakai! Coba lagi nanti.", 105);
            garisBatas(); system("pause"); return;
        }
        garisBatas();
        tengah("1. Pesan Unit", 105);
        tengah("2. Kembali   ", 105);
        garisBatas();
        cout << "  Pilih menu: ";
        cin >> pilih; bersihkanBuffer();

        if (pilih == 2) return;

        if (pilih == 1) {
            system("cls"); banner();
            tengah("FORM PEMESANAN", 105);
            garisBatas();

            int pUnit;
            cout << "  Pilih nomor unit (1-10) : ";
            cin >> pUnit; bersihkanBuffer();

            if (pUnit < 1 || pUnit > 10) {
                cout << "  Nomor unit tidak valid!\n";
                system("pause"); continue;
            }
            if (daftarUnit[pUnit-1].status != "Tersedia") {
                cout << "  Unit ini tidak tersedia saat ini!\n";
                system("pause"); continue;
            }

            int durasi;
            cout << "  Durasi sewa (1-5 jam)   : ";
            cin >> durasi; bersihkanBuffer();

            if (durasi < 1 || durasi > 5) {
                cout << "  Durasi tidak valid! Masukkan 1 sampai 5.\n";
                system("pause"); continue;
            }

            int harga = daftarUnit[pUnit-1].hargaPerJam * durasi;
            int poin  = durasi * 10; 

            system("cls"); banner();
            tengah("RINGKASAN PESANAN", 105);
            garisBatas();
            tengah("Unit        : " + to_string(pUnit) + " (" + daftarUnit[pUnit-1].tipe + ")", 105);
            tengah("Durasi      : " + to_string(durasi) + " jam", 105);
            tengah("Total Harga : Rp " + to_string(harga), 105);
            tengah("Poin Dapat  : +" + to_string(poin) + " poin (diberikan setelah selesai)", 105);
            garisBatas();
            char konfirm;
            cout << "  Konfirmasi booking? (y/n): ";
            cin >> konfirm; bersihkanBuffer();

            if (konfirm != 'y' && konfirm != 'Y') {
                cout << "  Booking dibatalkan.\n";
                system("pause"); continue;
            }

            simpanBooking(daftarBooking, &jumlahBooking,
                          currentUsername, daftarMember.name[memberLoginIdx],
                          pUnit, daftarUnit[pUnit-1].tipe,
                          durasi, harga, poin);
                          
            updateStatusUnit(&daftarUnit[pUnit-1], "Dipakai");

            cout << "\n  Booking berhasil! Menunggu konfirmasi Operator.\n";
            cout << "  Poin akan diberikan setelah sesi selesai.\n";
            system("pause"); efekLoading("Loading");
        }
    }
}

void menuRiwayat() {
    system("cls"); banner();
    tengah("RIWAYAT SEWA", 105);
    garisBatas();

    bool ada = false;
    int no = 1;
    for (int i = 0; i < jumlahBooking; i++) {
        if (daftarBooking[i].memberUsername == currentUsername) {
            string info = to_string(no++) +
                          ". Unit " + to_string(daftarBooking[i].unitId) +
                          " | " + daftarBooking[i].tipePS +
                          " | " + to_string(daftarBooking[i].durasi) + " jam" +
                          " | Rp " + to_string(daftarBooking[i].totalHarga) +
                          " | " + daftarBooking[i].status;
            tengah(info, 105);
            ada = true;
        }
    }
    if (!ada) tengah("Belum ada riwayat sewa.", 105);
    garisBatas();
    system("pause");
}

void menuRedeem() {
    int pilih;
    while (true) {
        system("cls"); banner();
        tengah("REDEEM POIN", 105);
        garisBatas();
        tengah("1. Tukar Poin dengan Hadiah", 105);
        tengah("2. History Redeem          ", 105);
        tengah("3. Kembali                 ", 105);
        garisBatas();
        cout << "  Poin Anda  : " << daftarMember.poin[memberLoginIdx] << " poin\n";
        cout << "  Pilih menu : ";
        cin >> pilih; bersihkanBuffer();

        if (pilih == 3) break;

        if (pilih == 1) {
            int pilihBarang;
            while (true) {
                system("cls"); banner();
                tengah("DAFTAR HADIAH REDEEM", 105);
                garisBatas();
                for (int i = 0; i < jumlahBarang; i++) {
                    string info = to_string(i+1) + ". " +
                                  daftarBarang[i].nama + "  -  " +
                                  to_string(daftarBarang[i].hargaPoin) + " poin";
                    tengah(info, 105);
                }
                garisBatas();
                tengah("0. Kembali", 105);
                garisBatas();
                cout << "  Poin Anda    : " << daftarMember.poin[memberLoginIdx] << " poin\n";
                cout << "  Pilih hadiah : ";
                cin >> pilihBarang; bersihkanBuffer();

                if (pilihBarang == 0) break;

                if (pilihBarang < 1 || pilihBarang > jumlahBarang) {
                    cout << "  Pilihan tidak valid!\n";
                    system("pause"); continue;
                }

                int hargaBarang = daftarBarang[pilihBarang-1].hargaPoin;
                if (daftarMember.poin[memberLoginIdx] < hargaBarang) {
                    cout << "  Poin Anda tidak cukup!\n";
                    system("pause"); continue;
                }

                daftarMember.poin[memberLoginIdx]            -= hargaBarang;
                daftarMember.pengeluaranPoin[memberLoginIdx] += hargaBarang;
                historyRedeem[jumlahHistory] = daftarBarang[pilihBarang-1].nama;
                jumlahHistory++;

                cout << "  Berhasil redeem: " << daftarBarang[pilihBarang-1].nama << "!\n";
                cout << "  Sisa poin      : " << daftarMember.poin[memberLoginIdx] << " poin\n";
                system("pause"); efekLoading("Loading");
            }
        } else if (pilih == 2) {
            system("cls"); banner();
            tengah("HISTORY REDEEM", 105);
            garisBatas();
            if (jumlahHistory == 0) {
                tengah("Belum ada barang yang diredeem.", 105);
            } else {
                for (int i = 0; i < jumlahHistory; i++) {
                    tengah(to_string(i+1) + ". " + historyRedeem[i], 105);
                }
            }
            garisBatas();
            system("pause");
        }
    }
}
