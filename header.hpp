#pragma once
#include <vector>
#include <string>
#include <utility>
#include "header0.hpp"
#include <chrono>
using namespace std;
//======================================
struct node;

class tree
{
    private:
    node* root;
    node* active;
    hashmap_v* vmap;
    bool handlesnap();
    void delete_subt(node* n);
    public:
    std::string filename;
    int vcount;
    std::chrono::time_point<std::chrono::system_clock> ltime;
    tree(std::string filename); 
    ~tree(); 
    void snap(const std::string& message); 
    void read() const; 
    bool insert(std::string content); 
    bool update(std::string content); 
    void rollback(int id); 
    void history() const; 
};
//======================================
size_t hashstr(const string& s);
int hashint(int n);

string printer(chrono::time_point<std::chrono::system_clock> timestamp);

//======================================
//======================================
class hashmap_f
{
    private:
    vector<vector<std::pair<std::string, tree*>>> hashmap;
    int capacity;

    public:
    hashmap_f(); 
    void insert(const std::string& name, tree* pointer); 
    tree* getfile(const std::string& name) const; 
};
//======================================
class maxheap
{
    private:
    std::vector<tree*> heap;
    int capacity;
    void heap_up(int i);
    void heap_down(int i); 
    public:
    int size;
    maxheap(); 
    ~maxheap(); 
    void insert(tree* file); 
    void topk(int k); 
    tree* poptop(); 
    void heapify(); 
};
//======================================

class recheap
{
    private:
    std::vector<tree*> heap;
    int capacity;
    void heap_up(int i);
    void heap_down(int i); 
    public:
    int size;
    recheap(); 
    ~recheap(); 
    void insert(tree* file); 
    void topk(int k); 
    tree* poptop(); 
    void heapify(); 
};
//======================================
class filesys
{
    private:
    maxheap* biggest;
    hashmap_f* allfiles;
    recheap* recents;
    public:
    filesys(); 
    ~filesys();
    void create(const string& filename); 
    void read(const string& filename) const; 
    void insert(const string& filename, const string& content); 
    void update(const string& filename, const string& content); 
    void snapshot(const string& filename, const string& message); 
    void history(const string& filename); 
    void rollback(const string& filename, int ID); 
    void big(int n);
    void rec(int n);
};