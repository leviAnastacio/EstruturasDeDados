# Árvore Binária de Busca 

Esta é a implmentação de uma Árvore binária de busca em linguagem C. Esta estrutura de dados possui certas propriedades para manter seus nós ligados entre si e garantir características peculiares acerca de suas definições.

## Propriedades

**1.** Todo nó em uma ABB possui um chave (id), que serve para facilitar a operação de busca;

**2.** Todo nó na árvore pode ou não possuir nós-filhos, caso possua filhos os nós à esquerda de determinado nó v sempre possuirão chaves cujo valor será menor ou igual ao valor da chave desse nó v. E os nós à direita já possuirão chaves de valor maior ou igual ao valor da chave de v.

**->** v.esquerda.chave ≤ v.chave ≤ v.direita.chave

**3.** Todo folha **Externa** é **Negra**;

**4.** Se um nó possui a cor **Rubro**, então ambos os seus filhos são *Negros*;

**5.** Para todo nó, **todos os caminhos** do nó até as folhas desecedentes contêm o mesmo número de nós **Negros**.

## Descrição do código

O código está organizado de modo a englobar as principais operações do algoritmo da Árvore Rubro-Negra, tais como: ***Inserção***, ***Remoção***, ***Rotações*** e ***Colorações***. O código possui, também a implementação de "funções-extra", tais como: ***Cáculo da altura negra***, ***Verificação se uma árvore é rubro-negra ou não*** e ***Contagem de nós***. O código conta, ainda com uma função de teste, a qual define a criação de 1000 árvores rubro-negras, insere 10000 nós em cada uma delas, verifica se as árvores são rubro-negras, realiza a remoção de 1000 desses nós, e verifica mais uma vez se as árvores permanecem rubro-negras após as remoções.

## Compilação e Execução

Para compilar o código, esteja ciente da necessidade de instalação de um compilador para a linguagem C, e logo após isso, basta abrir o arquivo no terminal e aplicar o seguinte comando: 

```bash
gcc <nome_do_arquivo>.c -o ABB_RN
```

Para rodar o código, execute o seguinte comando:

```bash
./ABB_RN
```

