#include <iostream>
#include "header.hpp"
#include <vector>
#include <string>
#include <utility>
#include <ctime>
using namespace std;

//====================================
bool tree::handlesnap()
{
    bool flag = false;
    if(active->snapshot.first == true)
    {
        flag = true;
        node* temp = new node;
        active->children.push_back(temp);
        temp->parent = active;
        vcount+=1;
        temp->ID = vcount;
        temp->content = active->content;
        vmap->insert(vcount, temp);
        active = temp;
    }
    return flag;
}

void tree::delete_subt(node* n)
{
    if (n)
    {
        for (node* c : n->children)
        {
            delete_subt(c);
        }
        delete n;
    }
    return;
}
//====================================
tree::tree(std::string filename)
{
    root = new node();
    root->ID = 0;
    active = root;
    snap("This is the initial snapshot");
    vmap = new hashmap_v(); 
    vmap->insert(0,root);
    this->filename = filename;
    ltime = chrono::system_clock::now();
    vcount = 0;
}

tree::~tree()
{
    delete_subt(root);
    delete vmap; 
}

//====================================
void tree::snap(const string& message)
{
    active->snapshot.first = true;
    active->snapshot.second = message;
    ltime = chrono::system_clock::now();
    active->snapshot_t = ltime;
}

void tree::read() const
{
    string msg = active->content;
    cout << msg << endl;
}

bool tree::insert(string content)
{
    bool temp = handlesnap();
    ltime = chrono::system_clock::now();
    active->content += content;
    return temp;
}

bool tree::update(string content)
{
    bool temp = handlesnap();
    ltime = chrono::system_clock::now();
    active->content = content;
    return temp;
}

void tree::rollback(int id)
{
    if(id == -1){active = active->parent; return;}
    node* pointer = vmap->getfile(id);
    if(pointer == nullptr){return;}
    else{active = pointer;}
}

void tree::history() const
{
    node* temp = active;
    while(temp != nullptr)
    {
        if(temp->snapshot.first == true)
        {
            cout << "ID: " << temp->ID << " message: " << temp->snapshot.second << "time: " << printer(temp->snapshot_t) << endl;
        }
        temp = temp->parent;
    }
}