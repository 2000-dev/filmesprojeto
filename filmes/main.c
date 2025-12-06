#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constante para o tamanho máximo do acervo
#define TAMANHO_ACERVO 20
#define ARQUIVO_ACERVO "acervo.dat"  // arquivo binário onde o acervo será salvo

// Definição da struct Livro
struct Livro {
    int codigo;
    char titulo[50];
    char autor[30];
    char area[30];
    int ano;
    char editora[30];
};

// Protótipos das funções principais
void cadastrarLivros(struct Livro acervo[], int tamanho);
void imprimirLivros(struct Livro acervo[], int tamanho);
void pesquisarLivro(struct Livro acervo[], int tamanho, int codigoBusca);
void ordenarLivros(struct Livro acervo[], int tamanho);

// Protótipos do DESAFIO EXTRA (arquivos)
void carregarAcervo(struct Livro acervo[], int tamanho, const char *nomeArquivo);
void salvarAcervo(struct Livro acervo[], int tamanho, const char *nomeArquivo);

int main() {
    struct Livro acervo[TAMANHO_ACERVO];
    int opcao;
    int codigoBusca;
    int i;

    // Inicializa o acervo com valores "vazios"
    for (i = 0; i < TAMANHO_ACERVO; i++) {
        acervo[i].codigo = 0;
        acervo[i].ano = 0;
        strcpy(acervo[i].titulo, "");
        strcpy(acervo[i].autor, "");
        strcpy(acervo[i].area, "");
        strcpy(acervo[i].editora, "");
    }

    // DESAFIO EXTRA: tenta carregar dados de arquivo, se existir
    carregarAcervo(acervo, TAMANHO_ACERVO, ARQUIVO_ACERVO);

    do {
        printf("\n===== SISTEMA DE GERENCIAMENTO DE LIVROS =====\n");
        printf("1 - Cadastrar livros\n");
        printf("2 - Imprimir todos os livros\n");
        printf("3 - Pesquisar livro por codigo\n");
        printf("4 - Ordenar livros por ano de publicacao\n");
        printf("5 - Sair do programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        fflush(stdin); // limpa o buffer do teclado (usado em muitas implementacoes no Windows)

        switch (opcao) {
            case 1:
                cadastrarLivros(acervo, TAMANHO_ACERVO);
                break;
            case 2:
                imprimirLivros(acervo, TAMANHO_ACERVO);
                break;
            case 3:
                printf("Digite o codigo do livro que deseja pesquisar: ");
                scanf("%d", &codigoBusca);
                fflush(stdin);
                pesquisarLivro(acervo, TAMANHO_ACERVO, codigoBusca);
                break;
            case 4:
                ordenarLivros(acervo, TAMANHO_ACERVO);
                printf("\nLivros ordenados por ano de publicacao (e titulo como desempate).\n");
                break;
            case 5:
                // DESAFIO EXTRA: salva o acervo antes de sair
                printf("\nSalvando acervo em arquivo...\n");
                salvarAcervo(acervo, TAMANHO_ACERVO, ARQUIVO_ACERVO);
                printf("Saindo do programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 5);

    return 0;
}

/*
 * Função: cadastrarLivros
 * -----------------------
 * Percorre o vetor de livros e cadastra até TAMANHO_ACERVO livros.
 * Cada livro terá: codigo, titulo, autor, area, ano e editora.
 */
void cadastrarLivros(struct Livro acervo[], int tamanho) {
    int i;

    printf("\n=== CADASTRO DE LIVROS ===\n");
    for (i = 0; i < tamanho; i++) {
        printf("\nCadastro do livro %d de %d\n", i + 1, tamanho);

        printf("Codigo (inteiro, 0 para deixar vazio): ");
        scanf("%d", &acervo[i].codigo);
        fflush(stdin);

        // Se o usuario digitar 0, vamos considerar esta posicao como "vaga"
        if (acervo[i].codigo == 0) {
            printf("Posicao %d deixada vazia.\n", i + 1);
            // Zera os outros campos
            acervo[i].ano = 0;
            strcpy(acervo[i].titulo, "");
            strcpy(acervo[i].autor, "");
            strcpy(acervo[i].area, "");
            strcpy(acervo[i].editora, "");
            continue;
        }

        printf("Titulo: ");
        scanf(" %49[^\n]", acervo[i].titulo); // le ate a quebra de linha (com espacos)
        fflush(stdin);

        printf("Autor: ");
        scanf(" %29[^\n]", acervo[i].autor);
        fflush(stdin);

        printf("Area: ");
        scanf(" %29[^\n]", acervo[i].area);
        fflush(stdin);

        printf("Ano de publicacao: ");
        scanf("%d", &acervo[i].ano);
        fflush(stdin);

        printf("Editora: ");
        scanf(" %29[^\n]", acervo[i].editora);
        fflush(stdin);

        printf("Livro %d cadastrado com sucesso!\n", i + 1);
    }
}

/*
 * Função: imprimirLivros
 * ----------------------
 * Percorre o vetor e imprime todos os livros cujo codigo seja diferente de 0.
 */
void imprimirLivros(struct Livro acervo[], int tamanho) {
    int i;
    int encontrou = 0;

    printf("\n=== LISTA DE LIVROS CADASTRADOS ===\n");
    for (i = 0; i < tamanho; i++) {
        if (acervo[i].codigo != 0) { // considera 0 como posicao vazia
            printf("\nLivro %d:\n", i + 1);
            printf("Codigo : %d\n", acervo[i].codigo);
            printf("Titulo : %s\n", acervo[i].titulo);
            printf("Autor  : %s\n", acervo[i].autor);
            printf("Area   : %s\n", acervo[i].area);
            printf("Ano    : %d\n", acervo[i].ano);
            printf("Editora: %s\n", acervo[i].editora);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("\nNenhum livro cadastrado.\n");
    }
}

/*
 * Função: pesquisarLivro
 * ----------------------
 * Recebe o codigo que o usuario deseja buscar e
 * percorre o acervo até encontrar ou terminar o vetor.
 */
void pesquisarLivro(struct Livro acervo[], int tamanho, int codigoBusca) {
    int i = 0;
    int encontrado = 0;

    while (i < tamanho && !encontrado) {
        if (acervo[i].codigo == codigoBusca) {
            printf("\nLivro encontrado na posicao %d:\n", i + 1);
            printf("Codigo : %d\n", acervo[i].codigo);
            printf("Titulo : %s\n", acervo[i].titulo);
            printf("Autor  : %s\n", acervo[i].autor);
            printf("Area   : %s\n", acervo[i].area);
            printf("Ano    : %d\n", acervo[i].ano);
            printf("Editora: %s\n", acervo[i].editora);
            encontrado = 1;
        } else {
            i++;
        }
    }

    if (!encontrado) {
        printf("\nLivro com codigo %d nao encontrado.\n", codigoBusca);
    }
}

/*
 * Função: ordenarLivros
 * ---------------------
 * Ordena os livros por ano de publicação usando Bubble Sort.
 * Se dois livros tiverem o mesmo ano, usa strcmp no titulo
 * para desempatar (aplicando função de string).
 */
void ordenarLivros(struct Livro acervo[], int tamanho) {
    int i, j;
    struct Livro temp;

    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - 1 - i; j++) {

            // Se a posicao estiver vazia (codigo 0), enviamos ela para o final
            if (acervo[j].codigo == 0 && acervo[j + 1].codigo != 0) {
                temp = acervo[j];
                acervo[j] = acervo[j + 1];
                acervo[j + 1] = temp;
            }
            // Se ambos nao estao vazios, ordena pelo ano
            else if (acervo[j].codigo != 0 && acervo[j + 1].codigo != 0) {
                if (acervo[j].ano > acervo[j + 1].ano) {
                    temp = acervo[j];
                    acervo[j] = acervo[j + 1];
                    acervo[j + 1] = temp;
                } else if (acervo[j].ano == acervo[j + 1].ano) {
                    // desempate pelo titulo usando strcmp
                    if (strcmp(acervo[j].titulo, acervo[j + 1].titulo) > 0) {
                        temp = acervo[j];
                        acervo[j] = acervo[j + 1];
                        acervo[j + 1] = temp;
                    }
                }
            }
        }
    }
}

/*
 * Função: carregarAcervo  (DESAFIO EXTRA)
 * --------------------------------------
 * Lê o conteúdo do acervo a partir de um arquivo binário.
 * Se o arquivo não existir, mantém o vetor como está (vazio).
 *
 * Observação: fread recebe um ponteiro para o início do vetor.
 */
void carregarAcervo(struct Livro acervo[], int tamanho, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "rb"); // rb = read binary

    if (f == NULL) {
        printf("\nNenhum arquivo de acervo encontrado. Iniciando acervo vazio.\n");
        return;
    }

    size_t lidos = fread(acervo, sizeof(struct Livro), tamanho, f);
    fclose(f);

    if (lidos == 0) {
        printf("\nArquivo de acervo estava vazio.\n");
    } else {
        printf("\nAcervo carregado do arquivo (%zu registros).\n", lidos);
    }
}

/*
 * Função: salvarAcervo  (DESAFIO EXTRA)
 * -------------------------------------
 * Grava todo o vetor de livros em um arquivo binário.
 *
 * Observação: fwrite também usa um ponteiro para o início do vetor.
 */
void salvarAcervo(struct Livro acervo[], int tamanho, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "wb"); // wb = write binary

    if (f == NULL) {
        printf("\nErro ao abrir o arquivo para salvar o acervo!\n");
        return;
    }

    size_t escritos = fwrite(acervo, sizeof(struct Livro), tamanho, f);
    fclose(f);

    if (escritos == tamanho) {
        printf("Acervo salvo com sucesso em '%s'.\n", nomeArquivo);
    } else {
        printf("Aviso: nem todos os registros foram salvos corretamente.\n");
    }
}
