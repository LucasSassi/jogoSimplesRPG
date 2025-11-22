# ⚔️ Rush RPG

**Rush RPG** é um jogo de aventura e estratégia em turnos desenvolvido em linguagem **C** utilizando a biblioteca **Raylib**. O jogador deve atravessar diferentes estágios, fazendo escolhas estratégicas de itens para se preparar para a batalha final contra o Chefe.

## 🎮 Como Jogar

O jogo é dividido em duas fases principais:

### 1\. Exploração (Fases 1 a 4)

Você controla o herói e deve caminhar até uma das duas portas disponíveis. Cada porta oferece um item diferente que será guardado no seu inventário (máximo de **4 itens**).

  * **Objetivo:** Escolher os itens que melhor se adaptam à sua estratégia (Cura, Dano, Defesa ou Sorte).

### 2\. Batalha (Fase Final)

Você enfrenta o Chefe usando os itens coletados durante a exploração. O combate é por turnos.

  * **Ataque:** Causa dano ao chefe (o dano aumenta se você pegou a Espada).
  * **Itens disponíveis:**
      * 🧪 **Poção:** Recupera vida.
      * 💣 **Bomba:** Causa dano massivo.
      * ⚔️ **Espada:** Passiva. Aumenta o dano dos seus ataques básicos.
      * 🛡️ **Armadura:** Passiva. Reduz o dano recebido do chefe.
      * 💰 **Moeda:** Tem **50% de chance** de distrair o chefe para você fugir (vitória imediata) ou falhar e perder o turno.

-----

## ⌨️ Controles

| Tecla | Ação | Contexto |
| :--- | :--- | :--- |
| **Setas / A e D** | Mover personagem | Exploração |
| **Setas / A e D** | Selecionar Item | Batalha |
| **Enter** | Entrar na Porta / Confirmar | Exploração / Menu |
| **Enter** | Usar Item Selecionado | Batalha |
| **A** | Atacar o Chefe | Batalha |

-----

## 📂 Estrutura de Arquivos

Para o jogo funcionar com os gráficos, certifique-se de que a pasta `assets` esteja no mesmo diretório do executável.

```plaintext
seu_projeto/
│
├── main.c              # O código fonte do jogo (ou rpc.c)
├── rush_rpg (ou .exe)  # O executável gerado
│
└── assets/             # Pasta de imagens (Opcional, mas recomendada)
    ├── boss_player/
    │   ├── player.png
    │   └── boss.png
    ├── cenarios/
    │   ├── title_bg.png
    │   ├── battle_bg.png
    │   └── cenario1.png
    │   └── ...
    ├── boss_attack.png
    ├── player_attack.png
    ├── boss_hit.png
    └── player_hit.png
```

-----

## 🚀 Como rodar

### 🐧 Linux (Ubuntu/Debian)

**1. Instalar Dependências**
Abra o terminal e instale o compilador GCC e a biblioteca Raylib:

```bash
sudo apt update
sudo apt install build-essential git libraylib-dev
```

**2. Compilar**
Navegue até a pasta do arquivo fonte (`rpg.c`) e execute:

```bash
gcc rpg.c -lraylib -lGL -lm -lpthread -ldl -rt -Xlinker -zmuldefs -o rush_rpg
```

**3. Executar**

```bash
./rush_rpg
```

### 🪟 Windows

Existem várias formas, mas a mais fácil é usando o kit de desenvolvimento `w64devkit` ou instalando o compilador MinGW.

**Opção 1: Usando o Notepad++ com Raylib (Recomendado para iniciantes)**

1.  Baixe o instalador do Raylib para Windows no site oficial ou GitHub.
2.  A instalação inclui um compilador pré-configurado (geralmente em `C:/raylib/w64devkit`).
3.  Abra o `rpg.c` no Notepad++ (incluso no pacote) e pressione **F6** para compilar e rodar.

**Opção 2: Compilando via Linha de Comando (MinGW)**
Se você já tem o GCC (MinGW) instalado e a biblioteca Raylib baixada:

1.  Certifique-se de que os arquivos de cabeçalho (`raylib.h`) e as bibliotecas (`libraylib.a`) estão acessíveis.
2.  Execute o comando (ajuste os caminhos conforme sua instalação):

<!-- end list -->

```cmd
gcc main.c -o rush_rpg.exe -O2 -I C:/caminho/para/raylib/include -L C:/caminho/para/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
```

3.  Execute o arquivo `rush_rpg.exe` criado.

-----

## 👥 Créditos

Desenvolvido por:

  * **Lucas Del Pozo**
  * **Lucas Sassi de Souza**
  * **Eduardo Parize**
  * **Vinicius Ribas Bida**