#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
const int tablesize=128;
struct node{
    int data;
    struct node* next;
};
class Hashentry{
public:
    node* key;
    node* value;
    Hashentry(int k,int v){
        key=new node;
        key->data=k;
        value=new node;
        value->data=v;
        key->next=value;
        value->next=nullptr;
    }
};
class Hashmap{
private:
    Hashentry **table;
public:
    Hashmap(){
        table=new Hashentry*[tablesize];
        for(int i=0;i<tablesize;++i)
            table[i]=nullptr;
    }
    int hashfunction(int key){
        return key%tablesize;
    }
    void insert(int key,int value){
        int hash=hashfunction(key);
        while(table[hash]!=nullptr && (table[hash]->key)->data!=key)
            hash=hashfunction(hash+1);
        if(table[hash]!=nullptr){
            node* loc;
            loc=(table[hash]->key)->next;
            while(loc){
                if(loc->data==value)
                    return;
                loc=loc->next;
            }
            node* p=new node;
            p->data=value;
            p->next=(table[hash]->key)->next;
            (table[hash]->key)->next=p;
        }
        else
            table[hash]=new Hashentry(key,value);
    }
    int search(int key){
        int hash=hashfunction(key);
        while(table[hash]!=nullptr && (table[hash]->key)->data!=key)
            hash=hashfunction(hash+1);
        if(table[hash]==nullptr)
            return -1;
        node* loc;
        loc=(table[hash]->key)->next;
        while(loc){
            cout<<loc->data<<" ";
            loc=loc->next;
        }
        return 0;
    }
    void remove(int key){
        int hash=hashfunction(key);
        while(table[hash]!=nullptr && (table[hash]->key)->data!=key)
            hash=hashfunction(hash+1);
        if(table[hash]==nullptr)
            return;
        node* loc;
        loc=(table[hash]->key)->next;
        while(loc){
            (table[hash]->key)->next=((table[hash]->key)->next)->next;
            delete loc;
            loc=(table[hash]->key)->next;
        }
        delete table[hash]->key;
    }
    void deleteHashmap(){
        for(int i=0;i<tablesize;i++){
            if(table[i]==nullptr){
                delete table[i];
                continue;
            }
            node* loc;
            loc=(table[i]->key)->next;
            while(loc){
                (table[i]->key)->next=((table[i]->key)->next)->next;
                cout<<"Deleting Value "<<loc->data<<" At key "<<(table[i]->key)->data<<endl;
                delete loc;
                loc=(table[i]->key)->next;
            }
            cout<<"Deleting Key "<<(table[i]->key)->data<<endl;
            delete table[i]->key;
            delete [] table[i];
            table[i]=nullptr;
        }
        delete [] table;
    }
    ~Hashmap(){}
};
int main()
{
    Hashmap hash;
    int key, value;
    int choice;
    while (1)
    {
        cout<<"\n----------------------"<<endl;
        cout<<"Operations on Hash Table"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Insert element into the table"<<endl;
        cout<<"2.Search element from the key"<<endl;
        cout<<"3.Delete element at a key"<<endl;
        cout<<"4.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter element to be inserted: ";
            cin>>value;
            cout<<"Enter key at which element to be inserted: ";
            cin>>key;
            hash.insert(key, value);
            break;
        case 2:
            cout<<"Enter key of the element to be searched: ";
            cin>>key;
            if (hash.search(key) == -1)
            {
            cout<<"No element found at key "<<key<<endl;
            continue;
        }
        else
        {
            cout<<"Element at key "<<key<<" : ";
            hash.search(key);
        }
            break;
        case 3:
            cout<<"Enter key of the element to be deleted: ";
            cin>>key;
            hash.remove(key);
            break;
        case 4:
            hash.deleteHashmap();
            return 0;
        default:
           cout<<"\nEnter correct option\n";
       }
    }
    return 0;
}