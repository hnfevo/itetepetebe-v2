#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

// Deklarasi struct menu
struct Menu {
    int id;
    string nama;
    int harga;
    Menu* prev;
    Menu* next;
};

// Deklarasi node head dan tail
Menu* head = nullptr;
Menu* tail = nullptr;
stack<Menu*> menuStack; // Stack untuk menyimpan menu
queue<Menu*> menuQueue; // Queue untuk membatasi jumlah menu menjadi maksimal 5

// Fungsi menambahkan menu
void TambahMenu() {
    if (menuQueue.size() >= 5) {
        cout << "\nBatas menu telah tercapai. Tidak dapat menambahkan menu baru." << endl;
        return;
    }

    Menu* menuBaru = new Menu();

    // Mengatur ID menu
    if (head == nullptr) {
        menuBaru->id = 1;
    } else {
        menuBaru->id = tail->id + 1;
    }

    // Meminta input dari user
    cin.ignore();
    cout << "\nMasukkan nama menu: ";
    getline(cin, menuBaru->nama);
    cout << "Masukkan harga menu: ";
    cin >> menuBaru->harga;

    // Menambahkan menu ke dalam daftar menu
    if (head == nullptr) {
        head = tail = menuBaru;
    } else {
        tail->next = menuBaru;
        menuBaru->prev = tail;
        tail = menuBaru;
    }

    menuStack.push(menuBaru); // Menambahkan menu ke dalam stack
    menuQueue.push(menuBaru); // Menambahkan menu ke dalam queue

    cout << "\nMenu berhasil ditambahkan!" << endl;
}

// Fungsi menghapus menu berdasarkan ID
void HapusMenu() {
    int idHapus;
    bool ditemukan = false;

    cout << "\nMasukkan ID menu yang ingin dihapus: ";
    cin >> idHapus;

    // Mencari menu yang ingin dihapus
    Menu* curr = head;
    while (curr != nullptr) {
        if (curr->id == idHapus) {
            // Menghapus menu dari daftar menu
            if (curr == head && curr == tail) {
                head = tail = nullptr;
            } else if (curr == head) {
                head = head->next;
                head->prev = nullptr;
            } else if (curr == tail) {
                tail = tail->prev;
                tail->next = nullptr;
            } else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }

            menuStack.pop(); // Menghapus menu dari stack
            delete curr;
            ditemukan = true;
            cout << "\nMenu berhasil dihapus!" << endl;
            break;
        }
        curr = curr->next;
    }

    // Menampilkan pesan jika menu tidak ditemukan
    if (!ditemukan) {
        cout << "\nMenu tidak ditemukan!" << endl;
    }
}

// Fungsi mengubah menu berdasarkan ID
void UbahMenu() {
    int idUbah;
    bool ditemukan = false;

    cout << "\nMasukkan ID menu yang ingin diubah: ";
    cin >> idUbah;

    // Mencari menu yang ingin diubah
    Menu* curr = head;
    while (curr != nullptr) {
        if (curr->id == idUbah) {
            // Meminta input dari user untuk data menu yang baru
            string namaMenuBaru;
            int hargaMenuBaru;
            cout << "\nMasukkan nama menu baru: ";
            cin.ignore();
            getline(cin, namaMenuBaru);
            cout << "Masukkan harga menu baru: ";
            cin >> hargaMenuBaru;
            curr->nama = namaMenuBaru;
            curr->harga = hargaMenuBaru;
            ditemukan = true;
            cout << "Menu berhasil diubah!" << endl;
            break;
        }
        curr = curr->next;
    }

    // Menampilkan pesan jika menu tidak ditemukan
    if (!ditemukan) {
        cout << "\nMenu tidak ditemukan!" << endl;
    }
}

// Fungsi menampilkan daftar menu
void TampilkanMenu() {
    cout << "\nDaftar Menu Restoran Nasi Goreng ENTUL" << endl;
    cout << "-------------------------------------" << endl;
    cout << "ID\tNAMA\t\tHARGA" << endl;
    Menu* curr = head;
    while (curr != nullptr) {
        cout << curr->id << endl;
        cout << "\t" << curr->nama << "\t\t" << curr->harga << endl;
        cout << endl;
        curr = curr->next;
    }
}

// Fungsi menampilkan graf menu
void TampilkanGrafMenu() {
    cout << "\nGraf Menu Restoran Nasi Goreng ENTUL" << endl;
    cout << "-----------------------------------" << endl;
    cout << "ID\tNAMA\t\tHARGA" << endl;
    Menu* curr = head;
    while (curr != nullptr) {
        cout << curr->id << endl;
        cout << "\t" << curr->nama << "\t\t" << curr->harga << endl;

        // Menampilkan hubungan dengan menu sebelumnya
        if (curr->prev != nullptr) {
            cout << "\t<-- ";
            cout << curr->prev->id << endl;
        }

        // Menampilkan hubungan dengan menu selanjutnya
        if (curr->next != nullptr) {
            cout << "\t--> ";
            cout << curr->next->id << endl;
        }

        cout << endl;
        curr = curr->next;
    }
}

int main() {
    int pilihan, totalPembayaran;

    // Menambahkan menu awal
    Menu* menu1 = new Menu();
    menu1->id = 1;
    menu1->nama = "Nasi Goreng Biasa";
    menu1->harga = 15000;

    Menu* menu2 = new Menu();
    menu2->id = 2;
    menu2->nama = "Nasi Goreng Spesial";
    menu2->harga = 20000;

    Menu* menu3 = new Menu();
    menu3->id = 3;
    menu3->nama = "Nasi Goreng Seafood";
    menu3->harga = 25000;

    menu1->next = menu2;
    menu2->prev = menu1;
    menu2->next = menu3;
    menu3->prev = menu2;

    head = menu1;
    tail = menu3;

    do {
        // Menampilkan menu pilihan
        cout << endl;
        cout << "===== NASI GORENG =====" << endl;
        cout << "1. Daftar Menu" << endl;
        cout << "2. Tambah Menu" << endl;
        cout << "3. HapusMenu" << endl;
        cout << "4. Ubah Menu" << endl;
        cout << "5. Menu Terakhir Yang Ditambahkan" << endl;
        cout << "6. Hitung Total Pembayaran" << endl;
        cout << "7. Tampilkan Graf Menu" << endl;
        cout << "8. Keluar\n" << endl;
        cout << "Pilihan anda: ";
        cin >> pilihan;

        // Memproses pilihan user
        switch (pilihan) {
            case 1:
                TampilkanMenu();
                break;
            case 2:
                TambahMenu();
                break;
            case 3:
                HapusMenu();
                break;
            case 4:
                UbahMenu();
                break;
            case 5:
                // Menampilkan menu terakhir yang ditambahkan
                if (!menuStack.empty()) {
                    cout << "\nMenu terakhir yang ditambahkan: " << endl;
                    Menu* lastMenu = menuStack.top();
                    cout << "ID\tNAMA\t\tHARGA" << endl;
                    cout << lastMenu->id << endl;
                    cout << "\t" << lastMenu->nama << "\t\t" << lastMenu->harga << endl;
                } else {
                    cout << "\nBelum ada menu yang ditambahkan." << endl;
                }
                break;
            case 6:
                // Meminta input dari user
                cout << "\nMasukkan jumlah menu yang dipesan: ";
                int jumlahMenu;
                cin >> jumlahMenu;

                // Menghitung total pembayaran
                totalPembayaran = 0;
                for (int i = 0; i < jumlahMenu; i++) {
                    int idMenu;
                    cout << "Masukkan ID menu: ";
                    cin >> idMenu;

                    // Mencari menu berdasarkan ID
                    bool ditemukan = false;
                    Menu* curr = head;
                    while (curr != nullptr) {
                        if (curr->id == idMenu) {
                            totalPembayaran += curr->harga;
                            ditemukan = true;
                            break;
                        }
                        curr = curr->next;
                    }

                    // Menampilkan pesan jika menu tidak ditemukan
                    if (!ditemukan) {
                        cout << "Menu tidak ditemukan!" << endl;
                    }
                }

                // Menampilkan total pembayaran
                cout << "\nTotal pembayaran: " << totalPembayaran << endl;
                break;
            case 7:
                TampilkanGrafMenu();
                break;
        }

     // Menunggu input dari user
    } while (pilihan != 8);

    // Menghapus semua node pada double linked list
    Menu* curr = head;
    while (curr != nullptr) {
        Menu* nextMenu = curr->next;
        delete curr;
        curr = nextMenu;
    }

    return 0;
}
