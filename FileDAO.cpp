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

    public:

        FileDAO(){
            Files[0] = new Archive("first.txt" , 0);
            Files[1] = new Archive("second.txt" , 1);
            Files[2] = new Archive("third.txt" , 2);
        }
        
        Archive* getFileForReader(){
            
            if ( mutex == 0){
                return NULL;
            }

            int i = rand() % 3;

            return Files[i];
        }

        Archive* getFileForWriter(){
            
            if ( mutex == 0){
                return NULL;
            }
            mutex = 0;
            
            int i = rand() % 3;
            for ( int j=0; j<3; j++){
                (i == j) ? up(j) : down(j);
            }

            return Files[i];
        }
        
        void allSynced(){
            
            bool synced = true;
            for ( int j=0; j<3; j++){
                if( semaphore[j] != 1){
                    synced  = false;
                }
            }

            if(synced){
                mutex = 1;
            }
        }

        array<Archive*, 2> getFilesForPhilosophers(){

            int i = rand() % 3;
            int j = rand() % 3;
            (j != i) ?  : j++;
            j = j % 3;

            array<Archive*, 2> archives;
            archives[0] = Files[i];
            archives[1] = Files[j];
            return archives;
        }

    private:
        void up(int index){
            if (semaphore[index] == 2 ){
                semaphore[index]++;
            } 
        }

        void down(int index){
            if (semaphore[index] == 0 ){
                semaphore[index]--;
            }
        }
};
