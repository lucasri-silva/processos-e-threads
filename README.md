<h1 align="center">SO - Processos e Threads</h1>

<h3 align ="center">Escalonamento e Gestão de Memória Primária</h3>

<p align="justify">Trabalho da disciplina Sistemas Operacionais. A atividade propõe a construção de um sistema de classificação cujas características nos permitirão observar os conceitos de Escalonamento e Gestão de Memória Primária. Neste sistema, vamos considerar duas bases de dados D e T - ambas se referem ao famoso Iris dataset utilizado em análise exploratória de dados. A base D será utilizada para simular a inicialização, fornecendo assim o conceito de bootstrapping, tal como no sistema operacional. A base T representará os processos a serem executados.</p>

<h2 align="left">Compilação e Execução</h2>

- OS: Ubuntu 22.04.1 LTS | Compilador: g++ version 11.2.0

- Para executar abra o diretório do arquivo desejado e execute o MakeFile.

| Comando    | Função                                                                                  |
| ---------- | --------------------------------------------------------------------------------------- |
| make clean | Apaga a última compilação realizada contida na pasta bin                                |
| make       | Executa a compilação do programa utilizando o g++, e o resultado vai para a pasta bin   |
| make run   | Executa o programa da pasta bin após a realização da compilação                         |
                
<h2 align ="left">Etapa I</h2>

<p align="justify">A primeira etapa constitui na elaboração das tabelas hash para itens e classes a partir do arquivo D. Dada uma linha do arquivo D, consideraremos item as colunas de 0 a n - 1 e classe a coluna n. Os itens serão armazenados na hash <code>itensD</code>, no qual a chave será representada por (coluna, medida) e o valor será representado pelos índices de todas as linhas onde a chave aparece. Para itens de mesmo valor, a indexação ocorrerá da seguinte maneira: se um item aparece na coluna 1 e 3 com valor 23.4, consideraremos como chave da hash (1, 23.4) e (3,23.4), respectivamente. De maneira análoga, a classe será armazenada na hash "classes", no qual a chave será representada por (espécie) e o valor será representado por suas indexações.</p>

| ![e1-itensD.png](./images/e1-itensD.png?width="400") | 
|:--:| 
| Imagem representa a hash itens, do arquivo D. |

| ![e1-classes.png](./images/e1-classes.png?width="400") | 
|:--:| 
| Imagem representa a hash classes, do arquivo D. |

<h2 align ="left">Etapa II</h2>

<p align="justify">Na segunda etapa é realizado a leitura do arquivo T, geração dos itens de T e em sua comparação com o itens criado na etapa anterior. Inicialmente, o conteúdo de T será armazenado na fila <code>itensT</code>, em que cada posição armazena uma linha inteira do arquivo T. Para cada valor decimal presente na linha esse deve ser armazenado junto a sua coluna correspondente (semelhante a chave de itens). Em seguida, é feito a comparação dos itens de T com a tabela hash de itens, do arquivo D. Os itens comuns entre eles serão armazenados no vector <code>commonItens</code>. Feito isso, para toda linha em commonItens é realizada a combinação entre seus elementos, sendo armazenados no arquivo "combinations.txt".</p>

| ![e2-itensT.png](./images/e2-itensT.png?width="400") | 
|:--:| 
| Imagem representa a fila itensT. Cada posição da fila armazena uma linha do arquivo T, que corresponde às chaves (coluna, medida). |

| ![e2-intersectionDeT.png](./images/e2-intersectionDeT.png?width="400") | 
|:--:| 
| Imagem representa o vetor commonItens gerado a partir da interseção dos itens D e T. |

| ![e2-combinations.png](./images/e2-combinations.png?width="400") | 
|:--:| 
| Arquivo com combinações geradas do vetor commonItens. Note que as combinações representadas acima correspondem a primeira linha do vetor commonItens (imagem acima). | 

<h2 align ="left">Etapa III</h2>

<p align="justify">Na terceira etapa, para cada conjunto de combinação gerado é realizada a busca na hash itens. Em seguida, para cada valor encontrado é realizada a interseção, gerando um vetor de interseção. Por fim, é realizada novamente a interseção do vetor de interseção com os valores de cada classe, computando o tamanho da interseção entre eles à classe em questão. Após o processamento a classe que apresentar um valor de sobreposição maior será apresentada como classe da tarefa em T.</p>

* Exemplo:

![e3-combinations-example.png](./images/e3-combinations-example.png?width="400")

- Considerando o conjunto de combinações, do arquivo "combinations.txt", na imagem acima, temos as seguintes chaves e valores:
  -  <code>(1, 5.1) : 23 77 90 92 97</code>
  -  <code>(2, 3.5) : 17 77 95</code>
  -  <code>(3, 1.4) : 11 13 31 72 77 82 85 88</code>
  -  <code>(4, 0.2) : 6 10 11 13 17 30 31 39 48 56 60 68 78 82 83 84 88 90 94 97</code>
  
<p align="justify">As chaves (1, 5.1)(2, 3.5)(3, 1.4)(4, 0.2) estão presentes em alguma linha do vetor "commonItens". Essas chaves geram um total de 15 combinações. Para combinações com apenas uma chave é realizado a interseção direta entre seu valor com as classes. Para combinações com mais de uma chave, por outro lado, é realizado primeiramente a interseção entre os valores das chaves para, em seguida, ser realizado a interseção do vetor interseção com os valores das classes.</p>
  
<p align="justify">Dessa forma, para as combinações (3, 1.4)(4, 0.2) temos o vetor de interseção <code>11 13 31 82 88</code> e para as combinações (1, 5.1)(2, 3.5)(3, 1.4) temos o vetor de interseção <code>77</code>. Assim que o vetor de interseção é gerado é chamada a função <code>computeClassIntersection</code>, que, por sua vez, recebe como parâmetro o vetor de interseção. Essa função então realiza a interseção do vetor de interseção com os valores das classes, computando o tamanho da nova interseção às seguintes variáveis: </p>
  
  - <code>unsigned int irisVersicolor = 0;</code>
  - <code>unsigned int irisVirginica = 0;</code>
  - <code>unsigned int irisSetosa = 0;</code>
  
<p align="justify">No fim de cada interseção do vetor de interseção com os valores das classes o vetor é limpado. As computações das variáveis classes, por sua vez, são acumulativas. Ao final é imprimido na tela a classe com maior número de sobreposições.</p>

| ![e3-sobreposicao.png](./images/e3-sobreposicao.png?width="400") | 
|:--:| 
| Resultado da interseção entre o vetor de interseção, gerado a partir da interseção das combinações, e os valores de cada classe. Podemos notar que a Iris-setosa obteve o maior número de interseções (573) entre as classes. |

<h2 align ="left">Etapa IV</h2>

<p align="justify">Essa etapa tem como objetivo a elaboração de um cache para armazenar o resultado das interseções já realizadas, de modo que para cada nova combinação é feita primeiramente a verificação se o resultado da interseção já foi processado, isto é, se o resultado está em cache. Em caso afirmativo, o resultado da interseção é retirado da cache para, em seguida, ser realizado sua interseção com as classes.</p>

* Exemplo:

<code>(3, 1.5) : 1 8 10 23 51 58 60 87 90</code>
<br><code>(4, 0.1) : 8 51 55 85 87</code>

<p align="justify">Para as combinações acima a hash terá como chave (3, 1.5)(4, 0.1) e valor a interseção dessas combinações, que será <code>8 51 87</code>. Dessa forma, caso existir uma nova ocorrência dessas combinações no futuro o resultado da interseção será buscado em cache - em vez de ser recomputado.</p>


| ![e4-cache.png](./images/e4-cache.png?width="400") | 
|:--:| 
| Hash cache criada para armazenar o resultado das interseções entre as combinações. |
