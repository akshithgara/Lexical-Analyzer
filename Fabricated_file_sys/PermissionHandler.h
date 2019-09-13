//
// Author: Akshith Gara
//
#ifndef PERMISSIONHANDLER_H
#define PERMISSIONHANDLER_H

#include<vector>
#include<string>

#include "ErrorHandler.h"

using namespace std;

//File and Directory PermissionHandler
class PermissionHandler
{
    public:
        PermissionHandler();

        //updates the permissions for an object
        void updatePerm(const string& numStr);

        //returns a permission string
        string getPermString() const;
        
        PermissionHandler& operator=(const PermissionHandler& permObj);

    private:
        bool validPermissionDigit(const char d);

        //constants 
        enum ModeIdx
        {
            ALL = 0,
            GROUP = 1,
            OWNER,
            NUM_MODES
        };
        //constants for the permission indices
        enum PermIdx
        {
            READ = 0,
            WRITE = 1,
            EXE,
            NUM_PERM
        };

        //strings associated with each permission
        const string permString[NUM_PERM];
        //the order permission groups should be displayed
        const ModeIdx stringOrder[NUM_MODES];
        //the PermissionHandler themselves
        bool perm[NUM_MODES][NUM_PERM];

        int mask[NUM_PERM];
};

#endif