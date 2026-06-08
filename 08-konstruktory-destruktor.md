## 8.2.3. Konstruktory 

W językach obiektowych wyróżnia się dwa specjalne rodzaje funkcji składowych klas: konstruktory i destruktory. Konstruktory służą do inicjalizacji obiektów danej klasy, czyli do wprowadzenia w dobrze określony, poprawny "stan początkowy". Na przykład konstruktor kontenera przechowującego elementy jakiegoś typu zapewne zbuduje wewnętrzne struktury danych służące do obsługi tych danych, a konstruktor głównego okna aplikacji prawdopodobnie inicjalizuje interfejs użytkownika, czyli wszystkie okienka, przyciski, paski narzędzi, menu widoczne po uruchomieniu aplikacji (co może obejmować też wczytanie plików konfiguracyjnych). 

Poniżej przedstawiam kilka przykładów definicji konstruktorów i sposobów ich użycia

##### 8.2.3.1 Liczby zespolone, wersja podstawowa

W poprzednim rozdziale przedstawiłem bardzo uproszczoną definicję klasy liczb zespolonych `Complex`:

```c++
class Complex
{
  public:
    double re() const { return _re; }
    double im() const { return _im; }
    void set_re(double x) { _re = x; }
    void set_im(double x) { _im = x; }
  private:
    double _re;
    double _im;
};
```

Liczbę zespoloną chcielibyśmy móc inicjalizować na 3 sposoby:

- nie podając żadnej wartości początkowej - w tym przypadku komputer powinien ustawić część rzeczywistą i urojoną takiej liczby na 0. 
- podając tylko wartość części rzeczywistej liczby - w tym przypadku jej część urojona powinna być równa 0. 
- Podając zarówno część rzeczywistą, jak i urojoną liczby.

Potrzebujemy więc trzech konstruktorów. Można je zaimplementować np. w następujący sposób:

```c++  
class Complex
{
  public:
    Complex()             // konstruktor bezargumentowy (tzw. "domyślny")
    : _re{0}, _im(0)      //   preambuła konstruktora
    {}                    //   treść konstruktora (tu: pusta)
    
    Complex(double re)    // konstruktor jednoargumentowy ("liczba rzeczywista")
    : _re{re}, _im{0}
    {}
    
    Complex(double re, double im) // konstruktor dwuargumentowy ("pełna liczba zespolona")
    : _re{re}, _im{im}
    { }
    
 // pozostałe funkcje składowe...
    
  private:
    double _re;
    double _im;
}
```

Jak widzimy, składnia konstruktorów bardzo przypomina składnię zwykłych funkcji składowych. Mamy bowiem listę argumentów konstruktora (w nawiasach okrągłych) i ciało funkcji (w klamrach). Różnice są trzy:

- Nazwa funkcji definiującej konstruktor klasy jest tożsama nazwie tej klasy (tu: `Complex`);
- Konstruktor nigdy nie zwraca wartości i nie sygnalizujemy tego nawet deklaratorem `void`, jak przy innych funkcjach (innymi słowy, gdyby konstruktor klasy `Complex` był zwykłą funkcją, deklarowany byłby jako `void Complex (/* lista argumentów */) { /* ciało funkcji */}`; )
- Konstruktor tuż przed swoim ciałem (czyli blokiem kodu ujętym w nawiasy klamrowe) może zawierać tzw. ***preambułę*** (zwaną też ***listą inicjalizacyjną***), która rozpoczyna się od dwukropka.

**Preambuła konstruktora** to po prostu lista jego składowych wraz z ich inicjalizatorami. Innymi słowy, zapis

```c++ 
: _re{re}, _im{0}
```

oznacza, że składowa `_re` tworzonego obiektu ma być zainicjalizowana wartością zmiennej `re`, a składowa `_im` - wartością literału `0`. Ponieważ obie te składowe są typu prostego `double`, składowej `_re` zostanie przypisana wartość argumentu `re`, a składowej `_im` - wartość `0`. Inicjalizatory można zapisywać w nawiasach klamrowych (sposób zalecany) lub okrągłych. Prawie zawsze oba te zapisy są sobie równoważne.   

Gdyby obiekty klasy `Complex` zawierały składowe bardziej złożonych typów, np. klasy, wtedy każdy z parametrów inicjalizacyjnych mógłby zawierać więcej niż 1 wartość. Poprawy więc jest hipotetyczny zapis

```c++ 
: foo{1, 2.0}
```

oznaczający, że dana klasa ma składową `foo`, którą należy konstruować konstruktorem dwuargumentowym z argumentami `1` i `2.0`.    

**Typowe przykłady użycia**

```c++
Complex z0;
Complex z1(8.0);
Complex z2(9);
Complex z3(1.0, 1.0);
```

W powyższym przykładzie

- Liczba `z0` odpowiada licznie zespolonej $0 + 0i$, czyli $0$, gdyż konstruowana jest za pomocą konstruktora bezargumentowego, który ustala wartości obu składowych liczby `z0` na `0`. Konstruktora bezargumentowego jako jedynego nie wywołujemy za pomocy notacji "funkcyjnej", gdyż byłaby nierozróżnialna od prawidłowej deklaracji funkcji:

  ```c++    
  Complex zz(); // zz jest bezargumentową funkcją zwracającą liczbę typu Complex
  ```

  Warto w tym miejscu porównać:

  ```c++
  Complex x(2);    // x jest obiektem klasy Complex inicjalizowanym liczba 2 
  Complex y(int);  // y jest bezargumentową funkcją zwracającą Complex
  ```

  Warto jeszcze wiedzieć, że w języku C++ od wersji 11 wprowadzono alternatywny zapis inicjalizatorów, wykorzystujący "notację z klamrami":

  ```c++ 
  Complex w{2.0};
  ```

  Ma ona kilka zalet, m.in. ogranicza błędy spowodowane konwersją zwężającą (temat zbyt skomplikowany na niniejszy wykład). Nie powoduje też problemów z niejednoznacznością interpretacji pustych klamer: one na pewno nie oznaczają deklaracji funkcji, dlatego

  ```C++ 
  Complex v{};
  ```

  jest poprawnym inicjalizatorem nakazującym konstrukcję `v` przy pomocy konstruktora bezargumentowego. Początkujący programista C++ nie musi się orientować we wszystkich subtelnościach inicjalizacji w tym języku programowania (sam czasami miewam tu wątpliwości), niemniej, trzeba rozumieć powszechnie używaną notację. 

- Liczba `z1` jest inicjalizowana konstruktorem jednoargumentowym, o czym świadczy zapis jej deklaracji i inicjalizatora, przypomnijmy:

  ```c++
  Complex z1(8.0);
  ```

  Widzimy tu jeden argument typu double. Wywołany więc zostanie konstruktor zadeklarowany w klasie `Complex`jako 

  ```c++
  Complex(double re)
  ```

- Liczba `z2` jest inicjalizowana tak samo, jak `z1`, co wynika z jej deklaracji

  ```c++
  Complex z2(9);
  ```

  Tu jednak typ argumentu, `int`, nie jest zgodny z typem oczekiwanym przez konstruktor, `double`. Dlatego przed wywołaniem konstruktora, liczba `9` zostanie skonwertowana do typu `double`. W praktyce kompilator zastąpi powyższe wywołanie instrukcją, w której występuje `9.0`:

  ```c++
  Complex z2(9.0);
  ```

  Wartość `z3` odpowiadać będzie liczbie zespolonej $9 + 0i = 9$. 

- Liczba `z3` jest inicjalizowana konstruktorem dwuargumentowym (trzecim w deklaracji klasy), gdyż jej inicjalizator ma 2 argumenty

  ```c++  
  Complex z3(1.0, 1.0);
  ```

  W wyniku tej inicjalizacji, wartość `z3` odpowiadać będzie liczbie zespolonej $1.0 + 1.0i$, czyli $i + 1$.


##### 8.2.3.2 Liczby zespolone, inne wersje

**a. Kod w konstruktorze**

Konstruktory można definiować na wiele sposobów. Na przykład zamiast

```c++
Complex(double re, double im) // konstruktor dwuargumentowy ("pełna liczba zespolona")
: _re{re}, _im{im}
{ }
```

można akurat ten konstruktor zapisać bez preambuły:

```c++
Complex(double re, double im)
{ 
    _re = re;
    _im = im;
}
```

Ten kod wydaje się bardziej zrozumiały od oryginału, niemniej, wersją z preambułą jest z wielu powodów lepsza (w  zaawansowanym C++ - w tak prostym przykładzie różnicy, poza składnią nie ma). Powyższą implementację przedstawiam głównie po to, żeby Czytelnik miał jasność, po co są nawiasy klamrowe. Można zapisać w niej dowolny kod, tak jak w każdej innej funkcji.

**b. Argumenty domyślne**

Kody źródłowe trzech konstruktorów przedstawionych w punkcie 8.2.3.1.1 są bardzo podobne. Czy można uniknąć powielania kodu? W tym przypadku - można. W tym celu wystarczy posłużyć się jednym konstruktorem z argumentami domyślnymi:

```c++ 
Complex(double re = 0, double im = 0)
: _re{re}, _im{im}
{ }
```

W takim przypadku, jeżeli pominiemy ostatni argument, to kompilator sam dopisze drugi, nadając mu wartość odczytaną z deklaracji, czyli `0`. Dlatego jeśli napiszemy

```c++  
Complex z(10.0);
```

to kompilator sam uzupełni powyższą definicję o drugi argument

```c++
Complex z(10.0, 0.0);
```

Analogicznie, jeżeli zdefiniujemy zmienną klasy `Complex` zdefiniujemy bez argumentów,

```c++ 
Complex z;
```

to kompilator niejako dopisze je za nas, wykorzystując wartości domyślne podane w deklaracji:

```c++  
Complex z(0.0, 0.0);
```

##### 8.2.3.4  Popularne rodzaje konstruktorów

Istnieje kilka popularnych rodzajów konstruktorów, tzn. konstruktorów, które mają swoje nazwy używane w dokumentacji bibliotek C++ i w samy standardzie języka C++.

- **Konstruktor domyślny** (ang. *default constructor*) to konstruktor, który można wywołać bez podawania argumentów. Oczywiście najprostszym przykłądem konstruktora domyślnego jest przedstawiony powyżej konstruktor bezargumentowy,

  ```c++    
  class Complex
  {
    public:
      Complex()             // konstruktor bezargumentowy (tzw. "domyślny")
      : _re{0}, _im(0)      //   preambuła konstruktora
      {}                    //   instrukcje konstruktora (tu: brak)
  // reszta kodu
  };
  ```

  Konstruktorem domyślnym jest też każdy konstruktor, którego wszystkie argumenty maj ą wartości domyślne, a więc i taki, znany już nam konstruktor:

  ```C++
  Complex(double re = 0, double im = 0)
  : _re{re}, _im{im}
  { }
  ```

  Cała idea konstruktora domyślnego polega na tym, że kompilator może go użyć samodzielnie, bez żadnych dodatkowych informacji od programisty. Dzięki temu możliwe jest m.in. tworzenie tablic (statycznych i dynamicznych) obiektów danej klasy:

  ```c++     
  Complex tab[10]; 
  std::vector<Complex> tab2(20);
  ```

  W powyższym przykładzie `tab` to statyczna (= o stałym rozmiarze) tablica 10 liczb typu `Complex`. Każda z nich zostanie zainicjalizowana konstruktorem domyślnym na liczbę $0 + 0i = 0$. Podobnie `tab2` to tablica dynamiczna (=mogąca zmieniać swój rozmiar w czasie działania programu) o 20 elementach typu `Complex`, z których każdy zostanie zainicjalizowany konstruktorem domyślnym na `0`.   

- **Konstruktor kopiujący** (znany też jako konstruktor kopii, ang. *copy constructor*) konstruuje nowy obiekt jako kopię obiektu już istniejącego. W przypadku klasy `Complex` mógłby wyglądać tak:

  ```c++ 
  Complex(const Complex& rhs)
  : _re{rhs.re}, _im{rhs.im}
  { }
  ```

  lub tak:

  ```c++
  Complex(const Complex& rhs)
  { 
    _re = rhs.re;
    _im = rhs.im;
  }
  ```

  Ogólnie, konstruktor kopiujący klasy `X` ma zawsze deklarację

  ```c++
  X(const X& arg);
  ```

  Czyli przyjmuje jeden argument klasy `X` przez stałą referencję. 

- **Konstruktor przenoszący** (ang. *move constructor*). Jego deklaracja przypomina nieco deklarację konstruktora kopiującego, tyle że zwykle nie ma tam słówka `const`, a znak `ampersand` występuje dwa razy:

  ```c++ 
  X(X&& arg);
  ```

  To temat zaawansowany, zapraszam na kolejne, bardziej zaawansowane zajęcia... Tu wspominam o nim tylko dlatego, że czasami widuje się wzmiankę o konstruktorze przenoszącym w komunikatach o błędach. Ten podwójny ampersand to nie jest błąd!

##### 8.2.3.5 Podsumowanie

- Konstruktor to funkcja składowa klasy wywoływana automatycznie podczas tworzenia każdego obiektu tej klasy
- Konstruktor ma taką samą nazwę, jak klasa, w której jest definiowany, i nie zwraca wartości
- Klasa może mieć dowolną liczbę konstruktorów (w tym zero)
- Preambuła konstruktora to lista jego składowych (niekoniecznie wszystkich) wraz z argumentami przekazywanymi do ich konstruktorów podczas ich automatycznej inicjalizacji.
- Ciało konstruktora może zawierać dowolny zestaw instrukcji, jak każda funkcja składowa, jednak wykonywane są one zawsze na samym końcu konstrukcji obiektu, czyli po automatycznej inicjalizacji składowych.
