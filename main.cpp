
#include "FindFileLocally.h"

int main(int argc, char* argv [])
{
    char* lookupFile = argv[1];
    char* foundPath = new char[2000];
    char* lookupDir = "/";

    struct UserFind::WrapperArgs wrappedArgs;
    wrappedArgs.dir = lookupDir;
    wrappedArgs.lookupFile = lookupFile;
    wrappedArgs.foundPath = &foundPath;

    int status;

    for (int i{0}; i < UserFind::MAX_THREADS; ++ i)
    {
        std::cout << "Creating a thread [" << i << "]\n" ;
        if ((status = pthread_create(&UserFind::threads[i], NULL, UserFind::WrapperIsFileInDir, &wrappedArgs))!= 0)
        {
            std::cerr << "Thread is not created\n";
        }
    }

    if(UserFind::isFileInDir(lookupDir, lookupFile, &foundPath))
    {
        std::cout << foundPath;
    }

}

