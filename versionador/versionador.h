#ifndef VERSIONADOR_H_
#define VERSIONADOR_H_

typedef struct{
    char arquivo[256];
    struct Node* prox;
} Node;

typedef struct {
    Node* inicio;
    Node* fim;
} Fila;

typedef struct {
    int identificador;
    Fila* arquivos;
    struct Snapshot* prox;
} Snapshot;

void criarDiretorios();

#endif 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

void criarDiretorios();
void criar_fila();
void enfileirar(Fila* fila, const char* arquivo);
char* desenfileirar(Fila* fila);

#endif 
