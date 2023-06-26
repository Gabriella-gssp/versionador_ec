#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include "versionador.h"

Fila* criarFila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

void enfileirar(Fila* fila, const char* arquivo) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    strcpy(novoNo->arquivo, arquivo);
    novoNo->prox = NULL;

    if (fila->inicio == NULL) {
        fila->inicio = novoNo;
        fila->fim = novoNo;
    } else {
        fila->fim->prox = novoNo;
        fila->fim = novoNo;
    }
}

char* desenfileirar(Fila* fila) {
    if (fila->inicio == NULL) {
        return NULL;
    }

    Node* noRemovido = fila->inicio;
    fila->inicio = fila->inicio->prox;
    char* arquivo = strdup(noRemovido->arquivo);
    free(noRemovido);
    return arquivo;
}

void iniciar() {
    struct stat st;

    // Verificar se o diretório .versionador já existe
    if (stat(".versionador", &st) == 0 && S_ISDIR(st.st_mode)) {
        return;  // O diretório já existe, não é necessário criar novamente
    }

    if (mkdir(".versionador") != 0) {
        printf("Erro ao criar o diretório .versionador.\n");
        exit(1);
    }

    if (mkdir(".versionador/versoes") != 0) {
        printf("Erro ao criar o diretório de versões.\n");
        exit(1);
    }

    if(mkdir(".versionador/conteudo") != 0) {
        printf("Erro ao criar o diretório de conteúdo.\n");
        exit(1);
    }
}
