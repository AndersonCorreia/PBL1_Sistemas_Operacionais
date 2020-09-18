#include <stdio.h>
#include <iostream>
#include <thread>
#include <array>
#include "FileDAO.cpp"

using namespace std;

int main (){
    srand(time(NULL));//usando o tempo atual como semente dos numeros aleatorios

    //this_thread::sleep_for(chrono::seconds(185));
    FileDAO files = FileDAO();
    cout << "testando, chamando getFilesForPhilosophers pela primeira vez \n";
    array<Archive *,2> livros = files.getFilesForPhilosophers();
    Archive* livro = livros[0];
    cout << "arquivo com id:" << livro->getId() << ", nome:" << livro->getName() << endl;
    livro = livros[1];
    cout << "arquivo com id:" << livro->getId() << ", nome:" << livro->getName() << endl;
    
    cout << "testando, chamando getFilesForPhilosophers pela segunda vez \n";
    livros = files.getFilesForPhilosophers();
    livro = livros[0];
    cout << "arquivo com id:" << livro->getId() << ", nome:" << livro->getName() << endl;
    livro = livros[1];
    cout << "arquivo com id:" << livro->getId() << ", nome:" << livro->getName() << endl;
    
    cout << "testando, chamando getFilesForPhilosophers pela terceira vez \n";
    livros = files.getFilesForPhilosophers();
    livro = livros[0];
    cout << "arquivo com id:" << livro->getId() << ", nome:" << livro->getName() << endl;
    livro = livros[1];
    cout << "arquivo com id:" << livro->getId() << ", nome:" << livro->getName() << endl;
    return 0;
}