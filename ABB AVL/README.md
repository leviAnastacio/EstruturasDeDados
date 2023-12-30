# Árvore Binária de Busca AVL

Esta é a implmentação de uma Árvore Binária de Busca AVL (ABB AVL) em linguagem C. Esta estrutura de dados possui as propriedades-base de uma Árvore Binária de Busca comum, mas com propriedades adicionais no que se refere a um balanceamento dos nós inseridos na Árvore, por meio do conceito do cáculo do fator de balanceamento (bal).

## Propriedades
**1.** ABB em que cada nó ***v*** temos que: -1 ≤ hD(v) - hE(v) ≤ 1
       
**->** hD(v) = altura da ***subárvore direita*** de um nó v.
       
 **->** hE(v) = altura da ***subárvore esquerda*** de um nó v.
       
**->** fator de balanceamento (bal):  ***hD(v) - hE(v)***.
       
## Descrição do código

O código está organizado de modo a englobar as principais operações do algoritmo da Árvore Rubro-Negra, tais como: ***Inserção***, ***Remoção***, ***Rotações*** e ***Colorações***. O código possui, também a implementação de "funções-extra", tais como: ***Cáculo da altura negra***, ***Verificação se uma árvore é rubro-negra ou não***. O código conta, ainda com uma função de teste, a qual define a criação de 1000 árvores rubro-negras, insere 10000 nós em cada uma delas, verifica se as árvores são rubro-negras, realiza a remoção de 1000 desses nós, e verifica mais uma vez se as árvores permanecem rubro-negras após as remoções.

## Compilação e Execução

Para compilar o código, esteja ciente da necessidade de instalação de um compilador para a linguagem C, e logo após isso, basta abrir o arquivo no terminal e aplicar o seguinte comando: 

```bash
gcc <nome_do_arquivo>.c -o ABB_RN
```

Para rodar o código, execute o seguinte comando:

```bash
./ABB_RN
```


