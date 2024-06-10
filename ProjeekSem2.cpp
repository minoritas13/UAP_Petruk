#include <iostream>
#include <string>

using namespace std;

const int MAX_USERS = 100;        // Maksimal jumlah pengguna yang dapat disimpan
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
    User users[MAX_USERS];
    ParkingSpot parkingSpots[MAX_PARKING_SPOTS];
    int userCount;

public:
    ParkingSystem() : userCount(0) {
        initializeParkingSpots();
    }

    void initializeParkingSpots() {
        for (int i = 0; i < MAX_PARKING_SPOTS; i++) {
            parkingSpots[i] = {"Lokasi " + to_string(i + 1), true};
        }
    }

    void registrasi() {
        if (userCount >= MAX_USERS) {
            cout << "Tidak bisa registrasi pengguna baru, kapasitas penuh." << endl;
            return;
        }

        string username, password;

        cout << "Registrasi Pengguna Baru" << endl;
        cout << "Masukkan Username: ";
        cin >> username;
        cout << "Masukkan Password: ";
        cin >> password;

        users[userCount] = {username, password};
        userCount++;

        cout << "Registrasi berhasil!" << endl;
    }

    bool login(User &loggedInUser) {
        string username, password;

        cout << "Login Pengguna" << endl;
        cout << "Masukkan Username: ";
        cin >> username;
        cout << "Masukkan Password: ";
        cin >> password;

        for (int i = 0; i < userCount; i++) {
            if (users[i].username == username && users[i].password == password) {
                loggedInUser = users[i];
                return true;
            }
        }
        return false;
    }

    void hapusAkun() {
        string username, password;

        cout << "Hapus Akun Pengguna" << endl;
        cout << "Masukkan Username: ";
        cin >> username;
        cout << "Masukkan Password: ";
        cin >> password;

        for (int i = 0; i < userCount; i++) {
            if (users[i].username == username && users[i].password == password) {
                for (int j = i; j < userCount - 1; j++) {
                    users[j] = users[j + 1];
                }
                userCount--;
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
        int pilihan;
        tampilkanLahanParkir();
        cout << "Masukkan nomor lahan parkir yang ingin dipesan: ";
        cin >> pilihan;

        if (pilihan < 1 || pilihan > MAX_PARKING_SPOTS || !parkingSpots[pilihan - 1].available) {
            cout << "Pilihan tidak valid atau lahan parkir sudah dipesan!" << endl;
        } else {
            parkingSpots[pilihan - 1].available = false;
            cout << "Lahan parkir di " << parkingSpots[pilihan - 1].location << " berhasil dipesan oleh " << currentUser.username << "!" << endl;
            cout << "Konfirmasi: Tempat parkir " << parkingSpots[pilihan - 1].location << " sudah dipesan untuk Anda." << endl;
        }
    }
};

int main() {
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
        cin >> choice;

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
