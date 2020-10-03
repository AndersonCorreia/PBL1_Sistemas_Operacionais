#include <iostream>
#include <thread>
#include <fstream>
#include <array>
using namespace std;

class Philosopher{
    
    private:
        FileDAO* fileDAO;
        int id;
        static int id_static;
        static int mutex;
        
    public:
        Philosopher(){};

        Philosopher(FileDAO* DAO) {
            fileDAO = DAO;
            id = id_static++;
        }
        
        void operator()(){
            while(true){
                if( mutex == 1){
                    mutex = 0;  //entrando na zona critica
                    array<Archive*, 2> archives = fileDAO->getFilesForPhilosophers();
                    int sem0 = fileDAO->getSemaphore( archives[0]->getId());
                    int sem1 = fileDAO->getSemaphore( archives[1]->getId());
                    
                    if( sem0 == 0 && sem1 == 1) {
                        // arquivo 1 atualizado e arquivo 0 não atualizado
                        update(1, 0, archives);
                    }
                    else if( sem0 == 1 && sem1 == 0) {
                        // arquivo 0 atualizado e arquivo 1 não atualizado
                        update(0, 1, archives);
                    }
                    // se não caiu em um dos if ou os arquivos estão atualizados ou ja tem um bloqueado para escrita
                    mutex = 1;  // sainda da zona critica
                    //trabalho do filosofo feito ou um dos arquivos estava bloqueado, indo dormir
                }
                sleep();
            }
        }
    private:
        void sleep(){
            int sec = rand() % 25 + 25;
            printf("Philosopher %i: sleep \n", this->id);
            this_thread::sleep_for(chrono::seconds(sec));
        }
        void update(int updated, int notupdated, array<Archive*, 2> archives){
            fileDAO->up( archives[notupdated]->getId() );
            fileDAO->up( archives[notupdated]->getId() ); //mudando para bloqueado para escrita
            mutex = 1;//saindo da zona critica
            synchronize( archives[updated], archives[notupdated]);
            fileDAO->down(archives[notupdated]->getId() ); //mudando para atualizado
            fileDAO->allSynced();
        }
        void synchronize( Archive* atualizado, Archive* desatualizado){
            ofstream f2(desatualizado->getName());
            ifstream f1(atualizado->getName());
            string line;
            
            printf("Philosopher %i: sicronizando o conteudo do arquivo %s com o arquivo %s \n",
                 this->id, atualizado->getName().c_str(), desatualizado->getName().c_str());

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