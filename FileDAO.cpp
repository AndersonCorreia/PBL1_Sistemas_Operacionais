#include <stdio.h>
#include <stdlib.h>
#include <array>
#include "Archive.cpp"

using namespace std;

class FileDAO {

    private:
        Archive * Files[3];
        int semaphore[3] = {1, 1, 1};
        //valores dos semaforos: 0-Desatualizado, 1-atualizado, 2-bloqueado para escrita
        int mutex = 1;
        int mutex_readers = 1;
        int rc = 0;

    public:

        FileDAO(){
            Files[0] = new Archive("zero.txt" , 0);
            Files[1] = new Archive("one.txt" , 1);
            Files[2] = new Archive("two.txt" , 2);
        }
        
        Archive* getFileForReader(){
            
            if ( mutex == 0 or mutex_readers == 0){
                printf("BLoqueando Reader \n");
                return NULL;
            }
            rc++;
            printf("\nArquivo fornecido a um leitor, quantidade de leitores: %i \n", rc);
            int i = rand() % 3;

            return Files[i];
        }
        
        void completeReading(){
            rc--;
            printf("\nLeitores restantes: %i \n", rc);
        }

        Archive* getFileForWriter(){
            
            if ( mutex == 0 or rc > 0){
                mutex_readers = 0;
                printf("\nBLoqueando todos os Readers \n");
                return NULL;
            }
            mutex = 0;
            printf("\nBLoqueando leitores e escritores \n");

            int i = rand() % 3;
            for ( int j=0; j<3; j++){
                (i == j) ? up(j) : down(j);
            }

            return Files[i];
        }
        
        void allSynced(){//função para acordar leitores e escritores
            
            bool synced = true;
            for ( int j=0; j<3; j++){
                if( semaphore[j] != 1){
                    synced  = false;
                }
            }

            if(synced){
                mutex = 1;
                mutex_readers = 1;
                printf("\n Todos os arquivos estão sicronizado. \n");
            }
        }

        array<Archive*, 2> getFilesForPhilosophers(){

            int i = rand() % 3;
            int j = rand() % 3;
            (j != i) ?  : j++;
            j = j % 3;

            printf("Fornecendo arquivo %i e %i para um filosofo. \n\n", i, j);

            array<Archive*, 2> archives;
            archives[0] = Files[i];
            archives[1] = Files[j];
            return archives;
        }

        int getSemaphore(int i){

            return semaphore[i];
        }

        void up(int index){
            if (semaphore[index] < 2 ){
                semaphore[index]++;
            } 
        }

        void down(int index){
            if (semaphore[index] > 0 ){
                semaphore[index]--;
            }
        }
};
