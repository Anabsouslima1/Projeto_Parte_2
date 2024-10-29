# Animal Rescue Quest
Este projeto traz um jogo imersivo de simulação sobre resgate de animais, com foco educativo. Criado como parte 2 do projeto da disciplina CCP230 - Desenvolvimento de Algoritmos. 

## Resumo

O jogo gira em torno de um estudante universitário que, prestes a se formar, precisa acumular horas complementares. Para isso, ele decide se voluntariar em uma ONG chamada "Patinhas da Esperança", que se dedica ao resgate de animais. Ao longo do dia, ele passa por testes criados pela recrutadora, que pretende entender se o estudante está apto para o trabalho. Se o estudante atingir 50 pontos, ele está apto.

## Forma de Compilação e Execução

O código foi desenvolvido na linguagem C e pode ser compilado e executado em qualquer ambiente que suporte o compilador GCC (GNU Compiler Collection).
Recomendamos usar o Replit por conta do último minigame (labirinto).

## Minigames

O repositório contém os seguintes jogos:

- **Minigame Adivinhação**: O jogo pede para adivinhar 5 animais. O jogador consegue acumular até 25 pontos com este minijogo. Usa 2 funções principais: *escolher_animal*: que retorna um animal da lista e incrementa o índice. *compara_strings*: Compara duas strings de forma case-insensitive.
- **Minigame Caça-Palavras**: O jogo pede para encontrar 7 animais em risco de extinção, com uma função de desistência disponível. Usa várias funções de criação: *inserir_palavra*: adiciona as palavras escolhidas no jogo e adiciona as letras aleatórias para completar o caça palavras.
- **Minigame Labirinto**: O jogo simula um labirinto com o protagonista sendo o cachorrinho. Usa várias funções de criação: iniciar o jogo desenhando o labirindo já definido, verificar se o jogador perdeu o jogo ou se ele conseguiu chegar na saída.

## Integrantes

- Ana Beatriz Sousa Lima (R.A: 22.124.085-6)
- Elizabeth Kremer Kruger (R.A: 52.124.009-3)
- Júlia Bastos Barreto (R.A: 22.124.071-6)
