#ifndef FIND_FILE_LOCALLY_H_INCLUDED
#define FIND_FILE_LOCALLY_H_INCLUDED

#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

namespace UserFind
{

// to control threads
inline constexpr int MAX_THREADS{8};
static pthread_t threads[MAX_THREADS]{};
inline constexpr pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// to hold arguments passed to thread
struct WrapperArgs
{
    char* dir;
    const char* lookupFile;
    char** foundPath;
};

// TODO the function will create a new thread up to 8
bool isFileInDir(char* dir, const char* lookupFile, char** foundPath);

// to be able to search with multiple threads we need a wrapper
void* WrapperIsFileInDir(void *arg);

}
#endif // FINDFILELOCALLY_H_INCLUDED
