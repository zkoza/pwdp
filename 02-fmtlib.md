#### 2.6.1 Biblioteka fmtlib

Biblioteka [fmtlib](02-fmtlib.md) to dobra alternatywa dla operacji wyjścia, stanowiąca inspirację dla `std::format` i `std::print`. Jeżeli Twój kompilator nie obsługuje którejś z tych funkcji biblioteki standardowej, nic nie stoi na przeszkodzie, by używać właśnie  `fmtlib`. Jest to tym prostsze, że zawiera ona wzorcową implementację funkcji `format` i `print`. 

Rozpatrzmy prosty przykład (stąd można pobrać [projekt](./cpp/w02/fmtlib/)):

```c++ 
#include <iostream>
#include <fmt/format.h>

int main()
{
    int n = 15;
    int m = 16;

    std::cout << fmt::format("{} + {} = {}\n", n, m, n + m);
    fmt::print("Ala ma {}\n", "kota");
    fmt::println("Ola ma {}\n", "psa");
}
```

- Domyślnie biblioteka przechowuje swój interfejs w pliku `<fmt/format.h>`, który należy włączyć do programu makropoleceniem `#include`.
  - Uwaga: jego dokładna lokalizacja zależy od sposobu instalacji biblioteki.  
-   Zamiast przestrzeni nazw `std` używamy przestrzeni nazw `fmt`. Stąd wyrażenia w rodzaju
  - `fmt::fotmat`
  - `fmt::print` 
  - `fmt::println`

I to wszystko! Prawie wszystko. Musimy bowiem poinformować kompilator, by dołączył do naszego programu skompilowane wersje funkcji zawartych w bibliotece. Możemy tego dokonać na kilka sposobów, zależnie od tego, jak kompilujemy program.

#### 2.6.1.1 Kompilacja za pomocą CMake

Jeżeli nasze programy kompilujemy za pośrednictwem programu `cmake`, nasz skrypt `CMakeLists.txt` musi ulec drobnej modyfikacji. Oto przykład minimalnego pliku `CMakeLists.txt` dołączającego do naszego programu bibliotekę `fmtlib`:

```cmake  
cmake_minimum_required (VERSION 3.10)
project(fmtlib-demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(fmtlib-demo main.cpp)
target_link_libraries(fmtlib-demo PUBLIC fmt)
```

- Zupełnie wystarcza język C++ w standardzie C++11. Oczywiście użycie nowszego standardu też jest możliwe.  
- Musimy dodać instrukcję `target_link_libaries` łączącą nasz program z biblioteką `fmtlib`. W najprostszej konfiguracji posiada ona 3 argumenty (oddzielone spacjami a nie np. przecinkami!) 
  - Argument 1: nazwa programu wynikowego. Tu: `fmtlib-demo`. W systemach WIndows może mu odpowiadać plik o nazwie `fmtlib-demo.exe`. 
  - Argument 2: słowo `PUBLIC` lub `PRIVATE`. W małych programach oba warianty będą działały tak samo. 
  - Argument 3: nazwa dołączanej biblioteki. Tu: `fmt`.

#### 2.6.1.2 Kompilacja "z ręki"

Programy możemy też kompilować bezpośrednio w linii komend. W przypadku kompilatora g++ odpowiednia komenda to:

 ```bash 
 > g++ main.cpp -lfmt
 ```

- Opcja `-lfmt` łączy program z biblioteką `fmt`. Można ją taż zapisać w nieco bardziej zrozumiały sposób, wstawiając spację między `l` i nazwę biblioteki, jednak jest to sposób rzadziej wykorzystywany:

  ```bash 
  > g++ main.cpp -l fmt
  ```

  Literka `l` pochodzi od słowa *link*, czyli "łączyć". 

  #### 2.6.2 Sztuczka z przestrzenią nazw

Jeżeli ktoś jest znużony ciągłym poprzedzaniem nazw funkcji `format`, `print` i `println`   nazwami ich przestrzeni nazw, czyli np. `std::format` (dla biblioteki standardowej) lub `fmt::format` (dla biblioteki fmtlib), można uprościć zapis za pomocą instrukcji `using`:

```c++
#include <iostream>
#include <fmt/format.h>

using std::cout;     // nie trzeba już pisać std::cout, wystarczy cout
using fmt::format;   // nie trzeba już pisać fmt::format, wystarczy format
using fmt::print;    // nie trzeba już pisać fmt::print, wystarczy print
using fmt::println;  // nie trzeba już pisać fmt::println, wystarczy println

int main()
{
    int n = 15;
    int m = 16;

    cout << format("{} + {} = {}\n", n, m, n + m);
    print("Ala ma {}\n", "kota");
    println("Ola ma {}\n", "psa");
}
```

- W ten sposób można uprościć użycie każdej funkcji zdefiniowanej w dowolnej przestrzeni nazw. 

- Istnieje też metoda hurtowego importu wszystkich nazw z przestrzeni nazw, czyli deklaracja `using namespace`:

  ```c++
  using namespace std;
  ```

  Odpowiednia komenda importująca do globalnej przestrzeni nazw wszystkie nazwy z biblioteki `fmt` to oczywiście
  
  ```c++   
  using namespace fmt;
  ```
  
  Takie włączanie całych bibliotek uważane jest za niezbyt profesjonalne, gdyż może prowadzić do nieporozumień czy wręcz błędów. Na przykład  







