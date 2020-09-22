#include <stdio.h>
#include <fstream>
#include <thread>

using namespace std;

class Reader {

    private:
        FileDAO file;
        int id;
        static int id_static;
        
    public: 
        Reader(FileDAO DAO) {
            file = DAO;
                id = id_static++;
        }

        void operator()(){
            Archive* Archive = file.getFileForReader();
            
            if ( Archive != NULL){
                readFile( Archive->getName() );
            }
            else
            {
                this_thread::sleep_for(chrono::seconds(185));
            }
            
        }

        void readFile(string nome){
            string line;

            ifstream myfile(nome);
            printf("Reader %i: iniciou a leitura do arquivo %s \n", this->id, nome.c_str());
            if (myfile.is_open()) {
                while ( getline (myfile,line) ) {
                    printf_s("Reader %i: %s.\n", this->id, line.c_str());
                }
                myfile.close();
            }
            printf("Reader %i: terminou de ler o arquivo %s \n", this->id, nome.c_str());
        }
};

int Reader::id_static = 1;