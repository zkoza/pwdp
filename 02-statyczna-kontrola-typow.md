### 2. 1 Statyczna kontrola typów. Definicje i deklaracje

#### 2.1.1 Statyczna kontrola typów

Statyczna kontrola typów to jeden z fundamentów C++. Ale co to znaczy, "statyczna kontrola typów"? Mamy tu trzy słowa, z których każde ma specyficzne znaczenie w informatyczne.

Po pierwsze - **typ**. Typ to pewna cecha przypisywana każdemu poprawnemu wyrażeniu języka programowania. Określa on reprezentację maszynową wartości tego wyrażenia oraz pełny zestaw możliwych operacji, jakie na nim można wykonać. Na przykład w C++ typem wyrażenia `1 + 3` jest `int`, a typem wyrażenia `"Ala"` jest `const char[4]`. To samo wyrażenie w różnych językach programowania może mieć inne znaczenie (np. `'AB'` w Pythonie znaczy coś zupełnie innego niż w C++), dlatego biegłość w  rozpoznawania typów wyrażeń to podstawowa umiejętność każdego programisty. 

Po drugie - **kontrola**. Kontrola typów to mechanizm, za pomocą którego komputer sprawdza, czy operacja na danym wyrażeniu jest w ogóle możliwa, a jeśli tak, to czy można ją wykonać bezpiecznie. Kontrola typów jest pierwszym elementem systemu stojącego na straży poprawności naszych programów. 

Po trzecie - **statyczność**. W żargonie komputerowym słowo "statyczny" zwykle odnosi się do "wykonywany przed uruchomieniu programu". W języku C++ **statyczną kontrolę typów** przeprowadza kompilator podczas kompilacji programu. Oznacza to, że kompilator "dedukuje" typ każdego wyrażenia, a następnie sprawdza, czy zapisane w programie operacje na tych wyrażeniach są zgodne ze specyfikacją ich typów. 

Przeciwieństwem statycznej kontroli typów jest kontrola dynamiczna, z jaką mamy do czynienia głównie w językach skryptowych (interpretowanych), jak Python czy JavaScript. W tych językach każdy obiekt, np. `x`, może w każdej chwili zmienić swój typ. Dlatego interpreter, napotykając wyrażenie w rodzaju `x.size()` musi podczas działania programu "zajrzeć" do `x` i sprawdzić, czy jego klasa posiada składową `size`. Nawet interpretując tak proste wyrażenie jak `x = x + 1` interpreter musi podczas działania programu za każdym razem sprawdzić, czy w tej chwili typ `x` dopuszcza możliwość dodawania obiektów tego typu do liczb całkowitych. Problemu tego nie ma w językach ze statyczną kontrola typów, jak C++. Chyba najważniejszą zaletą statycznej kontroli typów jest umożliwienie kompilatorowi stosowania bardzo agresywnych metod optymalizacji kodu, dzięki czemu programy są efektywne zarówno pod względem wykorzystania procesora, jak i pamięci operacyjnej. Wadą jest zwykle bardziej złożona definicja języka, przeniesienie wielu zadań na programistę, dłuższe pisanie kodu. Stąd można już zrozumieć, dlaczego programy pisane w C++ są kilka, kilkanaście, a nawet kilkadziesiąt razy szybsze niż ich odpowiedniki napisane w Pythonie czy Matlabie, ale jednocześnie samo napisanie wydajnego kodu w C++ wymaga znacznie większego nakładu pracy, zwykle  popartego latami doświadczenia.

#### 2.1.2 Definicje

Wróćmy do C++ i statycznej kontroli typów. Aby coś takiego w ogóle było możliwe, kompilator musi wiedzieć podczas kompilacji, jaki jest typ nie tylko literalnych wyrażeń typu `1 + 2`, ale i takich wyrażeń, w których występują zmienne i obiekty, np. `z = x + 1;`. W tym przypadku kompilator musi móc określić już podczas kompilacji, czy do `x` można dodać `1` oraz czy wynik tej operacji można przypisać do `z`, a jeśli tak - to jak. Aby to było możliwe typ każdej zmiennej czy obiektu musi być niezmienny podczas kompilacji i w dodatku od razu znany kompilatorowi. To z kolei oznacza, że już przy pierwszym użyciu dowolnej zmiennej, obiektu, klasy, wyliczenia, funkcji, kompilator musi znać ich typ.       

Problem powyższy rozwiązuje się najczęściej za pomocą **definicji** - zmiennych, obiektów, klas, funkcji, wyliczeń, przestrzeni nazw czy innych elementów programu. Tu na razie ograniczę się do definicji zmiennych i funkcji.  Oto przykład kilku definicji zmiennych i funkcji:

```c++
int x = 0;    // x jest typu int i ma wartość 0
int y;        // y jest typu int i ma dowolną wartość  
auto z = 17;  // typ z jest dedukowany z typu inicjalizatora (tu: 17), czyli int
int dziady() { return 40 + 4; } // dziady to funkcja bezargumentowa zwracająca int
int suma(int x, int y) { return x + y; } // suma to fun. 2-arg. zwracająca int
```

- W pierwszej instrukcji definiujemy `x` jako zmienną typiu `int` (= liczba całkowita) i nadajemy jej wartość 0. 
- W drugiej instrukcji definiujemy `y` jako zmienną typu `int` i nie nadajemy jej żadnej wartości - `y` będzie miało wartość przypadkową, tzw. śmieci.
- W trzeciej instrukcji definiujemy `z` jako zmienną typu wydedukowanego przez kompilator na podstawie typu inicjalizatora. Właśnie takie znaczenia ma tu słowo `auto`. Skoro typem inicjalizatora (tu: 17) jest `int`, typem `z` też jest `int`.
- W instrukcjach 4. i 5. definiujemy `dziady` i `suma` jako funkcje. 

W C++, jako języku ze statyczną kontrolą typów, nie można używać niezadeklarowanych zmiennych czy funkcji. Błędny więc jest kod:


```c++
x = 9;      // błąd: kompilator nie wie, jakiego typu jest x
int x = 0;
```


Podobnie błędny jest ten fragment programu:

```c++
int x = dziady(); // błąd: kompilator jeszcze nie wie, co to "dziady"
int dziady() { return 40 + 4; }
```

#### 2.1.3 ODR

W C++ obowiązuje zasada znana pod angielskim akronimem **ODR** (*one definition rule*): każda zmienna, obiekt czy funkcja może mieć tylko jedną definicję w całym programie. 

#### 2.1.4 Deklaracje

Ponieważ profesjonalne programy w C++ składają się z tysięcy osobnych plików, reguła ODR tworzy potrzebę wprowadzenia do języka możliwości deklarowania typu bez definiowania jego treści. W przypadku funkcji jest to bardzo proste, wystarczy z jej pełnej definicji usunąć jej treść (część ujętą w nawiasy klamrowe), a w to miejsce postawić średnik. Przykłady deklaracji funkcji:

```c++  
int dziady();            // dziady to funkcja bezargumentowa zwracająca int
void suma(int x, int y); // suma to fun. 2-arg. nic nie zwracająca
```

Każda definicja jest jednocześnie deklaracją, ale nie odwrotnie.W przeciwieństwie do definicji, liczba deklaracji tego samego obiektu (funkcji, zmiennej, klasy...) jest w programie nieograniczona.

Teraz możemy najpierw funkcję zadeklarować, potem jej użyć, a dopiero na końcu ją zdefiniować:

```c++    
int dziady();                   // deklaracja 
int x = dziady();               // użycie
int dziady() { return 40 + 4; } // definicja
```

##### 2.1.4.1 `extern`

Dla porządku podaję sposób deklarowania zmiennej bez jej jednoczesnego definiowania, jednak jest pewne, że ta cecha języka nie jest potrzebna osobom zaczynającym programować w C++ i póki co spokojnie można o niej zapomnieć:

```c++
extern int x;
```