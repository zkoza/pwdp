## 2.2 Zmienne typu `int`, `double`, `char`,`std::string`,  i `bool`

System typów w języku C++ jest niezwykle rozbudowany i, prawdę mówiąc, programiści C++ poznają go całe życie. Jednak istnieje kilka typów uniwersalnych, spotykanych w niemal każdym programie, a reguły ich dotyczące są proste. 

#### 2.2.1. `int`

Typ `int` służy do operacji na liczbach całkowitych (dodatnich, ujemnych i zera). Jego charakterystyczną cechą jest to, że jego reprezentacja odpowiada sprzętowej implementacji rejestrów całkowitoliczbowych na procesorach, co z kolei implikuje, że w komputerach z różnymi procesorami lub nawet tymi samymi, ale działających pod kontrolą różnych systemów operacyjnych  (np. 32- lub 64-bitowych) `int` może mieć inne właściwości.

Cechą charakterystyczną rejestrów (niemal?) wszystkich współczesnych komputerów jest to, że składają się z bitów, których liczba jest potęgą dwójki. W praktyce więc `int` musi być reprezentowane na 16, 32 lub 64 bitach, przy czym komputery osobiste współcześnie przechowują te liczby w rejestrach 32-bitowych. To z kolei oznacza, że w zmiennej typu `int` można przechować maksymalnie $2^{32}$ różnych wartości (to nieco ponad 4 miliardy). Czy dla zmiennych typu `int` istnieje zarówno wartość największa, równa $2^{31}-1$, jak i najmniejsza, równa $-2^{31}$. Ma to ciekawe konsekwencje. Co bowiem się stanie, gdy zwiększymy największą możliwą wartość zmiennej typu `int` o 1? Sprawdźmy:

```c++
#include <limits>
#include <iostream>

int main()
{
    int x = std::numeric_limits<int>::max();
    int y = std::numeric_limits<int>::min();
    std::cout << "największa wartość, jaką można zapisac w int =   " << x << "\n";
    x = x + 1;
    std::cout << "po zwiększeniu jej o 1 otrzymujemy              " << x << "\n";
    std::cout << "najmniejsza wartość, jaką można zapisac w int = " << y << "\n";
    std::cout << "liczba do niej przeciwna to                     " << -y << "\n";
}
```

Wynik działania tego programu w moim komputerze wygląda następująco:

```c++
największa wartość, jaką można zapisac w int =   2147483647
po zwiększeniu jej o 1 otrzymujemy              -2147483648
najmniejsza wartość, jaką można zapisac w int = -2147483648
liczba do niej przeciwna to                     -2147483648
```

[Tu można pobrać ten program](./cpp/w02/integer_overflow/) i sprawdzić, czy w Wasz komputer produkuje takie same wyniki. 

W powyższym kodzie widzimy m.in. następujące cechy języka C++:

- Deklaracja typu zmiennej zaczyna się od nazwy tego typu, po której następuje nazwa zmiennej.
- Każda instrukcja kończy się średnikiem.
- Liczby reprezentowane w typie `int` mogą być zarówno dodatnie, jak i ujemne. 
- Wartości zmiennych typu `int` są ograniczone z dołu i z góry. 
  - Wartości minimalne i maksymalne typów wbudowanych (czyli zdefiniowane bezpośrednio w specyfikacji języka) można uzyskać z wartości wyrażeń `std::numeric_limits<T>::min()` oraz `std::numeric_limits<T>::max()` , gdzie zamiast `T` należy wpisać nazwę tego typu. 
  - Wyrażenia te zdefiniowano w pliku `limits`, stąd na początku programu instrukcja `#include <limits>`.
- Liczby reprezentowane  w typie `int` mają strukturę pierścienia: po zwiększeniu największej z nich o `1`, otrzymuje się liczbę najmniejszą. Podobnie, po dojęciu 1 od najmniejszej dostaje się liczbę największą. 
- Suma dwóch dodatnich liczb typu `int` może być ujemna. 
- Liczba przeciwna do liczby ujemnej przechowywanej w typie `int` może być ujemna (sic!).

Istnieje bardzo wiele operacji na zmiennych typu `int`. Oczywiście należą do nich `+`, `-`, `/` i `*`. Na omówienie wszystkich w tej chwili jest zbyt wcześnie. 

Należy jednak pamiętać, że reguła "pamiętaj cholero, nigdy nie dziel przez zero" ma dla typu `int` szczególe znaczenie: dzielenie przez zero zmiennych typu `int` zwykle powoduje natychmiastowy pad programu.  

#### 2.2.2 `double`

Typ `double` służy do reprezentowania liczb rzeczywistych. Ponieważ jednak odpowiada on specjalnym rejestrom procesora, które zwykle zawierają 32 lub 64 bity, nie jest w stanie przechować dokładnie każdej liczby rzeczywistej. W związku z tym typ `double` zasadniczo przechowuje wartości przybliżone liczb  rzeczywistych. Zaokrąglenie następuje mniej więcej na 17. cyfrze znaczącej, więc błąd zaokrąglenia pojedynczej liczby nie jest wielki. Niemniej, w wielu zastosowaniach nawet taki mały błąd może szybko urosnąć do rozmiarów apokaliptycznych. Problemem tym zajmuje się analiza numeryczna - tu temat prawie kończymy. Prawie, bo powinniśmy pamiętać, że wewnętrzna reprezentacja liczb typu `dounle`, zwanego też typem zmiennopozycyjnym bądź zmiennoprzecinkowym, to liczby wymierne postaci $\pm n \times 2^{m}$, gdzie $n$ i $m$ to liczby całkowite, przy czym $n$ jest nieujemne, a $m$ może być ujemne. W szczególności liczby całkowite (niezbyt duże), np. 3, 234, 3451, a także ułamki o mianowniku równym 2, 4, 8,... są zapisywane w typie `double` bez zaokrągleń, czyli dokładnie. Kolejna niezwykle ważna cecha tego typu to brak łączności dodawania i odejmowania. Oznacza to, że jeżeli `x`, `y` i `z` to liczby typu `double`, to rzadko kiedy wyrażenia `(x + y) + z` oraz `x + (y + z)` mają takie same wartości.

Przykład użycia:

```c++
double pi = 3.14;
double milion = 1e6;
std::cout << milion + pi << "\n";
std::cout << std::numeric_limits<double>::max() << "\n";
```

#### `2.2.3 std::string, char i char[N]` 

##### 2.2.3.1 char

Programy zwykle posługują się nie tylko liczbami, ale i tekstem. Tekst może składać się z pojedynczych liter. W C++ pojedyncze litery (ogólnie: znaki) reprezentuje typ `char`.

```c++
char c = 'a';
```

Jak widać, literały znakowe zapisujemy w apostrofach, np. `'a'`, `'x'`, `'!'`. Literałami znakowymi mogą być tylko znaki o kodzie [ASCII](https://pl.wikipedia.org/wiki/ASCII) mniejszym od 128. W szczególności polskie litery nie mogą być użyte jako literały znakowe!

```c++ 
char c = 'Ą'; // błąd! Ą nie jest elementem zbioru znaków ASCII
```

Istnieją znaki specjalne, których nie da się zapisać jako tzw. glifu, czyli znaku drukarskiego widocznego na ekranie monitora czy wydruku. Są to m.in. wszystkie znaki sterujące (używane niegdyś np. do sterowania pracy drukarek wierszowych). Zapisuje się je za pomocą specjalnej notacji dwuznakowej, w której pierwszym znakiem jest ukośnik. Najbardziej znanym znakiem specjalnym jest znak przejścia do nowej linii, `'\n'`. Inne nieoczywiste dwuznaki reprezentujące jeden znak to m.in. `\\`, `\'` i `\"`. 

##### 2.2.3.2 `const char[N]`

Zwykle interesują nas nie pojedyncze litery, a cały łańcuchy liter, czyli tekst. Tekst można zapisać jako literał znakowy, umieszczając go między znakami cudzysłowu:

```c++ 
auto s = "Napis może zawierać polskie litery i nie tylko, בוקר טוב"
```

Literały napisowe przechowywane są w tablicach znaków. Na przykład typem wyrażenia `"Ala"` jest `const char[4]`. Modyfikator `const` informuje, że taki literał jest niemodyfikowalny. Z kolei `4` w nawiasach kwadratowych oznacza, że napis `"Ala"` przechowywany jest w tablicy 4 znaków. Dlaczego 4, skoro litery w napisie są tylko 3? Otóż kompilator zawsze na końcu literału napisowego dodaje specjalny znak, pełniący rolę znacznika końca tegoż napisu (zwanego też wartownikiem napisu). Znak ten ma wartość `0` i może być zapisany jako `\0`.  

##### 2.2.3.3 `std::string`  

Tablice znaków to dość niewygodny ("prymitywny") w użyciu sposób przechowywania tekstów. W praktyce częściej stosuje się typ `std::string`. Przykład:

```c++ 
#include <iostream>
#include <string>

int main()
{
  std::string s = "Ala";
  s = s + " ma kota.";
  std::cout << s << " -> " << s.length() << " znaków\n";
}
```

- typ `std::string` zaimplementowano w pliku `string` biblioteki standardowej - 
  por. `#include <string>`.
- `operator::` oddziela nawę typu (np. `string`) lub obiektu (np. `cout`) od nazwy przestrzeni nazw, w której ten typ lub obiekt został zdefiniowany.
  - Wszystkie elementy biblioteki standardowej znajdują się w przestrzeni nazw `std` (z kilkoma wyjątkami przejętymi z języka C, w którym przestrzeni nazw nie ma).

- Typ `std::string` jest wygodniejszy w użyciu od `char[N]`, gdyż zaimplementowano w nim bardzo wiele użytecznych funkcji. Można dzięki nim łatwo łączyć ze sobą obiekty tego typu w większy napis (tu: w wyrażeniu `s + " ma kota."` ), wyszukiwać podciągi (od przodu lub od tyłu), usuwać podciągi, porównywać z innymi napisami itp. Obiekty tego typu przechowują też informację o rozmiarze przechowywanego w nich tekstu, co jest bardzo wygodne (tu: `s.length()`). 

Nie jest moją intencją opisywać tu w sposób kompletny klasę `std::string`. Dokumentacja oficjalna, zapisana dość suchym językiem, znajduje się w serwisie [cpprefernce](https://en.cppreference.com/w/cpp/string/basic_string).  

#### 2.2.4 `bool`

Zmienne typu `bool` mają dwie wartości: `true` ("prawda") lub `false` ("fałsz"). Głównym obszarem ich zastosowań są wyrażenia logiczne. Np. typami wartości wyrażeń w rodzaju ` x < 0` (`x` jest mniejsze od `0`) czy `x == y` (`x` jest równe `y`)  jest `bool`. 

Przykład: 

```c++ 
bool dodatni = x > 0;
```

Wyrażenia typu `bool` można konwertować z liczb i na liczby. W wyrażeniu arytmetycznym `true` konwertowane jest do `1`, a `false` do `0`. Dlatego `1 + true` to `2` (ale praktycznie mało kto tej konwersji używa). Z kolei jeżeli należy dokonać konwersji wyrażenia arytmetycznego na logiczne, czyli np. z typu `int` do typu `bool`, to `0` konwertowane jest na `false`, a wszystkie inne wartości na `true`. Dlatego w instrukcji (nico dziwacznej) `bool b = 7`,  zmienna`b` zostanie zainicjalizowana na `true`.     

#### 2.2.5 Inne typy podstawowe

System typów w języku C++ jest niezwykle rozbudowany i niektórych jego aspektów sam do tej pory nie rozumiem w 100%. Nie ma jednak potrzeby uczyć się od razu wszystkiego. Tu nadmienię tylko, jakie inne typy podstawowe spotyka się dość często w programach napisanych w C++.

##### 2.2.5.1 `unsigned`

Typ `unsigned`, zapisywany też jako `unsigned int`, jest podobny do typu `int`, wyróżnia go jednak to, że nie ma w nim liczb ujemnych. Czyli `unsigned` może reprezentować zero i niezbyt duże liczby naturalne. Współcześnie jego zakres przebiega od 0 do $2^{32}$, czyli największa liczba tego typu ma wartość nieco ponad 4 miliardy.

##### 2.2.5.2 `short`, `long` i `long long`

Typ `short` to krótsza (zwykle 16-bitowa) wersja typu `int`. Używana rzadko, głównie dla oszczędności pamięci operacyjnej w przypadku korzystania z ogromnych tablic niewielkich liczb całkowitych. Maksymalna wartość w tym typie to zaledwie $2^{15} - 1$, czyli $32~767$. 

Typ `long long` to dłuższa, zwykle 64-bitowa wersja typu `int`. Maksymalna wartość w tym typie to  $2^{63} - 1$, czyli ok. $10^{19}$ (dokładnie: $9~223~372~036~854~775~807$).

Typ `long` to jakieś nieporozumienie. Obecnie znaczy co innego dla kompilatorów Microsoft i co innego dla kompilatorów działających w Linuksie (`gcc`, `clang`). Nie używaj.

Wszystkie powyższe typy mają też wersje bez znaku, np. `unsigned short` itd. 

Przykład:

```c++   
short i = 10;
unsigned long long n = 0;
```

##### 2.2.5.2 `size_t`, `int8_t`, `int16_t` itp. 

W programach napisanych w C++ trudno nie spotkać się z typem `size_t` używanym przez bibliotekę standardową m.in. jako typ dla liczby elementów zdefiniowanych w tej bibliotece kontenerów (np. `std::string`). Standard języka mówi, że `size_t` jest typem bez znaku. W praktyce jest on równoważny typowi `unsigned long long int`. 

Jak wiemy, podstawowy typ dla liczb całkowitych, `int`, zależy od platformy, na której wykonywany jest program, co bywa niewygodne. Dlatego do C++ dodano też typy o ściśle określonej reprezentacji bitowej. I tak typ `int8_t` to typ całkowity ze znakiem reprezentowany na 8 bitach, a `uint8_t` to jego odpowiednik bez znaku. Analogicznie definiuje się typy `int16_t`, `int32_t`, `int64_t`, `uint8_t`, `uint16_t`, `uint32_t` i `uint64_t`.  Wszystkie one zdefiniowane są w pliku nagłówkowym `cstdint`, który należy włączyć do programu dyrektywą `#include`.  

Przykład:

```c++        
#include <cstdint>
#include <limits>
#include <iostream>

int main()
{
   std::cout << std::numeric_limits<uint64_t>::max() << "\n"; // 2^64 - 1
   std::cout << std::numeric_limits<uint32_t>::max() << "\n"; // 2^32 - 1
   std::cout << std::numeric_limits<uint16_t>::max() << "\n"; // 2^16 - 1
}
```

Wynik działania tego programu:

```txt
18446744073709551615
4294967295
65535
```

##### 2.2.5.3 `float` i `long double`

Typ `float` to krótsza, "oszczędna" wersja typu `double`. Nie używaj, jeśli nie musisz.

Typ `long double` to dłuższa, "na bogato"  wersja typu `double`. Zwykle zajmuje 128 bitów, z których wykorzystywane jest 80. Nie używaj, jeśli nie musisz. 

#### 2.2.6 Literały

Literały całkowitoliczbowe można zapisywać w różnych systemach liczbowych dzięki notacji przedrostkowej  

| Przedrostek | System <br />liczbowy | cyfry                           | przykład  | wartość |
| ----------- | --------------------- | ------------------------------- | --------- | ------- |
|             | dziesiętny            | 0,1,2,3,4,5,6,7,8,9             | `26`      | 26      |
| `0x`        | szesnastkowy          | 0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f | `0x1a`    | 26      |
| `0`         | ósemkowy              | 0,1,2,3,4,5,6,7                 | `032`     | 26      |
| `0b`        | dwójkowy              | 0,1                             | `0b11010` | 26      |

W przypadku systemu szesnastkowemu cyfrom `a` ,`b`, ..., `f` odpowiadają odpowiednio liczby `10`, `11`,...,`15`. Zamiast liter małych też można używać liter dużych, mających takie samo znaczenie (np. wyrażenia  `0xa` oraz `0XA` mają tę samą wartość `10`).     

| Cyfra szesnastkowa | Wartość |
| ------------------ | ------- |
| `a` lub `A`        | 10      |
| `b` lub `B`        | 11      |
| `c` lub `C`        | 12      |
| `d` lub `D`        | 13      |
| `e` lub `E`        | 14      |
| `f` lub `F`        | 15      |

Przykład:

```c++
int n = 0xFF;   // n = 15*16 + 15 = 255
int m = 0b1101; // m = 8 + 4 + 1 = 13 
```

Literały mogą mieć też przyrostki sygnalizujące ich typ. Popularne przyrostki to `u` ("unsigned"), `l` ("long") i `ll` ("long long"). Na przykład w instrukcjach:

```c++
auto k = 1;     // int; wartość: 1
auto n = 1u;    // unsigned; wartość: 1
auto m = 0xall; // long long w notacji szesnastkowej; wartość: 10
```

`n` ma typ dedukowany jako `unsigned int`, a `m` jako `long long`. 

Przyrostek `f` sygnalizuje, że dany literał ma typ `float`. 

```c++ 
auto x = 3.14f; // x jest typu float
auto y = 3.14;  // y jest typu double
```

Jeżeli literał całkowitoliczbowy nie ma przyrostka, to jego typem jest `int`. Analogicznie, jeżeli literał zmiennopozycyjny nie ma przyrostka, to jego typem jest `double`. 

```c++
auto n = 10;   // n jest typu int
auto x = 3.14  // x jest typu double
auto y = 1e-4; // y jest typu double i ma wartość 0.0001 (notacja inżynierska)
```

Osobnym problemem są literały znakowe i napisowe. Jak wiemy, znak `\` ma tu szczególne znaczenie i jest to tzw. *escape character*: znak. który sam nie jest interpretowany jako znak, lecz jako przełącznik trybu znaków specjalnych. To znak lub znaki stojące za nim niosą informację o tym, o jaki znak chodzi. Np. `\n` to znany już znak przejścia do kolejnego wiersza, a np. `\"` to po prostu znak cudzysłowu. Znaki można też zapisywać w postaci ósemkowej i szesnastkowej. Na przykład skoro wartością ASCII znaku `'A'` jest 65, czyli szesnastkowo `'41'` (bo 65 = 4*16 + 1), to możemy tę literę zapisać także jako `\x41`. Czyli jako przedrostek stosujemy `'\x'`, a po nim wpisujemy kod ASCII w notacji szesnastkowej. Dlatego tajemnicza instrukcja

```c++   
std::cout << "\x41\x42\x43\n";
```

jest równoważna instrukcji

```c++
std::cout << "ABC\n";
```

i produkuje napis

```txt
ABC
```

#### 2.2.7 Konwersje i promocje w wyrażeniach

Jeżeli w *wyrażeniu arytmetycznym* (np. dodawaniu) któryś z argumentów jest "mniejszy" niż `int`, tzn. jeżeli zapisywany jest na mniejszej liczbie bitów, to zostanie poddany automatycznej promocji do typu `int`. Jest to źródłem ciekawych błędów. Np. jaki jest typ wyrażenia `'A' + 1`? Wielu początkujących adeptów C++ myśli, że `char`, a wartością jest `'B'`. Tymczasem typ pierwszego argumentu dodawania jest najpierw promowany z `char`  do `int`, w wyniku czego po lewej stronie plusa pojawia się liczba 65, będąca [kodem ASCII](https://pl.wikipedia.org/wiki/ASCII) znaku `'A'`.  Wynikiem dodawania `65 + 1` jest oczywiście `66`. Dlatego instrukcja

```c++
std::cout << 'A' + 1 << "\n"; 
```

daje następujący wynik:

```txt
66
```

Warto w tym miejscu zapamiętać, że w C++ typów znakowych: `char`, `signed char` i `unsigned char` można używać jak liczb zapisywanych na 8 bitach. W takich przypadkach znaki (czyli zmienne typu char) konwertowane są na liczby (i podobnie liczby na znaki) zgodnie z tabelą ASCII. To tłumaczy dość nieoczekiwany wynik instrukcji

```c++    
std::cout << std::numeric_limits<unsigned char>::max() << "\n";
```

który w moim komputerze wygląda następująco:

```
�
```

Otóż typem wartość wyrażenia `numeric_limits<T>::max()` jest `T`, czyli w powyższym przypadku jest to `unsigned char`. Obiekt `std::cout` wyświetla wyrażenia typu `unsigned char` jako znaki a nie liczby. Niestety, znak o wartości 255 nie mieści się w tabeli ASCII, która standaryzuje jedynie znaki o wartościach od 0 do 127. Interpreter mojego terminala interpretuje więc znak o wartości 255 (bitowo: `0b11111111`) jako początek litery zapisanej w systemie kodowania [UTF-8](https://pl.wikipedia.org/wiki/UTF-8). Problem w tym, że żadna litera z tego zestawu nie może zacząć się od takiej kombinacji bitów. Czyli błąd. Znak � występuje w zestawie [znaków specjalnych standardu UNICODE](https://en.wikipedia.org/wiki/Specials_(Unicode_block)), gdzie definiowany jest jako *REPLACEMENT CHARACTER used to replace an unknown, unrecognised, or unrepresentable character* (znak zastępczy wykorzystywany jako zamiennik znaku nieznanego, nierozpoznanego lub niemającego swojej reprezentacji). 

Jeżeli chcemy ujrzeć znak jako liczbę, musimy skonwertować ją do typu liczbowego. Np. tak:

```c++
int mx = std::numeric_limits<unsigned char>::max();
std::cout << mx << "\n";
```

co daje oczekiwany wynik:

```c++
255
```

Kolejną cechą wyrażeń jest konwersja typów całkowitych do `double`, jeżeli jeden z argumentów operatora arytmetycznego jest typu `double`. Tak więc w wyrażeniu `n + x`, gdzie `n` jest typu `int` a `x` jest typu `double`, kompilator najpierw wygeneruje kod konwersji wartości `n` na typ `double` , a potem operację dodawania jej do wartości `x`.

##### 2.2.7.1 static_cast<T> i inne proste rzutowania  

W C++ istnieją operatory rzutowania (konwersji) jednego typu na drugi. Stosuje się co najmniej 4 rodzaje notacji:

```c++
auto i = static_cast<int>('a');
auto j = int('a');
auto k = (int)'a';
auto l = int{'a'};
```

Każda z powyższych instrukcji konwertuje wyrażenie typu `char` (tu: `'a'`) na wyrażenie typu `int`. Każda ze zmiennych `i`, `j`, `k`, `l` jest więc typu `int` i ma wartość kodu ASCII znaku `a`, czyli 97.

W programach profesjonalnych używa się wyłącznie pierwszej notacji. W programach pisanych "dla siebie" częściej widuje się bardziej zwięzłe notacje 2., 3. i, chyba nieco rzadziej, 4.
