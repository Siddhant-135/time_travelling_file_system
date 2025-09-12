#include "header.hpp"
#include <iomanip>
#include <utility>
#include <type_traits>

TreeNode::TreeNode(int id, const string& content, TreeNode* par) 
    : version_id(id), content(content), parent(par), snapshot_timestamp(0), 
      is_snapshot(false) {
    created_timestamp = time(nullptr);
}

TreeNode::~TreeNode() {
    for (TreeNode* child : children) {
        delete child;
    }
}

template<typename K, typename V>
int HashMap<K, V>::hash(const K& key) {
    // integers
    if constexpr (std::is_same_v<K, int>) {
        unsigned int hash_val = static_cast<unsigned int>(key);
        hash_val = hash_val * 2654435761u; 
        return hash_val % capacity;
    }
    // strings
    else if constexpr (std::is_same_v<K, std::string>) {
        unsigned int hash_val = 5381; 
        for (char c : key) {
            hash_val = ((hash_val << 5) + hash_val) + static_cast<unsigned char>(c);
        }
        return hash_val % capacity;
    }
    // others
    else {
        unsigned int hash_val = 0;
        const unsigned char* data = reinterpret_cast<const unsigned char*>(&key);
        for (size_t i = 0; i < sizeof(K); ++i) {
            hash_val = hash_val * 31 + data[i];
        }
        return hash_val % capacity;
    }
}

template<typename K, typename V>
HashMap<K, V>::HashMap(int init_capacity) : capacity(init_capacity), size(0) {
    buckets = new HashNode*[capacity];
    for (int i = 0; i < capacity; i++) {
        buckets[i] = nullptr;
    }
}

template<typename K, typename V>
HashMap<K, V>::~HashMap() {
    for (int i = 0; i < capacity; i++) {
        HashNode* current = buckets[i];
        while (current) {
            HashNode* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] buckets;
}

template<typename K, typename V>
void HashMap<K, V>::rehash() {
    int old_capacity = capacity;
    HashNode** old_buckets = buckets;
    
    capacity *= 2;
    size = 0;
    buckets = new HashNode*[capacity];
    for (int i = 0; i < capacity; i++) {
        buckets[i] = nullptr;
    }
    
    for (int i = 0; i < old_capacity; i++) {
        HashNode* current = old_buckets[i];
        while (current) {
            insert(current->key, current->value);
            HashNode* next = current->next;
            delete current;
            current = next;
        }
    }
    
    delete[] old_buckets;
}


template<typename K, typename V>
void HashMap<K, V>::insert(const K& key, const V& value) {
    if (size >= capacity * 0.75) {
        rehash();
    }
    
    int index = hash(key);
    HashNode* current = buckets[index];
    
    while (current) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    
    HashNode* newNode = new HashNode(key, value);
    newNode->next = buckets[index];
    buckets[index] = newNode;
    size++;
}

template<typename K, typename V>
V* HashMap<K, V>::find(const K& key) {
    int index = hash(key);
    HashNode* current = buckets[index];
    
    while (current) {
        if (current->key == key) {
            return &(current->value);
        }
        current = current->next;
    }
    
    return nullptr;
}

template<typename K, typename V>
bool HashMap<K, V>::contains(const K& key) {
    return find(key) != nullptr;
}

template<typename K, typename V>
void HashMap<K, V>::remove(const K& key) {
    int index = hash(key);
    HashNode* current = buckets[index];
    HashNode* prev = nullptr;
    
    while (current) {
        if (current->key== key) {
            if (prev) {
                prev->next= current->next;
            } else {
                buckets[index]= current->next;
            }
            delete current;
            size--;
            return;
        }
        prev= current;
        current= current->next;
    }
}

template<typename T>
MaxHeap<T>::MaxHeap() {}

template<typename T>
void MaxHeap<T>::heapifyUp(int index) {
    while (index > 0 && heap[index] > heap[parent(index)]) {
        swap(heap[index], heap[parent(index)]);
        index = parent(index);
    }
}

template<typename T>
void MaxHeap<T>::heapifyDown(int index) {
    int largest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (left < static_cast<int>(heap.size()) && heap[left] > heap[largest]) {
        largest = left;
    }
    
    if (right < static_cast<int>(heap.size()) && heap[right] > heap[largest]) {
        largest = right;
    }
    
    if (largest != index) {
        swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

template<typename T>
void MaxHeap<T>::insert(const T& element) {
    heap.push_back(element);
    heapifyUp(heap.size() - 1);
}

template<typename T>
T MaxHeap<T>::extractMax() {
    if (heap.empty()) {
        throw runtime_error("Heap is empty");
    }
    
    T max_val = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    
    if (!heap.empty()) {
        heapifyDown(0);
    }
    
    return max_val;
}

template<typename T>
T MaxHeap<T>::getMax() {
    if (heap.empty()) {
        throw runtime_error("Heap is empty");
    }
    return heap[0];
}

template<typename T>
MinHeap<T>::MinHeap() {}

template<typename T>
void MinHeap<T>::heapifyUp(int index) {
    while (index > 0 && heap[index] < heap[parent(index)]) {
        swap(heap[index], heap[parent(index)]);
        index = parent(index);
    }
}

template<typename T>
void MinHeap<T>::heapifyDown(int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (left < heap.size() && heap[left] < heap[smallest]) {
        smallest = left;
    }
    
    if (right < heap.size() && heap[right] < heap[smallest]) {
        smallest = right;
    }
    
    if (smallest != index) {
        swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

template<typename T>
void MinHeap<T>::insert(const T& element) {
    heap.push_back(element);
    heapifyUp(heap.size() - 1);
}

template<typename T>
T MinHeap<T>::extractMin() {
    if (heap.empty()) {
        throw runtime_error("Heap is empty");
    }
    
    T min_val = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    
    if (!heap.empty()) {
        heapifyDown(0);
    }
    
    return min_val;
}

template<typename T>
T MinHeap<T>::getMin() {
    if (heap.empty()) {
        throw runtime_error("Heap is empty");
    }
    return heap[0];
}

Recency::Recency(const string& name, time_t modified)
    : filename(name), last_modified(modified) {}

Biggery::Biggery(const string& name, int versions)
    : filename(name), total_versions(versions) {}

bool operator<(const Recency& a, const Recency& b) {
    return a.last_modified < b.last_modified;
}

bool operator>(const Recency& a, const Recency& b) {
    return a.last_modified > b.last_modified;
}

bool operator<(const Biggery& a, const Biggery& b) {
    return a.total_versions < b.total_versions;
}

bool operator>(const Biggery& a, const Biggery& b) {
    return a.total_versions > b.total_versions;
}

File::File(const string& name) : total_versions(1), filename(name) {
    root = new TreeNode(0, "", nullptr);
    root->is_snapshot = true;
    root->message = "Initial snapshot";
    root->snapshot_timestamp = time(nullptr);
    active_version = root;
    version_map.insert(0, root);
    last_modified = time(nullptr);
}

File::~File() {
    delete root;
}

TreeNode* File::createNewVersion(const string& content) {
    TreeNode* new_version = new TreeNode(total_versions, content, active_version);
    active_version->children.push_back(new_version);
    version_map.insert(total_versions, new_version);
    active_version = new_version;
    total_versions++;
    last_modified = time(nullptr);
    return new_version;
}

void File::insert(const string& content) {
    if (active_version->is_snapshot) {
        // Create new version when active version is a snapshot
        createNewVersion(active_version->content + content);
    } else {
        // In-place modification when active version is not a snapshot
        active_version->content += content;
        last_modified = time(nullptr);
    }
}

void File::update(const string& content) {
    if (active_version->is_snapshot) {
        // Create new version when active version is a snapshot
        createNewVersion(content);
    } else {
        // In-place modification when active version is not a snapshot
        active_version->content = content;
        last_modified = time(nullptr);
    }
}

void File::snapshot(const string& message) {
    // Check if already a snapshot
    if (active_version->is_snapshot) {
        cout << "its already a snapshot" << endl;
        return;
    }
    
    active_version->is_snapshot = true;
    active_version->message = message;
    active_version->snapshot_timestamp = time(nullptr);
    // Do NOT update last_modified - snapshotting is not a file modification
    
    cout << "Snapshot created: Version " << active_version->version_id << " at ";
    cout << put_time(localtime(&active_version->snapshot_timestamp), "%Y-%m-%d %H:%M:%S") << endl;
}

bool File::rollback(int version_id, string& error_msg) {
    if (version_id == -1) {
        if (active_version->parent) {
            active_version = active_version->parent;
            return true;
        } else {
            error_msg = "Error: Cannot rollback from root version (version 0)";
            return false;
        }
    }
    
    if (version_id < 0 || version_id >= total_versions) {
        error_msg = "Error: Version ID " + to_string(version_id) + " is out of bounds (valid range: 0-" + to_string(total_versions-1) + ")";
        return false;
    }
    
    TreeNode** target_version = version_map.find(version_id);
    if (target_version && *target_version) {
        active_version = *target_version;
        return true;
    } else {
        error_msg = "Error: Version " + to_string(version_id) + " not found";
        return false;
    }
}

bool File::rollback(int version_id) {
    string dummy_msg;
    return rollback(version_id, dummy_msg);
}

string File::read() const {
    return active_version->content;
}

void File::history() const {
    vector<TreeNode*> versions;
    TreeNode* current = active_version;
    
    while (current) {
        // Only include snapshotted versions as per clarification
        if (current->is_snapshot) {
            versions.push_back(current);
        }
        current = current->parent;
    }
    
    for (auto it = versions.rbegin(); it != versions.rend(); ++it) {
        TreeNode* node = *it;
        cout << "Version " << node->version_id << ": ";
        // Show snapshot timestamp for snapshotted versions
        cout << put_time(localtime(&node->snapshot_timestamp), "%Y-%m-%d %H:%M:%S");
        cout << " [SNAPSHOT] - " << node->message;
        cout << endl;
    }
}

FileSystem::FileSystem() {}

FileSystem::~FileSystem() {
    // Clean up all File objects to prevent memory leaks
    for (const string& filename : file_keys) {
        File** file = files.find(filename);
        if (file && *file) {
            delete *file;
        }
    }
}

bool FileSystem::isValidFilename(const string& filename) {
    if (filename.empty()) return false;
    
    // Check for whitespace
    for (char c : filename) {
        if (isspace(c)) {
            return false;
        }
    }
    return true;
}

bool FileSystem::isValidVersionId(const string& version_str, int& version_id) {
    if (version_str.empty()) return false;
    
    // Check if all characters are digits (except possible leading minus)
    bool is_negative = version_str[0] == '-';
    size_t start = is_negative ? 1 : 0;
    
    if (start >= version_str.length()) return false;
    
    for (size_t i = start; i < version_str.length(); i++) {
        if (!isdigit(version_str[i])) {
            return false;
        }
    }
    
    try {
        version_id = stoi(version_str);
        return true;
    } catch (...) {
        return false;
    }
}

int FileSystem::countTieBreaking(const vector<pair<time_t, string>>& entries, time_t tie_value) {
    int count = 0;
    for (const auto& entry : entries) {
        if (entry.first == tie_value) count++;
    }
    return count;
}

int FileSystem::countTieBreaking(const vector<pair<int, string>>& entries, int tie_value) {
    int count = 0;
    for (const auto& entry : entries) {
        if (entry.first == tie_value) count++;
    }
    return count;
}

void FileSystem::updateMetrics(File* /* file */) {
    // Metrics are calculated dynamically for optimal performance
}

void FileSystem::createFile(const string& filename) {
    if (!isValidFilename(filename)) {
        cout << "Error: Invalid filename '" << filename << "'. Filenames cannot contain whitespace." << endl;
        return;
    }
    
    if (files.contains(filename)) {
        cout << "Error: File '" << filename << "' already exists" << endl;
        return;
    }
    
    File* new_file = new File(filename);
    files.insert(filename, new_file);
    file_keys.push_back(filename);
    updateMetrics(new_file);
    cout << "File '" << filename << "' created successfully" << endl;
}

void FileSystem::readFile(const string& filename) {
    if (!isValidFilename(filename)) {
        cout << "Error: Invalid filename '" << filename << "'. Filenames cannot contain whitespace." << endl;
        return;
    }
    
    File** file = files.find(filename);
    if (!file || !*file) {
        cout << "Error: File '" << filename << "' not found" << endl;
        return;
    }
    
    cout << (*file)->read() << endl;
}

void FileSystem::insert_content(const string& filename, const string& content) {
    if (!isValidFilename(filename)) {
        cout << "Error: Invalid filename '" << filename << "'. Filenames cannot contain whitespace." << endl;
        return;
    }
    
    File** file = files.find(filename);
    if (!file || !*file) {
        cout << "Error: File '" << filename << "' not found" << endl;
        return;
    }
    
    (*file)->insert(content);
    updateMetrics(*file);
}

void FileSystem::update_file(const string& filename, const string& content) {
    if (!isValidFilename(filename)) {
        cout << "Error: Invalid filename '" << filename << "'. Filenames cannot contain whitespace." << endl;
        return;
    }
    
    File** file = files.find(filename);
    if (!file || !*file) {
        cout << "Error: File '" << filename << "' not found" << endl;
        return;
    }
    
    (*file)->update(content);
    updateMetrics(*file);
}

void FileSystem::snapshot_file(const string& filename, const string& message) {
    if (!isValidFilename(filename)) {
        cout << "Error: Invalid filename '" << filename << "'. Filenames cannot contain whitespace." << endl;
        return;
    }
    
    File** file = files.find(filename);
    if (!file || !*file) {
        cout << "Error: File '" << filename << "' not found" << endl;
        return;
    }
    
    (*file)->snapshot(message);
    updateMetrics(*file);
}

void FileSystem::rollback_file(const string& filename, int version_id) {
    File** file = files.find(filename);
    if (!file || !*file) {
        cout << "Error: File '" << filename << "' not found" << endl;
        return;
    }
    
    string error_msg;
    if ((*file)->rollback(version_id, error_msg)) {
        cout << "Rollback completed for '" << filename << "'" << endl;
    } else {
        cout << error_msg << endl;
    }
}

void FileSystem::rollback_file(const string& filename, const string& version_str) {
    File** file = files.find(filename);
    if (!file || !*file) {
        cout << "Error: File '" << filename << "' not found" << endl;
        return;
    }
    
    int version_id;
    if (!isValidVersionId(version_str, version_id)) {
        cout << "Error: Invalid version ID format '" << version_str << "'. Please provide a valid number." << endl;
        return;
    }
    
    string error_msg;
    if ((*file)->rollback(version_id, error_msg)) {
        cout << "Rollback completed for '" << filename << "'" << endl;
    } else {
        cout << error_msg << endl;
    }
}

void FileSystem::fileHistory(const string& filename) {
    if (!isValidFilename(filename)) {
        cout << "Error: Invalid filename '" << filename << "'. Filenames cannot contain whitespace." << endl;
        return;
    }
    
    File** file = files.find(filename);
    if (!file || !*file) {
        cout << "Error: File '" << filename << "' not found" << endl;
        return;
    }
    
    cout << "History for '" << filename << "':" << endl;
    (*file)->history();
}

void FileSystem::recentFiles(int num) {
    if (num <= 0) {
        cout << "Error: Number of files must be positive" << endl;
        return;
    }
    
    if (file_keys.empty()) {
        cout << "No files exist in the system" << endl;
        return;
    }
    
    MaxHeap<pair<time_t, string>> heap;
    
    // Insert all files into max heap with modification times (O(n log n))
    for (const string& filename : file_keys) {
        File** file = files.find(filename);
        if (file && *file) {
            heap.insert(make_pair((*file)->getLastModified(), filename));
        }
    }
    
    int total_files = heap.size();
    int display_count = min(num, total_files);
    
    // Extract top k elements from heap (O(k log n))
    vector<pair<time_t, string>> top_files;
    for (int i = 0; i < display_count && heap.size() > 0; i++) {
        top_files.push_back(heap.extractMax());
    }
    
    // Sort extracted elements for tie-breaking (only k elements, so O(k log k))
    sort(top_files.begin(), top_files.end(), [](const pair<time_t, string>& a, const pair<time_t, string>& b) {
        if (a.first != b.first) return a.first > b.first; // More recent first
        return a.second < b.second; // Alphabetical for ties
    });
    
    cout << "Recent Files:" << endl;
    for (int i = 0; i < display_count; i++) {
        cout << top_files[i].second << " - ";
        cout << put_time(localtime(&top_files[i].first), "%Y-%m-%d %H:%M:%S") << endl;
    }
    
    if (num > total_files) {
        cout << "Displayed " << total_files << " files. No more files available." << endl;
    } else if (display_count > 0 && display_count < total_files) {
        // Check for ties at the boundary
        time_t boundary_time = top_files[display_count - 1].first;
        int tied_files = countTieBreaking(top_files, boundary_time);
        if (tied_files > 1) {
            cout << "Tie broken alphabetically among " << tied_files << " files for the last spot" << endl;
        }
    }
}

void FileSystem::biggestTrees(int num) {
    if (num <= 0) {
        cout << "Error: Number of files must be positive" << endl;
        return;
    }
    
    if (file_keys.empty()) {
        cout << "No files exist in the system" << endl;
        return;
    }
    
    MaxHeap<pair<int, string>> heap;
    
    // Insert all files into max heap with version counts (O(n log n))
    for (const string& filename : file_keys) {
        File** file = files.find(filename);
        if (file && *file) {
            heap.insert(make_pair((*file)->getTotalVersions(), filename));
        }
    }
    
    int total_files = heap.size();
    int display_count = min(num, total_files);
    
    // Extract top k elements from heap (O(k log n))
    vector<pair<int, string>> top_files;
    for (int i = 0; i < display_count && heap.size() > 0; i++) {
        top_files.push_back(heap.extractMax());
    }
    
    // Sort extracted elements for tie-breaking (only k elements, so O(k log k))
    sort(top_files.begin(), top_files.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
        if (a.first != b.first) return a.first > b.first; // More versions first
        return a.second < b.second; // Alphabetical for ties
    });
    
    cout << "Biggest Trees:" << endl;
    for (int i = 0; i < display_count; i++) {
        cout << top_files[i].second << " - " << top_files[i].first << " versions" << endl;
    }
    
    if (num > total_files) {
        cout << "Displayed " << total_files << " files. No more files available." << endl;
    } else if (display_count > 0 && display_count < total_files) {
        // Check for ties at the boundary
        int boundary_size = top_files[display_count - 1].first;
        int tied_files = countTieBreaking(top_files, boundary_size);
        if (tied_files > 1) {
            cout << "Tie broken alphabetically among " << tied_files << " files for the last spot" << endl;
        }
    }
}

void FileSystem::mainstuff(const string& command) {
    if (command.empty()) {
        return;
    }
    
    istringstream iss(command);
    string cmd;
    iss >> cmd;
    
    // Convert to uppercase for comparison
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
    
    if (cmd == "CREATE") {
        string filename;
        iss >> filename;
        if (filename.empty()) {
            cout << "Error: CREATE requires a filename" << endl;
            return;
        }
        createFile(filename);
    } else if (cmd == "READ") {
        string filename;
        iss >> filename;
        if (filename.empty()) {
            cout << "Error: READ requires a filename" << endl;
            return;
        }
        readFile(filename);
    } else if (cmd == "INSERT") {
        string filename, content;
        iss >> filename;
        if (filename.empty()) {
            cout << "Error: INSERT requires a filename" << endl;
            return;
        }
        getline(iss, content);
        if (!content.empty() && content[0] == ' ') content = content.substr(1);
        insert_content(filename, content);
    } else if (cmd == "UPDATE") {
        string filename, content;
        iss >> filename;
        if (filename.empty()) {
            cout << "Error: UPDATE requires a filename" << endl;
            return;
        }
        getline(iss, content);
        if (!content.empty() && content[0] == ' ') content = content.substr(1);
        update_file(filename, content);


    } else if (cmd == "SNAPSHOT") {
        string filename, message;
        iss >> filename;
        if (filename.empty()) {
            cout << "Error: SNAPSHOT requires a filename" << endl;
            return;
        }
        getline(iss, message);
        if (!message.empty() && message[0] == ' ') message = message.substr(1);
        if (message.empty()) {
            cout << "Error: SNAPSHOT recommends adding a message" << endl;
            return;
        }
        snapshot_file(filename, message);
    } else if (cmd == "ROLLBACK") {
        string filename, version_str;
        iss >> filename;
        if (filename.empty()) {
            cout << "Error: ROLLBACK requires a filename" << endl;
            return;
        }
        
        string remaining;
        getline(iss, remaining);
        if (!remaining.empty() && remaining[0] == ' ') remaining = remaining.substr(1);
        
        if (remaining.empty()) {
            rollback_file(filename, -1);
        } else {
            rollback_file(filename, remaining);
        }
    } else if (cmd == "HISTORY") {
        string filename;
        iss >> filename;
        if (filename.empty()) {
            cout << "Error: HISTORY command requires a filename" << endl;
            return;
        }
        fileHistory(filename);


    } else if (cmd == "RECENT_FILES") {
        string num_str;
        iss >> num_str;

        if(num_str.empty()){
            cout <<"Error: RECENT_FILES requires a positive integer arguement" << endl;
            return;
        }
        int parsed_num;
        if (!num_str.empty()) {
            if (!isValidVersionId(num_str, parsed_num) || parsed_num <= 0) {
                cout << "Error: Invalid number '" << num_str << "' for RECENT_FILES" << endl;
                return;
            }
        }
        recentFiles(parsed_num);
    } else if (cmd == "BIGGEST_TREES") {
        string num_str;
        iss >> num_str;

        if(num_str.empty()){
            cout <<"Error: BIGGEST_TREES requires a positive integer arguement" << endl;
            return;
        }
        int parsed_num;
        if (!num_str.empty()) {

            if (!isValidVersionId(num_str, parsed_num) || parsed_num <= 0) {
                cout << "Error: Invalid number '" << num_str << "' for BIGGEST_TREES" << endl;
                return;
            }
        }
        biggestTrees(parsed_num);




    } else if (cmd.empty()) {
        return;
    } else {
        cout << "Error: Unknown command '" << cmd << "'" << endl;
        cout << "Available commands: CREATE, READ, INSERT, UPDATE, SNAPSHOT, ROLLBACK, HISTORY, RECENT_FILES, BIGGEST_TREES" << endl;
    }
}




template class HashMap<int, TreeNode*>;
template class HashMap<string, File*>;
template class MaxHeap<pair<time_t, string>>;
template class MaxHeap<pair<int, string>>;