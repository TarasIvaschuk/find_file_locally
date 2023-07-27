#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>


#define MAX_THREADS 8

// to control threads
pthread_t threads[MAX_THREADS];

// to hold arguments passed to thread
struct WrapperArgs
{
    char* dir;
    const char* lookupFile;
    char** foundPath;
};

//forward declaration
void* WrapperIsFileInDir(void *arg);

// TODO the function will create a new thread up to 8
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


// to be able to search with multiple threads we need a wrapper
void* WrapperIsFileInDir(void *arg)
{
    struct WrapperArgs *a = static_cast<WrapperArgs *>(arg);
    bool retval = isFileInDir(a->dir, a->lookupFile, a->foundPath);
    bool *ret = new bool(sizeof(bool));
    *ret = retval;
    return ret;
}


int main(int argc, char* argv [])
{
    char* lookupFile = argv[1];
    char* foundPath = new char[2000];
    char* lookupDir{"/"};

    struct WrapperArgs wrapper;
    wrapper.dir = lookupDir;
    wrapper.lookupFile = lookupFile;
    wrapper.foundPath = &foundPath;

    int status; // to track is thread creation is successful

    for (int i{0}; i < MAX_THREADS; ++ i)
    {
        std::cout << "Creating a thread [" << i << "]\n" ;
        if ((status = pthread_create(&threads[i], NULL, WrapperIsFileInDir, &wrapper))!= 0)
        {
            std::cerr << "Thread is not created\n";
        }
    }

    if(isFileInDir(lookupDir, lookupFile, &foundPath))
    {
        std::cout << foundPath;
    }

}

