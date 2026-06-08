### 8.2.4. Destruktor

#### 8.2.4.1 Co to jest i do czego służy destruktor? 

Destruktor to funkcja składowa klasy wywoływana  automatycznie na obiekcie tuż przed jego  "unieważnieniem", czyli zwolnieniem pamięci przypisanej temu obiektowi. Innymi słowy, tak jak konstruktor jest pierwszą funkcją, jaka wywoływana jest podczas życia obiektu, tak destruktor jest funkcją ostatnią. Obie te funkcje, konstruktor i destruktor, wywoływane są automatycznie, tzn. to kompilator a nie człowiek wstawia ich wywołania do kodu wynikowego programu. Dzięki temu obsługę pamięci w C++ (tworzenie i zwalnianie obiektów) można w znacznym stopniu zautomatyzować, co czyni język bardziej bezpiecznym od jego pierwowzoru, czyli języka C. Prawdziwy sens, wręcz konieczność istnienia konstruktorów i destruktorów wynika jednak z tego, że w języku C++ zaimplementowano obsługę wyjątków - złożony temat, który naszkicuję w dalszej części tego opracowania. 

Destruktory zwykle implementuje się po to, by nawet w przypadku nieoczekiwanego zakończenia życia jakiegoś obiektu (co zdarza się właśnie na skutek pojawienia się w programie wyjątku), program działał poprawnie i znajdował się w dobrze zdefiniowanym, w pełni kontrolowanym stanie. W przypadku omówionej w poprzednim punkcie klasy `Complex` nie ma żadnego niebezpieczeństwa związanego z nagłym zakończeniem życia przez obiekty tej klasy. Niemniej, możemy prześledzić, w jaki sposób destruktory się definiuje. Oto przykład:

```c++
Class Complex
{
    ~Complex()   // destruktor 
    { }          //    który jest pusty (nic nie robi)
  // ... jakiś kod  
};
```

Jak pamiętamy, konstruktory rozpoznajemy po tym, że mają nazwę identyczną z nazwą klasy. Podobnie destruktory mają nazwę tożsamą z nazwą klasy, tyle że ta nazwa poprzedzona jest znakiem tyldy (`~`), który w C++ w niektórych kontekstach reprezentuje negację. Konstruktor jest więc ":zaprzeczeniem" konstruktora.

Podstawowe cech destruktorów w języku C++: 

- Destruktor klasy `X` to funkcja składowa tej klasy o sygnaturze  `~X()`;
  - Destruktor nigdy nie ma argumentów;
  - Destruktor nie zwraca żadnej wartości;
- Destruktor nie ma tez żadnej preambuły, którą posiadać może konstruktor;  
- W danej klasie można zdefiniować tylko jeden destruktor;
- Destruktor, podobnie jak konstruktor, wywoływany jest automatycznie. 

#### 8.2.4.2 Zakres obiektu, czyli kiedy wywoływany jest destruktor?

Blok kodu w C++ to zestaw instrukcji zawartych między parą odpowiadających sobie klamer, czyli między `{` i `}` lub między definicją a końcem pliku źródłowego, jeżeli ta definicja występuje poza jakimikolwiek klamrami. Przykład:

```c++ 
#include <iostream>

int a = 0;

int main()
{
    int b;
    std::cin >> b;
    if (b > 0)
    {
        int c = 9;
        std::cout << b + c << "\n";
    }
}
```

W powyższym kodzie mamy trzy bloki, jeden globalny (= poza wszelkimi funkcjami) i dwa lokalne (= wewnątrz funkcji).

**Zakres zmiennej** to część najmniejszego bloku kodu, w której ją zdefiniowano, od instrukcji, w której tę zmienną zdefiniowano do końca tego bloku. W powyższym przykładzie mamy 3 zmienne typu `int`: `a`, `b` i `c`. 

- `a` jest zmienną globalną (= poza klamrami), więc jej zakres zaczyna się na instrukcji `int a = 0;`, a kończy się na końcu pliku.
- `b` jest zmienną lokalną (= zdefiniowaną wewnątrz jakiejś funkcji), więc jej zakres zaczyna się od jej definicji, `int b;`, a kończy się na klamrze kończącej funkcję `main`.
- `c` jest zmienną lokalną, więc jej zakres zaczyna się od instrukcji, w której jest definiowana, `int c = 9;`, a kończy się na  klamrze kończącej blok instrukcji sterowanej instrukcją `if`.   

Zakres zmiennej definiuje **czas życia zmiennej**: zmienna "pojawia się" w kodzie w instrukcji, która ją definiuje, a "znika z programu" w chwili, gdy sterowanie wychodzi z jej zakresu. Mówiąc bardziej konkretnie, na początku czasu życia zmiennej kompilator ma obowiązek wstawić w kodzie wywołanie odpowiedniego konstruktora tego obiektu (o ile w klasie zdefiniowano odpowiedni konstruktor), a na końcu zakresu tej tej zmiennej kompilator ma obowiązek wstawić jej destruktor. Konstruktor wywoływany jest *automatycznie* przy "narodzinach", a destruktor - przy "śmierci" zmiennej lub obiektu.

Problem ze zmiennymi typu `int` jest taki, że typ ten nie posiada ani konstruktora, ani destruktora. Skomplikujmy go więc nieco, zastępując prosty typ `int`  bardziej złożonym typem `std::vector<int>`, który posiada i konstruktor(y), jak i destruktor: 

```c++
#include <iostream>

std::vector<int> a = {0, 1, 2};  // konstruktor obiektu a

int main()
{
    std::vector<int> b;  // konstruktor obiektu b
    czytaj(b);           // jakaś funkcja wczytująca b z konsoli lub pliku  
    if (b.size() > 0)
    {
        std::vector<int> c = {9};
        std::cout << b[0] + c[0] << "\n";
    }  // destruktor obiektu c
}  // destruktor obiektu b
// destruktor obiektu a
```

Widzimy, że w powyższym przykładzie mamy 3 obiekty. Komentarze wskazują miejsca, w których wywoływane są ich konstruktory i destruktor.

Jeżeli w tym samym zakresie zdefiniuje się więcej niż jeden obiekt wymagający destrukcji, to ich destruktory wywoływane są w kolejności odwrotnej do wywołań konstruktorów.   