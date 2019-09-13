//
// Author: Akshith Gara
//

#include"MyShell.h"


//Initializing constructor
MyShell::MyShell()
{
    //Working directory at starting point is the root directory
    workingDir = &rootDir;

    exitToggle = false;
}
//Function to print out welcome text
string MyShell::welcomeText()
{


    string welcomeText = "Welcome to Akshith Gara's C++ Shell!\n"
          "Commands:\n"
          "ls -l:\n\tLists contents of current directory with elaborate information regarding size and permissions\n\n"
          "cd <directory>:\n\tChanges current working directory to the given directory name\n\n"
          "pwd:\n\tPrints the path to the current working directory\n\n"
          "mkdir <directory>:\n\tMakes a new directory in the current working directory\n\n"
          "rmdir <directory>:\n\tRemoves a directory from the current working directory\n\n"
          "rm <file>:\n\tRemove a file from the current working directory\n\n"
          "chmod <permission string>:\n\tChange the permissions on a file or directory in the current working directory\n\n"
          "touch <file>:\n\tIf a file exists in the current working directory with the indicated name, update it's modification time, otherwise create it\n\n"
          "touch <directory>:\n\tUpdate the modification time of a directory in the current working directory\n\n"
          "exit/quit:\n\tQuit the shell\n\n";

    return welcomeText;
}

//Function to parse just the commands from the input with spaces in it
void MyShell::parse(string command, vector<string>& parsedCmd)
{
    string temp;
    int begin;
    int end;
    int len = command.length();
    //skip through all the spaces in the command
    for(begin = 0;begin<len;begin++){
        if(command[begin] != ' '){
            break;
        }
    }
    //if the the user hasn't typed anything, then return out of the function
    if(begin == len)
    {
        return;
    }
    //finding where the next space is starting from begin
    end = command.find(' ', begin);
    if(end == string::npos)   //if find returns an error
    {
        end = len;
    }

    //extracting the command substr and adding it to our parsedCmd vector
    temp = command.substr(begin, end-begin);
    parsedCmd.push_back(temp);

    //if end isn't the end of the command, recurse over the substring starting at end
    if(end != len)
    {
        temp = command.substr(end+1);
        parse(temp, parsedCmd);
    }
}

string MyShell::shellPrompt()
{
    return getWorkingDir() + "$";
}

string MyShell::getWorkingDir()
{
    return getWorkingDir_helper(workingDir) + "/";
}

//A recursive function that keeps going up until we reach the root
string MyShell::getWorkingDir_helper(Directory* d)
{
    //returns when it reaches the root
    if(d->parentDir == NULL)
    {
        return d->info.name;
    }
    else
    {
        return getWorkingDir_helper(d->parentDir) + "/" + d->info.name;
    }
}

void MyShell::ls(const vector<string>& parsedCmd)
{
    //If the command is just ls
    if(parsedCmd.size() == 1)
    {
        cout << "\n";
        int subDirNum = workingDir->subDirectories.size();
        for(int i = 0; i < subDirNum; i++)
        {
            cout << workingDir->subDirectories[i].info.name << "\t";
        }
        int subFileNum = workingDir->files.size();
        for(int i = 0; i < subFileNum; i++)
        {
            cout << workingDir->files[i].info.name << "\t";
        }
        cout << "\n\n";
    }
    else
    {
        //If the command is ls with additional tags
        if(parsedCmd[1][0] == '-')
        {
            if(parsedCmd[1][1] == 'l')
            {
                //looping through each directory and file and displaying the detailed information that ls -l shows
                cout << "\n";
                int subDirNum = workingDir->subDirectories.size();
                for(int i = 0;i < subDirNum; ++i)
                {
                    cout << getInfo(workingDir->subDirectories[i].info) << "\n";
                }
                int subFileNum = workingDir->files.size();
                for(int i = 0;i < subFileNum; ++i)
                {
                    cout << getInfo(workingDir->files[i].info) << "\n";
                }
                cout << "\n";
            }
            //If something else apart from the valid commands is entered, we output an error
            else
            {
                ErrorHandler error;
                error.errMsg = "ls command option" ;
                error.errMsg += " is invalid";
                throw(error);
            }
        }
            //If ls command option provided is invalid
        else
        {
            ErrorHandler error;
            error.errMsg = "ls command (\"" + parsedCmd[1] + "\") is invalid";

            throw(error);
        }
    }
}

void MyShell::cd(const vector<string>& parsedCmd)
{
    //If cd is entered without a directory name

    bool found = false;
    if(parsedCmd.size() == 1)
    {
        ErrorHandler error;
        error.errMsg = "Please provide a target directory name";

        throw(error);
    }
    //Moving back
    if(parsedCmd[1] == "..")
    {
        //moving up until the user stops or we hit the root
        if(workingDir->parentDir != NULL)
        {
            workingDir = workingDir->parentDir;
        }
    }
    //Going right back to root
    else if(parsedCmd[1] == "~")
    {
        workingDir = &rootDir;
    }

    else
    {
        //look through the directories, trying to find the one indicated
        int subDirNum = workingDir->subDirectories.size();
        for(int i = 0;i < subDirNum; ++i)
        {
            //if it is found, update cwd and set our flag so we leave the loop and know we found it
            if(!found) {
                if (workingDir->subDirectories[i].info.name == parsedCmd[1]) {
                    workingDir = &workingDir->subDirectories[i];
                    found = true;
                }
            }
        }

        //if we did not find the directory indicated, let the user know
        if(!found)
        {
            ErrorHandler err;
            err.errMsg = "(\"" + parsedCmd[1] + "\") - Directory does not exist";

            throw(err);
        }
    }
}

void MyShell::mkdir(const vector<string>& parsedCmd)
{
    //If mkdir is typed in without a directory name
    if(parsedCmd.size() == 1)
    {
        ErrorHandler err;
        err.errMsg = "Please enter a directory name to create a directory";

        throw(err);
    }
    //If the directory already exists, then an error is thrown
    int subDirNum = workingDir->subDirectories.size();
    for(int i = 0;i < subDirNum; i++)
    {
        if(parsedCmd[1] == workingDir->subDirectories[i].info.name)
        {
            ErrorHandler err;
            err.errMsg = "\"" + parsedCmd[1] + "\" - Directory already exists. Please enter a unique name.";

            throw(err);
        }
    }

    Directory newDir; //Creating a new directory
    newDir.info.name = parsedCmd[1]; //setting its name
    newDir.parentDir = workingDir; // setting its parent pointer

    workingDir->subDirectories.push_back(newDir); //Adding it to the subDirectories vector of the working Directory
}

void MyShell::rmdir(const vector<string>& parsedCmd)
{
    //If rmdir is typed in without a directory name
    if(parsedCmd.size() == 1)
    {
        ErrorHandler err;
        err.errMsg = "Please provide a directory name";

        throw(err);
    }

    //Finding the directory we intend to remove
    int targetDir = -1;
    int subDirNum = workingDir->subDirectories.size();
    for(int i = 0; i < subDirNum; ++i)
    {
        if(targetDir == -1) {
            if (parsedCmd[1] == workingDir->subDirectories[i].info.name) {
                targetDir = i;
            }
        }
    }

    //if the directory doesn't exist, throw an error
    if(targetDir == -1)
    {
        ErrorHandler er;
        er.errMsg = "Directory (\"" + parsedCmd[1] + "\") not found";

        throw(er);
    }

    //remove the directory from the subDirectories vector
    workingDir->subDirectories.erase(workingDir->subDirectories.begin() + targetDir);
}

void MyShell::rm(const vector<string>& parsedCmd)
{
    //If rm is typed in without a file name
    if(parsedCmd.size() == 1)
    {
        ErrorHandler er;
        er.errMsg = "Please enter a file name";

        throw(er);
    }

    //Finding the file we intend to remove
    int targetFile = -1;
    int subFileNum = workingDir->files.size();
    for(int i = 0; i < subFileNum; ++i)
    {
        if(targetFile == -1) {
            if (parsedCmd[1] == workingDir->files[i].info.name) {
                targetFile = i;
            }
        }
    }

    //if the directory doesn't exist, throw an error
    if(targetFile == -1)
    {
        ErrorHandler er;
        er.errMsg = "File (\"" + parsedCmd[1] + "\") not found";

        throw(er);
    }

    //Remove the file from files vector
    workingDir->files.erase(workingDir->files.begin() + targetFile);

}

void MyShell::chmod(const vector<string>& parsedCmd)
{
    //error check
    if(parsedCmd.size() != 3)
    {
        ErrorHandler er;
        er.errMsg = "Must provide three digit permission string and file/directory name to chmod command";

        throw(er);
    }

    Info* target = NULL;

    //find the file/directory that we are updating. As soon as target is not NULL, both of these
    //loops fall through
    int subDirNum = workingDir->subDirectories.size();
    for(int i = 0; i < subDirNum && target == NULL; ++i)
    {
        if(parsedCmd[2] == workingDir->subDirectories[i].info.name)
        {
            target = &workingDir->subDirectories[i].info;
        }
    }
    for(int i = 0, i_end = workingDir->files.size(); i < i_end && target == NULL; ++i)
    {
        if(parsedCmd[2] == workingDir->files[i].info.name)
        {
            target = &workingDir->files[i].info;
        }
    }

    //if we could not a file or directory with the name indicated, let the user know
    if(target == NULL)
    {
        ErrorHandler er;
        er.errMsg = "Could not find file indicated in chmod command (\"" + parsedCmd[2] + "\")";

        throw(er);
    }

    //update the target's permissions
    target->perm.updatePerm(parsedCmd[1]);
}

void MyShell::touch(const vector<string>& parsedCmd)
{
    //If touch command is entered without a filename
    if(parsedCmd.size() < 2)
    {
        ErrorHandler er;
        er.errMsg = "Please provide a filename for touch";

        throw(er);
    }

    Info* target = NULL;
    //If the file already exists, then we exit loop
    int subDirNum = workingDir->subDirectories.size();
    for(int i = 0; i < subDirNum && target == NULL; ++i)
    {
        if(parsedCmd[1] == workingDir->subDirectories[i].info.name)
        {
            target = &workingDir->subDirectories[i].info;
        }
    }
    int subFileNum = workingDir->files.size();
    for(int i = 0; i < subFileNum && target == NULL; ++i)
    {
        if(parsedCmd[1] == workingDir->files[i].info.name)
        {
            target = &workingDir->files[i].info;
        }
    }

    //updating the modification time if the file already exists
    if(target != NULL)
    {
        time(&target->modTime);
    }
    //creating a new file and adding it to out files vector
    else
    {
        File newFile;
        newFile.info.name = parsedCmd[1];

        workingDir->files.push_back(newFile);
    }
}
/*
 * A function to call the appropriate commands based on the user input
 */
void MyShell::execute(const string &command)
{
    vector<string> parsedCmd;
    parse(command, parsedCmd);

    if(parsedCmd.size() == 0)
    {
        return;
    }
    if(parsedCmd[0] == "ls")
    {
        ls(parsedCmd);
    }
    else if(parsedCmd[0] == "cd")
    {
        cd(parsedCmd);
    }
    else if(parsedCmd[0] == "pwd")
    {
        cout << "\n" << getWorkingDir() << "\n\n";
    }
    else if(parsedCmd[0] == "mkdir")
    {
        mkdir(parsedCmd);
    }
    else if(parsedCmd[0] == "rmdir")
    {
        rmdir(parsedCmd);
    }
    else if(parsedCmd[0] == "rm")
    {
        rm(parsedCmd);
    }
    else if(parsedCmd[0] == "chmod")
    {
        chmod(parsedCmd);
    }
    else if(parsedCmd[0] == "touch")
    {
        touch(parsedCmd);
    }
    else if(parsedCmd[0] == "quit" || parsedCmd[0] == "exit")
    {
        exitToggle = true;
    }
    else
    {
        ErrorHandler er;
        er.errMsg = "Command (\"" + parsedCmd[0] + "\") not found";

        throw(er);
    }
}