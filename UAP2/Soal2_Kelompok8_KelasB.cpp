#include <iostream>

using namespace std;

// struct 
struct Mahasiswa {
    char nama[100];
    char nim[100];
    int nilai[5];
    int presensi;

    Mahasiswa() {}

    Mahasiswa(const char* nama, const char* nim, int nilai[5], int presensi) {
        for (int i = 0; i < 100; ++i) {
            this->nama[i] = nama[i];
            this->nim[i] = nim[i];
            if (nama[i] == '\0') break;
        }
        for (int i = 0; i < 5; ++i) {
            this->nilai[i] = nilai[i];
        }
        this->presensi = presensi;
    }
    //menghitung nilai rata rata dari array input 
    float rata_rata_nilai() {
        int total = 0;
        for (int i = 0; i < 5; ++i) {
            total += nilai[i];
        }
        return total / 5.0f;
    }
};

struct Node {
    Mahasiswa data;
    Node* next;
    // konstruktor node, parameter input tipe mahasiswa (struct)
    Node(Mahasiswa data) : data(data), next(nullptr) {}
};


// fungsi untuk membandingkan ASCII pada char namanya
int Banding_ASCII(const char* str1, const char* str2) {
    //dia akan loop tiap charnya
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    // kedua ascii charnya di kurangi
    // jika hasil positif maka str1 > str 2
    // jika hasil negatif maka str2 > str1
    // jika sama, maka str1=str2
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

struct Data_Mahasiswa {
    Node* head;
    int jumlah_mahasiswa;

    Data_Mahasiswa() {
        head = nullptr;
        jumlah_mahasiswa = 0;
    }

    void tambah_mahasiswa(const char* nama, const char* nim, int nilai[5], int presensi) {
        Mahasiswa mhs(nama, nim, nilai, presensi);
        Node* new_node = new Node(mhs);  // buat node baru 
        if (head == nullptr) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new_node;
        }
        jumlah_mahasiswa++;
    }
    // untuk menukar node 
    void swap(Node* a, Node* b) {
        Mahasiswa temp = a->data;
        a->data = b->data;
        b->data = temp;
    }

    void bubble_sort_nama(bool ascendORdescend) {
        for (int i = 0; i < jumlah_mahasiswa - 1; ++i) {
            Node* current = head;
            for (int j = 0; j < jumlah_mahasiswa - i - 1; ++j) {
                if (current->next == nullptr) break;
                bool should_swap = false;
                if (ascendORdescend) {
                    if (Banding_ASCII(current->data.nama, current->next->data.nama) > 0) {
                        should_swap = true;
                    }
                } else { // descending 
                    if (Banding_ASCII(current->data.nama, current->next->data.nama) < 0) {
                        should_swap = true;
                    }
                }
                if (should_swap) {
                    swap(current, current->next);
                }
                current = current->next;
            }
        }
    }

    void bubble_sort_nim(bool ascendORdescend) {
        for (int i = 0; i < jumlah_mahasiswa - 1; ++i) {
            Node* current = head;
            for (int j = 0; j < jumlah_mahasiswa - i - 1; ++j) {
                if (current->next == nullptr) break;
                bool should_swap = false;
                if (ascendORdescend) {
                    if (Banding_ASCII(current->data.nim, current->next->data.nim) > 0) {
                        should_swap = true;
                    }
                } else {
                    if (Banding_ASCII(current->data.nim, current->next->data.nim) < 0) {
                        should_swap = true;
                    }
                }
                if (should_swap) {
                    swap(current, current->next);
                }
                current = current->next;
            }
        }
    }

    void bubble_sort_rata_rata(bool ascendORdescend) {
        for (int i = 0; i < jumlah_mahasiswa - 1; ++i) {
            Node* current = head;
            for (int j = 0; j < jumlah_mahasiswa - i - 1; ++j) {
                if (current->next == nullptr) break;
                bool should_swap = false;
                if (ascendORdescend) {
                    if (current->data.rata_rata_nilai() > current->next->data.rata_rata_nilai()) {
                        should_swap = true;
                    }
                } else {
                    if (current->data.rata_rata_nilai() < current->next->data.rata_rata_nilai()) {
                        should_swap = true;
                    }
                }
                if (should_swap) {
                    swap(current, current->next);
                }
                current = current->next;
            }
        }
    }

    void bubble_sort_presensi(bool ascendORdescend) {
        for (int i = 0; i < jumlah_mahasiswa - 1; ++i) {
            Node* current = head;
            for (int j = 0; j < jumlah_mahasiswa - i - 1; ++j) {
                if (current->next == nullptr) break;
                bool should_swap = false;
                if (ascendORdescend) {
                    if (current->data.presensi > current->next->data.presensi) {
                        should_swap = true;
                    }
                } else {
                    if (current->data.presensi < current->next->data.presensi) {
                        should_swap = true;
                    }
                }
                if (should_swap) {
                    swap(current, current->next);
                }
                current = current->next;
            }
        }
    }

    void urutkan(int kriteria, bool ascendORdescend) {
        if (kriteria == 1) {
            bubble_sort_nama(ascendORdescend);
        } else if (kriteria == 2) {
            bubble_sort_nim(ascendORdescend);
        } else if (kriteria == 3) {
            bubble_sort_rata_rata(ascendORdescend);
        } else if (kriteria == 4) {
            bubble_sort_presensi(ascendORdescend);
        }
    }
    
    void tampilkan() {
        Node* current = head;
        while (current != nullptr) {
            Mahasiswa& mhs = current->data;
            cout << mhs.nama << " - " << mhs.nim << " - ";
            for (int j = 0; j < 5; ++j) {
                cout << mhs.nilai[j] << (j < 4 ? ", " : " - ");
            }
            cout << mhs.rata_rata_nilai() << " - " << mhs.presensi << "%" << endl;
            current = current->next;
        }
    }

    void tampilkan_presensi_lebih_dari_80() {
        Node* current = head;
        while (current != nullptr) {
            Mahasiswa& mhs = current->data;
            if (mhs.presensi > 80) {
                cout << mhs.nama << " - " << mhs.nim << " - ";
                for (int j = 0; j < 5; ++j) {
                    cout << mhs.nilai[j] << (j < 4 ? ", " : " - ");
                }
                cout << mhs.rata_rata_nilai() << " - " << mhs.presensi << "%" << endl;
            }
            current = current->next;
        }
    }
};

int main() {
    Data_Mahasiswa Data_MHS;
    char pilihan;
    int jumlah_mahasiswa;

    

    cout << "Masukkan jumlah mahasiswa: ";
    cin >> jumlah_mahasiswa;

    for (int i = 0; i < jumlah_mahasiswa; ++i) {
        char nama[100], nim[100];
        int nilai[5];
        int presensi;

        cout << "Masukkan data untuk mahasiswa ke-" << (i + 1) << ": " <<endl;
        cout << "Nama: ";
        cin.ignore();
        cin >> nama;
        cout << "NIM: ";
        cin >> nim;
        cout << "Nilai (5 nilai dipisahkan dengan spasi): ";
        for (int j = 0; j < 5; ++j) {
            cin >> nilai[j];
        }
        cout << "Persentase Presensi: ";
        cin >> presensi;

        Data_MHS.tambah_mahasiswa(nama, nim, nilai, presensi);
        cout << endl;
    }
    // inputan
    do{
    int kriteria, urutan;
    cout << endl <<"Pilih kriteria pengurutan:\n1. Nama\n2. NIM\n3. Nilai Rata-Rata\n4. Persentase Presensi\n Pilih : ";
    cin >> kriteria;
    cout << endl << "Pilih urutan pengurutan:\n1. Ascending\n2. Descending\n Pilih :";
    cin >> urutan;

    Data_MHS.urutkan(kriteria, urutan == 1);

    cout << "\nDaftar mahasiswa yang telah diurutkan:" <<endl;
    Data_MHS.tampilkan();

    cout <<endl<< "Mahasiswa dengan presensi lebih dari 80%:"<<endl;
    Data_MHS.tampilkan_presensi_lebih_dari_80();
    cout << endl << "Apakah ingin menyorting lagi ? (Y/N) :";
    cin>>pilihan;
    cout << endl;
    }while (pilihan == 'y' || pilihan =='Y');
    return 0;
}
