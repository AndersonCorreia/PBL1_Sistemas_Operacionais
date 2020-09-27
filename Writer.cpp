#include <stdio.h>
#include <fstream>
#include <thread>

using namespace std;

class Writer {

    private:
        string content[4] = {"alguma coisa", "final fantasy", "soul eater", "texto aleatorio"};
        FileDAO* fileDAO;
        Archive* Archive;
        int id;
        static int id_static;
        static int mutex;

    public:
        Writer(){};

        Writer(FileDAO* DAO) {
            fileDAO = DAO;
            id = id_static++;
        }

        void operator()(){
            while(true){
                if( mutex == 1){
                    mutex = 0;//entrando na zona critica
                    Archive = fileDAO->getFileForWriter();
                    mutex = 1;//saindo da zona critica
                }

                if ( Archive != NULL){
                    writerFile( Archive->getName() );
                    fileDAO->down( Archive->getId());
                }
                else
                {   
                    int sec = rand() % 25 + 25;
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
int Writer::mutex = 1;