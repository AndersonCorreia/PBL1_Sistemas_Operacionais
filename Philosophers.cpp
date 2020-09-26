#include <iostream>
#include <fstream>
#include <array>
using namespace std;

#define N 5
#define WAITING 0       // think
#define OUT_OF_SYNCH 1  // hungry
#define SYNCHRONIZING 2 // eating

class Philosopher{
    
    private:
        FileDAO* file;
        int id;
        static int id_static;
        static int mutex;
        
    public:
        Philosopher(){};

        Philosopher(FileDAO* DAO) {
            file = DAO;
                id = id_static++;
        }
        
        void operator()(){
            while(true){
                if( mutex == 1){
                    mutex = 0;
                    array<Archive*, 2> archives = file.getFilesForPhilosophers();
                    int sem0 = file.getSemaphore( archives[0].getId());
                    int sem1 = file.getSemaphore( archives[1].getId());
                    
                    if( sem0 == 1 && sema1 == 0){// arquivo 1 atualizado e arquivo 0 não
                        file.up( archives[1].getId() );
                        file.up( archives[1].getId() );//mudando para bloqueado para escrita
                        mutex = 1;//saindo da zona critica
                        sincronizar( archives[0], archives[1]);
                    }
                    else if( sem1 == 0 && sema1 == 1){// arquivo 0 atualizado e arquivo 1 não
                        file.up( archives[0].getId() );
                        file.up( archives[0].getId() );//mudando para bloqueado para escrita
                        mutex = 1;// saindo da zona critica
                        sincronizar( archives[1], archives[0]);
                    }// se não caiu em um dos if ou os arquivos estão atualizados ou ja tem um bloqueado para escrita
                    mutex = 1;// sainda da zona critica
                    //trabalho do filosofo feito ou um dos arquivos estava bloqueado, indo dormir
                    int sec = rand() % 10;
                    printf("Philosopher %i: sleep \n", this->id);
                    this_thread::sleep_for(chrono::seconds(sec));
                }
                else {
                    int sec = rand() % 10;
                    printf("Philosopher %i: sleep \n", this->id);
                    this_thread::sleep_for(chrono::seconds(sec));
                }
            }
        }
    private:
        void sincronizar( Archive* atualizado, Archive* desatualizado){
            ofstream f2(desatualizado.getName());
            ifstream f1(atualizado.getName());
            string line;
            
            printf("Philosopher %i: sicronizando o conteudo do arquivo %s com o arquivo %s \n",
                 this->id, atualizado.getName().c_str(), desatualizado.getName().c_str());

            while(getline(f1, line)){
                f2 << line;
            }
            printf("Philosopher %i: terminou a sicronização \n", this->id);

            f2.close();
            f1.close();
        }
};

int Philosopher::id_static = 1;
int Philosopher::mutex = 1;