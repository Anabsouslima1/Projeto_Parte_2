#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINHAS 20
#define COLUNAS 20
#define MAX_PALAVRAS 7
#define MAX_NOME 100
#define MAX_LINHA 150
#define grupo_animais 18

#define RESET "\033[0m"

// Códigos de Escape ANSI - CORES
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"

// Códigos de Escape ANSI - ESTILOS
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"

// SISTEMA DE PONTOS
int p1 = 0;
int p2 = 0;
int p3 = 0;

// PARA USO DO CÓDIGO BINÁRIO
typedef struct {
  char nome_jogador[50];
  int pontos;
} Registro;

void salvar_pontuacao(const char *nome, int pontos) {
  // Cria uma instância da estrutura Registro
  Registro registro;
  strncpy(registro.nome_jogador, nome, sizeof(registro.nome_jogador) - 1);
  registro.nome_jogador[sizeof(registro.nome_jogador) - 1] =
      '\0'; // Garante a terminação da string
  registro.pontos = pontos;

  // Abre o arquivo em modo binário para escrita
  FILE *arquivo =
      fopen("pontuacoes.bin", "ab"); // "ab" para adicionar ao final do arquivo
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  // Escreve os dados no arquivo antes de fechar
  fwrite(&registro, sizeof(Registro), 1, arquivo);
  fclose(arquivo);
}

void caixa_minigames(const char *mensagem) {
  printf(YELLOW "\t ===+-------------------------------------+===\n" RESET);
  printf("\t  %s\n", mensagem);
  printf(YELLOW "\t ===+-------------------------------------+===\n" RESET);
}

void tabulacao(const char *mensagem) { printf("\t %s \n", mensagem); }

void tabulacao_dupla(const char *mensagem) { printf("\t\t %s \n", mensagem); }

void tabulacao_tripla(const char *mensagem) {
  printf("\t\t\t %s \n", mensagem);
}

// PARA USO DO TXT
int gerar_novo_id() {
  FILE *arquivo = fopen("jogadores.txt", "r");
  if (arquivo == NULL) {
    return 1; // Retorna o ID 1 se o arquivo não existir
  }

  int ultimo_id = 0;
  char linha[MAX_LINHA];

  // Ler cada linha e encontrar o maior ID
  while (fgets(linha, MAX_LINHA, arquivo) != NULL) {
    int id;
    sscanf(linha, "%d", &id);
    if (id > ultimo_id) {
      ultimo_id = id;
    }
  }

  fclose(arquivo);
  return ultimo_id + 1; // O próximo ID será o maior ID + 1
}

// Estrutura dos animais
typedef struct {
  char nome[50];
  char dicas[5][100]; // Array de dicas
  char tipo[20];
} animal;

// Função para selecionar um animal aleatoriamente
animal escolher_animal(int *animais_usados) {

  animal animais[grupo_animais] = {
      {"Vaca",
       {"Uma das principais fontes de leite no mundo.",
        "Normalmente encontrada em fazendas", "Muge.",
        "Têm sido domesticada há milhares de anos.",
        "Símbolo de riqueza e fertilidade em muitas culturas."},
       "Herbívoro"},
      {"Elefante",
       {"É o maior mamífero terrestre.", "Possui uma memória excepcional.",
        "Têm grandes orelhas.", "Possui uma tromba multifuncional.",
        "Possui presas de marfim."},
       "Herbívoro"},
      {"Girafa",
       {"É o animal terrestre mais alto do mundo.",
        "Come folhas de árvores altas, como acácias.",
        "Sua pele é coberta por manchas.", "Sua língua e pescoço são longos.",
        "Se comunicam através de sons de baixa frequência."},
       "Herbívoro"},
      {"Coelho",
       {"Adora cenouras.", "Possui orelhas longas.",
        "É um excelente escavador.", "Conhecido como símbolo de fertilidade.",
        "Pode ser um animal de estimação."},
       "Herbívoro"},
      {"Cavalo",
       {"Capaz de carregar cargas pesadas.", "Dorme em pé.",
        "Podem ser treinados para competições e trabalhos agrícolas.",
        "É um animal muito inteligente.", "Corre como um carro."},
       "Herbívoro"},
      {"Porco",
       {"Tem um focinho altamente sensível.", "Adora tomar banho de lama.",
        "São frequentemente domesticados, até mesmo como animais de estimação.",
        "É considerado um dos mais espertos do reino animal.",
        "Conhecidos por comerem sobras."},
       "Onívoro"},
      {"Gato",
       {"É um animal de estimação popular.", "Gosta de caçar pequenos animais.",
        "Conhecidos por sua natureza independente.", "É um animal dorminhoco.",
        "Têm um instinto territorial."},
       "Onívoro"},
      {"Cachorro",
       {"Famoso por ser o melhor amigo do homem.",
        "Precisam de exercício regular.",
        "Existem mais de 300 raças diferentes.",
        "Podem agir como animais de serviço.", "Adoram brincar e socializar."},
       "Onívoro"},
      {"Tartaruga",
       {"Possui um casco duro que a protege de predadores.",
        "Algumas espécies podem viver por mais de 100 anos.",
        "Vive principalmente nos oceanos.",
        "As fêmeas retornam à praia para desovar.",
        "Muitas de suas espécies estão ameaçadas de extinção."},
       "Onívoro"},
      {"Urso",
       {"Sua dieta pode variar de mel a peixes.", "É um símbolo de força.",
        "Hiberna durante o inverno.",
        "Pode ser encontrado em diferentes regiões do mundo.",
        "Apesar de seu tamanho, consegue correr rapidamente em curtas "
        "distâncias."},
       "Onívoro"},
      {"Tigre",
       {"Maior felino do mundo.", "É um caçador solitário.",
        "Encontrado principalmente na Ásia.", "Possui listras em sua pelagem.",
        "É um animal territorial."},
       "Carnívoro"},
      {"Lobo",
       {"Vive em matilhas.", "É um animal territorial.",
        "É um caçador estratégico.", "Consegue se comunicar por uivos.",
        "Pode ser encontrado em diversos habitats."},
       "Carnívoro"},
      {"Baleia",
       {"É o maior animal do mundo.", "É um mamífero.",
        "Vive nos oceanos e realizam migrações anuais.",
        "Podem se comunicar através de canções longas e complexas.",
        "São animais muito inteligentes."},
       "Carnívoro"},
      {"Pinguim",
       {"É uma ave, mas não voa.", "Vive em regiões frias.",
        "Os machos chocam os ovos.", "É um excelente nadador.",
        "Muitas espécies formam pares monogâmicos."},
       "Carnívoro"},
      {"Boto",
       {"Encontrados em água doce.",
        "Uma de suas variações é um símbolo do folclore brasileiro.",
        "É um nadador ágil e costuma saltar fora da água.",
        "Nativo da América do Sul e Central.",
        "É um animal extremamente social e inteligente."},
       "Carnívoro"},
      {"Capivara",
       {"Maior roedor do mundo.", "Vive próxima a corpos d'água.",
        "Podem ser encontradas em diversas regiões do Brasil.",
        "Vivem em grupos grandes (10 a 20 indivíduos).",
        "Têm dentes fortes, que as ajudam a se defender de predadores."},
       "Herbívoro"},
      {"Tatu",
       {"Sua carapaça é coberta por uma pele dura.",
        "Muitas espécies tem uma dieta predominantemente insetívora.",
        "Conhecidos por suas habilidades de escavação.",
        "Quando ameaçados, costumam se enrolar em uma bola.",
        "Encontrados em florestas tropicais, savanas e áreas semiáridas."},
       "Onívoro"}};

  int animal_escolhido;

  do {
    animal_escolhido = rand() % grupo_animais; // Gerar animal aleatório
  } while (animais_usados[animal_escolhido] == 1);

  animais_usados[animal_escolhido] = 1; // Armazena o índice do animal escolhido
  return animais[animal_escolhido];     // Retorna o animal escolhido
}

// Função para comparar strings sem diferenciar maiúsculas e minúsculas
int compara_strings(const char *str1, const char *str2) {
  while (*str1 && *str2) {
    if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2)) {
      return 0;
    }
    str1++;
    str2++;
  }
  return (*str1 == *str2); // Verifica se ambas terminaram ao mesmo tempo
}

int minigame_adivinha(const char *nome_jogador) {
  srand(time(0));
  int animais_usados[grupo_animais] = {
      0}; // Inicializa vetor para marcar animais
  char resposta[50];

  // Menu do minigame
  caixa_minigames("   Minijogo escolhido: Adivinhe o animal!");
  tabulacao("• Seu trabalho é reconhecer os animais pelas dicas. Serão 5 "
            "tentativas.");
  tabulacao(
      "• A palavra que você deve chutar está no singular e não é composta.");
  tabulacao("• Você só consegue jogar este jogo uma vez, e não há como voltar "
            "atrás.");
  tabulacao("• Portanto, tente fazer o máximo de pontos que conseguir "
            "adivinhando todos os animais!\n");

  for (int i = 0; i < 5; i++) {
    animal escolhido = escolher_animal(animais_usados);
    int tentativas = 0;
    int max_tentativas = 5;
    int acertou = 0;

    printf("\tDica: %s\n", escolhido.dicas[tentativas]);

    while (tentativas < max_tentativas && !acertou) {
      printf("\tTentativa %d: ", tentativas + 1);
      scanf("%s", resposta);
      tentativas++;

      // Verifica se a resposta está correta, ignorando maiúsculas/minúsculas
      if (compara_strings(resposta, escolhido.nome) == 1) {
        acertou = 1;
        p1 += 5; // Incrementa 5 pontos
      } else {
        tabulacao("==----------------------==");
        tabulacao("Errado. Tente novamente.");
        tabulacao("==----------------------==");
        if (tentativas < max_tentativas) { // Dicas na tentativa do erro
          printf("\tDica: %s\n",
                 escolhido.dicas[tentativas]); // Dica nova a cada erro
        }
      }
    }

    if (acertou) {
      tabulacao("==----------------------------==");
      tabulacao("Parabéns, você acertou o animal!");
      tabulacao("==----------------------------==");
      tabulacao(GREEN "      Você ganhou 5 pontos!" RESET);
      tabulacao("==----------------------------==");
    } else {
      printf("\tVocê não acertou. O animal era: %s.\n", escolhido.nome);
    }
  }
  printf("\n\t     Pontuação total: %d pontos\n\n", p1);
  tabulacao("==----------------------------==");
  salvar_pontuacao(nome_jogador, p1);
  return p1;
}

// PARTES DO CAÇA PALAVRAS
// DOCUMENTAÇÃO
void criar_matriz(char matriz[LINHAS][COLUNAS]);
void aparecer_matriz(char matriz[LINHAS][COLUNAS]);
void inserir_palavra(char matriz[LINHAS][COLUNAS], char palavra[]);
void letras_aleatorias(char matriz[LINHAS][COLUNAS]);
char *ler_palavra();
int verificar_palavra(char matriz[LINHAS][COLUNAS], char palavra[]);
void remover_palavra(char palavras[][20], int *num_palavras, char palavra[]);
int palavra_encontrada(char palavras_encontradas[][20], int num_encontradas,
                       char *palavra);

// Função para calcular pontos por base da palavra
int calcular_pontos(char palavra[]) {
  int tamanho = strlen(palavra);
  if (tamanho <= 6) {
    return 3; // 3 pontos para palavras menores
  } else if (tamanho == 8) {
    return 4; // 4 pontos para palavras médias
  } else if (tamanho == 9) {
    return 5; // 5 pontos para palavras grandes
  }
}

// Função para jogar o jogo das palavras
int minigame_palavras() {
  char matriz[LINHAS][COLUNAS];
  char palavras[MAX_PALAVRAS][20] = {"tucano",   "peixeboi",  "arara", "anta",
                                     "ariranha", "tartaruga", "tatu"};
  int num_palavras = MAX_PALAVRAS;
  const char *dica = "As palavras devem ser digitadas sem acento e sem hífen, "
                     "em letras minúsculas.";
  char palavras_encontradas[MAX_PALAVRAS][20]; // Armazenar palavras encontradas
  int num_encontradas = 0;                     // Conta as palavras encontradas

  caixa_minigames("\tMinijogo escolhido: Caça-palavras!");
  tabulacao("");

  srand(time(NULL));

  criar_matriz(matriz);

  for (int i = 0; i < num_palavras; i++) {
    inserir_palavra(matriz, palavras[i]);
  }

  letras_aleatorias(matriz);
  aparecer_matriz(matriz);
  printf("\n\tDica: %s\n", dica); // Imprime a dica

  while (num_palavras > 0) {
    char *palavra_digitada = ler_palavra();

    // Verifica se o jogador deseja desistir
    if (palavra_digitada[0] == 'D' || palavra_digitada[0] == 'd') {
      tabulacao("==----------------------------------------------------==");
      printf("\tVocê desistiu do jogo. Você fez %d ponto(s). Até a próxima!\n",
             p2);
      tabulacao("==----------------------------------------------------==");
      free(palavra_digitada);
      break;
    }

    // Verifica se a palavra digitada corresponde a palavra na matriz
    if (verificar_palavra(matriz, palavra_digitada)) {
      if (!palavra_encontrada(palavras_encontradas, num_encontradas,
                              palavra_digitada)) {
        printf("Parabéns! Você encontrou a palavra: %s\n", palavra_digitada);
        strcpy(palavras_encontradas[num_encontradas++],
               palavra_digitada); // Adiciona na lista de palavras encontradas
        remover_palavra(palavras, &num_palavras, palavra_digitada);
        int pontos_ganhos = calcular_pontos(palavra_digitada);
        p2 += pontos_ganhos; // Adiciona um ponto
        tabulacao("==----------------------------==");
        printf(PURPLE "\t      Você ganhou %d pontos!\n" RESET, pontos_ganhos);
        tabulacao("==----------------------------==");
      } else {
        printf("Você já encontrou essa palavra: %s\n", palavra_digitada);
      }
      free(palavra_digitada);

      // Verifica se ainda há palavras restantes
      if (num_palavras > 0) {
        printf("Você ainda tem %d palavras para encontrar.\n", num_palavras);
      } else {
        printf("Você encontrou todas as palavras! Total de pontos: %d\n", p2);
      }
    } else {
      printf("Palavra não encontrada ou inválida. Tente novamente.\n");
      free(palavra_digitada);
    }
  }

  // Exibe a pontuação final
  if (num_palavras == 0) {
    printf("Você fez um total de %d ponto(s). Parabéns!\n", p2);
  }
  return p2;
}

void criar_matriz(char matriz[LINHAS][COLUNAS]) {
  memset(matriz, ' ', sizeof(char) * LINHAS * COLUNAS);
}

void inserir_palavra(char matriz[LINHAS][COLUNAS], char palavra[]) {
  int tamanho_palavra = strlen(palavra);
  int linha, coluna, direcao;

  int posicao_v;
  do {
    posicao_v = 1;
    linha = rand() % LINHAS;
    coluna = rand() % COLUNAS;
    direcao = rand() % 2;

    // Verifica se a palavra cabe na matriz
    if (direcao == 0 && coluna + tamanho_palavra > COLUNAS) {
      posicao_v = 0;
    } else if (direcao == 1 && linha + tamanho_palavra > LINHAS) {
      posicao_v = 0;
    } else {
      for (int i = 0; i < tamanho_palavra; i++) {
        if (direcao == 0 && matriz[linha][coluna + i] != ' ') {
          posicao_v = 0;
          break;
        } else if (direcao == 1 && matriz[linha + i][coluna] != ' ') {
          posicao_v = 0;
          break;
        }
      }
    }
  } while (!posicao_v);

  // Insere a palavra na matriz
  for (int i = 0; i < tamanho_palavra; i++) {
    if (direcao == 0) {
      matriz[linha][coluna + i] = palavra[i];
    } else {
      matriz[linha + i][coluna] = palavra[i];
    }
  }
}

void letras_aleatorias(char matriz[LINHAS][COLUNAS]) {
  for (int i = 0; i < LINHAS; i++) {
    for (int j = 0; j < COLUNAS; j++) {
      if (matriz[i][j] == ' ') {
        matriz[i][j] = 'a' + rand() % 26;
      }
    }
  }
}

void aparecer_matriz(char matriz[LINHAS][COLUNAS]) {
  for (int i = 0; i < LINHAS; i++) {
    printf("\t\t");
    for (int j = 0; j < COLUNAS; j++) {
      printf("%c ", matriz[i][j]);
    }
    printf("\n");
  }
}

char *ler_palavra() {
  char palavra[20];
  tabulacao("Digite a palavra encontrada (ou d para desistir): ");
  scanf("%19s", palavra);
  char *resultado = malloc(strlen(palavra) + 1);
  if (resultado) {
    strcpy(resultado, palavra);
  }
  return resultado;
}

int verificar_palavra(char matriz[LINHAS][COLUNAS], char palavra[]) {
  int tamanho_palavra = strlen(palavra);

  for (int i = 0; i < LINHAS; i++) {
    for (int j = 0; j < COLUNAS; j++) {
      // Verifica horizontalmente
      if (j + tamanho_palavra <= COLUNAS &&
          memcmp(&matriz[i][j], palavra, tamanho_palavra) == 0) {
        return 1;
      }

      // Verifica verticalmente
      if (i + tamanho_palavra <= LINHAS) {
        int n = 1;
        for (int k = 0; k < tamanho_palavra; k++) {
          if (matriz[i + k][j] != palavra[k]) {
            n = 0;
            break;
          }
        }
        if (n) {
          return 1;
        }
      }
    }
  }
  return 0;
}

void remover_palavra(char palavras[][20], int *num_palavras, char palavra[]) {
  for (int i = 0; i < *num_palavras; i++) {
    if (strcmp(palavras[i], palavra) == 0) {
      for (int j = i; j < *num_palavras - 1; j++) {
        strcpy(palavras[j], palavras[j + 1]);
      }
      (*num_palavras)--;
      break;
    }
  }
}

int palavra_encontrada(char palavras_encontradas[][20], int num_encontradas,
                       char *palavra) {
  for (int i = 0; i < num_encontradas; i++) {
    if (strcmp(palavras_encontradas[i], palavra) == 0) {
      return 1; // Palavra já encontrada
    }
  }
  return 0; // Palavra não encontrada
}

// PARTES DO LABIRINTO

#define LINHAS 20
#define COLUNAS 20

char labirinto[LINHAS][COLUNAS] = {
    {'*', ' ', '*', '*', '*', '*', '*', '*', '*', '*',
     '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', ' ', ' ', ' ', '*', '*', '*', '*', '*', '*',
     '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', ' ', '*', ' ', '*', '*', '*', '*', '*', ' ',
     ' ', ' ', '*', '*', ' ', '*', '*', '*', '*', '*'},
    {'*', ' ', '*', ' ', ' ', ' ', ' ', '*', '*', '*',
     '*', ' ', '*', '*', ' ', '*', '*', '*', '*', '*'},
    {'*', ' ', '*', ' ', '*', '*', ' ', '*', '*', '*',
     '*', ' ', ' ', ' ', ' ', ' ', ' ', '*', '*', '*'},
    {'*', ' ', '*', ' ', '*', '*', ' ', ' ', ' ', '*',
     '*', '*', '*', '*', '*', '*', ' ', ' ', '*', '*'},
    {'*', ' ', ' ', ' ', '*', '*', ' ', '*', ' ', '*',
     '*', '*', '*', '*', '*', '*', '*', ' ', '*', '*'},
    {'*', ' ', '*', ' ', '*', '*', ' ', '*', '*', '*',
     '*', '*', '*', '*', '*', '*', '*', ' ', '*', '*'},
    {'*', ' ', '*', ' ', ' ', ' ', ' ', '*', '*', '*',
     '*', '*', ' ', ' ', ' ', '*', '*', ' ', '*', '*'},
    {'*', ' ', '*', '*', '*', '*', ' ', ' ', ' ', ' ',
     ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', ' ', ' ',
     '*', '*', '*', '*', '*', '*', '*', ' ', '*', '*'},
    {'*', ' ', ' ', ' ', '*', '*', '*', '*', ' ', '*',
     '*', ' ', '*', '*', '*', '*', ' ', ' ', '*', '*'},
    {'*', ' ', '*', ' ', '*', '*', '*', '*', '*', '*',
     '*', ' ', '*', '*', '*', '*', ' ', '*', '*', '*'},
    {'*', ' ', '*', ' ', ' ', ' ', ' ', '*', '*', '*',
     '*', ' ', '*', '*', '*', '*', ' ', '*', '*', '*'},
    {'*', ' ', '*', ' ', '*', '*', ' ', '*', '*', '*',
     '*', ' ', '*', '*', '*', '*', ' ', ' ', ' ', '*'},
    {'*', '*', '*', ' ', '*', '*', ' ', ' ', ' ', '*',
     '*', ' ', '*', '*', '*', '*', '*', '*', ' ', '*'},
    {'*', ' ', ' ', ' ', '*', '*', ' ', '*', ' ', ' ',
     ' ', ' ', ' ', ' ', ' ', ' ', '*', '*', ' ', '*'},
    {'*', ' ', '*', ' ', '*', '*', ' ', '*', ' ', '*',
     '*', ' ', '*', '*', '*', ' ', '*', '*', ' ', '*'},
    {'*', ' ', '*', ' ', '*', '*', ' ', '*', ' ', ' ',
     '*', ' ', '*', '*', '*', ' ', ' ', ' ', ' ', 'S'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
     '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}

};

// Posição inicial do jogador
int jogador_x = 0, jogador_y = 1;

void iniciar_jogo() {
  jogador_x = 0;
  jogador_y = 1;
}

void desenho_labirinto() {
  system("clear");
  for (int i = 0; i < LINHAS; i++) {
    for (int j = 0; j < COLUNAS; j++) {
      if (i == jogador_x && j == jogador_y) {
        printf("J ");
      } else {
        printf("%c ", labirinto[i][j]);
      }
    }
    printf("\n");
  }
}

// Função para mover o jogador
int m_jogador(char direcao) {
  int nova_posicao_x = jogador_x, nova_posicao_y = jogador_y;

  switch (direcao) {
  case 'w': // Cima
    nova_posicao_x--;
    break;
  case 's': // Baixo
    nova_posicao_x++;
    break;
  case 'a': // Esquerda
    nova_posicao_y--;
    break;
  case 'd': // Direita
    nova_posicao_y++;
    break;
  default:
    return 0;
  }

  // Verifica se a nova posição é um espaço vazio ou a saída
  if (labirinto[nova_posicao_x][nova_posicao_y] == ' ' ||
      labirinto[nova_posicao_x][nova_posicao_y] == 'S') {
    jogador_x = nova_posicao_x;
    jogador_y = nova_posicao_y;
    return 1;
  }
  return 0;
}

int minigame_labirinto() {
  char direcao;
  char jogar_novamente;

  iniciar_jogo();
  int jogo_funcionando = 1;
  desenho_labirinto();

  // Loop principal do jogo
  while (jogo_funcionando) {
    printf("\n w (cima), s (baixo), a (esquerda), d (direita)\n");
    direcao = getchar(); // Ve qual tecla foi pressionada

    if (direcao == '\n') {
      continue;
    }

    if (m_jogador(direcao)) {
      desenho_labirinto();
    } else {
      printf("Você perdeu!\n");
      jogo_funcionando = 0; // Finaliza o jogo
    }

    // Verifica se o jogador chegou na saída
    if (labirinto[jogador_x][jogador_y] == 'S') {
      printf("\nVocê encontrou a saída!\n");
      p3 += 20;
      jogo_funcionando = 0; // Finaliza o jogo
    }
  }
  return p3;
}

// HISTÓRIA

typedef struct {
  char name[50];
  char emote[10];
} Personagem;

void dialogo(Personagem p, const char *fala) {
  printf("%s %s: %s", p.emote, p.name, fala);
  getchar(); // Força o usuário a interagir para avançar diálogo
}

void print_wait(const char *texto) {
  printf("%s", texto);
  getchar();
}

Personagem recrutadora = {"Dona Annelise", "🐾"}
;

void contar_historia(const char *nome_jogador) {

  dialogo(recrutadora, "Você finalmente chegou! Estou ansiosa para começarmos, "
                       "temos um dia cheio hoje.");
  dialogo(recrutadora, "Antes de qualquer coisa, vou te apresentar o lugar. "
                       "Temos muito para cobrir.");
  dialogo(recrutadora, "Nossa ONG é responsável pelo resgate de diversos "
                       "animais, especialmente os domésticos.");
  dialogo(recrutadora, "Porém, para dar conta do trabalho, você deverá saber "
                       "reconhecer bem a natureza de cada espécie.");
  dialogo(recrutadora, "É por isso que vou começar com um pequeno teste. Não "
                       "se preocupe, vou pegar leve com você.");
  dialogo(recrutadora, "Acha que consegue fazer isso?\n");
  minigame_adivinha(nome_jogador);
  dialogo(recrutadora, "Bom trabalho! Você se saiu muito bem!\n");
  dialogo(recrutadora, "Ah, você deve estar se perguntando sobre esses "
                       "'pontos' que você ganhou.");
  dialogo(recrutadora, "Não se preocupe. No final do dia eu explicarei sobre "
                       "eles. Por enquanto, não os perca!");
  dialogo(recrutadora,
          "Continuando de onde paramos, tenho uma nova tarefa para você.");
  dialogo(recrutadora, "Nosso trabalho não se limita apenas a ajudar os "
                       "animais, mas também educar as pessoas.");
  dialogo(recrutadora, "Conscientizar sobre a importância da preservação é "
                       "fundamental para nosso objetivo.");
  dialogo(recrutadora, "Por isso, estarei organizando uma palestra em breve "
                       "sobre as espécies ameaçadas.");
  dialogo(recrutadora, "Preciso de ajuda para escolher os " GREEN
                       "7 animais brasileiros " RESET
                       "em risco de extinção que irei abordar.");
  dialogo(recrutadora, "Consegue encontrá-los para mim?\n");
  minigame_palavras();
  dialogo(recrutadora,
          "Como foi? Muito obrigada pela ajuda, de qualquer forma!\n");
  dialogo(recrutadora,
          "Olha só como o tempo voa. Estamos chegando ao fim do dia.");
  dialogo(recrutadora,
          "Antes de encerrarmos, gostaria de fazer um último teste.");
  dialogo(
      recrutadora,
      "Como você sabe, nós voluntários participamos de diversas atividades");
  dialogo(recrutadora, "Inclusive na parte prática.");
  dialogo(recrutadora,
          "Imagine que estamos tentando resgatar um cachorro que se perdeu.");
  dialogo(recrutadora,
          "É preciso ter agilidade para encontrá-lo o mais rápido possível.");
  dialogo(recrutadora, "Então, que tal um pequeno desafio?");
  minigame_labirinto();
  dialogo(recrutadora, "Então, você chegou ao fim.");
}

// MAIN

int main() {
  char decisao;
  char nome_jogador[MAX_NOME];
  int id_jogador = gerar_novo_id();
  caixa_minigames("   Bem-vindo ao jogo Animal Rescue Quest!");
  printf("\t\t\t %sObservações:%s\n\n", UNDERLINE, RESET);
  tabulacao("• Este jogo é uma simulação imersiva.\n");
  tabulacao("• Existem 3 minigames ao longo da história.\n");
  tabulacao("• Pressione Enter para avançar diálogos.\n");
  tabulacao("===+-------------------------------------+===\n");

  while (1) { // Laço de verificação
    printf("\t\tEstá pronto para começar? (Y/N): ");
    scanf("%c", &decisao);
    if (decisao == 'Y' || decisao == 'y') {
      printf("\n");
      tabulacao("===+-------------------------------------+===\n");
      tabulacao_dupla("Como podemos lhe chamar?");
      printf("\t\t Digite o seu nome: ");
      scanf("%s", nome_jogador);

      FILE *arquivo = fopen("jogadores.txt", "a");

      if (arquivo == NULL) {
        tabulacao("Erro ao abrir o arquivo!");
        exit(1); // Encerra o programa se não conseguir abrir o arquivo
      }

      // Escrever o nome do jogador no arquivo
      fprintf(arquivo, "ID #%d: %s\n", id_jogador, nome_jogador);

      // Fechar o arquivo
      fclose(arquivo);

      tabulacao("===+-------------------------------------+===");
      printf("\t\t  Perfeito, %s! Vamos começar!\n", &nome_jogador);
      tabulacao("===+-------------------------------------+===\n");
      break;
    } else if (decisao == 'N' || decisao == 'n') {
      tabulacao("===+-------------------------------------+===\n");
      tabulacao_tripla("Até uma outra hora!\n");
      exit(0); // Encerra o programa
    } else {
      tabulacao_dupla("Essa decisão não é válida!");
    }

    while (getchar() != '\n')
      ; // Descarta a linha restante no buffer
  }

  tabulacao_tripla("   HISTÓRIA:\n");

  print_wait(" Como um bom estudante universitário, você acaba de entrar em "
             "seu último ano de curso.");
  print_wait("\n Contanto, seu currículo consta um total de " RED
             "0 horas complementares." RESET);
  print_wait(" Você precisa de " CYAN "200 horas" RESET " para se formar.");
  print_wait(" Por sorte, você conheceu à ONG" ITALIC
             " Patinhas da Esperança" RESET " recentemente.");
  print_wait(" A ONG está sempre em busca de ajuda, e você adora animais, "
             "então é a oportunidade perfeita!");
  print_wait(" Você decide que conseguirá essas horas ao se voluntariar.");
  print_wait(" Após uma breve troca de e-mails com a responsável, você marca "
             "um horário para visitar a ONG.\n");

  printf("[14:35] - Segunda-feira\n");
  contar_historia(nome_jogador);

  int pontuacao_geral = p1 + p2 + p3;

  if (pontuacao_geral >= 50) {
    printf("%d", pontuacao_geral);
    dialogo(recrutadora, "Meus parabéns! Você passou!");
    dialogo(recrutadora, "Você demonstrou conhecimento, agilidade e braveza "
                         "nos testes de hoje.");
    dialogo(recrutadora,
            "Isso prova que você está apto a agir como voluntário!");
    dialogo(recrutadora, "E nós estamos muito felizes em receber você!");
    tabulacao(BLUE "Final 1 de 2: Você passou no treinamento e conseguirá as "
                   "horas complementares em seu ano final!" RESET);

  } else {
    printf("%d", pontuacao_geral);
    dialogo(recrutadora, "E, sinto muito, mas não poderemos receber você como "
                         "voluntário nesse momento.");
    dialogo(recrutadora, "Mas, ei, quem sabe numa próxima vez?");
    tabulacao(RED "Final 2 de 2: Você não conseguirá suas horas complementares "
                  "por aqui. Melhor pensar em outros jeitos..." RESET);
  }

  return 0;
}