#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Bank{
    public:
    int accno;
    string name;
    float balance;
    string password;

    void create_account();
    void check_balance();
    void deposit();
    void withdraw();
};

void Bank::create_account(){
    cout<<"Enter account number: ";
    cin>>accno;
    cout<<"Enter name: ";
    cin>>name;
    cout<<"Enter password: ";
    cin>>password;
    cout<<"Enter initial balance: ";
    cin>>balance;

    ofstream file;
    file.open("bank.dat", ios::app | ios::binary);
    file.write((char*)this, sizeof(*this));
    file.close();
}

void Bank::check_balance(){
    int num;
    string pass;
    cout<<"Enter account number: ";
    cin>>num;
    cout<<"Enter password: ";
    cin>>pass;

    ifstream file;
    file.open("bank.dat", ios::in | ios::binary);
    while(file.read((char*)this, sizeof(*this))){
        if(accno == num && password == pass){
            cout<<"Balance: "<<balance<<endl;
            break;
        }
    }
    file.close();
}

void Bank::deposit(){
    int num;
    string pass;
    float amount;
    cout<<"Enter account number: ";
    cin>>num;
    cout<<"Enter password: ";
    cin>>pass;
    cout<<"Enter amount to deposit: ";
    cin>>amount;

    fstream file;
    file.open("bank.dat", ios::in | ios::out | ios::binary);
    while(file.read((char*)this, sizeof(*this))){
        if(accno == num && password == pass){
            balance += amount;
            int pos = (-1)*static_cast<int>(sizeof(*this));
            file.seekp(pos, ios::cur);
            file.write((char*)this, sizeof(*this));
            break;
        }
    }
    file.close();
}

void Bank::withdraw(){
    int num;
    string pass;
    float amount;
    cout<<"Enter account number: ";
    cin>>num;
    cout<<"Enter password: ";
    cin>>pass;
    cout<<"Enter amount to withdraw: ";
    cin>>amount;

    fstream file;
    file.open("bank.dat", ios::in | ios::out | ios::binary);
    while(file.read((char*)this, sizeof(*this))){
        if(accno == num && password == pass){
            if(balance >= amount){
                balance -= amount;
                int pos = (-1)*static_cast<int>(sizeof(*this));
                file.seekp(pos, ios::cur);
                file.write((char*)this, sizeof(*this));
            }else{
                cout<<"Insufficient balance!\n";
            }
            break;
        }
    }
    file.close();
}

int main(){
    Bank b;
    int choice;
    do{
        cout<<"1. Create Account\n2. Check Balance\n3. Deposit\n4. Withdraw\n5. Exit\nEnter your choice: ";
        cin>>choice;
        switch(choice){
            case 1: b.create_account(); break;
            case 2: b.check_balance(); break;
            case 3: b.deposit(); break;
            case 4: b.withdraw(); break;
            case 5: break;
            default: cout<<"Invalid choice!\n";
        }
    }while(choice != 5);

    return 0;
}
