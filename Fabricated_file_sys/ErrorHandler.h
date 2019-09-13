//
// Author: Akshith Gara
//
#ifndef FABRICATED_FILE_SYS_ERRORHANDLER_H
#define FABRICATED_FILE_SYS_ERRORHANDLER_H

#include <string>

using namespace std;

//An error struct to handle errors
struct ErrorHandler
{
    ErrorHandler() : error(false) {}

    string errMsg;
    bool error;
};


#endif
