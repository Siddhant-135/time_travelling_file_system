#ifndef TIME_TRAVEL_FS_H
#define TIME_TRAVEL_FS_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

struct TreeNode {
    int version_id;
    string content;
    string message;
    time_t created_timestamp;
    TreeNode* parent;
    time_t snapshot_timestamp;
    vector<TreeNode*> children;
    bool is_snapshot;
    
    TreeNode(int id, const string& cont, TreeNode* par = nullptr);
    ~TreeNode();
};

template<typename K, typename V>
class HashMap {
private:
    struct HashNode {
        K key;
        V value;
        HashNode* next;
        
        HashNode(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };
    
    HashNode** buckets;
    int capacity;
    int size;
    
    int hash(const K& key);
    void rehash();
    
public:
    HashMap(int init_capacity = 16);
    ~HashMap();
    
    void insert(const K& key, const V& value);
    V* find(const K& key);
    bool contains(const K& key);
    void remove(const K& key);
    int getSize() const { return size; }
};

template<typename T>
class MaxHeap {
private:
    vector<T> heap;
    
    void heapifyUp(int index);
    void heapifyDown(int index);
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
public:
    MaxHeap();
    
    void insert(const T& element);
    T extractMax();
    T getMax();
    bool empty() const { return heap.empty(); }
    int size() const { return heap.size(); }
    void clear() { heap.clear(); }
};

template<typename T>
class MinHeap {
private:
    vector<T> heap;
    
    void heapifyUp(int index);
    void heapifyDown(int index);
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
public:
    MinHeap();
    
    void insert(const T& element);
    T extractMin();
    T getMin();
    bool empty() const { return heap.empty(); }
    int size() const { return heap.size(); }
    void clear() { heap.clear(); }
};

struct Recency {
    string filename;
    time_t last_modified;
    
    Recency(const string& name, time_t modified);
};

struct Biggery {
    string filename;
    int total_versions;
    
    Biggery(const string& name, int versions);
};

bool operator<(const Recency& a, const Recency& b);
bool operator>(const Recency& a, const Recency& b);
bool operator<(const Biggery& a, const Biggery& b);
bool operator>(const Biggery& a, const Biggery& b);

class File {
private:
    TreeNode* root;
    TreeNode* active_version;
    HashMap<int, TreeNode*> version_map;
    int total_versions;
    string filename;
    time_t last_modified;
    
    TreeNode* createNewVersion(const string& content);
    
public:
    File(const string& name);
    ~File();
    
    void insert(const string& content);
    void update(const string& content);
    void snapshot(const string& message);
    bool rollback(int version_id, string& error_msg);
    bool rollback(int version_id = -1);
    string read() const;
    void history() const;
    
    time_t getLastModified() const { return last_modified; }
    int getTotalVersions() const { return total_versions; }
    string getFilename() const { return filename; }
};

class FileSystem {
private:
    HashMap<string, File*> files;
    vector<string> file_keys;  // Track file names for iteration
    
    void updateMetrics(File* file);
    
public:
    FileSystem();
    ~FileSystem();
    
    void createFile(const string& filename);
    void readFile(const string& filename);
    void insert_content(const string& filename, const string& content);
    void update_file(const string& filename, const string& content);
    void snapshot_file(const string& filename, const string& message);
    void rollback_file(const string& filename, int version_id = -1);
    void rollback_file(const string& filename, const string& version_str);
    void fileHistory(const string& filename);
    void recentFiles(int num);
    void biggestTrees(int num);
    bool isValidFilename(const string& filename);
    bool isValidVersionId(const string& version_str, int& version_id);
    int countTieBreaking(const vector<pair<time_t, string>>& entries, time_t tie_value);
    int countTieBreaking(const vector<pair<int, string>>& entries, int tie_value);
    
    void mainstuff(const string& command);
};

#endif