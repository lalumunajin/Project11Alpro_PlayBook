#include <iostream>  
#include <conio.h> 
#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define BLUE   "\033[36m"
#define RESET  "\033[0m"  
using namespace std;

// ============================================================
//   PLAYBOOK - Sistem Rental PlayStation
// ============================================================

// ===== FUNGSI PAD (pengganti iomanip setw+left/right, manual) =====
string pad(string teks, int lebar, bool kiri = true) {
    if ((int)teks.length() >= lebar) return teks;
    string spasi(lebar - (int)teks.length(), ' ');
    return kiri ? teks + spasi : spasi + teks;
}

// ===== FUNGSI BANNER =====
void banner() {
    for (int i = 0; i < 105; i++) cout << "="; cout << endl;
    cout << BLUE << R"(

     ooooooooo.   oooo                         oooooooooo.                     oooo        
     `888   `Y88. `888                        `888'   `Y8b                     `888        
      888   .d88'  888   .oooo.   oooo    ooo  888     888  .ooooo.   .ooooo.   888  oooo  
      888ooo88P'   888  `P  )88b   `88b..8P'   888oooo888' d88' `88b d88' `88b  888 .8P'  
      888          888   .oP"888     Y888'     888    `88b 888   888 888   888  888888.    
      888          888  d8(  888   .o8"'       888    .88P 888   888 888   888  888 `88b.  
     o888o        o888o `Y888""8o o88'         o888bood8P' `Y8bod8P' `Y8bod8P' o888o o888o 

)" << RESET;
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
string select(string teks) { return string(BLUE) + teks + RESET; }

void bersihkanBuffer() { cin.clear(); cin.ignore(1000, '\n'); }
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

// ===== CETAK BARIS TABEL =====
void baris5(string k1, int w1, string k2, int w2, string k3, int w3,
            string warnaK3, string k4, int w4, string k5, int w5) {
    cout << "| " << pad(k1, w1) << "| " << pad(k2, w2) << "| "
         << warnaK3 << pad(k3, w3) << RESET << "| "
         << pad(k4, w4, false) << "| " << pad(k5, w5) << "|" << endl;
}

// ===== CETAK STATISTIK (label...........nilai=====
void cetakStatistik(string label, string nilai) {
    string titik(50, '.'); // 3+25+50+1+25+1 = 105
    cout << "|  " << pad(label, 25) << titik << " " << pad(nilai, 25) << "|" << endl;
}

// ============================================================
//   STRUCT & DATA GLOBAL
// ============================================================
struct dataMember {
    string username[50], name[50], email[50], pass[50], noTelp[50];
    int umur[50], poin[50], totalJamSewa[50], pemasukanPoin[50], pengeluaranPoin[50];
} daftarMember;
int jumlahMember = 0;

struct dataOperator {
    string username[20], name[20], pass[20];
    int count = 0;
} daftarOperator;
int operatorLoginIdx = -1;

struct UnitPS { int id; string tipe, status; int hargaPerJam; };
UnitPS daftarUnit[10] = {
    {1,  "PS4 Reguler", "Tersedia", 8000 }, {2,  "PS4 Reguler", "Tersedia", 8000 },
    {3,  "PS4 Reguler", "Tersedia", 8000 }, {4,  "PS4 VIP",     "Tersedia", 12000},
    {5,  "PS4 VIP",     "Tersedia", 12000}, {6,  "PS4 VIP",     "Tersedia", 12000},
    {7,  "PS5 Reguler", "Tersedia", 15000}, {8,  "PS5 Reguler", "Tersedia", 15000},
    {9,  "PS5 VIP",     "Tersedia", 20000}, {10, "PS5 VIP",     "Tersedia", 20000}
};

struct Booking {
    string memberUsername, memberName, tipePS, status;
    int unitId, durasi, totalHarga, poinDapat;
};
Booking daftarBooking[100];
int jumlahBooking = 0;

struct BarangRedeem { string nama; int hargaPoin; };
BarangRedeem daftarBarang[] = {
    {"Snack Gratis",         20 }, {"Minuman Gratis",       15 },
    {"Extend 30 Menit",      25 }, {"Gratis 1 Jam PS4",     50 },
    {"Gratis 1 Jam PS5",     80 }, {"Merchandise PlayBook", 100}
};
const int jumlahBarang = 6;

string historyRedeem[100];
int jumlahHistory = 0;
int totalPendapatan = 0;

string currentUsername = "", currentRole = "";
int memberLoginIdx = -1;

// ============================================================
//   FUNGSI POINTER
// ============================================================
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
// Hapus booking dari array dengan teknik shifting
void hapusBooking(Booking *arr, int *jumlah, int index) {
    for (int i = index; i < (*jumlah) - 1; i++) arr[i] = arr[i + 1];
    (*jumlah)--;
}

// ============================================================
//   FITUR MEMBER
// ============================================================
void menuProfilMember() {
    int pilih;
    while (true) {
        system("cls"); banner();
        tengah("PROFIL MEMBER", 105);
        garisBatas();
        int i = memberLoginIdx;
        cetakStatistik("Nama Lengkap",  daftarMember.name[i]);
        cetakStatistik("Username",      daftarMember.username[i]);
        cetakStatistik("Email",         daftarMember.email[i]);
        cetakStatistik("No. HP",        daftarMember.noTelp[i]);
        cetakStatistik("Umur",          to_string(daftarMember.umur[i]) + " tahun");
        garisBatas();
        tengah("=== STATISTIK AKUN ===", 105);
        garisBatas();
        cetakStatistik("Poin Saat Ini",    to_string(daftarMember.poin[i]) + " poin");
        cetakStatistik("Pemasukan Poin",   to_string(daftarMember.pemasukanPoin[i]) + " poin");
        cetakStatistik("Pengeluaran Poin", to_string(daftarMember.pengeluaranPoin[i]) + " poin");
        cetakStatistik("Total Jam Sewa",   to_string(daftarMember.totalJamSewa[i]) + " jam");
        garisBatas();
        tengah("1. Edit Nama & No. HP", 105);
        tengah("2. Ganti Password    ", 105);
        tengah("3. Kembali           ", 105);
        garisBatas();
        cout << "  Pilih menu: "; cin >> pilih; bersihkanBuffer();

        if (pilih == 3) break;
        else if (pilih == 1) {
            system("cls"); banner();
            tengah("EDIT PROFIL", 105);
            garisBatas();
            cetakStatistik("Nama lama",  daftarMember.name[i]);
            cetakStatistik("No HP lama", daftarMember.noTelp[i]);
            garisBatas();
            editProfilMember(&daftarMember.name[i], &daftarMember.noTelp[i]);
            cout << GREEN << "  Profil berhasil diperbarui!\n" << RESET;
            system("pause");
        } else if (pilih == 2) {
            system("cls"); banner();
            tengah("GANTI PASSWORD", 105);
            garisBatas();
            if (gantiPassword(&daftarMember.pass[i])) cout << GREEN << "  Password berhasil diganti!\n" << RESET;
            system("pause");
        }
    }
}

void menuLihatUnit() {
    system("cls"); banner();
    tengah("STATUS UNIT PLAYSTATION", 105);
    garisBatas();
    baris5("No", 3, "Tipe", 14, "Status", 13, "", "Harga/Jam", 16, "Keterangan", 48);
    garisBatas();
    for (int i = 0; i < 10; i++) {
        string warna, ket;
        if (daftarUnit[i].status == "Tersedia")    { warna = GREEN;  ket = "Unit siap digunakan"; }
        else if (daftarUnit[i].status == "Dipakai") { warna = RED;    ket = "Sedang disewa member"; }
        else                                         { warna = YELLOW; ket = "Dalam perbaikan"; }
        baris5(to_string(daftarUnit[i].id), 3, daftarUnit[i].tipe, 14, daftarUnit[i].status, 13,
               warna, formatRupiah(daftarUnit[i].hargaPerJam) + "/jam", 16, ket, 48);
    }
    garisBatas();
    tengah(string(GREEN) + "[Hijau]" + RESET + " Tersedia   " + RED + "[Merah]" + RESET +
           " Dipakai   " + YELLOW + "[Kuning]" + RESET + " Maintenance", 105);
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
        baris5("No", 3, "Tipe", 14, "Status", 13, "", "Harga/Jam", 16, "", 48);
        garisBatas();

        bool adaUnit = false;
        for (int i = 0; i < 10; i++) {
            if (daftarUnit[i].status == "Tersedia") {
                baris5(to_string(daftarUnit[i].id), 3, daftarUnit[i].tipe, 14, "Tersedia", 13,
                       GREEN, formatRupiah(daftarUnit[i].hargaPerJam) + "/jam", 16, "", 48);
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
        cout << "  Pilih menu: "; cin >> pilih; bersihkanBuffer();
        if (pilih == 2) return;

        if (pilih == 1) {
            system("cls"); banner();
            tengah("FORM PEMESANAN", 105);
            garisBatas();
            int pUnit;
            cout << "  Pilih nomor unit (1-10) : "; cin >> pUnit; bersihkanBuffer();
            if (pUnit < 1 || pUnit > 10) {
                cout << RED << "  Nomor unit tidak valid!\n" << RESET; system("pause"); continue;
            }
            if (daftarUnit[pUnit-1].status != "Tersedia") {
                cout << RED << "  Unit ini tidak tersedia saat ini!\n" << RESET; system("pause"); continue;
            }
            int durasi;
            cout << "  Durasi sewa (1-5 jam)   : "; cin >> durasi; bersihkanBuffer();
            if (durasi < 1 || durasi > 5) {
                cout << RED << "  Durasi tidak valid! Masukkan 1 sampai 5.\n" << RESET; system("pause"); continue;
            }

            int harga = daftarUnit[pUnit-1].hargaPerJam * durasi;
            int poin  = durasi * 10;

            system("cls"); banner();
            tengah("RINGKASAN PESANAN", 105);
            garisBatas();
            cetakStatistik("Unit",         to_string(pUnit) + " - " + daftarUnit[pUnit-1].tipe);
            cetakStatistik("Durasi",       to_string(durasi) + " jam");
            cetakStatistik("Total Harga",  formatRupiah(harga));
            cetakStatistik("Poin Didapat", "+" + to_string(poin) + " poin");
            garisBatas();
            char konfirm;
            cout << "  Konfirmasi booking? (y/n): "; cin >> konfirm; bersihkanBuffer();
            if (konfirm != 'y' && konfirm != 'Y') {
                cout << YELLOW << "  Booking dibatalkan.\n" << RESET; system("pause"); continue;
            }

            simpanBooking(daftarBooking, &jumlahBooking, currentUsername,
                          daftarMember.name[memberLoginIdx], pUnit, daftarUnit[pUnit-1].tipe,
                          durasi, harga, poin);
            updateStatusUnit(&daftarUnit[pUnit-1], "Dipakai");

            cout << GREEN << "\n  Booking berhasil! Menunggu konfirmasi Operator.\n" << RESET;
            cout << "  Poin akan diberikan setelah sesi selesai.\n";
            system("pause");
        }
    }
}

void menuRiwayat() {
    int pilih;
    while (true) {
        system("cls"); banner();
        tengah("RIWAYAT SEWA", 105);
        garisBatas();
        cout << "| " << pad("No",3) << "| " << pad("Unit",10) << "| " << pad("Tipe",14)
             << "| " << pad("Durasi",8) << "| " << pad("Total Harga",16) << "| " << pad("Status",41) << "|" << endl;
        garisBatas();

        int indexAsli[100], totalTampil = 0;
        for (int i = 0; i < jumlahBooking; i++) {
            if (daftarBooking[i].memberUsername == currentUsername) {
                string warna = (daftarBooking[i].status == "Menunggu") ? YELLOW :
                               (daftarBooking[i].status == "Bermain")  ? GREEN : RESET;
                cout << "| " << pad(to_string(totalTampil + 1), 3) << "| "
                     << pad("Unit " + to_string(daftarBooking[i].unitId), 10) << "| "
                     << pad(daftarBooking[i].tipePS, 14) << "| "
                     << pad(to_string(daftarBooking[i].durasi) + " jam", 8) << "| "
                     << pad(formatRupiah(daftarBooking[i].totalHarga), 16, false) << "| "
                     << warna << pad(daftarBooking[i].status, 41) << RESET << "|" << endl;
                indexAsli[totalTampil] = i;
                totalTampil++;
            }
        }
        if (totalTampil == 0) {
            tengah("Belum ada riwayat sewa.", 105);
            garisBatas(); system("pause"); return;
        }
        garisBatas();
        tengah("Hanya booking berstatus 'Menunggu' yang bisa dibatalkan.", 105);
        tengah("Masukkan nomor untuk membatalkan, atau 0 untuk kembali.", 105);
        garisBatas();
        cout << "  Nomor booking: "; cin >> pilih; bersihkanBuffer();
        if (pilih == 0) return;
        if (pilih < 1 || pilih > totalTampil) {
            cout << RED << "  Nomor tidak valid!\n" << RESET; system("pause"); continue;
        }

        int idxAsli = indexAsli[pilih - 1];
        if (daftarBooking[idxAsli].status != "Menunggu") {
            cout << RED << "  Booking ini tidak bisa dibatalkan (status: "
                 << daftarBooking[idxAsli].status << ")!\n" << RESET;
            system("pause"); continue;
        }
        char konfirm;
        cout << "  Yakin batalkan booking Unit " << daftarBooking[idxAsli].unitId << "? (y/n): ";
        cin >> konfirm; bersihkanBuffer();
        if (konfirm != 'y' && konfirm != 'Y') {
            cout << YELLOW << "  Dibatalkan tidak jadi.\n" << RESET; system("pause"); continue;
        }
        updateStatusUnit(&daftarUnit[daftarBooking[idxAsli].unitId - 1], "Tersedia");
        hapusBooking(daftarBooking, &jumlahBooking, idxAsli);
        cout << GREEN << "  Booking berhasil dibatalkan! Unit kembali tersedia.\n" << RESET;
        system("pause");
    }
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
        cout << "  Pilih menu : "; cin >> pilih; bersihkanBuffer();
        if (pilih == 3) break;

        if (pilih == 1) {
            int pilihBarang;
            while (true) {
                system("cls"); banner();
                tengah("DAFTAR HADIAH REDEEM", 105);
                garisBatas();
                cout << "| " << pad("No",5) << "| " << pad("Nama Hadiah",28) << "| " << pad("Harga Poin",65) << "|" << endl;
                garisBatas();
                for (int i = 0; i < jumlahBarang; i++) {
                    cout << "| " << pad(to_string(i+1) + ".", 5) << "| " << pad(daftarBarang[i].nama, 28)
                         << "| " << pad(to_string(daftarBarang[i].hargaPoin) + " poin", 65, false) << "|" << endl;
                }
                garisBatas();
                tengah("0. Kembali", 105);
                garisBatas();
                cout << "  Poin Anda    : " << daftarMember.poin[memberLoginIdx] << " poin\n";
                cout << "  Pilih hadiah : "; cin >> pilihBarang; bersihkanBuffer();
                if (pilihBarang == 0) break;
                if (pilihBarang < 1 || pilihBarang > jumlahBarang) {
                    cout << RED << "  Pilihan tidak valid!\n" << RESET; system("pause"); continue;
                }
                int hargaBarang = daftarBarang[pilihBarang-1].hargaPoin;
                if (daftarMember.poin[memberLoginIdx] < hargaBarang) {
                    cout << RED << "  Poin Anda tidak cukup!\n" << RESET; system("pause"); continue;
                }
                daftarMember.poin[memberLoginIdx]            -= hargaBarang;
                daftarMember.pengeluaranPoin[memberLoginIdx] += hargaBarang;
                historyRedeem[jumlahHistory++] = daftarBarang[pilihBarang-1].nama;
                cout << GREEN << "  Berhasil redeem: " << daftarBarang[pilihBarang-1].nama << "!\n" << RESET;
                cout << "  Sisa poin      : " << daftarMember.poin[memberLoginIdx] << " poin\n";
                system("pause");
            }
        } else if (pilih == 2) {
            system("cls"); banner();
            tengah("HISTORY REDEEM", 105);
            garisBatas();
            cout << "| " << pad("No",5) << "| " << pad("Nama Hadiah",95) << "|" << endl;
            garisBatas();
            if (jumlahHistory == 0) tengah("Belum ada barang yang diredeem.", 105);
            else for (int i = 0; i < jumlahHistory; i++)
                cout << "| " << pad(to_string(i+1) + ".", 5) << "| " << pad(historyRedeem[i], 95) << "|" << endl;
            garisBatas();
            system("pause");
        }
    }
}

void menuMemberLandscape() {
    string menu[5] = {"Lihat Unit", "Booking", "Riwayat", "Redeem", "Profil"};
    int posisi = 0;
    char tombol;
    while (true) {
        system("cls"); banner();
        tengah("MENU MEMBER  |  " + daftarMember.name[memberLoginIdx] +
               "  |  Poin: " + to_string(daftarMember.poin[memberLoginIdx]), 105);
        garisBatas();

        int totalLen = 0;
        string menuStr[5];
        for (int i = 0; i < 5; i++) {
            string label = "[ " + menu[i] + " ]";
            menuStr[i] = (posisi == i) ? select(label) : label;
            totalLen += (int)label.length();
        }
        int sisaSpasi = 103 - totalLen;
        int spasiAntar = sisaSpasi / 4, spasiSisa = sisaSpasi % 4;
        cout << "|";
        for (int i = 0; i < 5; i++) {
            cout << menuStr[i];
            if (i < 4) {
                int sp = spasiAntar + (spasiSisa > 0 ? 1 : 0);
                cout << string(sp, ' ');
                if (spasiSisa > 0) spasiSisa--;
            }
        }
        cout << "|" << endl;
        garisBatas();
        tengah("Gunakan [ Panah Kiri/Kanan ] untuk navigasi  |  [ ENTER ] untuk pilih  |  [ L ] Logout", 105);
        garisBatas();

        tombol = getch();
        if      (tombol == 75) posisi = (posisi == 0) ? 4 : posisi - 1;
        else if (tombol == 77) posisi = (posisi == 4) ? 0 : posisi + 1;
        else if (tombol == 'l' || tombol == 'L') {
            currentUsername = ""; currentRole = ""; memberLoginIdx = -1; return;
        } else if (tombol == 13) {
            if      (menu[posisi] == "Lihat Unit") menuLihatUnit();
            else if (menu[posisi] == "Booking")    menuBooking();
            else if (menu[posisi] == "Riwayat")    menuRiwayat();
            else if (menu[posisi] == "Redeem")     menuRedeem();
            else if (menu[posisi] == "Profil")     menuProfilMember();
        }
    }
}

// ============================================================
//   FITUR OPERATOR
// ============================================================
void menuMonitorUnit() {
    system("cls"); banner();
    tengah("MONITOR SEMUA UNIT PS", 105);
    garisBatas();
    baris5("No", 3, "Tipe", 14, "Status", 13, "", "Harga/Jam", 16, "Keterangan", 48);
    garisBatas();

    int tersedia = 0, dipakai = 0, maintenance = 0;
    for (int i = 0; i < 10; i++) {
        string warna, ket;
        if (daftarUnit[i].status == "Tersedia")     { warna = GREEN;  ket = "Unit siap digunakan";  tersedia++; }
        else if (daftarUnit[i].status == "Dipakai") { warna = RED;    ket = "Sedang disewa member"; dipakai++; }
        else                                          { warna = YELLOW; ket = "Dalam perbaikan";      maintenance++; }
        baris5(to_string(daftarUnit[i].id), 3, daftarUnit[i].tipe, 14, daftarUnit[i].status, 13,
               warna, formatRupiah(daftarUnit[i].hargaPerJam) + "/jam", 16, ket, 48);
    }
    garisBatas();
    // '| ' + 19 + 19 + 64 + '|' = 2+19+19+64+1 = 105
    cout << "| " << pad("Tersedia   : " + to_string(tersedia), 19)
         << pad("Dipakai      : " + to_string(dipakai), 19)
         << pad("Maintenance  : " + to_string(maintenance), 64) << "|" << endl;
    garisBatas();
    system("pause");
}

void menuKonfirmasi() {
    int pilih;
    while (true) {
        system("cls"); banner();
        tengah("KONFIRMASI BOOKING MEMBER", 105);
        garisBatas();
        cout << "| " << pad("No",4) << "| " << pad("Nama Member",20) << "| " << pad("Unit",8)
             << "| " << pad("Tipe PS",14) << "| " << pad("Durasi",8) << "| " << pad("Total Harga",38) << "|" << endl;
        garisBatas();

        bool ada = false;
        for (int i = 0; i < jumlahBooking; i++) {
            if (daftarBooking[i].status == "Menunggu") {
                cout << "| " << pad(to_string(i+1) + ".", 4) << "| " << pad(daftarBooking[i].memberName, 20)
                     << "| " << pad("Unit " + to_string(daftarBooking[i].unitId), 8) << "| "
                     << pad(daftarBooking[i].tipePS, 14) << "| "
                     << pad(to_string(daftarBooking[i].durasi) + " jam", 8) << "| "
                     << YELLOW << pad(formatRupiah(daftarBooking[i].totalHarga), 38, false) << RESET << "|" << endl;
                ada = true;
            }
        }
        if (!ada) {
            tengah("Tidak ada booking yang menunggu konfirmasi.", 105);
            garisBatas(); system("pause"); return;
        }
        garisBatas();
        cout << "  Nomor booking untuk dikonfirmasi (0 = kembali): "; cin >> pilih; bersihkanBuffer();
        if (pilih == 0) return;
        if (pilih < 1 || pilih > jumlahBooking) {
            cout << RED << "  Nomor tidak valid!\n" << RESET; system("pause"); continue;
        }
        if (daftarBooking[pilih-1].status != "Menunggu") {
            cout << RED << "  Booking ini sudah diproses!\n" << RESET; system("pause"); continue;
        }
        daftarBooking[pilih-1].status = "Bermain";
        cout << GREEN << "  Sesi dimulai! " << daftarBooking[pilih-1].memberName << " sedang bermain.\n" << RESET;
        system("pause");
    }
}

void menuSelesaikan() {
    int pilih;
    while (true) {
        system("cls"); banner();
        tengah("SESI YANG SEDANG BERJALAN", 105);
        garisBatas();
        cout << "| " << pad("No",4) << "| " << pad("Nama Member",20) << "| " << pad("Unit",8)
             << "| " << pad("Tipe PS",14) << "| " << pad("Durasi",8) << "| " << pad("Total Harga",38) << "|" << endl;
        garisBatas();

        bool ada = false;
        for (int i = 0; i < jumlahBooking; i++) {
            if (daftarBooking[i].status == "Bermain") {
                cout << "| " << pad(to_string(i+1) + ".", 4) << "| " << pad(daftarBooking[i].memberName, 20)
                     << "| " << pad("Unit " + to_string(daftarBooking[i].unitId), 8) << "| "
                     << pad(daftarBooking[i].tipePS, 14) << "| "
                     << pad(to_string(daftarBooking[i].durasi) + " jam", 8) << "| "
                     << GREEN << pad(formatRupiah(daftarBooking[i].totalHarga), 38, false) << RESET << "|" << endl;
                ada = true;
            }
        }
        if (!ada) {
            tengah("Tidak ada sesi yang sedang berjalan.", 105);
            garisBatas(); system("pause"); return;
        }
        garisBatas();
        cout << "  Nomor sesi untuk diselesaikan (0 = kembali): "; cin >> pilih; bersihkanBuffer();
        if (pilih == 0) return;
        if (pilih < 1 || pilih > jumlahBooking) {
            cout << RED << "  Nomor tidak valid!\n" << RESET; system("pause"); continue;
        }
        if (daftarBooking[pilih-1].status != "Bermain") {
            cout << RED << "  Sesi ini tidak sedang berjalan!\n" << RESET; system("pause"); continue;
        }
        int idx = pilih - 1;
        daftarBooking[idx].status = "Selesai";
        updateStatusUnit(&daftarUnit[daftarBooking[idx].unitId - 1], "Tersedia");
        for (int m = 0; m < jumlahMember; m++) {
            if (daftarMember.username[m] == daftarBooking[idx].memberUsername) {
                tambahPoin(&daftarMember.poin[m], &daftarMember.pemasukanPoin[m],
                           &daftarMember.totalJamSewa[m], daftarBooking[idx].poinDapat, daftarBooking[idx].durasi);
                break;
            }
        }
        totalPendapatan += daftarBooking[idx].totalHarga;
        cout << GREEN << "  Sesi selesai! Unit " << daftarBooking[idx].unitId << " kembali tersedia.\n" << RESET;
        cout << "  Poin +" << daftarBooking[idx].poinDapat << " diberikan ke " << daftarBooking[idx].memberName << ".\n";
        system("pause");
    }
}

void menuKelolaUnit() {
    int pilih;
    while (true) {
        system("cls"); banner();
        tengah("KELOLA UNIT PS", 105);
        garisBatas();
        baris5("No", 3, "Tipe", 14, "Status", 13, "", "Harga/Jam", 16, "", 48);
        garisBatas();
        for (int i = 0; i < 10; i++) {
            string warna = (daftarUnit[i].status == "Tersedia") ? GREEN :
                           (daftarUnit[i].status == "Dipakai")  ? RED : YELLOW;
            baris5(to_string(daftarUnit[i].id), 3, daftarUnit[i].tipe, 14, daftarUnit[i].status, 13,
                   warna, formatRupiah(daftarUnit[i].hargaPerJam) + "/jam", 16, "", 48);
        }
        garisBatas();
        tengah("1. Set Unit ke Maintenance", 105);
        tengah("2. Set Unit ke Tersedia   ", 105);
        tengah("3. Kembali                ", 105);
        garisBatas();
        cout << "  Pilih menu: "; cin >> pilih; bersihkanBuffer();
        if (pilih == 3) return;

        int nUnit;
        cout << "  Nomor unit yang ingin diubah (1-10): "; cin >> nUnit; bersihkanBuffer();
        if (nUnit < 1 || nUnit > 10) {
            cout << RED << "  Nomor unit tidak valid!\n" << RESET; system("pause"); continue;
        }
        if (pilih == 1) {
            updateStatusUnit(&daftarUnit[nUnit-1], "Maintenance");
            cout << YELLOW << "  Unit " << nUnit << " berhasil diset ke Maintenance.\n" << RESET;
        } else if (pilih == 2) {
            updateStatusUnit(&daftarUnit[nUnit-1], "Tersedia");
            cout << GREEN << "  Unit " << nUnit << " berhasil diset ke Tersedia.\n" << RESET;
        }
        system("pause");
    }
}

void menuLaporan() {
    system("cls"); banner();
    tengah("LAPORAN PENDAPATAN", 105);
    garisBatas();
    cetakStatistik("Total Pendapatan", formatRupiah(totalPendapatan));
    garisBatas();
    tengah("Detail Transaksi Selesai:", 105);
    garisBatas();
    cout << "| " << pad("No",4) << "| " << pad("Nama Member",20) << "| " << pad("Unit",8)
         << "| " << pad("Durasi",8) << "| " << pad("Total Harga",54) << "|" << endl;
    garisBatas();

    bool ada = false;
    int no = 1;
    for (int i = 0; i < jumlahBooking; i++) {
        if (daftarBooking[i].status == "Selesai") {
            cout << "| " << pad(to_string(no++) + ".", 4) << "| " << pad(daftarBooking[i].memberName, 20)
                 << "| " << pad("Unit " + to_string(daftarBooking[i].unitId), 8) << "| "
                 << pad(to_string(daftarBooking[i].durasi) + " jam", 8) << "| "
                 << pad(formatRupiah(daftarBooking[i].totalHarga), 54, false) << "|" << endl;
            ada = true;
        }
    }
    if (!ada) tengah("Belum ada transaksi yang selesai.", 105);
    garisBatas();
    system("pause");
}

void menuOperatorLandscape() {
    string menu[5] = {"Monitor Unit", "Konfirmasi", "Selesaikan", "Kelola Unit", "Laporan"};
    int posisi = 0;
    char tombol;
    while (true) {
        system("cls"); banner();
        tengah("MENU OPERATOR  |  " + daftarOperator.name[operatorLoginIdx], 105);
        garisBatas();

        int totalLen = 0;
        string menuStr[5];
        for (int i = 0; i < 5; i++) {
            string label = "[ " + menu[i] + " ]";
            menuStr[i] = (posisi == i) ? select(label) : label;
            totalLen += (int)label.length();
        }
        int sisaSpasi = 103 - totalLen;
        int spasiAntar = sisaSpasi / 4, spasiSisa = sisaSpasi % 4;
        cout << "|";
        for (int i = 0; i < 5; i++) {
            cout << menuStr[i];
            if (i < 4) {
                int sp = spasiAntar + (spasiSisa > 0 ? 1 : 0);
                cout << string(sp, ' ');
                if (spasiSisa > 0) spasiSisa--;
            }
        }
        cout << "|" << endl;
        garisBatas();
        tengah("Gunakan [ Panah Kiri/Kanan ] untuk navigasi  |  [ ENTER ] untuk pilih  |  [ L ] Logout", 105);
        garisBatas();

        tombol = getch();
        if      (tombol == 75) posisi = (posisi == 0) ? 4 : posisi - 1;
        else if (tombol == 77) posisi = (posisi == 4) ? 0 : posisi + 1;
        else if (tombol == 'l' || tombol == 'L') {
            currentUsername = ""; currentRole = ""; operatorLoginIdx = -1; return;
        } else if (tombol == 13) {
            if      (menu[posisi] == "Monitor Unit") menuMonitorUnit();
            else if (menu[posisi] == "Konfirmasi")   menuKonfirmasi();
            else if (menu[posisi] == "Selesaikan")   menuSelesaikan();
            else if (menu[posisi] == "Kelola Unit")  menuKelolaUnit();
            else if (menu[posisi] == "Laporan")      menuLaporan();
        }
    }
}

// ============================================================
//   SIGN UP & LOGIN
// ============================================================
bool hanyaHuruf(string teks) {
    if (teks.empty()) return false;
    for (char c : teks) if (!isalpha(c) && c != ' ') return false;
    return true;
}
bool hanyaAngka(string teks) {
    if (teks.empty()) return false;
    for (char c : teks) if (!isdigit(c)) return false;
    return true;
}
string inputValidasi(string label, bool (*validator)(string), string pesanError) {
    string val;
    while (true) {
        cout << label;
        val = inputString();
        if (validator(val)) return val;
        cout << RED << "  " << pesanError << "\n" << RESET;
    }
}
int inputUmur(string label) {
    string val;
    while (true) {
        cout << label;
        val = inputString();
        if (hanyaAngka(val) && stoi(val) >= 5 && stoi(val) <= 100) return stoi(val);
        cout << RED << "  Umur harus berupa angka (5-100)!\n" << RESET;
    }
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

// ============================================================
//   MAIN
// ============================================================
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
                    cout << GREEN << "Terima kasih telah menggunakan PlayBook!\n" << RESET;
                    return 0;
                }
                break;
        }
    }
    return 0;
}