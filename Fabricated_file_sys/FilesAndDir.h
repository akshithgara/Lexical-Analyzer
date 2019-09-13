//
// Author: Akshith Gara
//
#ifndef FABRICATED_FILE_SYS_DIRECTORY_H
#define FABRICATED_FILE_SYS_DIRECTORY_H

#include"PermissionHandler.h"


#include <string>
#include <vector>

using namespace std;
struct Info
{
    //Initializing info in the constructor
    Info() : ownerGroup("root_group"), owner("root")
    {
        perm.updatePerm("007");
        isDir = false;
        time(&modTime);

    }
    ~Info() {}

    string name;
    PermissionHandler perm;
    time_t modTime;
    string ownerGroup;
    string owner;
    bool isDir;


    Info& operator=(const Info& a);
};

struct File{

    File()
    {
        info.isDir = false;
    }

    ~File(){};

    Info info;
};

struct Directory{

    Directory()
    {
        info.isDir = true;
        parentDir = 0;
    }

    ~Directory(){};
    Directory* parentDir;
    vector<Directory> subDirectories;
    vector<File> files;

    Info info;
    Directory& operator=(const Directory& d);

};
//Function to get elaborate information when the command ls -l is used
string getInfo(const Info& a);

#endif