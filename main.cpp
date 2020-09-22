#include <stdio.h>
#include <iostream>
#include <thread>
#include <array>
#include "FileDAO.cpp"
#include "Reader.cpp"

using namespace std;

int main (){
    srand(time(NULL));//usando o tempo atual como semente dos numeros aleatorios

    //this_thread::sleep_for(chrono::seconds(185));
    FileDAO files = FileDAO();
    Reader reader1 = Reader(files);
    Reader reader2 = Reader(files);
    Reader reader3 = Reader(files);
    
    thread t1 = thread(reader1);
    thread t2 = thread(reader2);
    thread t3 = thread(reader3);
    t3.join();
    t1.join();
    t2.join();
    
    return 0;
}