#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAX_PARKING_SPOTS = 10; // Maksimal jumlah lahan parkir yang tersedia

struct User {
    string username;
    string password;
};

struct ParkingSpot {
    string location;
    bool available;
};

class ParkingSystem {
private:
    vector<User> users;
    vector<ParkingSpot> parkingSpots;

public:
    ParkingSystem() {
        initializeParkingSpots();
    }

    void initializeParkingSpots() {
        for (int i = 0; i < MAX_PARKING_SPOTS; i++) {
            parkingSpots.push_back({"Lokasi " + to_string(i + 1), true});
        }
    }

    void registrasi() {
        string username, password;

        cout << "Registrasi Pengguna Baru" << endl;
        cout << "Masukkan Username: ";
        getline(cin, username); // Menggunakan getline untuk membaca input
        cout << "Masukkan Password: ";
        getline(cin, password); // Menggunakan getline untuk membaca input

        users.push_back({username, password});
        cout << "Registrasi berhasil!" << endl;
    }

    bool login(User &loggedInUser) {
        string username, password;

        cout << "Login Pengguna" << endl;
        cout << "Masukkan Username: ";
        getline(cin, username); // Menggunakan getline untuk membaca input
        cout << "Masukkan Password: ";
        getline(cin, password); // Menggunakan getline untuk membaca input

        for (auto &user : users) {
            if (user.username == username && user.password == password) {
                loggedInUser = user;
                return true;
            }
        }
        return false;
    }

    void hapusAkun() {
        string username, password;

        cout << "Hapus Akun Pengguna" << endl;
        cout << "Masukkan Username: ";
        getline(cin, username); // Menggunakan getline untuk membaca input
        cout << "Masukkan Password: ";
        getline(cin, password); // Menggunakan getline untuk membaca input

        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->username == username && it->password == password) {
                users.erase(it);
                cout << "Akun berhasil dihapus!" << endl;
                return;
            }
        }
        cout << "Penghapusan gagal! Username atau password salah." << endl;
    }

    void tampilkanLahanParkir() {
        cout << "Lahan parkir yang tersedia:" << endl;
        for (int i = 0; i < MAX_PARKING_SPOTS; i++) {
            if (parkingSpots[i].available) {
                cout << i + 1 << ". " << parkingSpots[i].location << endl;
            }
        }
    }

    void pesanLahanParkir(User &currentUser) {
        srand(static_cast<unsigned int>(time(0))); 
        int my_rand = rand();
        string pilihanStr;
        int pilihan;
        tampilkanLahanParkir();
        cout << "Masukkan nomor lahan parkir yang ingin dipesan: ";
        getline(cin, pilihanStr); // Menggunakan getline untuk membaca input
        pilihan = stoi(pilihanStr); // Mengkonversi string menjadi integer

        if (pilihan < 1 || pilihan > MAX_PARKING_SPOTS || !parkingSpots[pilihan - 1].available) {
            cout << "Pilihan tidak valid atau lahan parkir sudah dipesan!" << endl;
        } else {
            parkingSpots[pilihan - 1].available = false;
            cout << "Lahan parkir di " << parkingSpots[pilihan - 1].location << " berhasil dipesan oleh " << currentUser.username << "!" << endl;
            cout << "Konfirmasi: Tempat parkir " << parkingSpots[pilihan - 1].location << " sudah dipesan untuk Anda." << endl;
            cout << "Barcode Anda: " << my_rand << endl;
        }
    }
};

int main() {
    string choiceStr;
    int choice;
    bool exitProgram = false;
    User loggedInUser;
    ParkingSystem parkingSystem;

    while (!exitProgram) {
        cout << "Selamat datang di sistem pemesanan tempat parkir" << endl;
        cout << "1. Registrasi" << endl;
        cout << "2. Login" << endl;
        cout << "3. Hapus Akun" << endl;
        cout << "4. Tampilkan Lahan Parkir" << endl;
        cout << "5. Pesan Lahan Parkir" << endl;
        cout << "6. Keluar" << endl;
        cout << "Masukkan pilihan Anda: ";
        getline(cin, choiceStr); // Menggunakan getline untuk membaca input
        choice = stoi(choiceStr); // Mengkonversi string menjadi integer

        switch (choice) {
            case 1:
                parkingSystem.registrasi(); 
                break;
            case 2:
                if (parkingSystem.login(loggedInUser)) {
                    cout << "Login berhasil! Anda bisa memesan tempat parkir sekarang." << endl;
                } else {
                    cout << "Login gagal! Username atau password salah." << endl;
                }
                break;
            case 3:
                parkingSystem.hapusAkun();
                break;
            case 4:
                parkingSystem.tampilkanLahanParkir();
                break;
            case 5:
                if (!loggedInUser.username.empty()) {
                    parkingSystem.pesanLahanParkir(loggedInUser);
                } else {
                    cout << "Anda harus login terlebih dahulu untuk memesan lahan parkir." << endl;
                }
                break;
            case 6:
                exitProgram = true;
                cout << "Terima kasih telah menggunakan sistem pemesanan tempat parkir." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }

        cout << endl;  // Menambah baris baru untuk kerapian output
    }

    return 0;
}
