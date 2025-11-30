c
#include <stdio.h>
#include <stdlib.h> // Para malloc e free (lista encadeada) e exit
#include <string.h> // Para strcpy, strcmp, strcasecmp, strcspn
#include <time.h>   // Para medir tempo, se necessario (requisito opcional)

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

// Global counters for search operations
long long comparacoesSequencial = 0;
long long comparacoesBinaria = 0;

// --- 1. DEFINICOES DE STRUCTS ---

// Struct Item: a carga de dados que ambas as estruturas usam
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Struct No: a estrutura para a Lista Encadeada
typedef struct No {
    Item dados;
    struct No* proximo; // Ponteiro para o próximo nó da lista
} No;

// --- SECAO 1: IMPLEMENTACAO USANDO VETOR (Lista Sequencial) ---

Item mochilaVetor[MAX_ITENS];
int contadorVetor = 0; // Controla quantos itens estão atualmente no vetor

// Prototipos das funcoes do Vetor
void inicializarVetor();
void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
void bubbleSortVetor();
void buscarSequencialVetor();
void buscarBinariaVetor();

// --- SECAO 2: IMPLEMENTACAO USANDO LISTA ENCADAEADA (Dinamica) ---

No* cabeca = NULL; // Ponteiro inicial (cabeça) da lista encadeada

// Prototipos das funcoes da Lista Encadeada
void inserirItemLista();
void removerItemLista();
void listarItensLista();
void buscarSequencialLista();

// --- FUNCOES PRINCIPAIS (Menus) ---

void menuVetor();
void menuListaEncadeada();

int main() {
    int opcaoMenuPrincipal;
    inicializarVetor(); // Inicializa o vetor antes de qualquer operacao

    do {
        printf("\n=======================================================\n");
        printf("  COMPARATIVO DE ESTRUTURAS DE DADOS (JOGO DE LOOT)  \n");
        printf("=======================================================\n");
        printf("Escolha a estrutura de dados que deseja testar:\n");
        printf("1. Mochila usando VETOR (Lista Sequencial)\n");
        printf("2. Mochila usando LISTA ENCADEDA (Dinamica)\n");
        printf("3. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcaoMenuPrincipal);
        while (getchar() != '\n'); // Limpa buffer

        switch (opcaoMenuPrincipal) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuListaEncadeada();
                break;
            case 3:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcaoMenuPrincipal != 3);

    return 0;
}

// Implementacao do menu secundario para o VETOR
void menuVetor() {
    int opcao;
    do {
        printf("\n--- Mochila VETOR (Capacidade Max: %d) ---\n", MAX_ITENS);
        printf("1. Inserir Item\n");
        printf("2. Remover Item por Nome\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Sequencial\n");
        printf("5. Ordenar Itens (para busca binaria)\n");
        printf("6. Buscar Binaria\n");
        printf("7. Voltar ao Menu Principal\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n'); // Limpa buffer

        switch (opcao) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: buscarSequencialVetor(); break;
            case 5: bubbleSortVetor(); break;
            case 6: buscarBinariaVetor(); break;
            case 7: printf("Retornando ao menu principal...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 7);
}

// Implementacao do menu secundario para a LISTA ENCADEDA
void menuListaEncadeada() {
    int opcao;
    do {
        printf("\n--- Mochila LISTA ENCADEDA (Dinamica) ---\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item por Nome\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Sequencial\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n'); // Limpa buffer

        switch (opcao) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4: buscarSequencialLista(); break;
            case 5: printf("Retornando ao menu principal...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 5);
}

// --- IMPLEMENTACOES DO VETOR ---

void inicializarVetor() {
    for (int i = 0; i < MAX_ITENS; i++) {
        // A flag 'ocupado' anterior foi substituída por um contador simples
        // Apenas zeramos o contador de itens validos.
    }
    contadorVetor = 0;
}

void inserirItemVetor() {
    if (contadorVetor >= MAX_ITENS) {
        printf("ERRO VETOR: Mochila cheia! Capacidade maxima de %d itens atingida.\n", MAX_ITENS);
        return;
    }

    printf("Nome do item (ex: Faca): ");
    fgets(mochilaVetor[contadorVetor].nome, TAM_NOME, stdin);
    mochilaVetor[contadorVetor].nome[strcspn(mochilaVetor[contadorVetor].nome, "\n")] = 0;

    printf("Tipo do item (ex: arma): ");
    fgets(mochilaVetor[contadorVetor].tipo, TAM_TIPO, stdin);
    mochilaVetor[contadorVetor].tipo[strcspn(mochilaVetor[contadorVetor].tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[contadorVetor].quantidade);
    while (getchar() != '\n'); // Limpa buffer

    contadorVetor++; // Incrementa o contador para o próximo item ir para a próxima posição
    printf("SUCESSO VETOR: Item adicionado na posicao %d.\n", contadorVetor - 1);
}

void removerItemVetor() {
    char nome_busca[TAM_NOME];
    printf("Digite o NOME do item a ser removido do vetor: ");
    fgets(nome_busca, TAM_NOME, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    int indice_encontrado = -1;
    for (int i = 0; i < contadorVetor; i++) {
        if (strcasecmp(mochilaVetor[i].nome, nome_busca) == 0) {
            indice_encontrado = i;
            break;
        }
    }

    if (indice_encontrado != -1) {
        // Move os elementos subsequentes uma posição para trás para preencher o "buraco"
        for (int i = indice_encontrado; i < contadorVetor - 1; i++) {
            mochilaVetor[i] = mochilaVetor[i+1];
        }
        contadorVetor--; // Reduz o número total de itens válidos
        printf("SUCESSO VETOR: Item '%s' removido.\n", nome_busca);
    } else {
        printf("ERRO VETOR: Item '%s' nao encontrado.\n", nome_busca);
    }
}

void listarItensVetor() {
    printf("\n--- Itens no VETOR (%d/%d ocupados) ---\n", contadorVetor, MAX_ITENS);
    printf("| %-25s | %-15s | %-10s |\n", "Nome do Item", "Tipo", "Quantidade");
    printf("|---------------------------|-----------------|--------------|\n");
    if (contadorVetor == 0) {
        printf("| %-57s |\n", "A mochila vetor esta vazia.");
    }
    for (int i = 0; i < contadorVetor; i++) {
        printf("| %-25s | %-15s | %-10d |\n", 
               mochilaVetor[i].nome, 
               mochilaVetor[i].tipo, 
               mochilaVetor[i].quantidade);
    }
    printf("-----------------------------------------------------------\n");
}

void bubbleSortVetor() {
    if (contadorVetor <= 1) {
        printf("Nao ha itens suficientes para ordenar.\n");
        return;
    }
    int i, j;
    Item temp;
    for (i = 0; i < contadorVetor - 1; i++) {
        for (j = 0; j < contadorVetor - i - 1; j++) {
            // Compara os nomes (strcmp retorna > 0 se o primeiro for lexicograficamente maior)
            if (strcasecmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0) {
                // Swap (troca) dos elementos
                temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = temp;
            }
        }
    }
    printf("VETOR ordenado com sucesso (Bubble Sort por nome).\n");
    listarItensVetor();
}

void buscarSequencialVetor() {
    char nome_busca[TAM_NOME];
    printf("Digite o NOME do item para busca sequencial no vetor: ");
    fgets(nome_busca, TAM_NOME, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    int indice_encontrado = -1;
    comparacoesSequencial = 0;
    
    for (int i = 0; i < contadorVetor; i++) {
        comparacoesSequencial++;
        if (strcasecmp(mochilaVetor[i].nome, nome_busca) == 0) {
            indice_encontrado = i;
            break;
        }
    }
    
    if (indice_encontrado != -1) {
        printf("\nITEM ENCONTRADO (Vetor): %s, Tipo: %s, Qtde: %d\n", 
               mochilaVetor[indice_encontrado].nome, mochilaVetor[indice_encontrado].tipo, mochilaVetor[indice_encontrado].quantidade);
    } else {
        printf("Item '%s' nao encontrado no vetor.\n", nome_busca);
    }
    printf("Contador de comparacoes na busca sequencial: %lld\n", comparacoesSequencial);
}


void buscarBinariaVetor() {
    char nome_busca[TAM_NOME];
    printf("Digite o NOME do item para busca BINARIA no vetor: ");
    fgets(nome_busca, TAM_NOME, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;
    
    // Assume que o usuário ordenou o vetor anteriormente, senão a busca binária falha.
    
    int esquerda = 0, direita = contadorVetor - 1;
    int encontrado = 0;
    comparacoesBinaria = 0;
    int meio;
    
    while (esquerda <= direita) {
        comparacoesBinaria++; // Contamos a comparação do while loop/cálculo do meio
        meio = esquerda + (direita - esquerda) / 2;
        
        // strcasecmp retorna 0 se forem iguais, < 0 se o primeiro for menor, > 0 se o primeiro for maior
        int resultadoComparacao = strcasecmp(mochilaVetor[meio].nome, nome_busca);
        
        if (resultadoComparacao == 0) {
            encontrado = 1;
            break;
        } else if (resultadoComparacao < 0) {
            esquerda = meio + 1; // Ignora a metade esquerda
        } else {
            direita = meio - 1; // Ignora a metade direita
        }
    }
    
    if (encontrado) {
        printf("\nITEM ENCONTRADO (Busca Binaria): %s, Tipo: %s, Qtde: %d\n", 
               mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
    } else {
        printf("Item '%s' nao encontrado (ou vetor nao estava ordenado corretamente).\n", nome_busca);
    }
    printf("Contador de comparacoes na busca binaria: %lld\n", comparacoesBinaria);
}


// --- IMPLEMENTACOES DA LISTA ENCADEDA ---

void inserirItemLista() {
    // Aloca memória para o novo nó
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("ERRO LISTA: Falha ao alocar memoria.\n");
        return;
    }

    printf("Nome do item (ex: Kit Medico): ");
    fgets(novoNo->dados.nome, TAM_NOME, stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = 0;

    printf("Tipo do item (ex: cura): ");
    fgets(novoNo->dados.tipo, TAM_TIPO, stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    while (getchar() != '\n'); // Limpa buffer

    // Inserção simples no início da lista (mais eficiente para listas encadeadas)
    novoNo->proximo = cabeca;
    cabeca = novoNo;

    printf("SUCESSO LISTA: Item '%s' adicionado dinamicamente.\n", novoNo->dados.nome);
}

void removerItemLista() {
    char nome_busca[TAM_NOME];
    printf("Digite o NOME do item a ser removido da lista encadeada: ");
    fgets(nome_busca, TAM_NOME, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    No* atual = cabeca;
    No* anterior = NULL;
    int encontrado = 0;

    while (atual != NULL) {
        if (strcasecmp(atual->dados.nome, nome_busca) == 0) {
            encontrado = 1;
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    if (encontrado) {
        if (anterior == NULL) {
            // Remove o primeiro elemento (a cabeça)
            cabeca = atual->proximo;
        } else {
            // Remove um elemento do meio ou do fim
            anterior->proximo = atual->proximo;
        }
        free(atual); // Libera a memória alocada para o nó removido
        printf("SUCESSO LISTA: Item '%s' removido.\n", nome_busca);
    } else {
        printf("ERRO LISTA: Item '%s' nao encontrado.\n", nome_busca);
    }
}

void listarItensLista() {
    printf("\n--- Itens na LISTA ENCADEDA ---\n");
    printf("| %-25s | %-15s | %-10s |\n", "Nome do Item", "Tipo", "Quantidade");
    printf("|---------------------------|-----------------|--------------|\n");

    No* atual = cabeca;
    int total_itens = 0;
    
    if (cabeca == NULL) {
         printf("| %-57s |\n", "A mochila dinamica esta vazia.");
    }
    
    while (atual != NULL) {
        printf("| %-25s | %-15s | %-10d |\n", 
               atual->dados.nome, 
               atual->dados.tipo, 
               atual->dados.quantidade);
        atual = atual->proximo;
        total_itens++;
    }
    printf("-----------------------------------------------------------\n");
    printf("Total de itens na lista: %d\n", total_itens);
}

void buscarSequencialLista() {
    char nome_busca[TAM_NOME];
    printf("Digite o NOME do item para busca sequencial na lista: ");
    fgets(nome_busca, TAM_NOME, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    No* atual = cabeca;
    int encontrado = 0;
    comparacoesSequencial = 0;

    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcasecmp(atual->dados.nome, nome_busca) == 0) {
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (encontrado) {
        printf("\nITEM ENCONTRADO (Lista): %s, Tipo: %s, Qtde: %d\n", 
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
    } else {
        printf("Item '%s' nao encontrado na lista encadeada.\n", nome_busca);
    }
     printf("Contador de comparacoes na busca sequencial: %lld\n", comparacoesSequencial);
}
Use o código com cuidado.




