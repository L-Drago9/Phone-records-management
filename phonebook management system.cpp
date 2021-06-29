#include <bits/stdc++.h>
using namespace std;
struct node{
    int num;
    string name;
    struct node *next;
};
struct node* head; //global start pointer
FILE *fp; // Global file pointer
struct node *getrecord(){
    struct node *temp,e;
    temp=new node();
    cout<<"Reached..."<<endl;
    getch();
    fflush(stdin);
    // fscanf(fp,"%d %s",&temp->num,temp->name);
    fread(&temp,sizeof(temp),1,fp);
    cout<<temp->num<<" "<<temp->name;
    // strcpy(temp->name,e.name);
    getch();
    temp->next=NULL;
    return temp;
}
struct node *getnode(){
    struct node *temp;
    temp=new node();
    cout<<"Enter the person's phone number- ";
    cin>>temp->num;
    cout<<"Enter the person's Name- ";
    cin>>temp->name;
    temp->next=NULL;
    return temp;
}
struct node *searchByNo(int number,int &flag){
    struct node *cur=head,*prev=NULL;
    flag=0;
    if(head==NULL)
        return NULL;
    while(cur){
        if(cur->num==number){
            flag=1;
            return prev;
        }
        prev=cur;
        cur=cur->next;
    }
    flag=-1;
    return NULL;
}
int insert(struct node *new1){
    struct node *prev;
    int flag;
    if(head==NULL){
        head=new1; //first node in list
        return 1;
    }
    prev=searchByNo(new1->num,flag);
    if(flag==-1)
        return -1;
    new1->next=prev->next;
    prev->next=new1; // insert in the middle or end
    return 1;
}
void display(){
    struct node *cur;
    int n=0;
    if(list==NULL){
        cout<<"List empty !"<<endl;
        return;
    }
    cout<<"The phone records are--->";
    cur=list;
    while(cur){
        cout<<"Record no.-"<<n+1;
        cout<<"Record holder's number-"<<cur->num;
        cout<<"Record holder's name-"<<cur->name;
        n++;
    }
}
int delnode(int id){
    struct node *prev,*temp;
    int flag=0;
    if(list==NULL)
        return -1;
    prev=search(id,flag);
    if(flag==0)
        return -1;
    if(prev==NULL){
        temp=list;
        list=list->next;
        free(temp);
    }
    temp=prev->next;
    prev->next=temp->next;
    free(temp);
    return 1;
}
void CopyToFile(){
    FILE *fp;
    struct node *cur;
    fp=fopen("phone.txt","w");

    cur=list;
    if(cur==NULL){
        printf("The list is empty, nothing to write back...");
        return;
    }
    while(curr)
        fprintf(fp,"%d %s",cur->num,cur->name); //writing back to file
    fclose(fp);
}
int main(){
    int ch=0,ans=0;
    int val=0;
    string str;
    struct node *new1,*new2;
    /* initialization of list with the existing records */
    fp=fopen("phone.txt","r");
    if(fp==NULL){
        printf("File cant be opened !");
        gets(str);
        return 0;
    }
    while(!feof(fp)){
        new1=getrecord();
        if(insert(new1)==-1)
            printf("Cant insert record ! Error...");
        else
            printf("Record entered...");
    }
    getch();
    fclose(fp);
    do{
        printf("Menu");
        printf("1. Add a New phone record.");
        printf("2. Delete an existing Record.");
        printf("3. show all Records.");
        printf("4. Modify a particular Record.");
        printf("5. Exit.");
        printf("Enter your choice--->");
        cin>>ch;
        switch(ch){
        case 1:
            new1 = getnode();
            val = insert(new1);
            if(val==-1)
                cout<<"Employee id already exists!";
            else
                cout<<"Employee details successfully stored";
            break;

        case 2:
            cout<<"Enter the phone no.you wish to delete- ";
            cin>>val;
            ans=delnode(val);
            if(ans==-1)
                cout<<"Record doesnt exist!";
            else
                cout<<"Record deleted!";
            break;

        case 3:
            display();
            break;

        case 4:
            cout<<"Search by phone no. or Name ? (1/2)";
            cin>>ch;
            if(ch==1){
                cout<<"Enter the phone no. you wish to search for- ");
                cin>>val;
                new2=searchByNo(val);
            }
            else{
                cout<<"Enter the name of the person you wish to search for--->";
                cin>>str;
                new2=searchByName(val);
            }
            if(new2){
                cout<<"Enter the New name of the person--->";
                cin>>new2->name;
                cout<<"Enter new phone no. of the person--->";
                cin>>new2->num;
                cout<<"Record modified successfully !";
            }
            break;
        case 5:
            printf("Leaving Database, writing back to file...");
            CopyToFile();
            getch();
            free(list);
            return 0;
            break;
        }
        getch();
    }
    while(1);

}
