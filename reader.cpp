#include <stdio.h>
#include <fstream>
#include <thread>

using namespace std;

class Reader {

    private:
        FileDAO* file;
        int id;
        static int id_static;
        
    public:
        Reader(){};

        Reader(FileDAO* DAO) {
            file = DAO;
                id = id_static++;
        }

        void operator()(){
            while(true){
                Archive* Archive = file->getFileForReader();

                if ( Archive != NULL){
                    readFile( Archive->getName() );
                    file->completeReading();
                }
                else
                {   
                    int sec = rand() % 10;
                    printf("Reader %i: sleep \n", this->id);
                    this_thread::sleep_for(chrono::seconds(sec));
                }
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