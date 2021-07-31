#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// Doubly linked list
struct node{
    string name;
    ll mobile;
    struct node* next;
    struct node* prev;
};

// Start of Phonebook
struct node* pb[26]={NULL};

// Add contact
void addContact(){
    cout<<"Enter name: ";
    string s;
    cin>>s;
    cout<<"Enter mobile no.: ";
    ll m;
    cin>>m;
    // Get starting letter;
    int key;
    if(s[0]>='a')
        s[0]=char(s[0]-32);
    key=(s[0]-65);
    struct node* head=pb[key];
    if(head==NULL){
        struct node* newEntry=new node();
        newEntry->name=s;
        newEntry->mobile=m;
        newEntry->next=NULL;
        newEntry->prev=NULL;
        pb[key]=newEntry;
        return;
    }
    while(head->next){
        if(head->name==s){
            cout<<"Entry already exists!"<<endl;
            return;
        }
        head=head->next;
    }
    if(head->name==s){
        cout<<"Entry already exists!"<<endl;
        return;
    }
    struct node* newEntry=new node();
    newEntry->name=s;
    newEntry->mobile=m;
    newEntry->next=NULL;
    newEntry->prev=head;
    head->next=newEntry;
}

// Search contact
void searchContactByName(){
    cout<<"Enter name: ";
    string s;
    cin>>s;
    // Get starting letter;
    int key;
    if(s[0]>='a')
        s[0]=char(s[0]-32);
    key=(s[0]-65);
    struct node* head=pb[key];
    while(head){
        if(head->name==s){
            cout<<head->name<<"\t\t"<<head->mobile<<endl;
            return;
        }
        head=head->next;
    }
    cout<<"Sorry no such contact exists!"<<endl;
}
void searchContactByNumber(){
    cout<<"Enter mobile no: ";
    ll m;
    cin>>m;
    for(int i=0;i<26;i++){
        struct node* head=pb[i];
        while(head){
            if(head->mobile==m){
                cout<<head->name<<"\t\t"<<head->mobile<<endl;
                return;
            }
            head=head->next;
        }
    }
    cout<<"Sorry no such contact exists!"<<endl;
}

// Delete a contact
void deleteContact(){
    cout<<"Enter name: ";
    string s;
    cin>>s;
    cout<<"Enter mobile no: ";
    ll m;
    cin>>m;
    // Get starting letter;
    int key;
    if(s[0]>='a')
        s[0]=char(s[0]-32);
    key=(s[0]-65);
    struct node* head=pb[key];
    struct node* headPrev=NULL;
    while(head){
        if(head->name==s && head->mobile==m){
            if(headPrev==NULL){
                pb[key]=head->next;
                head->next->prev=NULL;
                free(head);
                cout<<"Contact deleted successfully!"<<endl;
                return;
            }
            head->next->prev=headPrev;
            headPrev->next=head->next;
            head->prev=NULL;
            head->next=NULL;
            free(head);
            cout<<"Contact deleted successfully!"<<endl;
            return;
        }
        headPrev=head;
        head=head->next;
    }
    cout<<"Sorry no such contact exists!"<<endl;
}

// Modify mobile no.
void modifyNumber(){
    cout<<"Enter name: ";
    string s;
    cin>>s;
    cout<<"Enter current mobile no: ";
    ll m_old;
    cin>>m_old;
    // Get starting letter;
    int key;
    if(s[0]>='a')
        s[0]=char(s[0]-32);
    key=(s[0]-65);
    struct node* head=pb[key];
    while(head){
        if(head->name==s && head->mobile==m_old){
            cout<<"Enter new mobile no: ";
            ll m_new;
            cin>>m_new;
            head->mobile=m_new;
            cout<<"Contact modified successfully!"<<endl;
            return;
        }
        head=head->next;
    }
    cout<<"Sorry no such contact exists!"<<endl;
}

// Display Phonebook
void displayPB(){
    cout<<"Phonebook: \n\n";
    for(int i=0;i<26;i++){
        struct node* head=pb[i];
        if(!head){
            continue;
        }
        cout<<char(i+65)<<": "<<endl;
        int cnt=0;
        while(head){
            cnt++;
            cout<<cnt<<". "<<head->name<<"\t\t"<<head->mobile<<endl;
            head=head->next;
        }
        cout<<endl;
    }
}

// Main function
int main(){
    // Menu
    int loop;
    bool screen=true;
    cout<<"---------------MENU-----------------"<<endl;
    while(screen){
        cout<<"1. Add\t\t2. Search\t\t3. Delete\t\t4. Modify\t\t5. Display\t\t6. Exit"<<endl;
        string test;
        cin>>test;
        if(test.size()>1 || test[0]<'1' || test[0]>'6'){
            cout<<"Invalid Operation!"<<endl;
            continue;
        }
        loop=test[0]-'0';
        switch(loop){
            case 1:
                addContact();
                break;
            case 2:
                cout<<"Search by: "<<endl;
                cout<<"1. Name\t\t2. Mobile no."<<endl;
                int type;
                cin>>type;
                if(type==1){
                    searchContactByName();
                }
                else{
                    searchContactByNumber();
                }
                break;
            case 3:
                deleteContact();
                break;
            case 4:
                modifyNumber();
                break;
            case 5:
                displayPB();
                break;
            case 6:
                screen=false;
                break;
        }
    }
}
