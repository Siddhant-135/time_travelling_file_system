#include "header.hpp"

int main() {
    FileSystem fs;
    string command;
    
    cout << "Your time travelling file system is here" << endl;
    cout << "Available commands: CREATE, READ, INSERT, UPDATE, SNAPSHOT, ROLLBACK, HISTORY, RECENT_FILES, BIGGEST_TREES" << endl;
    cout << "Type 'exit' to quit" << endl;
    
    while (getline(cin, command)) {
        if (command == "exit" || command == "EXIT") {
            break;
        }
        
        if (!command.empty()) {
            fs.mainstuff(command);
        }
    }
    return 0;
}