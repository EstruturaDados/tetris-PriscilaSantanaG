#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 5

typedef struct {
    char nome;      // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;         // ID único da peça
} Peca;

typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// Gerar uma peça aleatória
Peca gerarPeca(int idProximo) {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    novaPeca.nome = tipos[rand() % 4];
    novaPeca.id = idProximo;
    return novaPeca;
}

// Inicializar a fila com 5 peças
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
    
    printf("\n=== Inicializando fila com 5 peças ===\n");
    for (int i = 0; i < MAX; i++) {
        Peca p = gerarPeca(i + 1);
        f->itens[f->fim] = p;
        f->fim = (f->fim + 1) % MAX;
        f->total++;
        printf("Peça %d adicionada: %c (ID: %d)\n", i + 1, p.nome, p.id);
    }
}

// Verificar se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Verificar se a fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Remover uma peça da frente (dequeue)
Peca removerPeca(Fila *f) {
    Peca vazia = {'X', -1};
    
    if (filaVazia(f)) {
        printf("\n Erro: Fila vazia! Não há peças para remover.\n");
        return vazia;
    }
    
    Peca removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    
    printf("\n Peça removida: %c (ID: %d)\n", removida.nome, removida.id);
    return removida;
}

// Inserir uma nova peça no final (enqueue)
void inserirPeca(Fila *f, int proximoId) {
    if (filaCheia(f)) {
        printf("\n Erro: Fila cheia! Não é possível inserir mais peças.\n");
        return;
    }
    
    Peca novaPeca = gerarPeca(proximoId);
    f->itens[f->fim] = novaPeca;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
    
    printf("\n✅ Nova peça inserida: %c (ID: %d)\n", novaPeca.nome, novaPeca.id);
}

// Visualizar o estado atual da fila
void visualizarFila(Fila *f) {
    printf("\n------------------------------------\n");
    printf("|     ESTADO ATUAL DA FILA (0 - 4)   |\n");
    printf("--------------------------------------\n");
    
    if (filaVazia(f)) {
        printf("❌ Fila vazia!\n");
        return;
    }
    
    printf("Total de peças: %d/%d\n\n", f->total, MAX);
    
    for (int i = 0; i < f->total; i++) {
        int posicao = (f->inicio + i) % MAX;
        printf("[Posição %d] Peça: %c | ID: %d\n", i, f->itens[posicao].nome, f->itens[posicao].id);
    }
    printf("\n");
}

// Limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Exibir o menu
void exibirMenu() {
    printf("\n-----------------------------------\n");
    printf("|   TETRIS STACK - FILA DE PEÇAS     |n");
    printf("|------------------------------------|\n");
    printf("| 1. Visualizar fila                 |\n");
    printf("| 2. Jogar peça (remover)            |\n");
    printf("| 3. Inserir nova peça               |\n");
    printf("| 4. Sair                            |\n");
    printf("|------------------------------------|\n");
    printf("Escolha uma opção: ");
}

// Programa principal
int main() {
    srand(time(NULL));
    Fila fila;
    int opcao;
    int proximoId = MAX + 1;
    char buffer[100];
    
    inicializarFila(&fila);
    visualizarFila(&fila);
    
    while (1) {
        exibirMenu();
        fflush(stdout);  // Garante que o prompt é exibido imediatamente
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\n Erro ao ler entrada!\n");
            continue;
        }
        
        if (sscanf(buffer, "%d", &opcao) != 1) {
            printf("\n Entrada inválida! Digite um número de 1 a 4.\n");
            continue;
        }
        
        switch (opcao) {
            case 1:
                visualizarFila(&fila);
                break;
            
            case 2:
                removerPeca(&fila);
                visualizarFila(&fila);
                break;
            
            case 3:
                if (filaCheia(&fila)) {
                    printf("\n Fila cheia! Remova uma peça antes de inserir.\n");
                } else {
                    inserirPeca(&fila, proximoId);
                    proximoId++;
                    visualizarFila(&fila);
                }
                break;
            
            case 4:
                printf("\nEncerrando programa tetris... Até logo!\n\n");
                return 0;
            
            default:
                printf("\n Opção inválida! Escolha entre 1 e 4.\n");
        }
    }
    
    return 0;
}
