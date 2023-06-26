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

void adicionar_arquivo(const char* arquivo) {
    char arquivoConteudo[256];
    snprintf(arquivoConteudo, sizeof(arquivoConteudo), ".versionador/conteudo/%s", arquivo);

    FILE* arquivoOriginal = fopen(arquivo, "r");
    if (arquivoOriginal == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", arquivo);
        return;
    }

    FILE* arquivoConteudoNovo = fopen(arquivoConteudo, "w");
    if (arquivoConteudoNovo == NULL) {
        printf("Erro ao criar o arquivo %s.\n", arquivoConteudo);
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL) {
        fprintf(arquivoConteudoNovo, "%s", linha);
    }

    fclose(arquivoOriginal);
    fclose(arquivoConteudoNovo);

    char arquivoVersao[256];
    snprintf(arquivoVersao, sizeof(arquivoVersao), ".versionador/versoes/%s", arquivo);

    FILE* arquivoVersaoNovo = fopen(arquivoVersao, "w");
    if (arquivoVersaoNovo == NULL) {
        printf("Erro ao criar o arquivo %s.\n", arquivoVersao);
        return;
    }

    fprintf(arquivoVersaoNovo, "%d\n", proximoIdentificador);
    fprintf(arquivoVersaoNovo, "%s\n", arquivo);

    fclose(arquivoVersaoNovo);
}

void criarSnapshot(Fila* arquivosMarcados) {
    if (arquivosMarcados->inicio == NULL) {
        printf("Nenhum arquivo marcado para snapshot.\n");
        return;
    }

    char arquivo[256];
    snprintf(arquivo, sizeof(arquivo), ".versionador/versoes/%d", proximoIdentificador);

    FILE* arquivoSnapshot = fopen(arquivo, "w");
    if (arquivoSnapshot == NULL) {
        printf("Erro ao criar o arquivo de snapshot.\n");
        return;
    }

    fprintf(arquivoSnapshot, "%d\n", proximoIdentificador);

    Node* arquivoAtual = arquivosMarcados->inicio;
    while (arquivoAtual != NULL) {
        fprintf(arquivoSnapshot, "%s\n", arquivoAtual->arquivo);
        arquivoAtual = arquivoAtual->prox;
    }

    fclose(arquivoSnapshot);

    printf("Snapshot %d criado com sucesso.\n", proximoIdentificador);

    Snapshot* novoSnapshot = (Snapshot*)malloc(sizeof(Snapshot));
    novoSnapshot->identificador = proximoIdentificador;
    novoSnapshot->arquivos = arquivosMarcados;
    novoSnapshot->prox = NULL;

    if (inicioSnapshot == NULL) {
        inicioSnapshot = novoSnapshot;
        fimSnapshot = novoSnapshot;
    } else {
        fimSnapshot->prox = novoSnapshot;
        fimSnapshot = novoSnapshot;
    }

    proximoIdentificador++;
}
