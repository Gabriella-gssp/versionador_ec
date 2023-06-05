#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include "versionador.h"

void criarDiretorios() {
    // Verifica se o diretório ".versionador" existe
    DIR* dir = opendir(".versionador");
    if (dir != NULL) {
        closedir(dir); // Fecha o diretório se ele existe
    } else {
        // Se o diretório não existe, cria-o
        if (mkdir(".versionador", 0777) != 0) {
            // Se ocorrer um erro ao criar o diretório, exibe uma mensagem de erro e encerra o programa
            printf("Erro ao criar o diretório .versionador.\n");
            exit(1);
        }
    }

    // Verifica se o diretório ".versionador/versoes" existe
    dir = opendir(".versionador/versoes");
    if (dir != NULL) {
        closedir(dir); // Fecha o diretório se ele existe
    } else {
        // Se o diretório não existe, cria-o
        if (mkdir(".versionador/versoes", 0777) != 0) {
            // Se ocorrer um erro ao criar o diretório, exibe uma mensagem de erro e encerra o programa
            printf("Erro ao criar o diretório de versões.\n");
            exit(1);
        }
    }

    // Verifica se o diretório ".versionador/arquivos" existe
    dir = opendir(".versionador/arquivos");
    if (dir != NULL) {
        closedir(dir); // Fecha o diretório se ele existe
    } else {
        // Se o diretório não existe, cria-o
        if (mkdir(".versionador/arquivos", 0777) != 0) {
            // Se ocorrer um erro ao criar o diretório, exibe uma mensagem de erro e encerra o programa
            printf("Erro ao criar o diretório de arquivos marcados.\n");
            exit(1);
        }
    }
}