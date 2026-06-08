## 8.2.1 Sekcje prywatne i publiczne

#### 8.2.1.1 Wprowadzenie

Przypomnijmy najprostszy sposób definiowania klasy poprzez zamianę słowa kluczowego `struct` w definicji struktury na słowo kluczowe `class`:

```c++
class Pixel
{
    int x;
    int y;
};
```

Wiemy, że możemy definiować (=tworzyć) obiekty tej klasy:

```c++
int main()
{
    Pixel p;  
}
```

W powyższym przykładzie utworzono ("skonstruowano") obiekt `p` typu ("klasy") `Pixel`.  Co się jednak stanie, gdy spróbujemy sięgnąć do którejś z jego składowych?

```c++
int main()
{
    Pixel p;
    p.x = 0;
}
```

W tym przypadku kompilator zgłosi błąd:

```txt
<source>: In function 'int main()':
<source>:12:7: error: 'int Pixel::x' is private within this context
   12 |     p.x = 0;
      |       ^
<source>:5:9: note: declared private here
    5 |     int x;
      |         ^
Compiler returned: 1
```

Kompilator informuje nas, że w deklaracji klasy `Pixel` zadeklarowaliśmy składową (=pole) `x` jako prywatną.  

#### 8.2.1.2 Sekcje prywatne i publiczne 

Jedną z głównych różnic między strukturami w języku C a klasami w C++ jest wprowadzenie w tym drugim koncepcji "praw dostępu" do składowych oraz związanych z tym deklaratorów tego dostępu (ang. *access specifiers*). Rozróżnia się trzy poziomy praw dostępu:

- ***public*** - dostęp publiczny. Wszędzie tam, gdzie dostępny jest obiekt, można sięgać do jego składowych
- ***protected*** - dostęp chroniony. Do składowych danego obiektu można sięgać wyłącznie w definicji jego klasy oraz w definicjach klas z niej wyprowadzonych przez dziedziczenie. Tego typu dostępu nie będę tu omawiał.
- ***private*** - dostęp prywatny. Do składowych danego obiektu można sięgać wyłącznie w definicji jego klasy (i tzw. funkcji zaprzyjaźnionych). 

Jak się to ma do przykładu ze wstępu. Otóż w `main`, a więc poza definicją klasy, utworzyliśmy obiekt `p` klasy `Pixel`. Następnie spróbowaliśmy sięgnąć do jego składowej `x`, żeby nadać jej wartość `0`. Jest to jednak zabronione, gdyż domyślnie wszystkie nazwy definiowane w klasie mają atrybut `private`, nie można więc do nich sięgać poza definicją klasy. 

Rozwiązanie tego problemu jest proste: aby móc sięgać do jakiejś składowej poza definicją klasy, należy nadać jej atrybut `public`:

```c++ 
class Pixel
{
  public:
    int x;
    int y;
};
```

Teraz możemy wszędzie w naszym programie sięgać zarówno do składowej `x`, jak i `y`, gdyż obie są publiczne. Nasza klasa jest całkowicie nierozróżnialna od analogicznie zdefiniowanej struktury. 

Po co więc całe to zamieszanie z klasami, skoro wróciliśmy do struktury, tyle że musieliśmy użyć słowa kluczowego `class` oraz deklaratora `public:`?

Tryby dostępu pozwalają nam podzielić definicję typu użytkownika (= klasy) na (publiczny) interfejs i (prywatną) implementację. Żeby jednak to, o czym właśnie napisałem, nabrało sensu, musimy pójść dalej - i zapoznać się z koncepcją funkcji składowych, bo to one z reguły tworzą ten "publiczny interfejs klasy".