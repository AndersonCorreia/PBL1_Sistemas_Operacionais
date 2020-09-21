#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

class Archive {
    public:
        int id;
        string name;

    public:
        Archive(){};

        Archive(char* name, int id) {
            this->id = id;
            this->name = name;
        };

        int getId(){
            return this->id;
        };

        string getName(){
            return name;
        }
};