#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include "versionador.h"

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
