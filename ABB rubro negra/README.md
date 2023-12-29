# Árvore Rubro-Negra

Esta é a implmentação de uma Árvore Rubro-Negra em linguagem C. Esta estrutura de dados possui as propriedades-base de uma Árvore Binária de Busca comum, mas com propriedades adicionais no que se refere a um balanceamento dos nós inseridos na Árvore, por meio do conceito de coloração e padronização dessa coloração aplicada a esses nós.

## Propriedades
**1.** Todo nó na árvore recebe a cor ou **Rubro** ou **Negro**;

**2.** O nó raiz da árvore é sempre **Negro**;

**3.** Todo folha **Externa** é **Negra**;

**4.** Se um nó possui a cor **Rubro**, então ambos os seus filhos são *Negros*;

**5.** Para todo nó, **todos os caminhos** do nó até as folhas desecedentes contêm o mesmo número de nós **Negros**.

## Descrição do código

O código está organizado de modo a englobar as principais operações do algoritmo da Árvore Rubro-Negra, tais como: ***Inserção***, ***Remoção***, ***Rotações*** e ***Colorações***. O código possui, também a implementação de "funções-extra", tais como: ***Cáculo da altura negra***, ***Verificação se uma árvore é rubro-negra ou não***. O código conta, ainda com uma função de teste, a qual define a criação de 1000 árvores rubro-negras, insere 10000 nós em cada uma delas, verifica se as árvores são rubro-negras, realiza a remoção de 1000 desses nós, e verifica mais uma vez se as árvores permanecem rubro-negras após as remoções.
