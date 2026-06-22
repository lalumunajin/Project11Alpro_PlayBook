# 🎮 PlayBook: Sistem Booking PlayStation

## 📌 Deskripsi Program

PlayBook adalah aplikasi berbasis C++ yang digunakan untuk mengelola proses booking PlayStation secara digital. Program ini menyediakan dua jenis pengguna, yaitu **Member** dan **Operator**, dengan hak akses yang berbeda.

Member dapat melakukan booking unit PlayStation, melihat riwayat booking, menukar poin dengan hadiah, serta mengelola profil akun. Sementara itu, Operator bertugas mengonfirmasi booking, menyelesaikan sesi bermain, mengelola status unit PlayStation, dan memantau laporan pendapatan.

Program ini dibuat menggunakan konsep dasar pemrograman seperti **array**, **struct**, **pointer**, **function pointer**, **validasi input**, **perulangan**, **percabangan**, dan **manajemen data berbasis memori**.

---

## 🎯 Tujuan Program

- Mempermudah proses booking PlayStation.
- Membantu operator dalam mengelola unit PlayStation.
- Menyediakan sistem poin dan reward bagi pelanggan.
- Menyimpan riwayat booking dan transaksi.
- Menghasilkan laporan pendapatan secara otomatis.

---

## 👥 Role Pengguna

### Member

Fitur yang tersedia untuk Member:

- Melihat status unit PlayStation
- Melakukan booking unit
- Melihat riwayat booking
- Membatalkan booking yang masih berstatus *Menunggu*
- Menukar poin dengan hadiah (Redeem)
- Melihat dan mengubah profil
- Mengganti password

### Operator

Fitur yang tersedia untuk Operator:

- Memonitor seluruh unit PlayStation
- Mengonfirmasi booking member
- Menyelesaikan sesi bermain
- Mengelola status unit PlayStation
- Melihat laporan pendapatan

---

## 🕹️ Daftar Unit PlayStation

| ID | Tipe Unit | Harga per Jam |
|----|-----------|---------------|
| 1 | PS4 Reguler | Rp 8.000 |
| 2 | PS4 Reguler | Rp 8.000 |
| 3 | PS4 Reguler | Rp 8.000 |
| 4 | PS4 VIP | Rp 12.000 |
| 5 | PS4 VIP | Rp 12.000 |
| 6 | PS4 VIP | Rp 12.000 |
| 7 | PS5 Reguler | Rp 15.000 |
| 8 | PS5 Reguler | Rp 15.000 |
| 9 | PS5 VIP | Rp 20.000 |
| 10 | PS5 VIP | Rp 20.000 |

---

## 🎁 Sistem Poin

Member akan memperoleh poin setelah sesi bermain selesai.

### Perhitungan Poin

- 1 Jam Bermain = 10 Poin

Contoh:

| Durasi | Poin |
|---------|---------|
| 1 Jam | 10 |
| 2 Jam | 20 |
| 3 Jam | 30 |
| 5 Jam | 50 |

---

## 🎀 Daftar Hadiah Redeem

| Hadiah | Harga Poin |
|---------|---------|
| Snack Gratis | 20 Poin |
| Minuman Gratis | 15 Poin |
| Extend 30 Menit | 25 Poin |
| Gratis 1 Jam PS4 | 50 Poin |
| Gratis 1 Jam PS5 | 80 Poin |
| Merchandise PlayBook | 100 Poin |

---

## 🔄 Alur Sistem

### Alur Booking

```text
Member Login
      ↓
Pilih Unit PS
      ↓
Pilih Durasi Bermain
      ↓
Konfirmasi Booking
      ↓
Status = Menunggu
      ↓
Operator Konfirmasi
      ↓
Status = Bermain
      ↓
Operator Menyelesaikan Sesi
      ↓
Status = Selesai
      ↓
Poin Ditambahkan
      ↓
Pendapatan Bertambah
```

---

## 📊 Status Booking

| Status | Keterangan |
|---------|---------|
| Menunggu | Menunggu konfirmasi operator |
| Bermain | Sesi sedang berlangsung |
| Selesai | Sesi telah selesai |

---

## 🔧 Status Unit

| Status | Keterangan |
|---------|---------|
| Tersedia | Unit dapat dibooking |
| Dipakai | Unit sedang digunakan |
| Maintenance | Unit sedang diperbaiki |

---

## 🧩 Struktur Data yang Digunakan

### Struct dataMember

Menyimpan data member:

- Username
- Nama Lengkap
- Email
- Password
- Nomor HP
- Umur
- Poin
- Total Jam Sewa
- Pemasukan Poin
- Pengeluaran Poin

### Struct dataOperator

Menyimpan data operator:

- Username
- Nama Lengkap
- Password

### Struct UnitPS

Menyimpan informasi unit PlayStation:

- ID Unit
- Tipe Unit
- Status Unit
- Harga per Jam

### Struct Booking

Menyimpan data transaksi booking:

- Username Member
- Nama Member
- Tipe PS
- Status Booking
- ID Unit
- Durasi
- Total Harga
- Poin yang Didapat

### Struct BarangRedeem

Menyimpan daftar hadiah redeem beserta harga poinnya.

---

## 💡 Konsep Pemrograman yang Digunakan

Program ini menerapkan konsep:

- Array
- Struct
- Pointer
- Function Pointer
- Parameter dan Return Value
- Percabangan (if-else dan switch-case)
- Perulangan (for dan while)
- Validasi Input
- Manipulasi String
- Modular Programming (Function)

---

## 🚀 Cara Menjalankan Program

1. Buka project menggunakan Visual Studio Code atau Dev-C++.
2. Compile file C++.
3. Jalankan program.
4. Pilih menu **Sign Up** untuk membuat akun.
5. Login sebagai **Member** atau **Operator**.
6. Gunakan fitur sesuai hak akses masing-masing.

---

## 🏆 Kesimpulan

PlayBook merupakan sistem booking PlayStation berbasis C++ yang dirancang untuk membantu proses pengelolaan penyewaan PlayStation secara lebih terstruktur. Sistem menyediakan fitur booking, monitoring unit, manajemen poin, redeem hadiah, serta laporan pendapatan dalam satu aplikasi yang terintegrasi.
