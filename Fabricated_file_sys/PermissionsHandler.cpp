//
// Author: Akshith Gara
//
#include "PermissionHandler.h"

PermissionHandler::PermissionHandler() : stringOrder{OWNER, GROUP, ALL}, permString{"r", "w", "x"}
{
    //initialize the PermissionHandler to all be false
    for(int m = 0; m < NUM_MODES; ++m)
    {
        for(int p = 0; p < NUM_PERM; ++p)
        {
            perm[m][p] = 0;
        }
    }
    mask[READ] = 0b100;
    mask[WRITE] = 0b010;
    mask[EXE] = 0b001;
}
//Function that returns a permission string
string PermissionHandler::getPermString() const
{
    string ps;

    //walk through our PermissionHandler, outputting either the associated string (if true) or a '-' if false
    for(int m = 0; m < NUM_MODES; ++m)
    {
        for(int p = 0; p < NUM_PERM; ++p)
        {
            if(perm[stringOrder[m]][p])
            {
                ps += permString[p];
            }
            else
            {
                ps += "-";
            }
        }
    }

    return ps;
}
//Function to check if the permission digit is valid
bool PermissionHandler::validPermissionDigit(const char d)
{
    //to make sure the permission characters are valid
    switch(d)
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
            return true;
    }
    return false;
}

//Function to update the permission string
void PermissionHandler::updatePerm(const string& numStr)
{
    if(numStr.length() != NUM_MODES)
    {
        ErrorHandler er;
        er.errMsg = "Invalid permission string: (\"" + numStr + "\")";

        throw(er);
    }

    string digitString;
    int digit;

    //our string is 3 digits, one for each permission group.
    for(int m = 0; m < NUM_MODES; ++m)
    {
        //error check
        if(!validPermissionDigit(numStr[m]))
        {
            ErrorHandler er;
            er.errMsg = "All digits in permission number must be between 0 and 7";

            throw(er);
        }

        //get the numeric version of the digit
        digitString = numStr[m];
        digit = stoi(digitString);

        //Using bitmasks to check if the permission should be set
        for(int p = 0; p < NUM_PERM; ++p)
        {
            if(digit & mask[p])
            {
                perm[m][p] = true;
            }
            else
            {
                perm[m][p] = false;
            }
        }
    }
}

PermissionHandler& PermissionHandler::operator=(const PermissionHandler& permObj)
{
    for(int m = 0; m < NUM_MODES; ++m)
    {
        for(int p = 0; p < NUM_PERM; ++p)
        {
            this->perm[m][p] = permObj.perm[m][p];
        }
    }

    return *this;
}