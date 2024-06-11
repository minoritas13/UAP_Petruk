#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;

struct User {
    string username;
    string password;
};

struct ParkingSpot {
    string location;
    bool available;
};

template <typename TUser, typename TParkingSpot>
class ParkingSystem {
private:
    vector<TUser> users;
    vector<TParkingSpot> parkingSpots;
    queue<TUser> waitingQueue; // Antrian untuk pengguna yang menunggu tempat parkir

public:
    ParkingSystem() {
        initializeParkingSpots();
    }

    void initializeParkingSpots() {
        for (int i = 0; i < 10; i++) {  // Menggunakan 10 sebagai jumlah maksimal tempat parkir
            parkingSpots.push_back({"Lokasi " + to_string(i + 1), true});
        }
    }

    void registrasi() {
        string username, password;

        cout << "Registrasi Pengguna Baru" << endl;
        cout << "Masukkan Username: ";
        getline(cin, username);
        cout << "Masukkan Password: ";
        getline(cin, password);

        users.push_back({username, password});

        cout << "Registrasi berhasil!" << endl;
    }

    bool login(TUser &loggedInUser) {
        string username, password;

        cout << "Login Pengguna" << endl;
        cout << "Masukkan Username: ";
        getline(cin, username);
        cout << "Masukkan Password: ";
        getline(cin, password);

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
        getline(cin, username);
        cout << "Masukkan Password: ";
        getline(cin, password);

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
        for (int i = 0; i < parkingSpots.size(); i++) {
            if (parkingSpots[i].available) {
                cout << i + 1 << ". " << parkingSpots[i].location << endl;
            }
        }
    }

    void pesanLahanParkir(TUser &currentUser) {
        srand((unsigned int) time(0)); 
        int my_rand = rand();
        int pilihan;
        tampilkanLahanParkir();
        cout << "Masukkan nomor lahan parkir yang ingin dipesan: ";
        cin >> pilihan;
        cin.get();  // Membersihkan newline character dari buffer

        if (pilihan < 1 || pilihan > parkingSpots.size() || !parkingSpots[pilihan - 1].available) {
            cout << "Pilihan tidak valid atau lahan parkir sudah dipesan!" << endl;
        } else {
            parkingSpots[pilihan - 1].available = false;
            cout << "Lahan parkir di " << parkingSpots[pilihan - 1].location << " berhasil dipesan oleh " << currentUser.username << "!" << endl;
            cout << "Konfirmasi: Tempat parkir " << parkingSpots[pilihan - 1].location << " sudah dipesan untuk Anda." << endl;
            cout << "Barcode anda : " << my_rand << endl;
        }
    }

    void tambahKeAntrian(TUser &currentUser) {
        waitingQueue.push(currentUser);
        cout << currentUser.username << " telah ditambahkan ke dalam antrian." << endl;
    }

    void cekAntrian() {
        if (!waitingQueue.empty()) {
            TUser nextUser = waitingQueue.front();
            cout << "Pengguna " << nextUser.username << " berada di urutan pertama dalam antrian." << endl;
        } else {
            cout << "Tidak ada pengguna dalam antrian." << endl;
        }
    }

    void notifikasiTempatParkirTersedia() {
        if (!waitingQueue.empty()) {
            for (auto &spot : parkingSpots) {
                if (spot.available) {
                    TUser nextUser = waitingQueue.front();
                    waitingQueue.pop();
                    cout << "Tempat parkir tersedia untuk " << nextUser.username << ". Silakan pesan segera." << endl;
                    return;
                }
            }
        }
    }
};

int main() {
    int choice;
    bool exitProgram = false;
    User loggedInUser;
    ParkingSystem<User, ParkingSpot> parkingSystem;

    while (!exitProgram) {
        cout << "Selamat datang di sistem pemesanan tempat parkir" << endl;
        cout << "1. Registrasi" << endl;
        cout << "2. Login" << endl;
        cout << "3. Hapus Akun" << endl;
        cout << "4. Tampilkan Lahan Parkir" << endl;
        cout << "5. Pesan Lahan Parkir" << endl;
        cout << "6. Tambah ke Antrian" << endl;
        cout << "7. Cek Antrian" << endl;
        cout << "8. Keluar" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> choice;
        cin.get();  // Membersihkan newline character dari buffer

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
                if (!loggedInUser.username.empty()) {
                    parkingSystem.tambahKeAntrian(loggedInUser);
                } else {
                    cout << "Anda harus login terlebih dahulu untuk masuk ke dalam antrian." << endl;
                }
                break;
            case 7:
                parkingSystem.cekAntrian();
                break;
            case 8:
                exitProgram = true;
                cout << "Terima kasih telah menggunakan sistem pemesanan tempat parkir." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }

        parkingSystem.notifikasiTempatParkirTersedia();
        cout << endl;  // Menambah baris baru untuk kerapian output
    }

    return 0;
}
