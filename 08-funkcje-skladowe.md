## 8.2.2 Funkcje składowe

Omówione w punkcie 8.1 struktury to kolekcje pól zawierających dane w zasadzie dowolnego typu. Mają swoje oczywiste zalety, ale i wady. Jedną z nich jest jawne eksponowanie w całym programie typów danych wszystkich pól struktury. Tymczasem jeśli tworzymy jakiś nietrywialny program, to często nie interesują nas konkretne typy składowych. Na przykład jeślibyśmy pisali program do gry w szachy, to byłoby dla nas bez znaczenia, w jaki sposób reprezentowany jest stan bierek na planszy. Znacznie bardziej ważny byłby dostąp do gotowych funkcji umożliwiających takie czynności, jak wykonanie ruchu czy weryfikacja stanu rozgrywki (czy król przeciwnika jest pod szachem, czy można zrobić roszadę itp.). Ma to też niebagatelne znaczenie wobec faktu, że potrzebujemy oprogramowania jak najbardziej niezależnego od sprzętu, na którym jest ono uruchamiane. Wyobraźmy sobie bibliotekę służącą wyświetlaniu standardowych okienek w systemie komputerowym. Taka biblioteka z dużym prawdopodobieństwem posługuje się wskaźnikami. Jeszcze kilkanaście lat temu w powszechnym użyciu były wskaźniki 32-bitowe. Obecnie standardem są wskaźniki 64-bitowe. Jak zapewnić możliwość możliwie jak najbardziej łagodnego przejścia z systemu 32-bitowego na 64-bitowy? Czy można dziś używać tej samej biblioteki na platformach 64- i 32-bitowych (np. w relatywnie tanich systemach wbudowanych)?

Odpowiedzią na powyższe dylematy są klasy. Klasy to typy danych, których autor może dowolnie ograniczyć ich użytkownikom zakres widoczności ich wewnętrznej struktury. Zmienne tych typów, zwane obiektami, jawią się użytkownikom jako swoiste czarne skrzynki z dobrze zdefiniowanym interfejsem tworzonym nie przez dane, lecz przez funkcje, czyli czynności, które można wykonać na obiekcie. Posługując się obiektami, nie zastanawiamy się, jaki układ bitów odpowiada określonemu stanowi obiektu, tak jak nie interesuje nas wewnętrzna budowa bankomatu. Jedyne, co nas interesuje, to zbiór dopuszczalnych (zwykle abstrakcyjnych) stanów danego obiektu oraz zestaw wszystkich funkcji, jakich na tych obiektach można używać. 

Żeby powyższy program działania mógł doczekać się realizacji, konieczne jest rozwiązanie dwóch problemów. Po pierwsze, musi istnieć mechanizm ograniczania widoczności pewnych cech strukturalnych klas dla zwykłych użytkowników obiektów tej klasy. Realizację tego mechanizmu w C++ już poznaliśmy - są nim sekcje `private`, `protected` i `public`. Każdy identyfikator zdefiniowany w klasie obowiązkowo należy do jednej  z nich. Po drugie, musi istnieć sposób na odróżnienie funkcji autora klasy od funkcji każdego innego jej użytkownika tak, aby tylko autor klasy miał pełny dostęp do informacji o wewnętrznej strukturze obiektów klasy i w związku z tym jako jedyny mógł z obiektami robić cokolwiek zechce. Z kolei zwykły  użytkownik klasy powinien mieć ustalony przez jej autora zestaw czynności (funkcji C++), które mógłby wykonywać na obiektach danej klasy. Ten zestaw powinien, w stosunku do obiektów danej klasy, być zamknięty - w sensie, że zwykły użytkownik nie powinien mieć prawa do jego rozszerzania. Bez tego warunku obiektów nie można by bowiem traktować jak czarnych skrzynek z dobrze zdefiniowaną funkcjonalności. Ten drugi problem rozwiązano, umożliwiając definiowanie funkcji wewnątrz definicji klas. W ten sposób tylko twórca klasy ma pełny dostęp do jej wewnętrznej struktury, zwykły użytkownik ograniczony jest do zestawu czynności, które udostępnił mu twórca klasy.  

#### Przykład klasy z funkcjami składowymi

Oto przykład klasy `Complex` (reprezentującej liczby zespolone) z dwiema funkcjami składowymi, wraz z przykładem użycia:

```
class Complex
{
  public:
    double re() const { return _re; }
    double im() const { return _im; }
  private:
    double _re;
    double _im;
};

int main()
{
    Complex z;
    std::cout << z.re() << "\n";
}
```

Powyższy program kompiluje się i uruchamia, łatwo jednak zauważyć, że ma poważną wadę: klasa `Complex` umożliwia odczyt składowych `_re` i `_im`, jednak nie dostarcza żadnego sposobu nie tylko na to, by  je zmodyfikować, ale nawet by je zainicjalizować. Tak zdefiniowana klasa jest wciąż bezużyteczna. Brakuje jej metod umożliwiających modyfikację jej składowych. Łatwo ten problem rozwiązać, dodając do klasy dwie nowe funkcje, `set_re` i `set_im`:

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

int main()
{
    Complex z;
    z.set_re(9.0);
    z.set_im(-11);
    std::cout << z.re() << "\n";
}
```

Tak zdefiniowana klasa jest już użyteczna (choć niezbyt wygodna w użyciu). Posiada jednak pewną wadę. Między utworzeniem obiektu a jego inicjalizacją obiekt znajduje się w stanie nieokreślonym, czy też po prostu błędnym. W tym stanie obiektu nie można "dotykać". Rodzi to wiele subtelnych problemów, zwłaszcza w zaawansowanym programowaniu. Cóż bowiem się stanie, gdy między momentem utworzenia obiektu a jego pełną inicjalizacją wystąpi błąd i w reakcji na jego wystąpienie program spróbuje usunąć obiekt znajdujący się w przypadkowym stanie? A co, jeśli ktoś zapomni zainicjalizować jakieś składowe obiektu? Co zrobić, jeśli w nowej wersji klasy dodamy jakąś składową - jak zapewnić, ze wszyscy jej użytkownicy, których mogą być grube tysiące, poprawnie ją zainicjalizują? Bez takiej gwarancji jakakolwiek poważna zmiana w strukturze klasy jest praktycznie niewykonalna bez ryzyka uszkodzenia kodu użytkowników, którzy zapłacili za nasze oprogramowanie. Rozwiązaniem tych problemów są omówione w kolejnym rozdziale konstruktory i destruktory obiektów klas.   

