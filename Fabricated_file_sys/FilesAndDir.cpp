//
// Author: Akshith Gara
//
#include "FilesAndDir.h"

Info& Info::operator=(const Info& a)
{
    this->modTime = a.modTime;
    this->ownerGroup = a.ownerGroup;
    this->name = a.name;
    this->owner = a.owner;
    this->perm = a.perm;

    return *this;
}

Directory& Directory::operator=(const Directory& d)
{
    this->files = d.files;
    this->subDirectories = d.subDirectories;
    this->parentDir = d.parentDir;
    this->info = d.info;


    return *this;
}
//This functions returns the detailed info of the files and directories when ls -l command is typed in
string getInfo(const Info& i)
{
    string lsl;

    //prefix for permission string of a directory starts with 'd'
    //it's '-' for others
    if(i.isDir)
    {
        lsl = "d";
    }
    else
    {
        lsl = "-";
    }
    lsl += i.perm.getPermString() + "   ";
    lsl += i.ownerGroup + "   " + i.owner + "   ";
    lsl += asctime(localtime(&i.modTime));
    lsl[lsl.length()-1] = ' ';
    lsl += "  ";

    lsl += i.name;

    return lsl;
}