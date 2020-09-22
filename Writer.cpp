#include <stdio.h>
#include <fstream>
#include <thread>

using namespace std;

class Writer {

    private:
        string content[4] = {"alguma coisa", "final fantasy", "soul eater", "texto aleatorio"};
        FileDAO* file;
        int id;
        static int id_static;
        
    public:
        Writer(){};

        Writer(FileDAO* DAO) {
            file = DAO;
                id = id_static++;
        }

        void operator()(){
            while(true){
                Archive* Archive = file->getFileForWriter();

                if ( Archive != NULL){
                    writerFile( Archive->getName() );
                }
                else
                {   
                    int sec = rand() % 10;
                    printf("Writer %i: sleep \n", this->id);
                    this_thread::sleep_for(chrono::seconds(sec));
                }
            }
        }

        void writerFile(string nome){
            string line;

            ofstream myfile(nome, ios_base::app);
            printf("Writer %i: iniciou uma escrita no arquivo %s \n", this->id, nome.c_str());
            if (myfile.is_open()) {
                myfile << content[ rand() % 4];
                myfile.close();
            }
            printf("Writer %i: terminou de escrever no arquivo %s \n", this->id, nome.c_str());
        }
};

int Writer::id_static = 1;