#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdlib.h>
#include<iomanip>


using namespace std;

class BloodGroup {
    private:
        int id;
        char name[30];
        char group[5];
        char phone[15];
    public:
        void get_details();
        void show_details();
        int get_id() {
            return id;
        }
};

void BloodGroup::get_details() {
    cout<<"Enter ID:";
        cin>>id;
    cout<<"Name: ";
        cin>>name;
    cout<<"Blood Group: ";
        cin>>group;
    cout<<"Phone Number: ";
        cin>>phone;

}
     
void BloodGroup::show_details() {
    cout<<id<<setw(12)<<name<<setw(14)<<group<<setw(25)<<phone<<endl;
}

void add_record();
void delete_record();
void show_record();
void show_all();
void modify_record();

BloodGroup bg;
fstream file;

int main() {
    int option;
    char choice='y';
    system("color 0B");
    system("cls");
    do {
        cout<<"Blood Group Management System\n";
        cout<<"1. Add Record\n2. Display All Records\n3. Display Single Record\n4. Delete Record\n5. Update Record\n";
        cout<<"Enter your choice: ";
        cin>>option;
        switch (option) {
            case 1:
                add_record();
                break;
            case 2:
                show_all();
                break;
            case 3:
                show_record();
                break;
            case 4:
                delete_record();
                break;
            case 5:
                modify_record();
                break;
            default:
                cout<<"Invalid option\n";
                break;
        }
        cout<<"Do you want to perform another operation? (yes or no): ";
        cin>>choice;
    } while(choice=='y' || choice=='Y');
    return 0;
}

void add_record() {
    char ch='y';
    file.open("blood.dat",ios::app|ios::binary);
    while(ch=='y' || ch=='Y') {
        bg.get_details();
        file.write((char*)&bg,sizeof(bg));
        cout<<"Add more records? (y or n): ";
        cin>>ch;
    }
    file.close();
}

void show_all() {
    file.open("blood.dat",ios::in|ios::binary);
    if(!file) {
        cout<<"File not found\n";
        exit(0);
    } else {
        system("cls");
        cout<<"ID\tName\t\tBlood Group\tPhone Number\n";
        cout<<"--------------------------------------------------------------\n";
        file.read((char*)&bg,sizeof(bg));
        while(!file.eof()) {
            bg.show_details();
            file.read((char*)&bg,sizeof(bg));
        }
    }
    file.close();
    getch();
}

void show_record() {
    int no,flag=0;
    file.open("blood.dat",ios::in|ios::binary);
    if(!file) {
        cout<<"File not found\n";
        exit(0);
    } else {
        cout<<"Enter the ID to search the record: ";
        cin>>no;
        file.read((char*)&bg,sizeof(bg));
        while(!file.eof()) {
            if(no==bg.get_id()) {
                flag=1;
                system("cls");
                cout<<"ID\tName\t\tBlood Group\tPhone Number\n";
                cout<<"--------------------------------------------------------------\n";
                bg.show_details();
            }
            file.read((char*)&bg,sizeof(bg));
        }
        if(flag==0) {
            cout<<"No record found\n";
        }
    }
    file.close();
    getch();
}

void delete_record() {
    int no;
    cout<<"Enter the ID to delete the record: ";
    cin>>no;
    ofstream file2;
    file2.open("new.dat",ios::out|ios::binary);
    file.open("blood.dat",ios::in|ios::binary);
    if(!file) {
        cout<<"File not found\n";
    } else {
        file.read((char*)&bg,sizeof(bg));
        while(!file.eof()) {
            if(no!=bg.get_id()) {
                file2.write((char*)&bg,sizeof(bg));
            }
            file.read((char*)&bg,sizeof(bg));
        }
        file2.close();
        file.close();
        remove("blood.dat");
        rename("new.dat","blood.dat");
        cout<<"Record deleted successfully\n";
    }
    getch();
}

void modify_record() {
    int no;
    cout<<"Enter the ID to modify the record: ";
    cin>>no;
    file.open("blood.dat",ios::in|ios::out|ios::binary);
    if(!file) {
        cout<<"File not found\n";
    } else {
        while(file.read((char*)&bg,sizeof(bg))) {
            if(bg.get_id()==no) {
                bg.get_details();
                int pos=sizeof(bg);
                file.seekp(-pos,ios::cur);
                file.write((char*)&bg,sizeof(bg));
                cout<<"Record updated successfully\n";
            }
        }
        file.close();
    }
    getch();
}