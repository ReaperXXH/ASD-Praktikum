#include <iostream>

using namespace std;

class Node {
public:
    char name[100];
    bool is_directory;
    Node* children[100];
    int counter;
    char owner[100];

    Node(const char* name, bool folder, const char* owner) 
        : is_directory(folder), counter(0) {
        int i = 0;
        while (name[i] != '\0') {
            this->name[i] = name[i];
            i++;
        }
        this->name[i] = '\0';

        i = 0;
        while (owner[i] != '\0') {
            this->owner[i] = owner[i];
            i++;
        }
        this->owner[i] = '\0';
    }

    void add_child(Node* child) {
        if (counter < 100) {
            children[counter++] = child;
        }
    }

    void remove_child(Node* child) {
        int index = -1;
        for (int i = 0; i < counter; i++) {
            if (children[i] == child) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            for (int i = index; i < counter - 1; i++) {
                children[i] = children[i + 1];
            }
            counter--;
        }
    }

    void list_children(bool detail) {
        for (int i = 0; i < counter; i++) {
            Node* child = children[i];
            if (detail) {
                cout << (child->is_directory ? "Directory" : "File") << "\t" 
                     << child->name << "\t" 
                     << child->owner << endl;
            } else {
                cout << child->name << endl;
            }
        }
    }

    void traverse(const char* indent = "") {
        cout << indent << name << (is_directory ? "/" : "") << endl;
        char new_indent[100];
        int i = 0;
        while (indent[i] != '\0') {
            new_indent[i] = indent[i];
            i++;
        }
        new_indent[i] = '\0';
        for (int j = 0; "    "[j] != '\0'; j++) {
            new_indent[i++] = "    "[j];
        }
        new_indent[i] = '\0';
        for (int j = 0; j < counter; j++) {
            children[j]->traverse(new_indent);
        }
    }

    const char* search(const char* name, const char* path = "") {
        static char found_path[1000];
        int name_len = 0;
        while (name[name_len] != '\0') {
            name_len++;
        }
        int path_len = 0;
        while (path[path_len] != '\0') {
            path_len++;
        }

        bool match = true;
        for (int i = 0; i < name_len; i++) {
            if (this->name[i] != name[i]) {
                match = false;
                break;
            }
        }

        if (match && this->name[name_len] == '\0') {
            int i = 0;
            while (path[i] != '\0') {
                found_path[i] = path[i];
                i++;
            }
            for (int j = 0; this->name[j] != '\0'; j++) {
                found_path[i++] = this->name[j];
            }
            found_path[i] = '\0';
            return found_path;
        }

        if (is_directory) {
            char new_path[1000];
            int i = 0;
            while (path[i] != '\0') {
                new_path[i] = path[i];
                i++;
            }
            for (int j = 0; this->name[j] != '\0'; j++) {
                new_path[i++] = this->name[j];
            }
            new_path[i++] = '/';
            new_path[i] = '\0';

            for (int j = 0; j < counter; j++) {
                const char* result = children[j]->search(name, new_path);
                if (result) {
                    return result;
                }
            }
        }
        return nullptr;
    }
};

class FileSystem {
private:
    Node* root;
    Node* current_node;
    char owner[100];

public:
    FileSystem(const char* owner) {
        int i = 0;
        while (owner[i] != '\0') {
            this->owner[i] = owner[i];
            i++;
        }
        this->owner[i] = '\0';

        root = new Node("user", true, owner);
        current_node = root;
    }

    void make_file(const char* name) {
        Node* new_file = new Node(name, false, owner);
        current_node->add_child(new_file);
    }

    void make_directory(const char* name) {
        Node* new_directory = new Node(name, true, owner);
        current_node->add_child(new_directory);
    }

    void change_directory(const char* path) {
        int path_len = 0;
        while (path[path_len] != '\0') {
            path_len++;
        }

        if (path_len == 4 && path[0] == 'u' && path[3] == 'r') {
            current_node = root;
        } else {
            for (int i = 0; i < current_node->counter; i++) {
                bool match = true;
                for (int j = 0; j < path_len; j++) {
                    if (current_node->children[i]->name[j] != path[j]) {
                        match = false;
                        break;
                    }
                }
                if (match && current_node->children[i]->name[path_len] == '\0' && current_node->children[i]->is_directory) {
                    current_node = current_node->children[i];
                    return;
                }
            }
            cout << "Directory not found" << endl;
        }
    }

    void remove(const char* name) {
        int name_len = 0;
        while (name[name_len] != '\0') {
            name_len++;
        }

        for (int i = 0; i < current_node->counter; i++) {
            bool match = true;
            for (int j = 0; j < name_len; j++) {
                if (current_node->children[i]->name[j] != name[j]) {
                    match = false;
                    break;
                }
            }
            if (match && current_node->children[i]->name[name_len] == '\0') {
                current_node->remove_child(current_node->children[i]);
                return;
            }
        }
        cout << "File or Directory not found" << endl;
    }

    void list_current_directory(bool detail = false) {
        current_node->list_children(detail);
    }

    void traverse_file_system() {
        root->traverse();
    }

    void search_file(const char* name) {
        const char* result = root->search(name, "");
        if (result) {
            cout << "Found: " << result << endl;
        } else {
            cout << "File not found" << endl;
        }
    }
};

int main() {
    FileSystem fs("owner");
    int choice;
    char name[100];
    char path[100];

    // Create default structure
    fs.make_directory("lib");
    fs.make_directory("src");
    fs.change_directory("lib");
    fs.make_file("LiquidCrystal_I2C.zip");
    fs.make_file("ServoESP32-master.zip");
    fs.change_directory("user");
    fs.change_directory("src");
    fs.make_directory("Smart_Fan");
    fs.change_directory("Smart_Fan");
    fs.make_file("config.h");
    fs.make_file("my_wifi.h");
    fs.make_file("Smart_Fan.ino");
    fs.make_file("wifi_communicator.h");

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Buat File\n";
        cout << "2. Buat Direktori\n";
        cout << "3. Hapus File/Direktori\n";
        cout << "4. Ubah Direktori\n";
        cout << "5. Daftar Isi Direktori\n";
        cout << "6. Traverse File System\n";
        cout << "7. Cari File\n";
        cout << "8. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Masukkan nama file: ";
                cin >> name;
                fs.make_file(name);
                break;
            case 2:
                cout << "Masukkan nama direktori: ";
                cin >> name;
                fs.make_directory(name);
                break;
            case 3:
                cout << "Masukkan nama file/direktori untuk dihapus: ";
                cin >> name;
                fs.remove(name);
                break;
            case 4:
                cout << "Masukkan path direktori: ";
                cin >> path;
                fs.change_directory(path);
                break;
            case 5:
                fs.list_current_directory(true);
                break;
            case 6:
                fs.traverse_file_system();
                break;
            case 7:
                cout << "Masukkan nama file untuk dicari: ";
                cin >> name;
                fs.search_file(name);
                break;
            case 8:
                return 0;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}
