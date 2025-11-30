#include <stdio.h>
#include <string.h>   // Necessário para strcpy, strcmp, strcspn
#include <stdlib.h>   // Incluído conforme solicitado (embora não seja estritamente necessário para este código específico)

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

// 1. Definição da struct Item conforme os requisitos
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO]; // Ex: arma, munição, cura, ferramenta
    int quantidade;
    int ocupado;         // Flag: 1 = item existe na posição, 0 = posição vazia
} Item;

// 2. Vetor de structs com capacidade para até 10 itens
Item mochila[MAX_ITENS];

// Protótipos das funções obrigatórias
void inicializarMochila();
void inserirItem();
void removerItem();
void listarItens();
// Implementação da busca sequencial solicitada
void buscarItem(); 

int main() {
    int opcao;
    // Inicializa o estado de todas as posições da mochila
    inicializarMochila();

    // Menu interativo usando do-while para garantir pelo menos uma execução
    do {
        printf("\n--- Sistema de Inventario (Mochila de Loot) ---\n");
        printf("O que voce deseja fazer?\n");
        printf("1. Inserir novo item na mochila\n");
        printf("2. Remover item pelo nome\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar item pelo nome (Busca Sequencial)\n");
        printf("5. Sair do jogo\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        // Limpa o buffer de entrada do teclado para evitar problemas com leituras futuras de string (fgets)
        while (getchar() != '\n'); 

        // Switch para gerenciar as opções do menu
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("Fechando inventario. Ate mais!\n");
                break;
            default:
                printf("Opcao invalida. Por favor, escolha um numero entre 1 e 5.\n");
        }
    } while (opcao != 5);

    return 0;
}

/**
 * @brief Inicializa todas as posições do vetor 'mochila' marcando-as como vazias.
 */
void inicializarMochila() {
    for (int i = 0; i < MAX_ITENS; i++) {
        mochila[i].ocupado = 0; // 0 indica que a posição está livre
    }
}

/**
 * @brief Encontra o primeiro índice vazio (nao ocupado) na mochila.
 * @return O índice disponível ou -1 se a mochila estiver cheia.
 */
int encontrarIndiceVazio() {
    for (int i = 0; i < MAX_ITENS; i++) {
        if (!mochila[i].ocupado) {
            return i;
        }
    }
    return -1; 
}

/**
 * @brief Encontra o índice de um item pelo nome usando busca sequencial.
 * @param nome_busca O nome do item a ser procurado.
 * @return O índice do item encontrado ou -1 se não for localizado.
 */
int encontrarIndicePorNome(const char* nome_busca) {
    for (int i = 0; i < MAX_ITENS; i++) {
        // strcasecmp compara strings ignorando maiúsculas/minúsculas para melhor usabilidade
        if (mochila[i].ocupado && strcasecmp(mochila[i].nome, nome_busca) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Permite ao jogador cadastrar um novo item na mochila.
 * Usa fgets para leitura segura de strings.
 */
void inserirItem() {
    int indice = encontrarIndiceVazio();

    if (indice == -1) {
        printf("ERRO: Mochila cheia! Capacidade maxima de %d itens atingida.\n", MAX_ITENS);
        return;
    }

    printf("\n--- Cadastro de Item ---\n");
    printf("Nome do item (ex: Rifle de Assalto): ");
    // Le a linha inteira, incluindo espacos, ate o \n
    fgets(mochila[indice].nome, TAM_NOME, stdin);
    // Remove a quebra de linha '\n' que o fgets adiciona no final
    mochila[indice].nome[strcspn(mochila[indice].nome, "\n")] = 0;

    printf("Tipo do item (ex: arma, municao, cura): ");
    fgets(mochila[indice].tipo, TAM_TIPO, stdin);
    mochila[indice].tipo[strcspn(mochila[indice].tipo, "\n")] = 0;

    printf("Quantidade coletada: ");
    scanf("%d", &mochila[indice].quantidade);
    while (getchar() != '\n'); // Limpa buffer após o scanf

    mochila[indice].ocupado = 1; // Marca a posição como ocupada
    printf("SUCESSO: Item '%s' adicionado a mochila!\n", mochila[indice].nome);
    listarItens(); // Lista os itens após a operação, conforme requisito
}

/**
 * @brief Remove um item da mochila buscando pelo nome informado pelo usuario.
 */
void removerItem() {
    char nome_busca[TAM_NOME];
    printf("\n--- Remocao de Item ---\n");
    printf("Digite o NOME exato do item a ser descartado: ");
    fgets(nome_busca, TAM_NOME, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    int indice = encontrarIndicePorNome(nome_busca);

    if (indice != -1) {
        // Para "remover" o item, basta marcar a posição como não ocupada/vazia
        mochila[indice].ocupado = 0; 
        printf("SUCESSO: Item '%s' descartado da mochila.\n", nome_busca);
        listarItens(); // Lista os itens após a operação, conforme requisito
    } else {
        printf("ERRO: Item '%s' nao encontrado na mochila. Verifique a ortografia.\n", nome_busca);
    }
}

/**
 * @brief Exibe todos os itens registrados na mochila em formato de tabela.
 */
void listarItens() {
    printf("\n--- Inventario Atual da Mochila ---\n");
    printf("| %-25s | %-15s | %-10s |\n", "Nome do Item", "Tipo", "Quantidade");
    printf("|---------------------------|-----------------|--------------|\n");
    
    int total_itens = 0;
    for (int i = 0; i < MAX_ITENS; i++) {
        // Itera sobre o vetor e imprime apenas as posições que estão ocupadas
        if (mochila[i].ocupado) {
            printf("| %-25s | %-15s | %-10d |\n", 
                   mochila[i].nome, 
                   mochila[i].tipo, 
                   mochila[i].quantidade);
            total_itens++;
        }
    }

    if (total_itens == 0) {
        printf("| %-57s |\n", "A mochila esta completamente vazia.");
    }
    printf("-----------------------------------------------------------\n");
}

/**
 * @brief Implementa a funcionalidade de busca sequencial. 
 * Solicita um nome ao usuário, busca na lista e exibe os detalhes se encontrado.
 */
void buscarItem() {
    char nome_busca[TAM_NOME];
    printf("\n--- Busca Sequencial de Item ---\n");
    printf("Digite o NOME do item que deseja localizar: ");
    fgets(nome_busca, TAM_NOME, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    int indice = encontrarIndicePorNome(nome_busca);

    if (indice != -1) {
        printf("\nITEM ENCONTRADO:\n");
        printf("  Nome:     %s\n", mochila[indice].nome);
        printf("  Tipo:     %s\n", mochila[indice].tipo);
        printf("  Qtde:     %d\n", mochila[indice].quantidade);
    } else {
        printf("RESULTADO: Item '%s' nao foi encontrado na mochila.\n", nome_busca);
    }
}
