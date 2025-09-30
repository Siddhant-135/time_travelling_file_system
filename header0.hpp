#pragma once
#include <vector>
#include <string>
#include <utility>
#include <chrono> // Added this include
using namespace std;
//======================================
struct node
{
    node* parent;
    vector<node*> children;
    string content;
    int ID;
    pair<bool, string> snapshot;
    chrono::time_point<std::chrono::system_clock> snapshot_t;
    node() : parent(nullptr), children(), content(""), ID(0), snapshot(false,"") {};
};

//======================================
class hashmap_v
{
    private:
    vector<vector<std::pair<int, node*>>> hashmap;
    int capacity;

    public:
    hashmap_v(); 
    void insert(const int& ID, node* pointer); 
    node* getfile(const int& ID) const; 
};