## 9.2 Przykłady szablonów

#### 9.2.1 `swap`

Tworzenie szablonu funkcji `swap`, zamieniającą wartości przypisane dwóm zmiennym lub obiektom,   możemy rozpocząć od napisania takiej funkcji dla liczb typu `int`:

```c++
void swap(int & n, int & m)
{
    int tmp = n;
    n = m;
    m = tmp;
}
```

Żeby tę funkcję zamienić na szablon funkcji, trzeba się zastanowić, które jej elementy zależą od typów argumentów. W tym prostym przypadku są to typy zmiennych `n`, `m` i `tmp`. Jeżeli oznaczymy ten typ przez `T`, to otrzymamy

```c++ 
using T = int;

void swap(T & n, T & m)
{
    T tmp = n;
    n = m;
    m = tmp;
}
```

W powyższym kodzie posłużyłem się instrukcją `using` o chyba oczywistym znaczeniu (wprowadzenie alternatywnej nazwy dla istniejącego typu).

Tak przygotowany kod zamieniamy na szablon, usuwając instrukcję `using` i dopisując preambułę szablonu:

```c++
template <typename T>
void swap(T & n, T & m)
{
    T tmp = n;
    n = m;
    m = tmp;
}
```

W ten sposób otrzymaliśmy gotowy szablon funkcji `swap`. 

Przykład użycia: 

```c++
int main()
{
    int n = 0;
    int m = 1;
    std::cout << "n = " << n << ", m = " << m << "\n";
    swap(n, m);
    std::cout << "n = " << n << ", m = " << m << "\n";    
}
```

Wynik tego programu:

```txt
n = 0, m = 1
n = 1, m = 0
```

#### 9.2.2 Klasa liczb zespolonych

Szablon bardzo, bardzo uproszczonej klasy liczb zespolonych:

```c++  
template <typename T>
class complex
{
  public:
    T real = 0;
    T imag = 0;
};
```

Mniej uproszczona implementacja powinna zamknąć dane w części prywatnej i udostępnić interfejs publiczny w postaci szeregu funkcji składowych. 

#### 9.2.3 Klasa reszt modulo `N`

W arytmetyce stosuje się [klasę reszt modulo N](https://pl.wikipedia.org/wiki/Arytmetyka_modularna#Pier%C5%9Bcie%C5%84_klas_reszt). Oto prosta implementacja, wraz z przykładem użycia:

```c++
template <typename T, int N>
class Modulo
{
    static_assert(T(-1) < 0, "Modulo must not be parametrized with unsigned or non-arithmetic types");
    static_assert(N > 0);

    T value;
  public:
    explicit Modulo(T n)
        : value{n}
    {
        if (n >= N || n < 0)
        {
            n %= N;
            if (n < 0)
                n += N;
        }
    }

    T val() const { return value; }
    Modulo& operator+=(Modulo rhs)
    {
        value += rhs.val();
        if (value >= N)
            value -= N;
        return *this;
    }
    Modulo operator-() const
    {
        Modulo tmp = *this;
        if (tmp.value > 0)
            tmp.value = N - tmp.value;
        return tmp;
    }

    Modulo operator+(Modulo rhs) const
    {
        Modulo tmp = *this;
        tmp += rhs;
        return tmp;
    }
    Modulo operator-(Modulo rhs)
    {
        return *this + -rhs;
    }
};

int main()
{
    Modulo<int, 8> m(7);
    Modulo<int, 8> n(6);
    std::cout << (-m).val() << "\n";
    std::cout << (m + n).val() << "\n";
    std::cout << (m - n).val() << "\n";
    std::cout << (n - m).val() << "\n";
}    
```

Kilka słów komentarza:

- Pierwszy argument szablonu, `T`, pozwala określić wewnętrzną reprezentację obiektów klasy `Modulo<T,N>`. Mogą to być  m.in. `signed char`, `short`, `int` i `long int`.   

- `static_assert` to warunek sprawdzany podczas kompilacji, służący weryfikacji, że kompilacja ma sens. Tu wykorzystałem tę instrukcję do bardzo prostej i - niestety - niepełnej weryfikacji sensowności użycia danych parametrów szablonu - `T` powinno reprezentować typ całkowity ze znakiem, a  `N` powinno być dodatnie. Istnieją lepsze i pewniejsze sposoby weryfikacji tych warunków, ale póki co, to jeszcze nie ten poziom zaawansowania C++, natomiast `static_assert` jest tak proste, jak tylko proste może coś być. 

- Klasa posiada niezmiennik: składowa `value` reprezentującą resztę z dzielenia przez `N` musi mieć wartość z zakresu `0`,..., `N - 1`. Jest on ustanawiany przez konstruktor i zachowywany przez każdą funkcję składową. 

- Dwuargumentowy `operator+` korzysta z wcześniej zdefiniowanego operatora `+=` (w instrukcji `tmp += rhs;`). To bardzo często stosowana, bardzo ułatwiająca programowanie "sztuczka".

- Analogicznie, dwuargumentowy `operator-` korzysta ze zdefiniowanych wcześniej `opertor+` i   jednoargumentowego `operator-` (instrukcja `return *this + -rhs;`), co dokładnie odpowiada definicji odejmowania: $a - b \equiv a + -b$.

- Dwa typy sparametryzowane różnymi wartościami `T` i `N` to różne typy i nie mogą brać udziału w operacjach dodawania czy odejmowania. Np. 

  ```c++
  Modulo<int, 8> a = 7;
  Modulo<int, 6> b = 4;
  auto c = a + b; // błąd czasu kompilacji: a i b muszą mieć ten sam typ! 
  ```

- Powyższy szablon pisałem szybko i nie testowałem go zbyt intensywnie, mam nadzieję, ze nie ma w nim błędów. 
