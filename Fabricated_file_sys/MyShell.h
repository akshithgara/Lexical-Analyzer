//
// Author: Akshith Gara
//

#ifndef FABRICATED_FILE_SYS_MYSHELL_H
#define FABRICATED_FILE_SYS_MYSHELL_H

#include<iostream>
#include<string>
#include<vector>
#include<ctime>

#include "FilesAndDir.h"

using namespace std;

class MyShell
{
public:
    //Constructor
    MyShell();
    string welcomeText();
    string shellPrompt();

    void execute(const string& command);

    bool exit() {return exitToggle;};

private:

    Directory rootDir;
    Directory* workingDir;

    bool exitToggle;

private:
    void parse(string command, vector<string>& parsedCmd);

    string getWorkingDir();
    string getWorkingDir_helper(Directory* d);

    void ls(const vector<string>& parsedCmd);
    void cd(const vector<string>& parsedCmd);
    void rm(const vector<string>& parsedCmd);
    void touch(const vector<string>& parsedCmd);
    void mkdir(const vector<string>& parsedCmd);
    void rmdir(const vector<string>& parsedCmd);
    void chmod(const vector<string>& parsedCmd);


};




#endif
