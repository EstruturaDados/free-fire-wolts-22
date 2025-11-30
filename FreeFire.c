#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Necessário para medir o tempo de execucao (clock())

#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20

// --- 1. DEFINICAO DA STRUCT COMPONENTE ---
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade; // De 1 (baixa) a 10 (alta)
} Componente;

// Vetor estatico para armazenar os componentes
Componente torreFuga[MAX_COMPONENTES];
int contadorComponentes = 0; // Quantidade atual de componentes cadastrados

// Contadores globais para medição de desempenho
long long comparacoesOrdenacao = 0;
long long comparacoesBusca = 0;

// Prototipos das funcoes obrigatórias
void menuPrincipal();
void cadastrarComponente();
void mostrarComponentes();
void bubbleSortNome();
void insertionSortTipo();
void selectionSortPrioridade();
void buscaBinariaPorNome();

// Funcao auxiliar para medir tempo de execucao
typedef void (*FuncOrdenacao)();
void medirTempoEExecutar(FuncOrdenacao func, const char* nome_algoritmo);


int main() {
    menuPrincipal();
    return 0;
}

/**
 * @brief Menu principal interativo do sistema.
 */
void menuPrincipal() {
    int opcao;
    do {
        printf("\n=== Modulo Avancado da Torre de Fuga (Componentes: %d/%d) ===\n", contadorComponentes, MAX_COMPONENTES);
        printf("1. Cadastrar novo componente\n");
        printf("2. Visualizar todos os componentes\n");
        printf("3. Ordenar por Nome (Bubble Sort) e medir desempenho\n");
        printf("4. Ordenar por Tipo (Insertion Sort) e medir desempenho\n");
        printf("5. Ordenar por Prioridade (Selection Sort) e medir desempenho\n");
        printf("6. Buscar Componente-Chave (Busca Binaria - Requer ordenacao por nome!)\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n'); // Limpa buffer

        switch (opcao) {
            case 1: cadastrarComponente(); break;
            case 2: mostrarComponentes(); break;
            case 3: medirTempoEExecutar(bubbleSortNome, "Bubble Sort (Nome)"); break;
            case 4: medirTempoEExecutar(insertionSortTipo, "Insertion Sort (Tipo)"); break;
            case 5: medirTempoEExecutar(selectionSortPrioridade, "Selection Sort (Prioridade)"); break;
            case 6: buscaBinariaPorNome(); break;
            case 7: printf("Plano de fuga encerrado.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 7);
}

/**
 * @brief Cadastra um novo componente na lista.
 */
void cadastrarComponente() {
    if (contadorComponentes >= MAX_COMPONENTES) {
        printf("ERRO: Limite de componentes (%d) atingido.\n", MAX_COMPONENTES);
        return;
    }

    printf("\nCadastro de Componente %d:\n", contadorComponentes + 1);
    printf("Nome (ex: chip central): ");
    fgets(torreFuga[contadorComponentes].nome, TAM_NOME, stdin);
    torreFuga[contadorComponentes].nome[strcspn(torreFuga[contadorComponentes].nome, "\n")] = 0;

    printf("Tipo (ex: controle, suporte, propulsao): ");
    fgets(torreFuga[contadorComponentes].tipo, TAM_TIPO, stdin);
    torreFuga[contadorComponentes].tipo[strcspn(torreFuga[contadorComponentes].tipo, "\n")] = 0;

    // Garante que a prioridade esteja entre 1 e 10
    do {
        printf("Prioridade (1 a 10): ");
        scanf("%d", &torreFuga[contadorComponentes].prioridade);
        while (getchar() != '\n');
    } while (torreFuga[contadorComponentes].prioridade < 1 || torreFuga[contadorComponentes].prioridade > 10);


    contadorComponentes++;
    printf("SUCESSO: Componente cadastrado.\n");
}

/**
 * @brief Exibe todos os componentes em formato de tabela.
 */
void mostrarComponentes() {
    printf("\n--- Componentes da Torre de Fuga ---\n");
    printf("| %-25s | %-15s | %-10s |\n", "Nome do Componente", "Tipo", "Prioridade");
    printf("|---------------------------|-----------------|--------------|\n");
    if (contadorComponentes == 0) {
        printf("| %-57s |\n", "Nenhum componente cadastrado.");
    }
    for (int i = 0; i < contadorComponentes; i++) {
        printf("| %-25s | %-15s | %-10d |\n",
               torreFuga[i].nome,
               torreFuga[i].tipo,
               torreFuga[i].prioridade);
    }
    printf("-----------------------------------------------------------\n");
}

/**
 * @brief Funcao auxiliar que mede o tempo de execucao de um algoritmo de ordenacao.
 * @param func Ponteiro para a funcao de ordenacao a ser executada.
 * @param nome_algoritmo O nome do algoritmo para display.
 */
void medirTempoEExecutar(FuncOrdenacao func, const char* nome_algoritmo) {
    if (contadorComponentes == 0) {
        printf("Cadastre componentes primeiro.\n");
        return;
    }
    clock_t inicio, fim;
    double tempo_cpu;

    comparacoesOrdenacao = 0; // Reseta o contador global
    inicio = clock();
    
    // Executa a função de ordenação passada como parâmetro
    func(); 
    
    fim = clock();
    tempo_cpu = ((double) (fim - inicio)) / CLOCKS_PER_SEC;

    printf("\n--- Desempenho da Ordenacao ---\n");
    printf("Algoritmo usado: %s\n", nome_algoritmo);
    printf("Tempo de execucao: %.4f segundos\n", tempo_cpu);
    printf("Total de comparacoes realizadas: %lld\n", comparacoesOrdenacao);
    mostrarComponentes();
}


// --- IMPLEMENTACAO DOS ALGORITMOS DE ORDENACAO ---

/**
 * @brief Ordena os componentes por NOME usando Bubble Sort.
 */
void bubbleSortNome() {
    int i, j;
    Componente temp;
    for (i = 0; i < contadorComponentes - 1; i++) {
        for (j = 0; j < contadorComponentes - i - 1; j++) {
            // Compara os nomes (case-insensitive)
            comparacoesOrdenacao++; // Conta a comparacao principal
            if (strcasecmp(torreFuga[j].nome, torreFuga[j+1].nome) > 0) {
                // Swap (troca) dos elementos
                temp = torreFuga[j];
                torreFuga[j] = torreFuga[j+1];
                torreFuga[j+1] = temp;
            }
        }
    }
}

/**
 * @brief Ordena os componentes por TIPO usando Insertion Sort.
 */
void insertionSortTipo() {
    int i, j;
    Componente chave;
    for (i = 1; i < contadorComponentes; i++) {
        chave = torreFuga[i];
        j = i - 1;

        /* Move os elementos de torreFuga[0..i-1], que são maiores que a chave (por tipo), 
           para uma posição à frente de sua posição atual */
        while (j >= 0 && strcasecmp(torreFuga[j].tipo, chave.tipo) > 0) {
            comparacoesOrdenacao++; // Conta a comparação dentro do while
            torreFuga[j + 1] = torreFuga[j];
            j = j - 1;
        }
        // Se o while loop foi executado pelo menos uma vez, a última comparação já foi contada.
        if (j >= 0) comparacoesOrdenacao++; // Contabiliza a última comparação que falhou na condição while
        
        torreFuga[j + 1] = chave;
    }
}

/**
 * @brief Ordena os componentes por PRIORIDADE (inteiro) usando Selection Sort.
 */
void selectionSortPrioridade() {
    int i, j, indice_minimo;
    Componente temp;

    for (i = 0; i < contadorComponentes - 1; i++) {
        indice_minimo = i;
        for (j = i + 1; j < contadorComponentes; j++) {
            comparacoesOrdenacao++; // Contabiliza cada comparação
            if (torreFuga[j].prioridade < torreFuga[indice_minimo].prioridade) {
                indice_minimo = j;
            }
        }
        // Troca o elemento mínimo encontrado com o primeiro elemento
        temp = torreFuga[indice_minimo];
        torreFuga[indice_minimo] = torreFuga[i];
        torreFuga[i] = temp;
    }
}

/**
 * @brief Realiza uma busca binária por nome. Requer que o vetor esteja ordenado por nome ANTES.
 */
void buscaBinariaPorNome() {
    char nome_busca[TAM_NOME];
    printf("Digite o NOME do componente-chave para a busca binaria: ");
    fgets(nome_busca, TAM_NOME, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;
    
    // Assume que o usuário ordenou o vetor anteriormente, senão a busca binária pode falhar.
    
    int esquerda = 0, direita = contadorComponentes - 1;
    int encontrado = 0;
    comparacoesBusca = 0;
    int meio = -1;
    
    printf("\nIniciando busca binaria...\n");

    while (esquerda <= direita) {
        comparacoesBusca++;
        meio = esquerda + (direita - esquerda) / 2;
        
        // strcasecmp retorna 0 se forem iguais
        int resultadoComparacao = strcasecmp(torreFuga[meio].nome, nome_busca);
        
        if (resultadoComparacao == 0) {
            encontrado = 1;
            break;
        } else if (resultadoComparacao < 0) {
            esquerda = meio + 1; // Ignora a metade esquerda
        } else {
            direita = meio - 1; // Ignora a metade direita
        }
    }
    
    printf("\n--- Resultado da Busca Binaria ---\n");
    if (encontrado) {
        printf("SUCESSO! O componente-chave foi localizado:\n");
        printf("  Nome:     %s\n", torreFuga[meio].nome);
        printf("  Tipo:     %s\n", torreFuga[meio].tipo);
        printf("  Prioridade: %d\n", torreFuga[meio].prioridade);
    } else {
        printf("FALHA: Componente '%s' nao encontrado. Verifique se o vetor foi ordenado por nome!\n", nome_busca);
    }
    printf("Total de comparacoes na busca binaria: %lld\n", comparacoesBusca);
}
