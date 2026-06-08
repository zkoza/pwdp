## 2.6 Nowoczesna obsługa standardowego strumienia wyjścia: `std::format` i `std::print`

Gdy w latach 90. ubiegłego wieku do języka C++ dodano obsługę strumieni wejścia/wyjścia poprzez obiekty `std::cin` and `std::cout`, był to spory postęp w stosunku do rozwiązań odziedziczonych z języka C. Minęło jednak ponad 30 lat i w tym czasie interfejs tych obiektów jest już dość archaiczny. Jest funkcjonalny, ale nie znam nikogo, kto by go lubił.

Czas na zmiany. Nowe wersje języka C++ wprowadziły `std::format` (C++20) i `std::print` (C++23). I to jest ta długo wyczekiwana rewolucja. 

#### 2.6.1 `std::format`

Funkcję `std::format` omówię na podstawie dość długiego, ale nie wymagającego wielu komentarzy przykładu:

```c++
#include <chrono>
#include <format>
#include <iostream>

int main()
{
    int n = 15;
    int m = 16;

    // podstawowe użycie:
    std::cout << std::format("{} + {} = {}\n", n, m, n + m);

    // argumenty nazwane
    std::cout << std::format("{1} + {0} = {2}\n", n, m, n + m);
    std::cout << std::format("{0} / {0} = 1\n", n);

    // jak wyświetlić klamry?
    std::cout << std::format("{{}} + {{}} = {}\n", "{} + {}");

    // szerokość pola
    std::cout << std::format("{:10} + {:10} = {:10}\n", n, m, n + m);

    // wyrównywanie: <. ^ lub >
    std::cout << std::format("{:>10} + {:^10} = {:<10}\n", n, m, n + m);

    // wyrównywanie z wypełnianiem:
    std::cout << std::format("{:.>10} + {:.^10} = {:.<10}\n", n, m, n + m);

    // zmiana systemu liczbowego
    std::cout << std::format("{:15d} {:15d}\n", 35, 266);
    std::cout << std::format("{:15b} {:15b}\n", 35, 266);
    std::cout << std::format("{:#15b} {:#15b}\n", 35, 266);
    std::cout << std::format("{:15x} {:15x}\n", 35, 266);
    std::cout << std::format("{:#15x} {:#15x}\n", 35, 266);
    std::cout << std::format("{:15o} {:15o}\n", 35, 266);
    std::cout << std::format("{:#15o} {:#15o}\n", 35, 266);

    // dokładność wyświetlania liczb zmiennopozycyjnych
    auto x = 1.0 / 3.0;
    std::cout << std::format("{:.4} \n", x);
    std::cout << std::format("{:.8} \n", x);
    std::cout << std::format("{:.16} \n", x);
    std::cout << std::format("{:.50} \n", x);
    std::cout << std::format("{:.60} \n", x);
    std::cout << std::format("{:.60} \n", 0.3);
    std::cout << std::format("{:.10} \n", 0.25);
    std::cout << "\n";

    // zagnieżdżanie specyfikatorów
    std::cout << std::format("{:.{}} \n", x, 2);
    std::cout << std::format("{:.{}} \n", x, 6);
    std::cout << std::format("{:.{}} \n", x, 10);
    std::cout << std::format("{:.{}} \n", x, 14);
    std::cout << std::format("{:.{}} \n", x, 18);
    std::cout << std::format("{1:>6}: {0:.{1}} \n", x, 10);
    std::cout << std::format("{1:>6}: {0:.{1}} \n", x, 20);

    // wyświetlanie czasu
    std::cout << std::format("Bieżąca data: {:%d %B %Y}\n", std::chrono::system_clock::now());
    std::cout << std::format("Bieżący czas: {:%H:%M:%OS}\n", std::chrono::system_clock::now());
}
```

Całość należy uzupełnić plikiem `CMakeLists.txt`, gdyż `std::format` wymaga kompilacji w trybie co najmniej C++20:

```cmake
cmake_minimum_required (VERSION 3.10)
project(format-demo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(format-demo main.cpp)
```

Projekt można pobrać [z tej linki](./cpp/w02/format/). 

- Funkcja `std::format` zwraca `std::string` wygenerowany na podstawie tekstu definiującego format (jest to jej pierwszy argument) i dowolnych wyrażeń (kolejne argumenty)

  ```c++
  std::string s = std::format("Ala ma {}", "kota");
  ```

  Wynik tej instrukcji:

  ```txt
  Ala ma kota
  ```

- Pierwszy argument może zawierać (wzorowane zapewne na języku Python) symbole zastępcze (ang.  *placeholders*) w postaci pary nawiasów klamrowych, `{}`. 

  ```c++
  std::cout << std::format("{} + {} = {}\n", n, m, n + m);
  ```

- Symbole zastępcze są zastępowane wartościami kolejnych wyrażeń na liście argumentów `std::format` (o ile nie zostaną nazwane - o czym poniżej).

- Symbole zastępcze można nazwać - przypisując im liczby od 0 do liczby pozostałych argumentów funkcji `std::format` pomniejszonej o 1

  ```c++
  std::cout << std::format("{1} + {0} = {2}\n", n, m, n + m);
  ```

  W powyższym przykładzie za `{0}` zostanie podstawiona wartość `n` , za `{1}` - wartość `m`, a za `{2}` - wartość wyrażenia `n + m`.

- Jeżeli chcemy wyświetlić po prostu klamrę, to ją powielmy, np.:

  ```c++ 
  std::cout << std::format("{{}} + {{}} = {}\n", "{} + {}");
  ```

  Powyższa instrukcja wyświetla na ekranie napis:

  ```txt
  {} + {} = {} + {}
  ```

- W klamrach po dwukropku możemy umieścić dodatkowe informacje dotyczące pożądanego sposobu formatowania. Np. liczba całkowita oznacza minimalną szerokość pola, na jakiej ma być zapisana wartość danego wyrażenia po zastąpieniu symbolu zastępczego:

  ```c++
  std::cout << std::format("{:10} + {:10} = {:10}\n", n, m, n + m);
  ```

- W przypadku liczb zmiennopozycyjnych możemy wskazać, po kropce, liczbę miejsc znaczących, np. 

  ```c++
  std::cout << std::format("{:.4}\n", 123.36);
  ```

  wyświetla napis 

  ```txt
  123.4
  ```

  czyli wartość zaokrągloną do pierwszego miejsca po przecinku, w której występują 4 cyfry znaczące.

- Możemy też wskazać, czy chcemy, by dana wartość była wyrównana do lewej, do prawej czy wycentrowana na przeznaczonym dla niej polu. Służą do tego znaki `<`, `^` i `>`:

  ```c++  
  std::cout << std::format("{:>10} + {:^10} = {:<10}\n", "lewa", "środek", "prawa");
  ```

  - `<` - wyrównaj do lewej
  - `^` - wyśrodkuj
  - `>` - wyrównaj do prawej

  Dlatego wynik powyższej instrukcji to:

  ```txt
  |lewa      |  środek  |     prawa|
  ```

- Możemy zażądać wyświetlania znaku `+` lub spacji przy liczbach dodatnich, np.

  ```c++
  std::cout << std::format("{:<5} {:<+5} {:< 5}\n", -5, -5, -5);
  std::cout << std::format("{:<5} {:<+5} {:< 5}\n", 5, 5, 5);
  std::cout << std::format("{:<5} {:<5} {:<5}\n", 5, 5, 5);
  ```

  daje następujący wynik: 

  ```
  -5    -5    -5   
  5     +5     5   
  5     5     5    
  ```

  - `+` - wyświetlaj `+` przed liczbami nieujemnymi
  - ` ` (spacja) - wyświetlaj spację przed liczbami nieujemnymi

- Możemy też sobie zażyczyć wyświetlenia liczby całkowitej w trybie dziesiętnym (`d`), szesnastkowym (`x`), ósemkowym (`o`) lub dwójkowym (`b`):

  ```c++
  std::cout << std::format("10: {:15d} {:15d}\n", 35, 266);
  std::cout << std::format(" 2: {:15b} {:15b}\n", 35, 266);
  std::cout << std::format("16: {:15x} {:15x}\n", 35, 266);
  std::cout << std::format(" 8: {:15o} {:15o}\n", 35, 266);
  ```

  co daje następujący wynik:

  ```txt
  10:              35             266
   2:          100011       100001010
  16:              23             10a
   8:              43             412
  ```

- Możemy też zażądać, by liczby wyświetlane w systemie liczenia innym niż dziesiętny poprzedzone były odpowiednim przedrostkiem

  - `#` - wyświetlaj przedrostek sygnalizujący niestandardową podstawę systemu liczbowego

  ```c++ 
  std::cout << std::format(" 2: {:#15b} {:#15b}\n", 35, 266);
  std::cout << std::format("16: {:#15x} {:#15x}\n", 35, 266);
  std::cout << std::format(" 8: {:#15o} {:#15o}\n", 35, 266);
  ```

  co daje

  ```txt
   2:        0b100011     0b100001010
  16:            0x23           0x10a
   8:             043            0412
  ```

- Możemy wyświetlać adresy zmiennych:

  ```c++
  std::cout << std::format("{}", (void*)&s);
  ```

  - koniecznie należy zauważyć, że wyświetlany adres zmiennej `s`, czyli `&s`, został poprzedzony operatorem rzutowania do nieomawianego jeszcze typu `void*`. Jest to jedyny typ wskaźnikowy obsługiwany przez `std::format`. Póki nie poznasz bliżej wskaźników, możesz `(void*)` traktować jak magiczne zaklęcie.

- Możemy też dokładnie kontrolować sposób wyświetlania daty i czasu (por. przykład poniżej).

- i wiele innych...

### `std::print` i `std::println`

`std::print` to funkcja dodana w standardzie C++23. Działa jak `std::format`, ale nie potrzebuje `std::cout`. Czyli jest mniej pisania. Poniższy przykład

```c++
#include <print>
int main
{
   std::print("Ala ma {} {}\n", 1, "kota");
   std::print("|{:<10}|{:^10}|{:>10}|\n", "lewa", "środek", "prawa");
}
```

wyświetla

```txt
Ala ma 1 kota
|lewa      |  środek  |     prawa|
```

Co więcej, istnieje wersja tej funkcji, która sama dodaje znak przejścia do nowej linii na końcu napisu, `std::println`:

```c++
std::println("Ala ma {} {}", 1, "kota");
std::println("|{:<10}|{:^10}|{:>10}|", "lewa", "środek", "prawa");
```

- Funkcja `std::print` wymaga kompilacji w standardzie C++23

  - W `CmakeLists.txt` dodaj 

    ```cmake
    set(CMAKE_CXX_STANDARD 23)
    ```

  - lub w inny sposób przekaż odpowiednią flagą do kompilatora. Dla gcc i clang ta flaga to 
    `-std=c++23`.  

- Funkcje `std::print` i `std::println`wymagają włączenia do tekstu programu pliku nagłówkowego `print`:

  ```c++
  #include<print>
  ```

  