
# Projeto de Sistemas Distribuídos

Tema: Jogo de Damas com um sistema de Lobby.

Time: Daniel e Mara.

Descrição: colocar como funciona o jogo

Tecnologia: C 

## Lobby de Chat

### Servidor Generico de Mensagens
  - Responsável por armazenar as conexões dos clientes.
  - Responsável por tratar erros de conexões e disponibilizar meios simples de tratá-los.
  - Deve ser semelhante a um sistema de lobby.

### Cliente Generico de Mensagens
  - Deve ser capaz de criar salas do servidor de mensagens e também se conectar a elas.

  - 1) Listar salas 
  - 2) Conectar a uma sala
  - 4) Criar uma sala
  - 5) Enviar mensagem
  - 6) Sair

### Protocolo Genérico

## **Criar**
|                     Argumentos                    | Tamanho (Bytes) |
|:-------------------------------------------------:|:---------------:|
|                     ID de erro                    |        4        |
|                  Cliente/Servidor                 |        4        |
|                      Operação                     |        4        |
|                  ID do protocolo                  |        4        |
|                  Nome do usuário                  |        64       |
|                       Senha                       |        64       |
|                    Nome da sala                   |        64       |
| Quantidade de usuários permitidos na sala [2, 16] |        4        |

## **Conectar**
|                     Argumentos                    | Tamanho (Bytes) |
|:-------------------------------------------------:|:---------------:|
|                     ID de erro                    |        4        |
|                  Cliente/Servidor                 |        4        |
|                      Operação                     |        4        |
|                  ID do protocolo                  |        4        |
|                  Nome do usuário                  |        64       |
|                       Senha                       |        64       |
|                    Nome da sala                   |        64       |

## **Enviar**
|                     Argumentos                    | Tamanho (Bytes) |
|:-------------------------------------------------:|:---------------:|
|                     ID de erro                    |        4        |
|                  Cliente/Servidor                 |        4        |
|                      Operação                     |        4        |
|                  ID do protocolo                  |        4        |
|                  Nome do usuário                  |        64       |
|                    Nome da sala                   |        64       |
|                      Mensagem                     |       256       |

## **Listar salas**
|                     Argumentos                    | Tamanho (Bytes) |
|:-------------------------------------------------:|:---------------:|
|                     ID de erro                    |        4        |
|                  Cliente/Servidor                 |        4        |
|                      Operação                     |        4        |
|                  ID do protocolo                  |        4        |

## Game

### Cliente do Jogo : Cliente Generico de Mensagens
  - Controla o andamento do jogo (Permitir o envio de mensagens)
  - Salas de tamanho fixo igual a 2

  - Criar um jogo (Criar)
  - Logar em um jogo (Connetar)

### **(Maybe)** Servidor do Jogo : Servidor Generico de Mensagens
  - Controle de pontuação dos jogadores
  - Ranking
  - Tournament

### TODO
  - Armazenar de forma persistente o estado do servidor e do cliente