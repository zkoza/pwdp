## 2.3 Zakres zmiennej. Operator pobrania adresu. Przestrzeń nazw. 

Skoro typowe programy w C++ składają się z kilku, kilkunastu a nawet kilku tysięcy plików źródłowych, to jasne jest, że często powtarzają się w nich zmienne o tych samych nazwach. Pojawia się więc pilna potrzeba określenia zasad widoczności i czasu życia zmiennych i obiektów.  Podstawowymi koncepcjami umożliwiającymi zapanowanie nad tym aspektem programu w C++ są zakres i przestrzeń nazw. 

#### 2.3.1 Zakres

Zakres (ang. *scope*) to obszar kodu ograniczony klamrami ({}). 

Zmienne (i obiekty) dzielimy na globalne i lokalne ze względu na to, czy należą, czy nie należą do jakiegoś zakresu. 

Spójrzmy na następujący (dość sztuczny) program:

 ```c++
 int x = 9;          // zakres globalny
 
 int main()
 {
     int y = 8;      // zakres lokalny funkcji main
     if (y > 0)
     {
         int z = 9;  // zakres lokalny instrukcji if
         {
             int k = 9; // zakres lokalny
         }
         y = y + z;
     }
     return x + y;
 }
 ```

Występują w nim trzy pary klamer, a więc i trzy zakresy. Zmienna `x` zdefiniowana jest poza jakimkolwiek zakresem. Pozostałe zmienne zdefiniowane są wewnątrz klamer z treścią funkcji `main`.  Uwaga: klamry stosowane w definicji przestrzeni nazw *nie* definiują zakresu! 

##### 2.3.1.1 Zmienne globalne

Zmienne (i obiekty) globalne to zmienne zdefiniowane poza jakimkolwiek zakresem. W przykładzie z poprzedniego punktu zmienną globalną jest `x` i tylko `x`. Wszystkie funkcje w C++ są globalne (nie można definiować funkcji wewnątrz funkcji).  

##### 2.3.1.2 Zmienne lokalne

Zmienna (i obiekty) lokalne to wszystkie zmienne, które nie są globalne. W przykładzie z punktu 2.3.1 zmiennymi lokalnymi są `y`, `z` i `k` .   

##### 2.3.1.3 Czas życia zmiennej

Zmienna "żyje" od punktu jej definicji do końca zakresu, w którym została zdefiniowana. Zmienne (i obiekty) globalne są tworzone  i inicjalizowane przed uruchomieniem funkcji `main` i "żyją" co najmniej tak długo, jak długo nie zakończy się działanie tej funkcji (czyli w praktyce - do końca programu). 

##### 2.3.1.4 Operator pobrania adresu (&)

Każda zmienna (i każdy obiekt) zajmuje miejsce w pamięci operacyjnej. Jej nazwa to tylko udogodnienie, dla procesora liczy się adres, pod jakim dana zmienna umieszczona jest w pamięci. Ten adres możemy pobrać za pomocą operatora `&` (ampersand). Przepiszmy powyższy program tak, by wyświetlał adres zmiennych:

```c++  
#include <iostream>

int x = 9;          // zakres globalny

int main()
{
    std::cout << "&x = " << &x << "\n";
    int y = 8;      // zakres lokalny funkcji main
    std::cout << "&y = " << &y << "\n";
    if (y > 0)
    {
        int z = 9;  // zakres lokalny instrukcji if
        std::cout << "&z = " << &z << "\n";
        {
            int k = 9; // zakres lokalny
            std::cout << "&k = " << &k << "\n";
        }
        y = y + z;
    }
    return x + y;
}
```

Wynik działania tego programu może prezentować się nastepująco:

```txt
&x = 0x404020
&y = 0x7ffe23b56f3c
&z = 0x7ffe23b56f38
&k = 0x7ffe23b56f34
```

Pójdźmy o krok dalej i nazwijmy wszystkie zmienne użyte w tym przykładzie tak samo: `x`.

```c++
#include <iostream>

int x = 1;

int main()
{
    std::cout << "&x = " << &x << ", x = " << x << "\n";
    int x = 2;
    std::cout << "&x = " << &x << ", x = " << x << "\n";
    if (x > 0)
    {
        int x = 3;
        {
            std::cout << "&x = " << &x << ", x = " << x << "\n";
            int x = 4;
            std::cout << "&x = " << &x << ", x = " << x << "\n";
        }
        x = x + ::x;
    }
    return x + ::x;
}
```

To dość dziwny program, w którym wszystkie zmienne mają tę samą nazwę, `x`. Czy jednak jest to ta sama zmienna? Nie! Gdyż każda przechowywana jest w innym miejscu pamięci operacyjnej i ma swoją wartość!:

```txt 
&x = 0x404028, x = 1
&x = 0x7ffd73d5195c, x = 2
&x = 0x7ffd73d51958, x = 3
&x = 0x7ffd73d51954, x = 4
```

###### 2.3.1.4.1 Przesłanianie

Przedstawione powyżej zjawisko polegające na tym, że w nowym zakresie wprowadzamy zmienną o takiej samej nazwie jak zmienna zdefiniowana w zakresie nadrzędnym, nazywamy ***przesłanianiem***. 

###### 2.3.1.4.2 Operator zakresu

Zmiennej przesłoniętej nie możemy odsłonić - z jednym wyjątkiem. Za pomocą operatora `::` możemy uzyskać dostęp do przesłoniętej zmiennej globalnej. Por. instrukcję `return ::x + x;`.  Pierwsza z użytych tu zmiennych `x` to zmienna globalna (o wartości 1), a druga - lokalna (o wartości 2). 

###### 2.3.1.4.3 Przesłanianie a zakresy

W tym samym zakresie można zdefiniować tylko jedną zmienną (obiekt) o tej samej nazwie. 

### 2.3.2 Przestrzenie nazw

Drugim sposobem na unikanie konfliktów nazw w C++ są przestrzenie nazw. Każdy może zdefiniować własną przestrzeń nazw - i zwykle korzystają z tego biblioteki, umieszczając definiowane przez siebie zmienne i funkcje w osobnej przestrzeni nazw. Ilustruje to następujący (mocno akademicki) przykład:

```c++    
#include <iostream>

namespace X {
    int x = 1;
}

namespace Y {
    int x = 2;
}

int main()
{
   std::cout << X::x + Y::x << "\n";
}
```

- W powyższym programie zdefiniowano dwie przestrzenie nazw (ang. *namespaces*): `X` i `Y`.

- Dostęp do zdefiniowanych w nich zmiennych globalnych możliwy jest poprzez operator zakresu, `::`, przed którym wpisujemy przestrzeń nazw, z której chcemy wybrać daną zmienną. Por. instrukcja stanowiąca treść funkcji `main`:
  ``` c++
  std::cout << X::x + Y::x << "\n";
  ```

W praktyce jeszcze długo nie będziesz tworzyć własnych przestrzeni nazw ani używać bibliotek z tej cechy języka C++ korzystających. Niemniej, rozumiesz już mniej więcej, skąd się bierze i co oznacza `std::` zapisywane przy funkcjach, zmiennych i obiektach biblioteki standardowej C++.