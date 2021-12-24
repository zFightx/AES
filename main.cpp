#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

// #include <Windows.h>
// #include <cstdio>

#include "aes.hpp"

using namespace std;

int main(void){    
    string nomeArquivo, key;
    int modo = 0, rounds = 10;
    Aes teste{};

    // Inicial
    cout << "Bem vindo ao Cifrador 2000" << endl;
    cout << "Para realizar a cifra, voce precisara de uma imagem no formato .bmp no diretorio do programa." << endl;
    cout << endl << endl;
    cout << "Nome do arquivo BMP: ";
    cin >> nomeArquivo;

    srand( time(NULL) );


    ifstream ifs(nomeArquivo, ios::in | ios::binary); // abrindo arquivo
    ifstream keyFile("key.txt"); // abrindo arquivo
    ostringstream oss; // string de leitura

    // Lendo arquivo BMP
    cout << "Lendo arquivo..." << endl;
    int len;
    char buf[1024];
    while((len = ifs.readsome(buf, 1024)) > 0)
    {
        oss.write(buf, len);
    }
    std::string data = oss.str(); // salvando leitura numa string
    ifs.close(); // fechando arquivo

    // Lendo Key
    if (keyFile.is_open()){
        while (! keyFile.eof()){
            getline (keyFile, key);
        }
        keyFile.close();
    }
    else cout << "Nao foi possivel abrir o arquivo."; 

    // Menu de escolhas
    cout << "Leitura concluida." << endl << endl;
    while(modo < 1 || modo > 4){
        cout << "Qual modo deseja utilizar?" << endl;
        cout << "1. ECB" << endl;
        cout << "2. Decifrar ECB" << endl;
        cout << "3. CTR" << endl;
        cout << "4. Decifrar CTR" << endl;
        cout << "Opcao: ";

        cin >> modo;
    }

    cout << "Quantos rounds ?" << endl;
    cout << "Resposta: ";
    cin >> rounds;

    if(modo == 1){   
        teste.SetCTR(false);
        teste.Cifrar(data, key, rounds);
    }
    else if(modo == 2){
        teste.SetCTR(false);
        teste.Decifrar(data, key, rounds);
    }
    else if(modo == 3){
        teste.SetCTR(true);
        teste.Cifrar(data, key, rounds);
    }
    else if(modo == 4){
        teste.SetCTR(true);
        teste.Decifrar(data, key, rounds);
    }

    // a    b   c   d
    // e    f   g   h
    // i    j   k   l
    // m    n   o   p

    // a    b   c   d
    // f    g   h   e
    // k    l   i   j
    // p    m   n   o

    // 61    62   63   64
    // 65    66   67   68
    // 69    6A   6B   6C
    // 6D    6E   6F   70

    return 0;
}