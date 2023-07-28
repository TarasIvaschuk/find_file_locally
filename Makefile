SOURCE = main.cpp

# LIB name does not include prefix lib_
LIB_NAME = user_find
LIB_OBJECT_FILES = lib_$(LIB_NAME).o
LIB = lib_$(LIB_NAME).a
LIB_PATH = -L. -l_$(LIB_NAME)
LIB_SOURCE = lib_$(LIB_NAME).cpp

CC = g++
FLAGS = -Wall -std=c++20 -Wsign-conversion -Wconversion -lpthread
TARGET = myapp

all: $(TARGET) clean

$(TARGET): $(LIB) $(SOURCE)
	$(CC) -o $(TARGET) $(SOURCE) $(LIB_PATH)

$(LIB): $(LIB_OBJECT_FILES)
	 ar -rcs $(LIB) $(LIB_OBJECT_FILES)
 
$(LIB_OBJECT_FILES): $(LIB_SOURCE)
	$(CC) $(FLAGS) -c $(LIB_SOURCE) -o $(LIB_OBJECT_FILES)
	
clean: 
	rm -f *.o *.a





