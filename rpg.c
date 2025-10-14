#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// --- ESTRUTURAS DE DADOS ---

typedef struct {
    char nome[50];
    char descricao[150];
} Item;

typedef struct {
    char nome[50];
    int saude;
    int saudeMaxima;
    int defesa;
    Item inventario[10];
    int totalItens;
} Jogador;

typedef struct {
    char nome[50];
    int saude;
    int dano;
} Monstro;

// --- VARIÁVEIS GLOBAIS ---
Jogador jogador;
Monstro esqueletoGuarda;

// --- DECLARAÇÕES ANTECIPADAS DE FUNÇÕES ---
void cena3();
void cenaFinal(int vitoria);

// --- FUNÇÕES AUXILIARES ---

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void aguardarEnter() {
    printf("\nPressione Enter para continuar...");
    // Limpa o buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

void getInput(char* buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        for (int i = 0; buffer[i]; i++) {
            buffer[i] = tolower(buffer[i]);
        }
    }
}

void addItemAoInventario(const char* nome, const char* descricao) {
    if (jogador.totalItens < 10) {
        strcpy(jogador.inventario[jogador.totalItens].nome, nome);
        strcpy(jogador.inventario[jogador.totalItens].descricao, descricao);
        jogador.totalItens++;
        printf("\n>> %s foi adicionado ao seu inventario!\n", nome);
    } else {
        printf("\n>> Seu inventario esta cheio!\n");
    }
}

int temItem(const char* nomeItem) {
    for (int i = 0; i < jogador.totalItens; i++) {
        if (strcmp(jogador.inventario[i].nome, nomeItem) == 0) {
            return 1;
        }
    }
    return 0;
}

// NOVO: Remove um item consumível do inventário
void removerItem(const char* nomeItem) {
    int encontrado = 0;
    for (int i = 0; i < jogador.totalItens; i++) {
        if (strcmp(jogador.inventario[i].nome, nomeItem) == 0) {
            encontrado = 1;
            // Move todos os itens subsequentes uma posição para trás
            for (int j = i; j < jogador.totalItens - 1; j++) {
                jogador.inventario[j] = jogador.inventario[j + 1];
            }
            jogador.totalItens--;
            printf("\n>> Voce usou %s.\n", nomeItem);
            break; // Sai do loop após remover o primeiro item encontrado
        }
    }
}

// --- FUNÇÕES DE CENAS E LÓGICA DO JOGO ---

void iniciarCombate() {
    limparTela();
    printf("--- COMBATE INICIADO ---\n\n");
    printf("Voce enfrenta o %s!\n", esqueletoGuarda.nome);

    while (jogador.saude > 0 && esqueletoGuarda.saude > 0) {
        printf("\n--- SEU TURNO ---\n");
        printf("Sua Saude: %d/%d HP | Sua Defesa: %d\n", jogador.saude, jogador.saudeMaxima, jogador.defesa);
        printf("Saude do %s: %d HP\n", esqueletoGuarda.nome, esqueletoGuarda.saude);
        
        printf("\nO que voce faz? (atacar / item / fugir)\n> ");
        char escolha[20];
        getInput(escolha, 20);

        if (strcmp(escolha, "atacar") == 0) {
            int danoCausado = (rand() % 10) + 5;
            esqueletoGuarda.saude -= danoCausado;
            printf("\nVoce ataca o esqueleto e causa %d de dano!\n", danoCausado);
        } else if (strcmp(escolha, "item") == 0) {
            if (temItem("Pocao de Cura")) {
                printf("\nVoce bebe a Pocao de Cura e recupera 40 de saude!\n");
                jogador.saude += 40;
                if (jogador.saude > jogador.saudeMaxima) {
                    jogador.saude = jogador.saudeMaxima;
                }
                removerItem("Pocao de Cura");
            } else {
                printf("\nVoce nao tem itens de cura para usar!\n");
            }
        } else if (strcmp(escolha, "fugir") == 0) {
            printf("\nVoce tenta fugir, mas o guardiao bloqueia o caminho! Nao ha escapatoria!\n");
        } else {
            printf("\nOpcao invalida. Voce perde tempo!\n");
        }

        if (esqueletoGuarda.saude <= 0) {
            printf("O %s foi derrotado!\n", esqueletoGuarda.nome);
            aguardarEnter();
            cenaFinal(1);
            return;
        }

        printf("\n--- TURNO DO GUARDIÃO ---\n");
        int danoBruto = (rand() % esqueletoGuarda.dano) + 5;
        int danoRecebido = danoBruto - jogador.defesa;
        if (danoRecebido < 0) danoRecebido = 0; // Defesa não pode curar

        jogador.saude -= danoRecebido;
        printf("O %s ataca! ", esqueletoGuarda.nome);
        if (jogador.defesa > 0) {
            printf("Sua armadura absorve %d de dano! ", jogador.defesa);
        }
        printf("Voce recebe %d de dano!\n", danoRecebido);
        aguardarEnter();
        limparTela();
    }

    if (jogador.saude <= 0) {
        cenaFinal(0);
    }
}

// NOVA CENA: Cripta da Armadura
void cena_cripta_armadura() {
    limparTela();
    printf("Apos a ponte, o caminho leva a uma pequena cripta. Um sarcofago de pedra esta no centro.\n");
    printf("A tampa esta levemente deslocada, convidando a curiosidade.\n");

    printf("\nO que voce faz? (abrir / ignorar)\n> ");
    char escolha[20];
    getInput(escolha, 20);

    if (strcmp(escolha, "abrir") == 0) {
        printf("\nCom esforco, voce empurra a tampa. Dentro, junto aos ossos de um antigo guerreiro,\n");
        printf("esta um peitoral de couro endurecido, ainda em bom estado.\n");
        addItemAoInventario("Peitoral de Couro", "Aumenta a defesa em 5 pontos.");
        jogador.defesa = 5; // Aumenta a defesa do jogador
    } else {
        printf("\nVoce decide que e melhor nao perturbar o descanso dos mortos e continua seu caminho.\n");
    }
    aguardarEnter();
    cena3();
}

// NOVA CENA: Laboratório da Poção
void cena_laboratorio_pocao() {
    limparTela();
    printf("O corredor o leva a uma sala pequena que parece ter sido um laboratorio de alquimista.\n");
    printf("Frascos quebrados cobrem o chao. Em uma mesa de pedra, uma bolsa de couro esta intacta.\n");

    printf("\nO que voce faz? (inspecionar / ignorar)\n> ");
    char escolha[20];
    getInput(escolha, 20);

    if (strcmp(escolha, "inspecionar") == 0) {
        printf("\nVoce abre a bolsa com cuidado. Dentro, encontra um frasco com um liquido vermelho cintilante.\n");
        printf("Parece ser uma pocao de cura.\n");
        addItemAoInventario("Pocao de Cura", "Restaura 40 pontos de saude.");
    } else {
        printf("\nVoce teme que os frascos possam conter venenos e decide nao arriscar, seguindo em frente.\n");
    }
    aguardarEnter();
    cena3();
}

void cena2B_armadilha() {
    limparTela();
    printf("Voce caminha em direcao ao brilho. E uma unica moeda de ouro no chao.\n");
    
    printf("\nO que voce faz? (pegar / ignorar)\n> ");
    char escolha[20];
    getInput(escolha, 20);

    if (strcmp(escolha, "pegar") == 0) {
        printf("\nE uma armadilha! Dardos sao disparados das paredes.\n");
        printf("Voce se esquiva, mas um deles o atinge de raspao. Voce perde 20 de saude!\n");
        jogador.saude -= 20;
        addItemAoInventario("Moeda de Ouro", "Uma moeda de ouro brilhante e pesada.");
        aguardarEnter();
        cena_laboratorio_pocao(); // Leva para a cena da poção
    } else {
        printf("\nSua intuicao diz que algo esta errado. Voce passa ao largo da moeda e continua.\n");
        aguardarEnter();
        cena_laboratorio_pocao(); // Leva para a cena da poção
    }
}

void cena2A_ponte() {
    limparTela();
    printf("Voce segue pelo corredor e chega a uma caverna com um rio subterraneo.\n");
    printf("Uma ponte de madeira velha e precaria e a unica forma de atravessar.\n");

    printf("\nComo voce atravessa? (correndo / cuidado)\n> ");
    char escolha[20];
    getInput(escolha, 20);

    if (strcmp(escolha, "correndo") == 0) {
        printf("\nNa pressa, voce pisa em uma tabua podre! Voce escorrega e torce o tornozelo.\n");
        printf("Voce consegue atravessar, mas a dor lhe custa 10 de saude.\n");
        jogador.saude -= 10;
        aguardarEnter();
        cena_cripta_armadura(); // Leva para a cena da armadura
    } else {
        printf("\nVoce testa cada tabua antes de pisar. Lentamente, voce chega ao outro lado.\n");
        aguardarEnter();
        cena_cripta_armadura(); // Leva para a cena da armadura
    }
}

void cena1_inicio() {
    limparTela();
    printf("Voce entra nas Catacumbas do Rei Esquecido. A porta se fecha atras de voce.\n\n");
    printf("A luz da sua tocha revela um corredor que se divide:\n");
    printf("  - A sua ESQUERDA, o caminho e umido e voce ouve agua corrente.\n");
    printf("  - A sua DIREITA, o ar e seco e voce ve algo brilhando a distancia.\n");

    printf("\nPara qual lado voce vai? (esquerda / direita)\n> ");
    
    char escolha[20];
    getInput(escolha, 20);

    if (strcmp(escolha, "esquerda") == 0) {
        cena2A_ponte();
    } else if (strcmp(escolha, "direita") == 0) {
        cena2B_armadilha();
    } else {
        printf("Opcao invalida. A indecisao pode ser perigosa. Tente novamente.\n");
        aguardarEnter();
        cena1_inicio();
    }
}

// As cenas 3 e Final permanecem muito similares
void cena3() {
    limparTela();
    printf("Finalmente, voce chega a uma camara magnifica: a sala do trono.\n");
    printf("No centro, o esqueleto do antigo rei esta sentado, usando a Coroa de Prata.\n\n");
    printf("Ao se aproximar, o esqueleto se ergue, com uma luz azul em seus olhos.\n");
    printf("Ele e o guardiao da coroa.\n");
    
    printf("\nO que voce faz? (lutar / enganar)\n> ");
    char escolha[20];
    getInput(escolha, 20);

    if (strcmp(escolha, "lutar") == 0) {
        iniciarCombate();
    } else if (strcmp(escolha, "enganar") == 0) {
        if (temItem("Moeda de Ouro")) {
            printf("\nVoce joga a moeda de ouro para o canto. Distraido pelo brilho,\n");
            printf("o esqueleto se vira. Essa e sua chance! Voce pega a coroa e foge!\n");
            aguardarEnter();
            cenaFinal(1);
        } else {
            printf("\nVoce nao tem nada para distrair o guardiao. Ele avanca!\n");
            aguardarEnter();
            iniciarCombate();
        }
    } else {
        printf("Opcao invalida. O guardiao nao espera!\n");
        aguardarEnter();
        iniciarCombate();
    }
}

void cenaFinal(int vitoria) {
    limparTela();
    if (vitoria) {
        printf("Com a Coroa do Rei Esquecido em maos, uma parede secreta se abre.\n");
        printf("\nParabens, %s! Voce escapou das catacumbas com seu premio!\n", jogador.nome);
        printf("\n--- FIM ---\n");
    } else {
        printf("\nSua saude chegou a zero...\n");
        printf("Sua aventura termina aqui, nas profundezas silenciosas das Catacumbas.\n");
        printf("\n--- FIM DE JOGO ---\n");
    }
}

void iniciarJogo() {
    srand(time(NULL));

    // Configura o jogador
    jogador.saude = 100;
    jogador.saudeMaxima = 100;
    jogador.defesa = 0;
    jogador.totalItens = 0;
    
    // Configura o monstro
    strcpy(esqueletoGuarda.nome, "Esqueleto Guardiao");
    esqueletoGuarda.saude = 80;
    esqueletoGuarda.dano = 15;

    limparTela();
    printf("Qual o nome do seu aventureiro?\n> ");
    getInput(jogador.nome, 50);

    printf("\nBem-vindo(a), %s, as Catacumbas do Rei Esquecido!\n", jogador.nome);
    
    aguardarEnter();
    cena1_inicio();
}

int main() {
    iniciarJogo();
    return 0;
}