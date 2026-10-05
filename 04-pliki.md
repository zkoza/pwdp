## 4.1 Pliki kontrolujemy za pomocą obiektów

Obsługa plików w zasadzie niewiele różni się od obsługi standardowego wejścia i wyjścia. Oczywiście musimy jakoś 

- otworzyć plik, podając jego nazwę i lokalizację w systemie plików
- wskazać, czy chcemy go tylko czytać, tylko w nim zapisywać, czy może i czytać, i zapisywać 
- określić, czy w pliku otwartym do zapisu mam wymazać istniejącą zawartość, czy też może chcemy dopisywać nowe treści do już istniejących
- określić, czy plik otwieramy w trybie tekstowym czy binarnym (ważne w Windows) 
- po otwarciu mieć do niego dostęp i odczytywać z niego lub zapisywać w nim określone dane
- zamknąć, gdy przestanie nam być potrzebny

W C++ większość z tych czynności wykonujemy w momencie otwierania pliku. Czynność ta polega na utworzeniu obiektu odpowiedniej klasy. Notabene, o obiektach jeszcze nic nie mówiłem. Przyjmijmy na potrzeby tej części wykładu, że obiekt to taka bardziej skomplikowana kolekcja zmiennych wraz z zestawem funkcji, które można na nich wykonywać.    

#### 4.1.1 Otwieranie plików do odczytu

Operacje związane z plikami otwieranymi do odczytu zdefiniowane są w pliku nagłówkowym `<ifstream>`, który w związku z tym musimy włączyć do naszego programu. Samo zaś otwarcie pliku realizujemy poprzez utworzenie obiektu klasy `std::ifstream` (ang. *input file stream*). 

```c++
#include <fstream>
#include <format>
#include <iostream>
#include <print>
#include <string>
#include <stdexcept>

int main()
{
    std::string filename;
    std::cout << "podaj nazwę pliku: ";
    std::cin >> filename;
    std::ifstream in(filename);
    if (!in)
        throw std::runtime_error(std::format("failed to open \"{}\"", filename));
    std::string line;
    std::println("{:->40}", "");
    while (std::getline(in, line))
    {
        std::println("{}", line);
    }
}
```

Najważniejsza instrukcja w powyższym programie to 

```c++ 
std::ifstream in(filename);
```

Tworzy ona obiekt o nazwie `in` związany z plikiem o nazwie zapisanej w zmiennej `filename`. Każda operacja na `in` jest jednocześnie operacją na odpowiadającym jej pliku. 

- Operacje na obiekcie `std::ifstream` są takie same jak na `std::cin`. Np. aby wczytać słowo do `std::string s`, wystarczy wydać instrukcję 
  ```c++   
  in >> s;
  ```

- Dodatkowo można stosować funkcje, jak np. w powyższym przypadku `std::getline`, która wczytuje cały wiersz tekstu. 

  - Oczywiście można jej też używać w kontekście `std::cin`, ale akurat to połączenie spotyka się rzadko, a użycie `std::getline` z plikami jest wręcz powszechne. 

- Warto zapamiętać idiom 

  ```c++  
  if(!in) 
  ```

  który jest powszechnie stosowany w celu sprawdzenia, czy plik został otwarty. 

- Podobnie warto zapamiętać idiom

  ```c++
  std::string line;  
  while (std::getline(in, line))
  {
      // rób coś z line
  }
  ```

  w który za pomocą pętli `while` wczytujemy całą zawartość pliku tekstowego, wiersz po wierszu (pomijając znaki końca wierszy).

- Plików zwykle nie zamykamy ręcznie. Pliki zostaną automatycznie zamknięte z chwilą, w której sterowanie wyjdzie poza zakres zmiennej `in`. W naszym przypadku będzie to klamra kończąca funkcję `main`. Wiąże się to z tzw. destruktorami obiektów, tematem, który omówię nieco później.

Użyta w powyższym programie instrukcja `throw` nie ma nic wspólnego z plikami i zostanie omówiona później. Jak można się domyślić, w kontekście powyższego kodu kończy ona działanie programu. 

#### 4.1.2 Otwieranie plików do zapisu

Otwieranie plików do zapisu jest podobne do otwierania plików do odczytu Zmienia się jednak typ obiektu sterującego plikiem: zamiast `std::ifstream` stosujemy `std::ofstream`. Ponadto zamiast operatora `>>` używamy operatora `<<`.  Oto prosty przykład:

```c++
#include <fstream>
#include <print>
#include <string>
#include <stdexcept>

int main()
{
    std::string filename = "wierszyk.txt";
    std::ofstream out(filename);
    if (!out)
        throw std::runtime_error(std::format("failed to open \"{}\"", filename));
    std::string s =
        "Przyszedł gość do doktora, biada na swe zdrowie.\n"
        "- Jakaś mi żaba - mówi - wyrosła na głowie.\n"
        "- Umówmy się - odrzekło to zwierzę niegłupie -\n"
        "Nie ja jemu na głowie, lecz on mnie na dupie.\n\n"
        "Andrzej Waligórski, \"Bajeczki Babci Pimpusiowej\"\n";

    std::print(out, "{}", s);
}
```

- W powyższym programie tworzymy obiekt `out` klasy `std::ofstream` (ang. *output file stream*).

- Zapis do pliku można wykonać tymi samymi metodami, jak do`std::cout` (czyli na konsolę). W powyższym przykładzie użyłem `std::print`, przy czym pierwszym argumentem musi w tym przypadku być obiekt sterujący strumieniem, tu: `out`. Mógłby jednak posłużyć się tu operatotem `<<`:

  ```c++     
  out << s;
  ```

  z identycznym skutkiem

- Warto jeszcze zauważyć, że w C++ można tworzyć dłuuuugie napisy, pisząc obok siebie (zwykle w kolejnych wierszach) literały tekstowe (ujęte w cudzysłowy). Czyli np. 

  ```c++  
  "ala ma"
  ```

  oraz 

  ```c++
  "ala " "ma"
  ```

  i 

  ```c++
  "ala "
  "ma"
  ```

  to równoważne wyrażenia. Kompilator i tak drugie i trzecie zredukuje do pierwszego.  

##### 4.1.2.1 Tryby otwarcia pliku

Na koniec krótka uwaga o trybach otwierania plików. Jeżeli chcemy, by treść pliku do zapisu podczas otwierania nie była kasowana i by każda operacja wyjścia dopisywała nowe dane na końcu już istniejących, to piszemy tak (`app` to skrót od angielskiego *append*, czyli "dołącz"):

```c++ 
std::ofstream out("moje.log", std::ios::app);  
```

Jeżeli z grubsza rozumiemy, czym [plik tekstowy](https://en.wikipedia.org/wiki/Text_file) różni się od [binarnego](https://en.wikipedia.org/wiki/Binary_file), to plik w trybie binarnym otwieramy tak:

```c++
std::ofstream out("moje.log", std::ios::binary);  
```

Niezłe wyjaśnienie różnicy między plikiem binarnym a tekstowym znajduje się [na tej stronie](https://stackoverflow.com/questions/26993086/what-the-point-of-using-stdios-basebinary). W każdym razie: zwykły tekst (cyfry, znaki przestankowe, litery, ogólnie - wszystkie znaki z zestawu UTF) zapisuj i odczytuje w domyślnym dla C++ trybie tekstowym, natomiast resztę, w tym grafikę, muzykę, pliki skompresowane, pliki wykonywalne itp - w trybie binarnym.    

Jeżeli chcemy utworzyć plik binarny w trybie dopisywania, piszemy tak:

```c++
std::ofstream out("moje.log", std::ios::binary | std::ios::app);  
```

##### 4.1.2.2 Dygresja: flagi

Zapis 

```c++
std::ios::binary | std::ios::app
```

jest charakterystyczny dla języka C++ i oznacza dodanie do siebie dwóch "flag": w tym przypadku są to flagi `app` i `binary`. Czy można by je dodać zwykłym operatorem dodawania, `+`? Tak, ale istnieją dobre powody, by tego nie robić, mimo że program działałby identycznie. Pisząc `+` mówimy osobom, czytającym program "Hej, dodaję do siebie dwie liczby: zajrzyj do dokumentacji lub kodu źródłowego, jeśli chcesz wiedzieć, co oznaczają ich wartości". Z kolei użycie `|` mówi każdej osobie czytającej tę instrukcję "Hej, ustawiam (= włączam) te dwie niezależne od siebie opcje; odpowiadające im wartości numeryczne nie mają żadnego znaczenia". Realizuje się to poprzez nadanie flagom wartości będących potęgami dwójki, czyli 1, 2, 4, 8, 16 itd. Teraz wystarczy zauważyć, że sumę potęg dwójki można zrealizować, z identycznym rezultatem, zarówno poprzez operator dodawania arytmetycznego `+`, jak i sumy bitowej `|`.

Kiedy się stosuje flagi? Ano wtedy, gdy mamy gdzieś przekazać szereg opcji "włącz/wyłącz". W przypadku plików, opcje te dotyczą m.in. tego, czy ma być on otwarty do czytania, do zapisu, w trybie dołączania, w trybie binarnym. W przypadku okien naszych aplikacji, flagi będą mówić m.in., czy okno ma mieć pasek tytułowy, przycisk opcji systemowych, przycisk minimalizacji, przycisk maksymalizacji, przycisk zamknięcia, ramkę, czy ma być oknem zwykłym, czy dialogowym, wyświetlanym nad innymi oknami - i tak dalej. Zamiast przesyłać gdzieś osobno 5, a czasami nawet 20 takich "flag" w 5 czy 20 zmiennych, przesyłamy je w jednej zmiennej (np. typu `unsigned int`), w której każdej fladze odpowiada inny bit. Dlatego właśnie flagi łączymy  operatorem sumy bitowej.

Więc, na koniec, co to są flagi? Są to jakieś obiekty (czy raczej po prostu liczby), prawdopodobnie typu całkowitego (bez znaku), które można ze sobą agregować za pomocą operatora sumy bitowej `|`.