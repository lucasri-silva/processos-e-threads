<h1 align="center">SO - Processos e Threads</h1>

<h3 align ="center">Escalonamento e Gestão de Memória Primária</h3>

Trabalho da disciplina Sistemas Operacionais. A atividade propõe a construção de um sistema de classificação cujas características nos permitirão observar os conceitos de Escalonamento e Gestão de Memória Primária. Neste sistema, vamos considerar duas bases de dados D e T - ambas se referem ao famoso [Iris dataset](http://www.lac.inpe.br/~rafael.santos/Docs/CAP394/WholeStory-Iris.html) utilizado em análise exploratória de dados. A base D será utilizada para simular a inicialização, fornecendo assim o conceito de bootstrapping, tal como no sistema operacional. A base T representará os processos a serem executados.

<p>| OS: Ubuntu 22.04.1 LTS | Compilador: gcc version 11.2.0 |</p>
                
                
     - Para executar abra o diretório do arquivo desejado e execute o MakeFile.

        ./make
        ./make run

<h2 align ="left">Etapa I</h2>

<p>A primeira etapa constitui na elaboração das tabelas hash para itens e classes a partir do arquivo D. Dada uma linha do arquivo D, consideraremos item as colunas de 0 a n - 1 e classe a coluna n. Os itens serão armazenados na hash "itensD", no qual a chave será representada por (coluna, medida) e o valor será representado pelos índices de todas as linhas onde a chave aparece. Para itens de mesmo valor, a indexação ocorrerá da seguinte maneira: se um item aparece na coluna 1 e 3 com valor 23.4, consideraremos como chave da hash (1, 23.4) e (3,23.4), respectivamente. De maneira análoga, a classe será armazenada na hash "classes", no qual a chave será representada por (espécie) e o valor será representado por suas indexações.</p>

| ![e1-itensD.png](./images/e1-itensD.png?width="400") | 
|:--:| 
| Imagem representa a hash itens, do arquivo D. |

| ![e1-classes.png](./images/e1-classes.png?width="400") | 
|:--:| 
| Imagem representa a hash classes, do arquivo D. |

<h2 align ="left">Etapa II</h2>

<p>Na segunda etapa é realizado a leitura do arquivo T, geração dos itens de T e em sua comparação com o itens criado na etapa anterior. Inicialmente, o conteúdo de T será armazenado na fila "itensT", em que cada posição armazena uma linha inteira do arquivo T. Para cada valor decimal presente na linha esse deve ser armazenado junto a sua coluna correspondente (semelhante a chave de itens). Em seguida, é feito a comparação dos itens de T com a tabela hash de itens, do arquivo D. Os itens comuns entre eles serão armazenados no vector "commonItens". Feito isso, para toda linha em commonItens é realizada a combinação entre seus elementos, sendo armazenados no arquivo "combinations.txt".</p>

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

Na terceira etapa, para cada conjunto de combinação gerado é realizada a busca na hash itens. Em seguida, para cada valor encontrado é realizada a interseção, gerando um vetor de interseção. Por fim, é realizada novamente a interseção do vetor de interseção com os valores de cada classe, computando o tamanho da interseção entre eles à classe em questão. Após o processamento a classe que apresentar um valor de sobreposição maior será apresentada como classe da tarefa em T.


| ![e3-sobreposicao.png](./images/e3-sobreposicao.png?width="400") | 
|:--:| 
| Resultado da interseção entre o vetor de interseção, gerado a partir da interseção das combinações, e os valores de cada classe. Podemos notar que a Iris-setosa obteve o maior número de interseções (573) entre as classes. |
