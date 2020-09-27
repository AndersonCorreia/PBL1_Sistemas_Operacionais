#include <stdio.h>
#include <iostream>
#include <thread>
#include <array>
#include "FileDAO.cpp"
#include "Reader.cpp"
#include "Writer.cpp"
#include "Philosophers.cpp"
#include <vector>
using namespace std;

int main (){
    srand(time(NULL));//usando o tempo atual como semente dos numeros aleatorios
    int qtd_readers = (rand() % 5) + 1;
    int qtd_writers = (rand() % 5) + 1;
    Reader readers[qtd_readers];
    Writer writers[qtd_writers];
    Philosopher philosophers[5];
    FileDAO files = FileDAO();
    vector<thread *> threads;
    
    thread* t;
    cout << "Quantidade de leitores: " << qtd_readers << "\n Quantidade de escritores: " << qtd_writers << "\n";
    for (int i = 0; i < qtd_readers; i++){
        readers[i] = Reader(&files);
        t = new thread(readers[i]);
        threads.push_back(t);
    }
    for (int i = 0; i < qtd_writers; i++){
        writers[i] = Writer(&files);
        t = new thread(writers[i]);
        threads.push_back(t);
    }
    for (int i = 0; i < 5; i++){
        philosophers[i] = Philosopher(&files);
        t = new thread(philosophers[i]);
        threads.push_back(t);
    }
    for (int i =0; i < threads.size(); i++){
        threads[i]->join();
    }

    return 0;
}