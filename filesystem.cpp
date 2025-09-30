#include "header.hpp"
#include <string> 
#include <iostream>
using namespace std; 
//======================================
filesys::filesys()
{
    biggest = new maxheap();
    allfiles = new hashmap_f();
    recents = new recheap();
}

filesys::~filesys()
{
    delete biggest;
    delete allfiles;
}
//======================================

void filesys::create(const string& filename)
{
    tree* file = new tree(filename);
    allfiles->insert(filename, file);
    biggest->insert(file);
    recents->insert(file);
    return;
}
void filesys::read(const string& filename) const
{
    tree* file = allfiles->getfile(filename);
    if(file != nullptr)
    {
        file->read();
    }
    return;
}
void filesys::insert(const string& filename, const string& content)
{
    tree* file = allfiles->getfile(filename);
    bool flag = false;
    if(file != nullptr)
    {
        flag = file->insert(content);
    }
    if(flag){biggest->heapify(); recents->heapify();}
    return;
}
void filesys::update(const string& filename, const string& content)
{
    tree* file = allfiles->getfile(filename);
    bool flag = false;
    if(file != nullptr)
    {
        flag = file->update(content);
    }
    if(flag){biggest->heapify(); recents->heapify();}
    return;
}
void filesys::snapshot(const string& filename, const string& message)
{
    tree* file = allfiles->getfile(filename);
    if(file != nullptr)
    {
        file->snap(message);
        recents->heapify();
    }
    return;
}
void filesys::history(const string& filename)
{
    tree* file = allfiles->getfile(filename);
    if(file != nullptr)
    {
        file->history();
    }
    return;
}
void filesys::rollback(const string& filename, int ID)
{
    tree* file = allfiles->getfile(filename);
    if(file != nullptr)
    {
        file->rollback(ID);
    }
    return;
}

//======================================
void filesys::big(int n)
{
    if(biggest->size < n){cout << "you ask too much" << endl; return;} 
    biggest->topk(n);
    return;
}
void filesys::rec(int n)
{
    if(recents->size < n){cout << "you ask too much" << endl; return;} 
    recents->topk(n);
    return;
}