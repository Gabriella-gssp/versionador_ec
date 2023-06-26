int main(int argc, char* argv[]) {
    if (argc < 2) {
        
        printf("Uso: %s <comando> [argumentos]\n", argv[0]);
        printf("Comandos disponíveis:\n");
        printf("versionador.exe iniciar\n");
        printf("versionador.exe adiciona <arquivo> [arquivo2] ...\n");
        printf("versionador.exe registra <mensagem>\n");
        printf("versionador.exe log [--conteudo]\n");
        printf("versionador.exe mostrar <identificador>\n");
        printf("versionador.exe mudar <identificador>\n");
        printf("versionador.exe mudar\n");

        return 1;
    }

    if (strcmp(argv[1], "iniciar") == 0) {
        iniciar();
    } else if (strcmp(argv[1], "adiciona") == 0) {
        if (argc < 3) {
            printf("Uso: %s adiciona <arquivo> [arquivo2] ...\n", argv[0]);
            return 1;
        }

        Fila* arquivosMarcados = criarFila();

        for (int i = 2; i < argc; i++) {
            enfileirar(arquivosMarcados, argv[i]);
        }

        criarSnapshot(arquivosMarcados);
    } else if (strcmp(argv[1], "registra") == 0) {
        if (argc < 3) {
            printf("Uso: %s registra <mensagem>\n", argv[0]);
            return 1;
        }

        Fila* arquivosMarcados = criarFila();

        for (int i = 2; i < argc; i++) {
            enfileirar(arquivosMarcados, argv[i]);
        }

        criarSnapshot(arquivosMarcados);
    } else if (strcmp(argv[1], "log") == 0) {
        if (argc > 2 && strcmp(argv[2], "--conteudo") == 0) {
            listarSnapshots(1);
        } else {
            listarSnapshots(0);
        }
    } else if (strcmp(argv[1], "mostrar") == 0) {
        if (argc < 3) {
            printf("Uso: %s mostrar <identificador>\n", argv[0]);
            return 1;
        }

        int identificador = atoi(argv[2]);
        mostrarSnapshot(identificador);
    } else if (strcmp(argv[1], "mudar") == 0) {
        if (argc < 3) {
            printf("Uso: %s mudar <identificador>\n", argv[0]);
            return 1;
        }

        int identificador = atoi(argv[2]);
        mudarSnapshot(identificador);
    } else if (strcmp(argv[1], "mudar") == 0) {
        mudarAtual();
    } else {
        printf("Comando %s não encontrado.\n", argv[1]);
        return 1;
    }
    return 0;
}
