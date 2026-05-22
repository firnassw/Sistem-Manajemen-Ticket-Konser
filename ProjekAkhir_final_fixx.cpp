#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char adminUser[100] = "admin";
char adminPass[100] = "123";

struct Konser {
    int id;
    char nama[100];
    char lokasi[100];
    int harga;
    int stok;
};

struct Node {
    Konser data;
    Node* next;
};

struct QueueNode {
    char pembeli[100];
    char konser[100];
    int jumlah;
    QueueNode* next;
};

struct StackNode {
    char pembeli[100];
    char konser[100];
    int jumlah;
    StackNode* next;
};

Node* head = NULL;
QueueNode* frontQ = NULL;
QueueNode* rearQ = NULL;
StackNode* topStack = NULL;

int countData() {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) { count++; temp = temp->next; }
    return count;
}

void copyToArray(Konser arr[]) {
    Node* temp = head;
    int i = 0;
    while (temp != NULL) { arr[i] = temp->data; temp = temp->next; i++; }
}

void tampilArray(Konser arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "\nID       : " << arr[i].id;
        cout << "\nNama     : " << arr[i].nama;
        cout << "\nLokasi   : " << arr[i].lokasi;
        cout << "\nHarga    : " << arr[i].harga;
        cout << "\nStok     : " << arr[i].stok;
        cout << "\n--------------------------";
    }
}

bool loginAdmin() {
    char user[100], pass[100];
    cout << "\n===== LOGIN ADMIN =====\n";
    cout << "Username : "; cin.getline(user, 100);
    cout << "Password : "; cin.getline(pass, 100);
    if (strcmp(user, adminUser) == 0 && strcmp(pass, adminPass) == 0) {
        cout << "\nLogin berhasil! Selamat datang, Admin.\n";
        return true;
    }
    cout << "\nUsername atau password salah!\n";
    return false;
}

void tambahKonser() {
    Node* baru = new Node;
    cout << "\n===== TAMBAH KONSER =====\n";
    cout << "ID Konser   : "; cin >> baru->data.id; cin.ignore();
    Node* cek = head;
    while (cek != NULL) {
        if (cek->data.id == baru->data.id) {
            cout << "\nID sudah digunakan! Silakan gunakan ID lain.\n";
            delete baru; return;
        }
        cek = cek->next;
    }
    cout << "Nama Konser : "; cin.getline(baru->data.nama, 100);
    cout << "Lokasi      : "; cin.getline(baru->data.lokasi, 100);
    cout << "Harga       : "; cin >> baru->data.harga;
    if (baru->data.harga < 0) {
        cout << "\nHarga tidak boleh negatif!\n";
        delete baru; return;
    }
    cout << "Stok        : "; cin >> baru->data.stok;
    if (baru->data.stok < 0) {
        cout << "\nStok tidak boleh negatif!\n";
        delete baru; return;
    }
    baru->next = NULL;
    if (head == NULL) { head = baru; }
    else {
        Node* temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = baru;
    }
    cout << "\nData berhasil ditambahkan!\n";
}

void tampilKonser() {
    if (head == NULL) { cout << "\nData kosong!\n"; return; }
    Node* temp = head;
    cout << "\n===== DATA KONSER =====";
    while (temp != NULL) {
        cout << "\nID       : " << temp->data.id;
        cout << "\nNama     : " << temp->data.nama;
        cout << "\nLokasi   : " << temp->data.lokasi;
        cout << "\nHarga    : " << temp->data.harga;
        cout << "\nStok     : " << temp->data.stok;
        cout << "\n--------------------------";
        temp = temp->next;
    }
}

void editKonser() {
    if (head == NULL) { cout << "\nData kosong!\n"; return; }
    tampilKonser();
    int id; bool found = false;
    cout << "\nMasukkan ID konser yang ingin diedit : "; cin >> id; cin.ignore();
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data.id == id) {
            found = true;
            cout << "\n===== EDIT KONSER =====\n";
            cout << "Nama Baru   : "; cin.getline(temp->data.nama, 100);
            cout << "Lokasi Baru : "; cin.getline(temp->data.lokasi, 100);
            cout << "Harga Baru  : "; cin >> temp->data.harga;
            if (temp->data.harga < 0) {
                cout << "\nHarga tidak boleh negatif! Edit dibatalkan.\n"; return;
            }
            cout << "Stok Baru   : "; cin >> temp->data.stok;
            if (temp->data.stok < 0) {
                cout << "\nStok tidak boleh negatif! Edit dibatalkan.\n"; return;
            }
            cout << "\nData berhasil diedit!\n"; break;
        }
        temp = temp->next;
    }
    if (!found) cout << "\nData tidak ditemukan!\n";
}

void hapusKonser() {
    if (head == NULL) { cout << "\nData kosong!\n"; return; }
    tampilKonser();
    int id; bool found = false;
    cout << "\nMasukkan ID konser yang ingin dihapus : "; cin >> id; cin.ignore();
    Node* temp = head;
    Node* prev = NULL;
    while (temp != NULL) {
        if (temp->data.id == id) {
            found = true;
            char konfirmasi;
            cout << "\nYakin ingin menghapus konser \"" << temp->data.nama << "\"? (y/n) : ";
            cin >> konfirmasi; cin.ignore();
            if (konfirmasi != 'y' && konfirmasi != 'Y') {
                cout << "\nPenghapusan dibatalkan.\n"; return;
            }
            if (prev == NULL) head = temp->next;
            else prev->next = temp->next;
            delete temp;
            cout << "\nData berhasil dihapus!\n"; break;
        }
        prev = temp;
        temp = temp->next;
    }
    if (!found) cout << "\nData tidak ditemukan!\n";
}

void sequentialSearch() {
    if (head == NULL) { cout << "\nData kosong!\n"; return; }
    char cari[100]; bool found = false;
    cout << "\nMasukkan nama konser : "; cin.getline(cari, 100);
    Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->data.nama, cari) == 0) {
            found = true;
            cout << "\n===== DATA DITEMUKAN =====";
            cout << "\nID       : " << temp->data.id;
            cout << "\nNama     : " << temp->data.nama;
            cout << "\nLokasi   : " << temp->data.lokasi;
            cout << "\nHarga    : " << temp->data.harga;
            cout << "\nStok     : " << temp->data.stok;
            break;
        }
        temp = temp->next;
    }
    if (!found) cout << "\nData tidak ditemukan!\n";
}

void binarySearch() {
    if (head == NULL) { cout << "\nData kosong!\n"; return; }
    int n = countData();
    Konser arr[100];
    copyToArray(arr);
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].id > arr[j + 1].id) {
                Konser tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp;
            }
    int cari;
    cout << "\nMasukkan ID konser : "; cin >> cari; cin.ignore();
    int low = 0, high = n - 1; bool found = false;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid].id == cari) {
            found = true;
            cout << "\n===== DATA DITEMUKAN =====";
            cout << "\nID       : " << arr[mid].id;
            cout << "\nNama     : " << arr[mid].nama;
            cout << "\nLokasi   : " << arr[mid].lokasi;
            cout << "\nHarga    : " << arr[mid].harga;
            cout << "\nStok     : " << arr[mid].stok;
            break;
        }
        else if (cari < arr[mid].id) high = mid - 1;
        else low = mid + 1;
    }
    if (!found) cout << "\nData tidak ditemukan!\n";
}

void bubbleSort() {
    if (head == NULL) { cout << "\nData kosong!\n"; return; }
    int n = countData();
    Konser arr[100];
    copyToArray(arr);
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].harga > arr[j + 1].harga) {
                Konser tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp;
            }
    cout << "\n===== BUBBLE SORT (Harga Termurah) =====";
    tampilArray(arr, n);
}

void selectionSort() {
    if (head == NULL) { cout << "\nData kosong!\n"; return; }
    int n = countData();
    Konser arr[100];
    copyToArray(arr);
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j].stok < arr[minIdx].stok) minIdx = j;
        Konser tmp = arr[i]; arr[i] = arr[minIdx]; arr[minIdx] = tmp;
    }
    cout << "\n===== SELECTION SORT (Stok Terkecil) =====";
    tampilArray(arr, n);
}

int partition(Konser arr[], int low, int high) {
    char pivot[100];
    strcpy(pivot, arr[high].nama);
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (strcmp(arr[j].nama, pivot) < 0) {
            i++;
            Konser tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    Konser tmp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = tmp;
    return i + 1;
}

void quickSort(Konser arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSortMenu() {
    if (head == NULL) { cout << "\nData kosong!\n"; return; }
    int n = countData();
    Konser arr[100];
    copyToArray(arr);
    quickSort(arr, 0, n - 1);
    cout << "\n===== QUICK SORT (Nama A-Z) =====";
    tampilArray(arr, n);
}

void enqueue(char pembeli[], char konser[], int jumlah) {
    QueueNode* baru = new QueueNode;
    strcpy(baru->pembeli, pembeli);
    strcpy(baru->konser, konser);
    baru->jumlah = jumlah;
    baru->next = NULL;
    if (frontQ == NULL) frontQ = rearQ = baru;
    else { rearQ->next = baru; rearQ = baru; }
}

void tampilQueue() {
    if (frontQ == NULL) { cout << "\nAntrean kosong!\n"; return; }
    QueueNode* temp = frontQ;
    int nomor = 1;
    cout << "\n===== DAFTAR ANTREAN =====";
    while (temp != NULL) {
        cout << "\nNo.      : " << nomor;
        cout << "\nPembeli  : " << temp->pembeli;
        cout << "\nKonser   : " << temp->konser;
        cout << "\nJumlah   : " << temp->jumlah;
        cout << "\n--------------------------";
        temp = temp->next; nomor++;
    }
}

void prosesQueue() {
    if (frontQ == NULL) { cout << "\nAntrean kosong!\n"; return; }
    QueueNode* hapus = frontQ;
    cout << "\n===== PROSES ANTREAN =====";
    cout << "\nMemproses pesanan :";
    cout << "\nPembeli  : " << hapus->pembeli;
    cout << "\nKonser   : " << hapus->konser;
    cout << "\nJumlah   : " << hapus->jumlah;
    frontQ = frontQ->next;
    delete hapus;
    if (frontQ == NULL) rearQ = NULL;
    cout << "\n\nPesanan berhasil diproses!\n";
}

void pushStack(char pembeli[], char konser[], int jumlah) {
    StackNode* baru = new StackNode;
    strcpy(baru->pembeli, pembeli);
    strcpy(baru->konser, konser);
    baru->jumlah = jumlah;
    baru->next = topStack;
    topStack = baru;
}

void undoTransaksi() {
    if (topStack == NULL) { cout << "\nTidak ada transaksi yang bisa di-undo!\n"; return; }
    
    StackNode* hapus = topStack;
    Node* temp = head;
    
    while (temp != NULL) {
        if (strcmp(temp->data.nama, hapus->konser) == 0) {
            temp->data.stok += hapus->jumlah; break;
        }
        temp = temp->next;
    }
    
    QueueNode* currQ = frontQ;
    QueueNode* prevQ = NULL;
    
    while (currQ != NULL) {
        if (strcmp(currQ->pembeli, hapus->pembeli) == 0 && 
            strcmp(currQ->konser, hapus->konser) == 0 && 
            currQ->jumlah == hapus->jumlah) {
            
            if (prevQ == NULL) {
                frontQ = currQ->next;
                if (frontQ == NULL) rearQ = NULL;
            } else {
                prevQ->next = currQ->next;
                if (currQ->next == NULL) rearQ = prevQ;
            }
            delete currQ;
            break;
        }
        prevQ = currQ;
        currQ = currQ->next;
    }

    cout << "\n===== UNDO TRANSAKSI =====";
    cout << "\nTransaksi dibatalkan :";
    cout << "\nPembeli  : " << hapus->pembeli;
    cout << "\nKonser   : " << hapus->konser;
    cout << "\nJumlah   : " << hapus->jumlah;
    cout << "\nStok konser telah dikembalikan.\n";
    
    topStack = topStack->next;
    delete hapus;
}

void pesanTiket() {
    if (head == NULL) { cout << "\nData konser kosong!\n"; return; }
    tampilKonser();
    int id; bool found = false;
    cout << "\nMasukkan ID konser yang ingin dipesan : "; cin >> id; cin.ignore();
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data.id == id) {
            found = true;
            char pembeli[100]; int jumlah;
            cout << "Nama Pembeli : "; cin.getline(pembeli, 100);
            cout << "Jumlah Tiket : "; cin >> jumlah; cin.ignore();
            if (jumlah <= 0) { cout << "\nJumlah tiket tidak valid!\n"; return; }
            if (jumlah > temp->data.stok) {
                cout << "\nStok tidak cukup! Stok tersedia : " << temp->data.stok << "\n"; return;
            }
            temp->data.stok -= jumlah;
            enqueue(pembeli, temp->data.nama, jumlah);
            pushStack(pembeli, temp->data.nama, jumlah);
            cout << "\nTiket berhasil dipesan! Pesanan masuk ke antrean.\n"; break;
        }
        temp = temp->next;
    }
    if (!found) cout << "\nKonser tidak ditemukan!\n";
}

void simpanFile() {
    FILE* file = fopen("konser.txt", "w");
    if (!file) { cout << "\nFile gagal dibuat!\n"; return; }
    Node* temp = head;
    while (temp != NULL) {
        fprintf(file, "%d|%s|%s|%d|%d\n",
                temp->data.id, temp->data.nama, temp->data.lokasi,
                temp->data.harga, temp->data.stok);
        temp = temp->next;
    }
    fclose(file);
    cout << "\nData berhasil disimpan ke file konser.txt!\n";
}

void loadFile() {
    FILE* file = fopen("konser.txt", "r");
    if (!file) { cout << "\nFile belum ada!\n"; return; }
    if (head != NULL) {
        char konfirmasi;
        cout << "\nData yang ada akan diganti dengan data dari file. Lanjutkan? (y/n) : ";
        cin >> konfirmasi; cin.ignore();
        if (konfirmasi != 'y' && konfirmasi != 'Y') {
            fclose(file); cout << "\nMuat data dibatalkan.\n"; return;
        }
    }
    while (head != NULL) {
        Node* hapus = head; head = head->next; delete hapus;
    }
    while (!feof(file)) {
        Node* baru = new Node;
        if (fscanf(file, "%d|%99[^|]|%99[^|]|%d|%d\n",
                   &baru->data.id, baru->data.nama, baru->data.lokasi,
                   &baru->data.harga, &baru->data.stok) != 5) {
            delete baru; break;
        }
        baru->next = NULL;
        if (head == NULL) head = baru;
        else {
            Node* temp = head;
            while (temp->next != NULL) temp = temp->next;
            temp->next = baru;
        }
    }
    fclose(file);
    cout << "\nData berhasil dimuat dari file konser.txt!\n";
}

void subMenuKelolaKonser() {
    int pilih;
    do {
        cout << "\n======================================";
        cout << "\n      MENU KELOLA KONSER (ADMIN)";
        cout << "\n======================================";
        cout << "\n1. Tambah Konser\n2. Tampilkan Konser";
        cout << "\n3. Edit Konser\n4. Hapus Konser\n0. Kembali";
        cout << "\n======================================";
        cout << "\nPilih menu : "; cin >> pilih; cin.ignore();
        switch (pilih) {
            case 1: tambahKonser(); break;
            case 2: tampilKonser(); break;
            case 3: editKonser(); break;
            case 4: hapusKonser(); break;
            case 0: cout << "\nKembali ke menu admin...\n"; break;
            default: cout << "\nMenu tidak tersedia!\n";
        }
    } while (pilih != 0);
}

void subMenuTransaksiAdmin() {
    int pilih;
    do {
        cout << "\n======================================";
        cout << "\n     MENU TRANSAKSI TIKET (ADMIN)";
        cout << "\n======================================";
        cout << "\n1. Proses Antrean\n2. Undo Transaksi\n3. Lihat Antrean\n0. Kembali";
        cout << "\n======================================";
        cout << "\nPilih menu : "; cin >> pilih; cin.ignore();
        switch (pilih) {
            case 1: prosesQueue(); break;
            case 2: undoTransaksi(); break;
            case 3: tampilQueue(); break;
            case 0: cout << "\nKembali ke menu admin...\n"; break;
            default: cout << "\nMenu tidak tersedia!\n";
        }
    } while (pilih != 0);
}

void subMenuSimpanMuatAdmin() {
    int pilih;
    do {
        cout << "\n======================================";
        cout << "\n   MENU SIMPAN & MUAT DATA (ADMIN)";
        cout << "\n======================================";
        cout << "\n1. Simpan Data ke File\n2. Muat Data dari File\n0. Kembali";
        cout << "\n======================================";
        cout << "\nPilih menu : "; cin >> pilih; cin.ignore();
        switch (pilih) {
            case 1: simpanFile(); break;
            case 2: loadFile(); break;
            case 0: cout << "\nKembali ke menu admin...\n"; break;
            default: cout << "\nMenu tidak tersedia!\n";
        }
    } while (pilih != 0);
}

void menuAdmin() {
    int pilih;
    do {
        cout << "\n======================================";
        cout << "\n   CONCERT TICKET MANAGEMENT SYSTEM";
        cout << "\n          MENU UTAMA - ADMIN";
        cout << "\n======================================";
        cout << "\n1. Kelola Konser\n2. Transaksi Tiket\n3. Simpan & Muat Data\n0. Keluar";
        cout << "\n======================================";
        cout << "\nPilih menu : "; cin >> pilih; cin.ignore();
        switch (pilih) {
            case 1: subMenuKelolaKonser(); break;
            case 2: subMenuTransaksiAdmin(); break;
            case 3: subMenuSimpanMuatAdmin(); break;
            case 0: cout << "\nKembali ke menu utama...\n"; break;
            default: cout << "\nMenu tidak tersedia!\n";
        }
    } while (pilih != 0);
}

void subMenuCariUrutUser() {
    int pilih;
    do {
        cout << "\n======================================";
        cout << "\n     MENU CARI & URUTKAN DATA";
        cout << "\n======================================";
        cout << "\n1. Cari Konser (Sequential Search)";
        cout << "\n2. Cari Konser (Binary Search)";
        cout << "\n3. Urutkan Harga (Bubble Sort)";
        cout << "\n4. Urutkan Stok (Selection Sort)";
        cout << "\n5. Urutkan Nama A-Z (Quick Sort)\n0. Kembali";
        cout << "\n======================================";
        cout << "\nPilih menu : "; cin >> pilih; cin.ignore();
        switch (pilih) {
            case 1: sequentialSearch(); break;
            case 2: binarySearch(); break;
            case 3: bubbleSort(); break;
            case 4: selectionSort(); break;
            case 5: quickSortMenu(); break;
            case 0: cout << "\nKembali ke menu user...\n"; break;
            default: cout << "\nMenu tidak tersedia!\n";
        }
    } while (pilih != 0);
}

void subMenuPesanUser() {
    int pilih;
    do {
        cout << "\n======================================";
        cout << "\n       MENU PEMESANAN TIKET";
        cout << "\n======================================";
        cout << "\n1. Pesan Tiket\n2. Lihat Antrean Saya\n0. Kembali";
        cout << "\n======================================";
        cout << "\nPilih menu : "; cin >> pilih; cin.ignore();
        switch (pilih) {
            case 1: pesanTiket(); break;
            case 2: tampilQueue(); break;
            case 0: cout << "\nKembali ke menu user...\n"; break;
            default: cout << "\nMenu tidak tersedia!\n";
        }
    } while (pilih != 0);
}

void menuUser() {
    int pilih;
    do {
        cout << "\n======================================";
        cout << "\n   CONCERT TICKET MANAGEMENT SYSTEM";
        cout << "\n          MENU UTAMA - USER";
        cout << "\n======================================";
        cout << "\n1. Tampilkan Konser\n2. Cari & Urutkan Konser\n3. Pemesanan Tiket\n0. Keluar";
        cout << "\n======================================";
        cout << "\nPilih menu : "; cin >> pilih; cin.ignore();
        switch (pilih) {
            case 1: tampilKonser(); break;
            case 2: subMenuCariUrutUser(); break;
            case 3: subMenuPesanUser(); break;
            case 0: cout << "\nKembali ke menu utama...\n"; break;
            default: cout << "\nMenu tidak tersedia!\n";
        }
    } while (pilih != 0);
}

int main() {
    int pilih;
    do {
        cout << "\n======================================";
        cout << "\n   CONCERT TICKET MANAGEMENT SYSTEM";
        cout << "\n======================================";
        cout << "\n1. Masuk sebagai Admin\n2. Masuk sebagai User\n0. Keluar";
        cout << "\n======================================";
        cout << "\nPilih : "; cin >> pilih; cin.ignore();
        if (pilih == 1) {
            if (loginAdmin()) menuAdmin();
        }
        else if (pilih == 2) {
            cout << "\nSelamat datang, User!\n";
            menuUser();
        }
        else if (pilih == 0) cout << "\nProgram selesai.\n";
        else cout << "\nPilihan tidak tersedia!\n";
    } while (pilih != 0);
    return 0;
}
