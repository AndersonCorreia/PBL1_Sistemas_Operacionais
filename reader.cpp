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

        void run(){
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
            cout << "Reader " << this->id <<": iniciou a leitura do arquivo " << nome << ".\n";
            if (myfile.is_open()) {
                while ( getline (myfile,line) ) {
                    cout << "Reader " << this->id << ":" << line << '\n';
                }
                myfile.close();
            }
            cout << "Reader " << this->id <<": terminou de ler o arquivo " << nome << ".\n";
        }
};

int Reader::id_static = 1;