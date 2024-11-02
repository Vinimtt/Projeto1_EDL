# Gerenciador de Playlist

Este projeto é um gerenciador de playlist em C que permite ao usuário adicionar, remover, visualizar e procurar músicas em uma lista circular duplamente encadeada.

## Funcionalidades

- Adicionar novas músicas à playlist
- Remover músicas pelo título
- Visualizar todas as músicas na playlist
- Limpar a playlist
- Pesquisar uma música pelo título
- Contar o número total de músicas na playlist

## Estruturas de Dados

O código utiliza as seguintes structs:

- `Musica`: Representa uma música com nome, artista e duração.
- `No`: Representa um nó na lista encadeada, contendo uma música e ponteiros para o próximo e o anterior.
- `Lista`: Representa a lista de músicas, com ponteiros para o início e o fim.

