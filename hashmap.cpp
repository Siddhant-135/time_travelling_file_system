#include<vector>
#include<utility>
#include <string>
#include "header.hpp"
using namespace std;
//======================================
//======================================

size_t hashstr(const string& s) //djb2 hash
{
    size_t hash = 5381;
    for (unsigned char c : s)
    {
        hash = ((hash<<5) + hash) + c;
    }
    return hash;
}
int hashint(int n)
{
    return n;
}

//======================================
//======================================
hashmap_f::hashmap_f()
{
    capacity = 31;
    hashmap.resize(capacity);
}
void hashmap_f::insert(const string& name, tree* pointer)
{
    int key = hashstr(name) % capacity;
    hashmap[key].emplace_back(name,pointer);
}
tree* hashmap_f::getfile(const string& name) const
{
    int key = hashstr(name) % capacity;
    const auto &temp = hashmap[key];
    for (const auto& p : temp)
    {
        if (p.first == name)
        {
            return p.second;
        }
    }
    return nullptr;
}

//======================================
//======================================
hashmap_v::hashmap_v()
{
    capacity = 31;
    hashmap.resize(capacity);
}
void hashmap_v::insert(const int& ID, node* pointer)
{
    int key = hashint(ID) % capacity;
    hashmap[key].emplace_back(ID,pointer);
}
node* hashmap_v::getfile(const int& ID) const
{
    int key = hashint(ID) % capacity;
    const auto &temp = hashmap[key];
    for (const auto& p : temp)
    {
        if (p.first == ID)
        {
            return p.second;
        }
    }
    return nullptr;
}