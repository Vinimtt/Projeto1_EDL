#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 30

typedef struct msc {
    char nome[TAM];
    char artista[TAM];
    float duracao;
} Musica;

typedef struct no {
    Musica musica;           
    struct no *prox;
    struct no *ant;
} No;

typedef struct lista {
    No *comeco;
    No *fim;
} Lista;

void inicializar(Lista *lista) {
    lista->comeco = NULL;
    lista->fim = NULL;
}

int isEmpty(Lista *lista) {
    if (lista->comeco == NULL && lista->fim == NULL)
        return 1;
    else
        return 0;
}

void adicionar_nova_musica(Lista *lista, char nomeM[TAM], char nomeA[TAM], float numero) {
    No *novoNo = (No *)malloc(sizeof(No));

    strcpy(novoNo->musica.nome, nomeM);
    strcpy(novoNo->musica.artista, nomeA);
    novoNo->musica.duracao = numero;

    if (isEmpty(lista) == 1) {
        lista->comeco = novoNo;
        lista->fim = novoNo;
        novoNo->prox = lista->fim;
        novoNo->ant = lista->comeco;
    } else {
        lista->fim->prox = novoNo;
        novoNo->ant = lista->fim;
        novoNo->prox = lista->comeco;
        lista->fim = lista->fim->prox;
    }
}

void remover_inicio(Lista *lista) {
    No *aux;
    aux = lista->comeco;
    lista->comeco->prox->ant = lista->fim;
    lista->comeco = lista->comeco->prox;
    lista->fim->prox = lista->comeco;
    free(aux);
}

void remover_fim(Lista *lista) {
    No *aux;
    aux = lista->fim;
    lista->fim->ant->prox = NULL;
    lista->fim = lista->fim->ant;
    free(aux);
}

void remover_musica(Lista *lista, char *nome) {
    No *temp;
    temp = lista->comeco;

    while (strcmp(nome, temp->musica.nome) != 0) {
        temp = temp->prox;
    }
    if (lista->comeco == temp) {
        remover_inicio(lista);
    } else if (lista->fim == temp) {
        remover_fim(lista);
    } else {
        temp->prox->ant = temp->ant;
        temp->ant->prox = temp->prox;
        free(temp);
    }
    printf("Musica removida!\n");
}

void visualizar_todas_musicas(Lista lista) {
    if (isEmpty(&lista)) {
        printf("A playlist esta vazia.\n");
        return;
    }

    No *temp = lista.comeco;

    do {
        printf("Nome: %s\n", temp->musica.nome);
        printf("Artista: %s\n", temp->musica.artista);
        printf("Duracao: %.2f\n\n", temp->musica.duracao);
        temp = temp->prox;
    } while (temp != lista.comeco);
}

int contar_musicas(Lista *lista) {
    int valor = 0;
    No *temp;
    temp = lista->comeco;

    if (isEmpty(lista) == 1) {
        return 0;
    }

    do {
        temp = temp->prox;
        valor++;
    } while (temp != lista->comeco);

    return valor;
}

void procurar_musica(Lista lista, char *titulo) {
    No *temp;
    temp = lista.comeco;

    do {
        if (strcmp(temp->musica.nome, titulo) == 0) {
            printf("Musica: %s foi encontrada e esta na playlist!\n", temp->musica.nome);
            return;
        }
        temp = temp->prox;
    } while (temp != lista.comeco);

    printf("Musica: %s nao encontrada!\n", titulo);
}

void print_menu() {
    printf("\nEscolha uma das opcoes: \n 1. Adicionar musicas\n 2. Remover uma musica pelo titulo\n 3. Visualizar toda playlist\n 4. Limpar a playlist\n 5. Pesquisar musica por titulo\n 6. Contar o total de musicas\n 0. Sair do programa\n");
}

void limpar_lista_musicas(Lista *lista) {
    if (isEmpty(lista) == 1) {
        printf("Playlist ja esta vazia!\n");
    }

    No *temp;
    No *prox_no;

    temp = lista->comeco;

    do {
        prox_no = temp->prox;
        free(temp);
        temp = prox_no;
    } while (temp != lista->comeco);

    lista->comeco = NULL;
    lista->fim = NULL;
    printf("Pronto!\n Sua playlist esta vazia.\n");
}

int validar_texto(char *verifica) {
    return strlen(verifica) > 0 && strlen(verifica) < TAM;
}

int main() {
    Lista lista;
    int opcao = 0;
    char titulo[TAM], artista[TAM];
    float duracao;

    inicializar(&lista);

    do {
        print_menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1:
            do {
                printf("Informe o titulo da musica: \n");
                fgets(titulo, TAM, stdin);
                titulo[strlen(titulo) - 1] = '\0';

                if (!validar_texto(titulo)) {
                    printf("Titulo invalido! Tente novamente.\n");
                }
            } while (!validar_texto(titulo));

            do {
                printf("Informe o artista: \n");
                fgets(artista, TAM, stdin);
                artista[strlen(artista) - 1] = '\0'; 

                if (!validar_texto(artista)) {
                    printf("Artista invalido! Tente novamente.\n");
                }
            } while (!validar_texto(artista));

            printf("Informe a duracao da musica: \n");
            scanf("%f", &duracao);
            getchar();

            adicionar_nova_musica(&lista, titulo, artista, duracao);
            break;

        case 2:
            do{
                printf("Informe o titulo da musica que deseja remover: \n");
                fgets(titulo, TAM, stdin);
                titulo[strlen(titulo) - 1] = '\0';
            }while(!validar_texto(titulo));

            remover_musica(&lista, titulo);
            break;

        case 3:
            visualizar_todas_musicas(lista);
            break;

        case 4:
            limpar_lista_musicas(&lista);
            break;

        case 5:
            do{
                printf("Informe o titulo da musica que deseja procurar: \n");
                fgets(titulo, TAM, stdin);
                titulo[strlen(titulo) - 1] = '\0';
            }while(!validar_texto(titulo));

            procurar_musica(lista, titulo);
            break;

        case 6:
            printf("A playlist atualmente tem %d musicas\n", contar_musicas(&lista));
            break;
        case 0: 
            printf("Fim de programa! \n");
            break;
        default: printf("Opcao invalida! \n");
        }

    } while (opcao != 0);

    return 0;
}
