#include "FindFileLocally.h"


namespace UserFind
{


//forward declaration
void* WrapperIsFileInDir(void *arg);


bool isFileInDir(char* dir, const char* lookupFile, char** foundPath)
{

    DIR* dp = opendir(dir);

    if(dp == NULL)
    {
        return 0;
    }

    struct dirent* de;
    char path[2000];

    //scan the directory
    while((de = readdir(dp)) != NULL)
    {

        // skip the . and .. directories
        if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
        {
            continue;
        }

        if(strcmp(de->d_name, lookupFile) == 0)
        {
            std::cout << "File found " << de->d_name <<'\n';
            char* result{de->d_name};

            // consctruct path
            strcpy(path, dir);
            strcat(path, de->d_name);
            strcpy(*foundPath, path);
            closedir(dp);

            return true;
        }


        // consctruct path
        strcpy(path, dir);
        strcat(path, de->d_name);
        strcat(path, "/");


        // recursion
        if (isFileInDir(path, lookupFile, foundPath))
        {
            closedir(dp);
            return true;
        }

    }
    closedir(dp);
    return false;
}


void* WrapperIsFileInDir(void *arg)
{
    struct WrapperArgs *a = static_cast<WrapperArgs *>(arg);
    bool retval = isFileInDir(a->dir, a->lookupFile, a->foundPath);
    bool *ret = new bool(sizeof(bool));
    *ret = retval;
    return ret;
}

}
