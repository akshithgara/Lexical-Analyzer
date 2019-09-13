//
// Author: Akshith Gara
//
#include<iostream>

#include "MyShell.h"

using namespace std;

int main()
{
    MyShell shell;
    bool errorCaught = false;
    string command;

    cout  << shell.welcomeText()<< "\n";

    do
    {
        try {
            cout << shell.shellPrompt();
            getline(cin, command);
            shell.execute(command);
        }
        catch(ErrorHandler er)
        {
            cout << "\nERROR:\n" << er.errMsg << "\n\n";
            errorCaught = er.error;
        }
    }while(!errorCaught && !shell.exit());

    return 0;
}