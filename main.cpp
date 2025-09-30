// main.cpp
#include <iostream>
#include <sstream>
#include <string>
#include "header.hpp"
using namespace std;
//======================================
int main()
{
    cout << "why fear, time travelling file system is here !" << endl;
    cout << "you have commands CREATE, READ, UPDATE, INSERT, SNAPSHOT, ROLLBACK, HISTORY at your becking" << endl;
    cout << "press EXIT to end. dont do bakchodi or this will stop working" << endl;
    filesys fs;
    string command;

    while (getline(cin, command))
    {
        istringstream iss(command);
        string cmd;
        iss >> cmd;

        if(cmd == "EXIT")
        {
            break;
        }
        else if (cmd == "CREATE")
        {
            string name;
            iss >> name;
            fs.create(name);
        }
        else if (cmd == "READ")
        {
            string name;
            iss>>name;
            fs.read(name);
        }
        else if(cmd == "INSERT")
        {
            string name;
            string content;
            iss >> name;
            getline(iss, content);
            fs.insert(name, content);
        }
        else if(cmd == "UPDATE")
        {
            string name;
            string content;
            iss >> name;
            getline(iss, content);
            fs.update(name, content);
        }
        else if(cmd == "SNAPSHOT")
        {
            string name;
            string message;
            iss >> name;
            getline(iss, message);
            fs.snapshot(name, message);
        }
        else if (cmd == "HISTORY")
        {
            string name;
            iss>>name;
            fs.history(name);
        }
        else if(cmd == "ROLLBACK")
        {
            string name;
            iss >> name;
            string ID = "";
            iss >> ID;
            if (ID.empty()) { ID = "-1"; }
            int id = stoi(ID);
            fs.rollback(name, id);
        }
        else if(cmd == "BIGGEST_TREES")
        {
            string num;
            iss >> num;
            if(num.empty()){cout<<"enter number"<<endl;}
            else
            {
                int num2 = stoi(num);
                fs.big(num2);
            }
        }
        else if(cmd == "RECENT_FILES")
        {
            string num;
            iss >> num;
            if(num.empty()){cout<<"enter number"<<endl;}
            else
            {
                int num2 = stoi(num);
                fs.rec(num2);
            }
        }
    }
    return 0;
}