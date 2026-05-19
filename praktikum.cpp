#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// ==========================================
// ABSTRACT BASE CLASS
// ==========================================
class RekeningBank {
protected:
    string nomorRekening;
    string namaNasabah;
    double saldo;

public:
    RekeningBank(string noRek, string nama, double saldoAwal)
        : nomorRekening(noRef), namaNasabah(nama), saldo(saldoAwal) {}

    virtual ~RekeningBank() {} // Destructor virtual untuk mencegah memory leak

    // Pure Virtual Function
    virtual void potongAdmin() = 0;

    // Helper function untuk menampilkan informasi rekening
    void tampilkanInformasi() const {
        cout << left << setw(15) << nomorRekening 
             << setw(20) << namaNasabah 
             << "Rp " << fixed << setprecision(0) << saldo << endl;
    }
};

// ==========================================
// DERIVED CLASSES (PRODUK LAMA)
// ==========================================
class RekeningSyariah : public RekeningBank {
public:
    RekeningSyariah(string noRek, string nama, double saldoAwal)
        : RekeningBank(noRek, nama, saldoAwal) {}

    // Implementasi Syariah: Bebas biaya admin
    void potongAdmin() override {
        // Saldo tetap utuh, tidak ada potongan
        cout << "[Syariah] " << namaNasabah << " -> Bebas biaya admin. Saldo tetap.\n";
    }
};

class RekeningKonvensional : public RekeningBank {
public:
    RekeningKonvensional(string noRek, string nama, double saldoAwal)
        : RekeningBank(noRek, nama, saldoAwal) {}

    // Implementasi Konvensional: Potongan flat Rp 15.000
    void potongAdmin() override {
        double biayaAdmin = 15000;
        saldo -= biayaAdmin;
        cout << "[Konvensional] " << namaNasabah << " -> Dipotong Rp 15.000.\n";
    }
};

// ==========================================
// DERIVED CLASS BARU (REKENING PREMIUM)
// ==========================================
class RekeningPremium : public RekeningBank {
public:
    RekeningPremium(string noRek, string nama, double saldoAwal)
        : RekeningBank(noRek, nama, saldoAwal) {}

    // Implementasi Premium: Potongan dinamis berdasarkan saldo
    void potongAdmin() override {
        double biayaAdmin = 0;
        
        // Aturan dinamis: > 10.000.000 gratis, <= 10.000.000 potong 50.000
        if (saldo <= 10000000) {
            biayaAdmin = 50000;
            saldo -= biayaAdmin;
            cout << "[Premium] " << namaNasabah << " -> Saldo <= 10jt. Dipotong Rp 50.000.\n";
        } else {
            cout << "[Premium] " << namaNasabah << " -> Saldo > 10jt. Bebas biaya admin!\n";
        }
    }
};

// ==========================================
// MAIN FUNCTION (SERVER OTOMATISASI BANK)
// ==========================================
int main() {
    // Simulasi database server bank menggunakan Vector of Pointers ke Base Class
    vector<RekeningBank*> daftarRekening;

    // Registrasi nasabah ke dalam sistem (termasuk produk baru Rekening Premium)
    daftarRekening.push_back(new RekeningSyariah("SYR001", "Ahmad Fauzi", 5000000));
    daftarRekening.push_back(new RekeningKonvensional("KONV02", "Budi Santoso", 2500000));
    
    // Test Case 1: Rekening Premium dengan saldo di bawah atau sama dengan 10 Juta
    daftarRekening.push_back(new RekeningPremium("PREM03", "Citra Lestari", 8000000));
    
    // Test Case 2: Rekening Premium dengan saldo di atas 10 Juta
    daftarRekening.push_back(new RekeningPremium("PREM04", "Dewi Handayani", 15000000));

    cout << "=== SALDO AWAL BULAN ===" << endl;
    cout << left << setw(15) << "No. Rek" << setw(20) << "Nama Nasabah" << "Saldo" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (const auto& rekening : daftarRekening) {
        rekening->tampilkanInformasi();
    }

    cout << "\n=== MEMPROSES OTOMATISASI POTONGAN ADMIN AKHIR BULAN ===" << endl;
    for (auto& rekening : daftarRekening) {
        // Di sinilah keunggulan polimorfisme: satu command, eksekusi berbeda tiap kelas
        rekening->potongAdmin(); 
    }

    cout << "\n=== SALDO SETELAH PROSES AKHIR BULAN ===" << endl;
    cout << left << setw(15) << "No. Rek" << setw(20) << "Nama Nasabah" << "Saldo" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (const auto& rekening : daftarRekening) {
        rekening->tampilkanInformasi();
    }

    // Cleanup memory (mencegah memory leak)
    for (auto& rekening : daftarRekening) {
        delete rekening;
    }
    daftarRekening.clear();

    return 0;
}