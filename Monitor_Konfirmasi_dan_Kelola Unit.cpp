#include <iostream>  // Library untuk input/output standar (cout, cin, dll)
#include <conio.h>   // Library untuk fungsi getch() (input karakter tanpa enter)
using namespace std;

// ============================================================
//   PLAYBOOK - Sistem Rental PlayStation
//   Rekonstruksi dari RonggoTa dengan konsep Booking PS
// ============================================================

// Variabel global untuk navigasi menu
char navigasi;

// ===== FUNGSI EFEK LOADING =====
// Menampilkan animasi loading dengan titik-titik
void efekLoading(string proses) {
    cout << proses;
    for (int i = 0; i < 3; i++) {
        cout << ". ";
        sleep(1);
    }
    cout << endl;
}

// ===== FUNGSI BANNER =====
// Menampilkan banner aplikasi PlayBook
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

// ===== FUNGSI TENGAH =====
// Menampilkan teks di tengah kolom dengan garis pinggir '|'
void tengah(string teks, int kolom) {
    int totalSpasi = kolom - 2 - (int)teks.length();
    int spasiKiri  = max(0, totalSpasi / 2);
    int spasiKanan = max(0, totalSpasi - spasiKiri);
    cout << "|" << string(spasiKiri, ' ') << teks << string(spasiKanan, ' ') << "|\n";
}

// ===== FUNGSI GARIS =====
// Menampilkan garis horizontal penuh sepanjang 105 karakter
void garis() {
    for (int i = 0; i < 105; i++) cout << "="; cout << endl;
}

// ===== FUNGSI GARIS BATAS =====
// Menampilkan garis batas dengan pinggir '|' kiri dan kanan
void garisBatas() {
    cout << "|";
    for (int i = 0; i < 103; i++) cout << "=";
    cout << "|" << endl;
}

// ===== FUNGSI SELECT =====
// Memberi warna cyan pada teks untuk highlight menu yang sedang dipilih
string select(string teks) {
    return "\033[36m" + teks + "\033[0m";
}

// ===== FUNGSI BERSIHKAN BUFFER =====
// Membersihkan sisa karakter di buffer cin agar input berikutnya tidak skip
void bersihkanBuffer() {
    cin.clear();
    cin.ignore(1000, '\n');
}

// ===== FUNGSI INPUT STRING =====
// Membaca satu baris teks dengan aman, menghindari skip akibat sisa buffer
string inputString() {
    string hasil;
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, hasil);
    return hasil;
}

// ============================================================
//   STRUCT & DATA GLOBAL
// ============================================================

// Struct dataMember: menyimpan data semua member yang terdaftar
struct dataMember {
    string username[50];
    string name[50];
    string email[50];
    string pass[50];
    string noTelp[50];         // string agar no HP tidak integer overflow
    int    umur[50];
    int    poin[50];           // poin reward member saat ini
    int    totalJamSewa[50];   // akumulasi total jam sewa
    int    pemasukanPoin[50];  // total poin yang pernah masuk
    int    pengeluaranPoin[50];// total poin yang pernah keluar
} daftarMember;
int jumlahMember = 0; // jumlah member yang sudah terdaftar

// Struct dataOperator: menyimpan data operator/admin
struct dataOperator {
    string username[20];
    string name[20];
    string pass[20];
    int count = 0;
} daftarOperator;
int operatorLoginIdx = -1; // index operator yang sedang login

// Struct UnitPS: menyimpan informasi setiap unit PlayStation
struct UnitPS {
    int    id;
    string tipe;         // PS4 Reguler / PS4 VIP / PS5 Reguler / PS5 VIP
    string status;       // Tersedia / Dipakai / Maintenance
    int    hargaPerJam;
};
// Inisialisasi 10 unit PS yang tersedia di rental
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

// Struct Booking: menyimpan data setiap pemesanan sesi bermain
struct Booking {
    string memberUsername; // username member yang melakukan booking
    string memberName;     // nama lengkap member
    int    unitId;         // nomor unit yang dipesan
    string tipePS;         // tipe unit PS yang dipesan
    int    durasi;         // durasi sewa dalam satuan jam
    int    totalHarga;     // total harga yang harus dibayar
    int    poinDapat;      // poin yang akan didapat setelah sesi selesai
    string status;         // Menunggu / Bermain / Selesai
};
Booking daftarBooking[100]; // array untuk menyimpan semua data booking
int jumlahBooking = 0;      // jumlah booking yang sudah masuk

// Struct BarangRedeem: menyimpan nama dan harga poin setiap hadiah
struct BarangRedeem {
    string nama;
    int    hargaPoin;
};
// Daftar hadiah yang bisa ditukar dengan poin oleh member
BarangRedeem daftarBarang[] = {
    {"Snack Gratis        ", 20 },
    {"Minuman Gratis      ", 15 },
    {"Extend 30 Menit     ", 25 },
    {"Gratis 1 Jam PS4    ", 50 },
    {"Gratis 1 Jam PS5    ", 80 },
    {"Merchandise PlayBook", 100}
};
const int jumlahBarang = 6; // total jumlah hadiah yang tersedia

string historyRedeem[100]; // array riwayat nama hadiah yang sudah diredeem
int    jumlahHistory   = 0; // jumlah entri riwayat redeem
int    totalPendapatan = 0; // akumulasi total pendapatan operator

// Variabel sesi login yang sedang aktif
string currentUsername = "";
string currentRole     = "";
int    memberLoginIdx  = -1;

// ============================================================
//   FUNGSI POINTER
// ============================================================

// Fungsi tambahPoin: menambah poin, pemasukan poin, dan jam sewa member
// Menggunakan pointer agar nilai asli langsung berubah
void tambahPoin(int *poin, int *pemasukanPoin, int *totalJam, int jumlahPoin, int jam) {
    *poin          += jumlahPoin;
    *pemasukanPoin += jumlahPoin;
    *totalJam      += jam;
}

// Fungsi updateStatusUnit: mengubah status unit PS melalui pointer ke struct
// Dipanggil saat booking dibuat (Dipakai) atau sesi selesai (Tersedia)
void updateStatusUnit(UnitPS *unit, string statusBaru) {
    unit->status = statusBaru;
}

// Fungsi editProfilMember: mengubah nama dan no HP member melalui pointer
// Dipanggil dari menu profil member
void editProfilMember(string *nama, string *noTelp) {
    cout << "  Nama baru    : "; *nama   = inputString();
    cout << "  No. HP baru  : "; *noTelp = inputString();
}

// Fungsi gantiPassword: mengubah password member melalui pointer
// Mengembalikan true jika berhasil, false jika password lama salah atau konfirmasi tidak cocok
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

// Fungsi simpanBooking: menyimpan data booking baru ke array menggunakan pointer
// Parameter jumlah adalah pointer agar nilai jumlahBooking global ikut bertambah
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

// ============================================================
//   FITUR MEMBER
// ============================================================

// --- [PROFIL MEMBER] ---
// Fungsi menuProfilMember: menampilkan statistik dan mengedit data profil member
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
            // Panggil fungsi pointer editProfilMember untuk update nama & no HP
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
            // Panggil fungsi pointer gantiPassword untuk update password
            system("cls"); banner();
            tengah("GANTI PASSWORD", 105);
            garisBatas();
            bool berhasil = gantiPassword(&daftarMember.pass[i]);
            if (berhasil) cout << "  Password berhasil diganti!\n";
            system("pause");
        }
    }
}

// --- [LIHAT UNIT] ---
// Fungsi menuLihatUnit: menampilkan daftar dan status semua unit PS
void menuLihatUnit() {
    system("cls"); banner();
    tengah("STATUS UNIT PLAYSTATION", 105);
    garisBatas();
    tengah("No  | Tipe          | Status      | Harga/Jam", 105);
    garisBatas();
    for (int i = 0; i < 10; i++) {
        // Tentukan warna berdasarkan status unit
        string warna;
        if      (daftarUnit[i].status == "Tersedia")  warna = "\033[32m"; // hijau
        else if (daftarUnit[i].status == "Dipakai")   warna = "\033[31m"; // merah
        else                                          warna = "\033[33m"; // kuning

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

// --- [BOOKING UNIT] ---
// Fungsi menuBooking: member memilih unit PS dan menentukan durasi sewa
void menuBooking() {
    int pilih;
    while (true) {
        system("cls"); banner();
        tengah("BOOKING UNIT PS", 105);
        garisBatas();
        tengah("Unit Yang Tersedia:", 105);
        garisBatas();

        // Tampilkan hanya unit yang berstatus Tersedia
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

            // Validasi nomor unit yang dipilih
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

            // Validasi durasi sewa
            if (durasi < 1 || durasi > 5) {
                cout << "  Durasi tidak valid! Masukkan 1 sampai 5.\n";
                system("pause"); continue;
            }

            // Hitung total harga dan poin yang akan didapat member
            int harga = daftarUnit[pUnit-1].hargaPerJam * durasi;
            int poin  = durasi * 10; // setiap 1 jam = 10 poin

            // Tampilkan ringkasan sebelum member konfirmasi
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

            // Simpan booking menggunakan fungsi pointer simpanBooking
            simpanBooking(daftarBooking, &jumlahBooking,
                          currentUsername, daftarMember.name[memberLoginIdx],
                          pUnit, daftarUnit[pUnit-1].tipe,
                          durasi, harga, poin);

            // Update status unit menjadi Dipakai menggunakan fungsi pointer
            updateStatusUnit(&daftarUnit[pUnit-1], "Dipakai");

            cout << "\n  Booking berhasil! Menunggu konfirmasi Operator.\n";
            cout << "  Poin akan diberikan setelah sesi selesai.\n";
            system("pause"); efekLoading("Loading");
        }
    }
}

// --- [RIWAYAT SEWA] ---
// Fungsi menuRiwayat: menampilkan semua riwayat booking milik member yang login
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

// --- [REDEEM POIN] ---
// Fungsi menuRedeem: member menukar poin dengan hadiah dan melihat history redeem
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
            // Tampilkan daftar hadiah yang bisa diredeem
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

                // Validasi nomor hadiah yang dipilih
                if (pilihBarang < 1 || pilihBarang > jumlahBarang) {
                    cout << "  Pilihan tidak valid!\n";
                    system("pause"); continue;
                }

                int hargaBarang = daftarBarang[pilihBarang-1].hargaPoin;
                if (daftarMember.poin[memberLoginIdx] < hargaBarang) {
                    cout << "  Poin Anda tidak cukup!\n";
                    system("pause"); continue;
                }

                // Proses redeem: kurangi poin dan catat ke array history
                daftarMember.poin[memberLoginIdx]            -= hargaBarang;
                daftarMember.pengeluaranPoin[memberLoginIdx] += hargaBarang;
                historyRedeem[jumlahHistory] = daftarBarang[pilihBarang-1].nama;
                jumlahHistory++;

                cout << "  Berhasil redeem: " << daftarBarang[pilihBarang-1].nama << "!\n";
                cout << "  Sisa poin      : " << daftarMember.poin[memberLoginIdx] << " poin\n";
                system("pause"); efekLoading("Loading");
            }
        } else if (pilih == 2) {
            // Tampilkan seluruh riwayat redeem member ini
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

// --- [MENU MEMBER LANDSCAPE] ---
// Fungsi menuMemberLandscape: menu utama member, navigasi horizontal dengan getch
void menuMemberLandscape() {
    string menu[5] = {"Lihat Unit", "Booking", "Riwayat", "Redeem", "Profil"};
    int  posisi = 0;
    char tombol;

    while (true) {
        system("cls"); banner();
        tengah("MENU MEMBER  |  " + daftarMember.name[memberLoginIdx] +
               "  |  Poin: " + to_string(daftarMember.poin[memberLoginIdx]), 105);
        garisBatas();

        // Hitung spasi agar menu terdistribusi merata secara horizontal
        int totalMenu = 5;
        int totalLen  = 0;
        string menuStr[5];
        for (int i = 0; i < totalMenu; i++) {
            string label = "[ " + menu[i] + " ]";
            menuStr[i]   = (posisi == i) ? select(label) : label;
            totalLen    += (int)label.length();
        }
        int sisaSpasi  = 103 - totalLen;
        int spasiAntar = (totalMenu > 1) ? sisaSpasi / (totalMenu - 1) : 0;
        int spasiSisa  = (totalMenu > 1) ? sisaSpasi % (totalMenu - 1) : 0;

        cout << "|";
        for (int i = 0; i < totalMenu; i++) {
            cout << menuStr[i];
            if (i < totalMenu - 1) {
                int sp = spasiAntar + (spasiSisa > 0 ? 1 : 0);
                cout << string(sp, ' ');
                if (spasiSisa > 0) spasiSisa--;
            }
        }
        cout << "|" << endl;
        garisBatas();
        tengah("Gunakan [ Panah Kiri/Kanan ] untuk navigasi  |  [ ENTER ] untuk pilih  |  [ L ] Logout", 105);
        garisBatas();

        // Tangkap tombol navigasi dari keyboard
        tombol = getch();
        if      (tombol == 75) posisi = (posisi == 0) ? totalMenu - 1 : posisi - 1; // Panah Kiri
        else if (tombol == 77) posisi = (posisi == totalMenu - 1) ? 0 : posisi + 1; // Panah Kanan
        else if (tombol == 'l' || tombol == 'L') { // Shortcut logout
            currentUsername = ""; currentRole = ""; memberLoginIdx = -1;
            efekLoading("Logout"); return;
        } else if (tombol == 13) { // Enter
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

// --- [MONITOR UNIT] ---
// Fungsi menuMonitorUnit: operator melihat status semua unit PS secara real-time
void menuMonitorUnit() {
    system("cls"); banner();
    tengah("MONITOR SEMUA UNIT PS", 105);
    garisBatas();
    tengah("No  | Tipe          | Status      | Harga/Jam", 105);
    garisBatas();

    int tersedia = 0, dipakai = 0, maintenance = 0;
    for (int i = 0; i < 10; i++) {
        string warna;
        if      (daftarUnit[i].status == "Tersedia")  { warna = "\033[32m"; tersedia++; }
        else if (daftarUnit[i].status == "Dipakai")   { warna = "\033[31m"; dipakai++; }
        else                                           { warna = "\033[33m"; maintenance++; }

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
    tengah("Tersedia: " + to_string(tersedia) +
           "  |  Dipakai: " + to_string(dipakai) +
           "  |  Maintenance: " + to_string(maintenance), 105);
    garisBatas();
    system("pause");
}

// --- [KONFIRMASI BOOKING] ---
// Fungsi menuKonfirmasi: operator mengkonfirmasi booking agar status jadi Bermain
void menuKonfirmasi() {
    int pilih;
    while (true) {
        system("cls"); banner();
        tengah("KONFIRMASI BOOKING MEMBER", 105);
        garisBatas();

        // Tampilkan semua booking yang masih berstatus Menunggu
        bool ada = false;
        for (int i = 0; i < jumlahBooking; i++) {
            if (daftarBooking[i].status == "Menunggu") {
                string info = to_string(i+1) +
                              ". " + daftarBooking[i].memberName +
                              " | Unit " + to_string(daftarBooking[i].unitId) +
                              " (" + daftarBooking[i].tipePS + ")" +
                              " | " + to_string(daftarBooking[i].durasi) + " jam" +
                              " | Rp " + to_string(daftarBooking[i].totalHarga) +
                              " | \033[33mMenunggu\033[0m";
                tengah(info, 105);
                ada = true;
            }
        }
        if (!ada) {
            tengah("Tidak ada booking yang menunggu konfirmasi.", 105);
            garisBatas(); system("pause"); return;
        }
        garisBatas();
        cout << "  Nomor booking untuk dikonfirmasi (0 = kembali): ";
        cin >> pilih; bersihkanBuffer();

        if (pilih == 0) return;
        if (pilih < 1 || pilih > jumlahBooking) {
            cout << "  Nomor tidak valid!\n"; system("pause"); continue;
        }
        if (daftarBooking[pilih-1].status != "Menunggu") {
            cout << "  Booking ini sudah diproses!\n"; system("pause"); continue;
        }

        // Ubah status booking dari Menunggu menjadi Bermain
        daftarBooking[pilih-1].status = "Bermain";
        cout << "  Sesi dimulai! \033[32m" << daftarBooking[pilih-1].memberName << "\033[0m sedang bermain.\n";
        system("pause"); efekLoading("Loading");
    }
}

// --- [SELESAIKAN SESI] ---
// Fungsi menuSelesaikan: operator menyelesaikan sesi Bermain dan memberikan poin
void menuSelesaikan() {
    int pilih;
    while (true) {
        system("cls"); banner();
        tengah("SESI YANG SEDANG BERJALAN", 105);
        garisBatas();

        // Tampilkan semua booking yang berstatus Bermain
        bool ada = false;
        for (int i = 0; i < jumlahBooking; i++) {
            if (daftarBooking[i].status == "Bermain") {
                string info = to_string(i+1) +
                              ". " + daftarBooking[i].memberName +
                              " | Unit " + to_string(daftarBooking[i].unitId) +
                              " (" + daftarBooking[i].tipePS + ")" +
                              " | " + to_string(daftarBooking[i].durasi) + " jam" +
                              " | Rp " + to_string(daftarBooking[i].totalHarga) +
                              " | \033[32mBermain\033[0m";
                tengah(info, 105);
                ada = true;
            }
        }
        if (!ada) {
            tengah("Tidak ada sesi yang sedang berjalan.", 105);
            garisBatas(); system("pause"); return;
        }
        garisBatas();
        cout << "  Nomor sesi untuk diselesaikan (0 = kembali): ";
        cin >> pilih; bersihkanBuffer();

        if (pilih == 0) return;
        if (pilih < 1 || pilih > jumlahBooking) {
            cout << "  Nomor tidak valid!\n"; system("pause"); continue;
        }
        if (daftarBooking[pilih-1].status != "Bermain") {
            cout << "  Sesi ini tidak sedang berjalan!\n"; system("pause"); continue;
        }

        int idx = pilih - 1;
        daftarBooking[idx].status = "Selesai";

        // Kembalikan status unit ke Tersedia menggunakan fungsi pointer
        updateStatusUnit(&daftarUnit[daftarBooking[idx].unitId - 1], "Tersedia");

        // Cari member lalu berikan poin menggunakan fungsi pointer tambahPoin
        for (int m = 0; m < jumlahMember; m++) {
            if (daftarMember.username[m] == daftarBooking[idx].memberUsername) {
                tambahPoin(
                    &daftarMember.poin[m],
                    &daftarMember.pemasukanPoin[m],
                    &daftarMember.totalJamSewa[m],
                    daftarBooking[idx].poinDapat,
                    daftarBooking[idx].durasi
                );
                break;
            }
        }
        totalPendapatan += daftarBooking[idx].totalHarga;

        cout << "  Sesi selesai! Unit " << daftarBooking[idx].unitId << " kembali tersedia.\n";
        cout << "  Poin +" << daftarBooking[idx].poinDapat
             << " diberikan ke " << daftarBooking[idx].memberName << ".\n";
        system("pause"); efekLoading("Loading");
    }
}

// --- [KELOLA UNIT] ---
// Fungsi menuKelolaUnit: operator mengubah status unit PS (Maintenance/Tersedia)
void menuKelolaUnit() {
    int pilih;
    while (true) {
        system("cls"); banner();
        tengah("KELOLA UNIT PS", 105);
        garisBatas();
        for (int i = 0; i < 10; i++) {
            string warna;
            if      (daftarUnit[i].status == "Tersedia")  warna = "\033[32m";
            else if (daftarUnit[i].status == "Dipakai")   warna = "\033[31m";
            else                                           warna = "\033[33m";
            tengah("Unit " + to_string(daftarUnit[i].id) +
                   "  |  " + daftarUnit[i].tipe +
                   "  |  " + warna + daftarUnit[i].status + "\033[0m", 105);
        }
        garisBatas();
        tengah("1. Set Unit ke Maintenance", 105);
        tengah("2. Set Unit ke Tersedia   ", 105);
        tengah("3. Kembali                ", 105);
        garisBatas();
        cout << "  Pilih menu: ";
        cin >> pilih; bersihkanBuffer();

        if (pilih == 3) return;

        int nUnit;
        cout << "  Nomor unit yang ingin diubah (1-10): ";
        cin >> nUnit; bersihkanBuffer();

        if (nUnit < 1 || nUnit > 10) {
            cout << "  Nomor unit tidak valid!\n"; system("pause"); continue;
        }

        // Update status unit menggunakan fungsi pointer updateStatusUnit
        if (pilih == 1) {
            updateStatusUnit(&daftarUnit[nUnit-1], "Maintenance");
            cout << "  Unit " << nUnit << " berhasil diset ke Maintenance.\n";
        } else if (pilih == 2) {
            updateStatusUnit(&daftarUnit[nUnit-1], "Tersedia");
            cout << "  Unit " << nUnit << " berhasil diset ke Tersedia.\n";
        }
        system("pause"); efekLoading("Loading");
    }
}