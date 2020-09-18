#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

class Archive {
    public:
        FILE * file;
        int id;
        string name;

    public:
        Archive(){};

        Archive(char* name, int id) {
            this->id = id;
            this->file = fopen(name, "a");
            this->name = name;
        };

        int getId(){
            return this->id;
        };

        FILE * getFile(){
            return file;
        }

        string getName(){
            return name;
        }
};