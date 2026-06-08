## Lista zadań nr 5

1. (2 pkt.) Funkcje działające na tablicy i pętle

   - Zaimplementuj i przetestuj funkcję `int suma(int tab[], int size)`. Jej pierwszym argumentem jest tablica liczb typu `int`, a drugim - jej rozmiar. Funkcja powinna zwracać sumę `size` pierwszych liczb z tablicy.
     Przykład użycia:

     ```c++
     int a[4] = {1, 2, 3, -5};
     std::cout << suma(a, 4) << "\n";   // 1
     std::cout << suma(a, 2) << "\n";   // 3
     std::cout << suma(a, 0) << "\n";   // 0 
     ```

   - Zaimplementuj i przetestuj funkcję `void print(int tab[], int size)`. Jej pierwszym argumentem jest tablica liczb typu `int`, a drugim - jej rozmiar. Funkcja powinna wypisywać na konsoli  `size` pierwszych liczb z tablicy. 

   - Zaimplementuj i przetestuj funkcję `void inverse(int tab[], int size)`. Jej pierwszym argumentem jest tablica liczb typu `int`, a drugim - jej rozmiar. Funkcja powinna odwracać kolejność  `size` pierwszych liczb w tablicy. Np. dla tablicy 

     ```c++
     int b[] = {1, 2, 3};
     ```

     po wywołaniu funkcji `inverse(b, 3)` tablica `b` powinna mieć postać `{3, 2, 1}`. 

   - Zaimplementuj i przetestuj funkcję `void seq (int tab[], int size, int a0, int r)`, która wypełnia `size` pierwszych elementów tablicy `tab` liczbami całkowitymi tworzącymi ciąg arytmetyczny o pierwszym elemencie równym `a0` i różnicy `r`.    

2. (2 pkt.) Zaimplementuj funkcję `unsigned collatz(unsigned n`), która dla danej liczby naturalnej `n` zwraca kolejną wartość zgodną ze schematem z hipotezy Collatza, 

   $$c_{n+1} = \begin{cases} \frac{1}{2}c_n & \text{gdy } c_n \text{ jest parzysta} \\
     3c_n + 1 & \text{gdy } c_n \text{ jest nieparzysta} \end{cases}$$ 
   
   np. `collatz(11) == 34`, `collatz(34) == 17`. 
   Następnie:
   
   - napisz program, który dla liczb $n = 1,2,\ldots, 1000$ wypisuje w kolejnych wierszach:
     - `n`
     - liczbę elementów ciągu Collatza zaczynającego się od `n` i kończącego się na pierwszym wystąpieniu liczby 1. Przyjmujemy, że dla $n=1$ jest to ciąg 1-elementowy, dla $n = 2$ jest on   dwuelementowy itd.
     - wartość największego napotkanego elementu ciągu.
   
     10 pierwszych wierszy mojego rozwiązania wygląda następująco:
   
     ```txt 
     1	1	1
     2	2	2
     3	8	16
     4	3	4
     5	6	16
     6	9	16
     7	17	52
     8	4	8
     9	20	52
     10	7	16
     ```
   
     