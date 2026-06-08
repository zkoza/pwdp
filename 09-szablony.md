## 9.1 Dlaczego typ danych przechowywanych w `std::vector` zapisywany jest w nawiasach ostrokątnych?

#### 9.1.1 Wprowadzenie

Jednym z problemów, jakie pojawiają się w językach ze statyczną kontrolą typów, a więc i w C++, jest kwestia powtarzalności kodu. Powiedzmy, że chcemy mieć funkcję, która będzie wyznaczać mniejszą z dwóch liczb. W języku C można by ją napisać tak:

```C 
int min(int n, int m)
{
    return (n < m) ? n : m;
}
```

Co się stanie, gdy taką funkcję wywołamy z argumentami zmiennopozycyjnymi, np. `min(3.14, 4.13)`? Ponieważ typ argumentów funkcji zadeklarowaliśmy jako `int`,  kompilator przed jej wywołaniem zrzutuje je do tego typu, obcinając część ułamkową. Czyli tak, jak byśmy wywołali tę funkcję jako `min(3, 4)`.  Raczej nie o to nam chodzi. Więc może taką funkcję należy zdefiniować z argumentami `double`? W końcu rzutowanie liczb całkowitych do `double` nie powoduje utraty dokładności. To prawda, ale wiąże się z dodatkową pracą - konwersja liczb całkowitych do typów zmiennopozycyjnych nie odbywa się za darmo, a ponadto porównywanie liczb zmiennopozycyjnych jest bardziej kosztowne niż typów całkowitoliczbowych. Istnieją też platformy, na których zmienne typu `double` nie są obsługiwane. Co więcej, istnieją typy arytmetyczne (np. `long double` lub całkowite 128-bitowe), których konwersja do typu `double` nie jest dokładna.   

W językach, w których może istnieć tylko jedna funkcja o danej nazwie (np. w języku C), wprowadza się funkcje o nazwach różniących się tylko przyrostkami. Np. litera `f` często sygnalizuje, że funkcja działa na typie `float`:  

```c++
float minf(float n, float m)
{
    return (n < m) ? n : m;
}
```

Oczywiście nie jest to szczególnie ładne rozwiązanie. Raczej puder na wrzodzie. 

W C++ możemy mieć dowolną liczbę funkcji o tej samej nazwie, co nieco upraszcza sprawę: możemy zdefiniować kilka funkcji `min` dla różnych typów:

```c++
int min(int n, int m)
{
    return (n < m) ? n : m;
}

double min(double n, double m)
{
    return (n < m) ? n : m;
}

float min(float n, float m)
{
    return (n < m) ? n : m;
}
```

To rozwiązanie jest dość sensowne, jeżeli dotyczy kilku, kilkunastu prostych funkcji. Jednak byłoby nie do przyjęcia dla całej biblioteki standardowej. Po pierwsze, zwiększyłoby to jej rozmiar wielokrotnie, po drugie, i tak nie obsługiwałoby typów niestandardowych. Tymczasem każdy chciałby mieć funkcję sortującą, która obsługiwałaby elementy dowolnych typów a nie tylko typów standardowych. Po trzecie, czy naprawdę trzeba wielokrotnie definiować dziesiątki, może setki funkcji o praktycznie identycznym kodzie źródłowym?   

#### 9.1.2 Dawne sposoby definiowania kodu niezależnego od typów, na których ten kod działa

Dawno, dawno temu  w języku C opracowano co najmniej 3 sposoby obejścia problemów, jakie wiążą się z chęcią uniknięcia powielania niemal identycznego kodu w językach ze ścisłą statyczną kontrolą typów.  

1. Pierwszy polega na użyciu makr:

    ```c++ 
    #define mix(x, y) (((x) < (y)) ? (x) : (y))
    ```

    Makra to element języka niepodlegający statycznej kontroli typów. Makra zdefiniowane dyrektywą`#define` to po prostu polecenia, w których argumenty formalne (tu: `x` i `y`) zastępowane są - przed właściwą kompilacją - argumentami faktycznymi. Np. użycie powyższego makra w wyrażeniu 

    ```c++
int a = min(2, 2 + 3);
    ```

    kompilator przekształciłby do 

    ```
int a = (((2) < (2 + 3)) ? (2) : (2 + 3));
    ```

    Niestety, makra czasem zachowują się w sposób nieoczywisty dla programisty. Nie chcielibyśmy też w ten sposób implementować złożonych struktur danych (np. tablicy dynamicznej) czy funkcji (np. `sort`). Dlaczego - można przeczytać bardziej szczegółowo np. [tutaj](https://betterembsw.blogspot.com/2017/07/dont-use-macros-for-min-and-max.html). 

2. Drugi sposób także opiera się na makrach (do deklaracji typów, np. klas) i nie będę go tu omawiać, bo to technologia dziś całkiem muzealna.

3. Trzeci sposób omija problem poprzez użycie wskaźników "na nie wiadomo co", czyli typu `void*`. Klasycznym przykładem jest tu przejęta w C++ z języka C funkcja sortująca `qsort`, której deklaracja zawiera aż trzy wskaźniki `void*`. 

    ```c++ 
    void qsort(void* ptr, 
               size_t count, 
               size_t size,
               int (*comp)(const void*, const void*));
    ```
    
    Podstawowa idea polega tu na chwilowym odrzuceniu systemu kontroli typów - właśnie poprzez zastosowanie typu `void*`. Sposób ten jest dość wymagający dla programisty (na pewno nie nadaje się jako materiał na kurs wstępny programowania), a w dodatku niezbyt efektywny. Więc go pomijam. Niemniej, funkcje z argumentami typu `void*` lub nawet `void**` są powszechnie stosowane w bibliotekach napisanych w języku C, warto mieć świadomość, jaka jest tego przyczyna.     

#### 9.1.3 Szablony

Szablony rozwiązują powyższe problemy poprzez wprowadzenie do języka konstrukcji przypominającej makra, jednak znacznie bardziej "inteligentnej". Są to właśnie szablony. 

Oto przykład szablonu funkcji `min`:

```c++
template<typename T>
T min(const T& n, const T& m)
{
    return (n < m) ? n : m;
}
```

Definicja szablonu zawsze rozpoczyna się od słowa kluczowego `template`, po którym występują nawiasy ostrokątne `< >`. Jest to miejsce na parametry szablonu. W powyższym przykładzie występuje jeden parametr oznaczony jako `T`. Parametry mogą być "typu" `typename` (lub, mającego identyczne znaczenie, `class`) i wtedy kompilator oczekuje w danym miejscu nazwy typu. Dlatego powyższy szablon funkcji można rozwinąć z typem `int`,  czyli jako `min<int>`, ale nie z liczbą całkowitą, czyli wyrażenie `min<8>` byłoby błędne.  

Parametrami szablonów mogą być też liczby typów całkowitoliczbowych. Stąd poprawna jest preambuła szablonu 

```c++  
template <typename T, int N>
```

Wróćmy do naszego przykładu szablonu funkcji `min`. Możemy użyć go następująco:

```c++
min<int>(4, 5 + 6);
```

W tym przypadku `min<int>` możemy traktować jak pełną nazwę funkcji. Dlatego `min<int>(1, 2)` i `min<double>(1, 2)` to dwa różne wyrażenia zawierające wywołania dwóch różnych funkcji. Gdy kompilator po raz pierwszy napotka wywołanie z danym parametrem, np. `min<int>(1, 2 + 3)`, rozpozna, że ma do czynienia z szablonem, a następnie wygeneruje z niego kod funkcji, po czym wywoła ją z odpowiednimi argumentami (tu: `1` oraz `2 + 3`). Funkcja ta będzie "normalną" funkcją C++, a więc rozpoznawalną i obsługiwana przez debugger. 

W C++ można definiować nie tylko szablony funkcji, ale i klas a nawet zmiennych. Oto przykład *bardzo uproszczonego* szablonu klasy reprezentującej wektor o N składowych:

```c++
template <typename T, int N>
class array
{
    T tab[N];
  public:
    auto size() const { return N; }
    T operator[](int n) const { return tab[n]; } 
    T& operator[](int n) { return tab[n]; } 
};
```

Klasy tej można by użyć nastepująco:

```c++
array<int, 8> tablica;
tablica[4] = 0;
auto s = tablica.size();   // 8
```

#### 9.1.4 Używanie szablonów

##### 9.1.4.1 Szablony funkcji

W większości przypadków, używając funkcji generowanych z szablonu, nie podaje się parametrów szablonu. Tak więc zamiast 

```c++ 
min<int>(4, 5 + 6);
```

zobaczymy w kodzie

```c++
min(4, 5 + 6);
```

W tym przypadku kompilator "domyśli się", że skoro oba argumenty funkcji `min<T>` są typu `int`, to `T = int` i potraktuje to wyrażanie, jakby zostało zapisane w postaci  `min<int>(4, 5 + 6)`. 

Parametry szablonu są konieczne, jeżeli kompilator nie może ich wydedukować na podstawie argumentów funkcji. Na przykład jeśli chcemy uzyskać mniejszą z liczb `int n` oraz `double x`, czyli zmiennych różnych typów, to wyrażenie `min(n, x)` nie pozwalałoby jednoznacznie określić parametru `T` szablonu, dlatego kompilator zgłosiłby błąd. W takich przypadkach podajemy wartość parametru `T` w nawiasach ostrokątnych tuż za nazwą funkcji:

```c++  
auto z = min<double>(n, x);
```

##### 9.1.4.2 Szablony klas

Tradycyjnie, podczas deklaracji obiektu klasy generowanej z szablonu klasy, podawało się jej parametry. Na przykład tak:

```c++ 
std::vector<int> v = {1, 2, 3, 4};
```

Od kilku lat można jednak ten zapis uprościć, pomijając parametry szablonu, które kompilator może wydedukować z inicjalizatora, Dlatego powyższą definicję obiektu `v` można uprościć do 

```c++  
std::vector v = {1, 2, 3, 4};
```

W tym przypadku kompilator na własne potrzeby przekształci ją do `std::vector<int> v = {1, 2, 3, 4};.`

#### 9.1.5 Dlaczego szablony są tak ważne w C++?

Szablony przez długie lata były swego rodzaju wizytówką C++ (dopóki inne języki programowania nie włączyły do swoich definicji podobnych mechanizmów), pozwalającą połączyć kilka wcześniej  nieosiągalnych w jednym języku programowania właściwości:

- szablony w pełni podlegają silnej statycznej kontroli typów, co jest cechą charakterystyczną języków ze statyczną kontrolą typów.
- szablony umożliwiają pisanie jednego, wspólnego kodu dla praktycznie nieskończonej liczby typów danych, na których on może działać (*single code base*), co upodabnia C++ do języków z dynamiczną kontrolą typów
- szablony umożliwiają kompilatorowi użycie wszystkich sposobów optymalizacji, jakie dostępne są dla zwykłych funkcji, a także kilka nowych, co powoduje, że niektóre operacje, np. sortowanie, są w C++ wykonywane nawet szybciej niż np. w C.    

Z powyższych powodów szablony są w C++ wszechobecne. Praktycznie cała biblioteka standardowa C++ opiera się na szablonach. Jako szablony udostępnia ona kontenery (np. `std::vector`) i algorytmy (np. `std::sort`). Nawet tak popularny typ, jak `std::string`, jest aliasem (alternatywną, prostszą nazwą) typu generowanego z szablonu, `std::basic_string<char>`. Podobnie, typ obiektu `std::cout` to generowany z szablonu typ `basic_ostream<char>`, który dostępny jest też pod uproszczoną nazwą (aliasem) `std::ostream`.

##### 9.1.5.1 Porównanie z językiem z dynamiczną kontrolą typów 

Przykładem języka z dynamiczną kontrolą typów jest Python. Funkcja `min` wyglądać w nim może następująco:

```python 
def min(a, b):
    return a if a < b else b
```

Charakterystyczną różnicą między tą definicją a analogicznym kodem w C++ jest brak deklaratorów typów. Funkcja w Pythonie "nie wie", na jakich obiektach działa. Zna tylko ich nazwy: `a` i `b`. Można więc wywołać ją na liczbach całkowitych, zmiennopozycyjnych, kombinacjach różnych typów liczbowych, ale też na napisach, listach czy obiektach klas użytkownika. Oto przykład interaktywnej sesji z interpreterem języka Python:  

```pyth
>>> min(1, 2)
1
>>> min(1.0, 2)
1.0
>>> min(1, 2.0)
1
>>> min("ala", "ola")
'ala'
>>> min([1, 2], [2, 3])
[1, 2]
>>> min([1, 2], [2])
[1, 2]
>>> min({1, 2}, {2})
>>> min("1", 1)
Traceback (most recent call last):
  File "<python-input-38>", line 1, in <module>
    min("1", 1)
    ~~~^^^^^^^^
  File "<python-input-30>", line 3, in min
    return a if a < b else b
                ^^^^^
TypeError: '<' not supported between instances of 'str' and 'int'
```

Jak widzimy, jedna funkcja w Pythonie obsługuje zasadniczo nieskończoną liczbę typów danych. Nic jednak nie jest za darmo. Skoro funkcja nie ma informacji o typach swoich argumentów, a chcemy, by język był bezpieczny i zawsze dawał oczekiwany wynik, to te informacje muszą być umieszczone w argumentach. Dlatego w języku Python wszystko jest obiektem. Każdy obiekt przechowuje informacje nie tylko o swojej wartości, ale i typie (i jeszcze kilka pól z danymi definiującymi obiekt). Tę informację interpreter języka odczytuje w chwili wywołania funkcji, po czym przy każdej operacji na jej argumentach sprawdza, czy ona w ogóle ma sens (czy została zdefiniowana). Porównanie `1 < 2` ma sens, ale `"1" <  2` już nie. To powoduje, że nawet rzecz tak zdawałoby się prosta, jak literał `1`, zajmuje w Pythonie kilkadziesiąt bajtów (w mojej implementacji: 24), podczas gdy w C++ są to maksymalnie 4 bajty, a w trybie kompilacji agresywnie optymalizującej kod - 0 (słowie: zero). 

​      







































































































   

​    