### Pierwszy program w C++

----

#### 1. Tekst programu

Programy w języku C++ można zapisywać w dowolnym edytorze tekstu pracującym w trybie [ASCII](https://pl.wikipedia.org/wiki/ASCII). Od pewnego czasu można też napisy (tekst ujęty w cudzysłowy) i komentarze pisać w standardzie [UTF-8](https://pl.wikipedia.org/wiki/UTF-8), w którym można reprezentować praktycznie każdy znak dowolnego alfabetu świata. Niniejszy tekst zapisany jest w systemie UTF-8. Istnieje ogromna liczba edytorów tekstu pracujących w trybie UTF-8. Ja w systemie Linux używam edytora [vim](https://www.vim.org/), w Windows - `notepad++`, każdy jednak ma tu pełną swobodę wyboru. Należy jednak pamiętać, że edytor tekstu i procesor tekstu to dwie różne pary kaloszy. Dlatego programów komputerowych nie piszemy w programach (procesorach tekstu) typu MS Word czy Libre Office.

Tradycyjnie pierwszy program w nowym języku programowania ogranicza się do wyświetlenia tekstu „[Hello, world!](https://www.scriptol.com/programming/hello-world.php)” (lub jego wersji spolszczonej – „Witaj świecie!”). Oto taki program w C++:

```c++
#include <iostream>

int main()
{
    std::cout << "Witaj świecie!\n";
}
```

Rozłóżmy ten  program na czynniki pierwsze:

- Programy w C++ składają się głównie z definicji funkcji. Słowo „funkcja” ma tu niewiele wspólnego z funkcjami znanymi z matematyki. „Funkcja” w językach C/C++ to po prostu podprogram, czyli fragment kodu posiadający własną nazwę i dobrze zdefiniowany sposób uruchamiania i zwracania ewentualnego wyniku. 
- Każdy program w C++ zawiera dokładnie jedną funkcję `main`, od której rozpoczyna się wykonywanie programu.
- Wszystkie działania, jakie funkcja ma wykonywać, zapisuje się w bloku ograniczonym nawiasami klamrowymi (`{...}`). 
- Do wyświetlania informacji w konsoli systemowej służy obiekt `std::cout` (z angielskiego *character output*). Identyfikator `std` oznacza, że jest to obiekt zdefiniowany w bibliotece standardowej języka. Zapis `::` to operator przestrzeni nazw: jego użycie mówi nam, że program używa obiektu `cout` z przestrzeni nazw `std`. Niemal wszystkie obiekty oraz zdecydowana większość funkcji udostępnianych przez bibliotekę standardową znajduje się w przestrzeni nazw  `std`.    
- Biblioteka standardowa języka C++ podzielona została na kilkadziesiąt, może nawet kilkaset części (nie liczyłem). Aby użyć którejkolwiek z nich, musimy do programu włączyć jej deklarację, zwykle instrukcją `#include <nazwa biblioteki>`. W naszym przykładzie włączamy do programu bibliotekę `iostream` (ang. *input-output stream*) zawierającą definicję obiektu `std::cout`. Chodzi tu o dosłowne włączenie do naszego programu zawartości pliku o nazwie `iostream` z lokalizacji znanej kompilatorowi.
-    Grupa symboli `<<` pełni w naszym programie funkcję operatora strumieniowego: przekazuje on argumenty znajdujące się po jego prawej stronie do strumienia danych reprezentowanego przez obiekt stojący po jego stronie lewej. W powyższym przykładzie dane trafiają do obiektu `std::cout`, który związany jest ze standardowym urządzeniem wyjścia (tzw. konsolą).
-    Dowolny tekst ujęty w cudzysłów (np. `"Witaj świecie!\n"`) to napis. Można tu używać polskich (greckich, gruzińskich itp.) liter. 
-    Każda funkcja, w tym `main()`, składa się z instrukcji. Każda instrukcja to wyrażenie zakończone średnikiem. Powyższy program zawiera jedną funkcję, która z kolei zawiera jedną instrukcję.  
-    Funkcje zwykle zwracają wartość. Jej typ zwykle zapisuje się przed nazwą funkcji. Stąd wyrażenie `int main()` oznacza, że funkcja `main` zwraca liczbę całkowitą (ang. `int`, czyli *integer*). Domyślnie funkcja `main` zwraca wartość `0` (zero).

     #### 2. Kompilacja programu

W przeciwieństwie do programów napisanych w językach skryptowych, takich jak Python czy JavaScript, które zwykle są przetwarzane przez [interpreter](https://pl.wikipedia.org/wiki/Interpreter_(program_komputerowy)), programy napisane w [językach kompilowanych](https://pl.wikipedia.org/wiki/J%C4%99zyk_kompilowany), jak C++, tłumaczone są bezpośrednio do kodu wykonywalnego (tzw. [kodu maszynowego](https://pl.wikipedia.org/wiki/J%C4%99zyk_maszynowy)), który może być bezpośrednio wykonywany przez procesor komputera. Translację tę wykonują specjalne programy zwane kompilatorami. W systemach Linux i pochodnych najbardziej popularne kompilatory języka C++ to `gcc` oraz `clang`. Każdy z nich można także zainstalować w innych systemach operacyjnych, w tym w Windows i OS X.  Oba te systemy posiadają też dedykowane im kompilatory, ale że nie używam tych systemów operacyjnych, przez chwilę ograniczę się do systemu Linux i kompilatora gcc. Co ciekawe, choć kompilator ten nazywa się gcc, komenda, którą jest wywoływany, to `g++`. W przypadku kompilatora clang, stosowna komenda to `clang++`. 

Jeżeli przedstawiony powyżej "pierwszy program w C++" zapisany został w pliku `pierwszy.cpp`, to kompilujemy go komendą

```bash     
> g++ pierwszy.cpp
```

gdzie `>` to oczywiście znak zachęty interpretatora terminala a nie część polecenia. Jak w systemie Windows otworzyć konsolę, znaleźć plik wykonywalny i go uruchomić – nie wiem. Tego systemu każdy używa na własną odpowiedzialność. 

W wyniku wykonania powyższej komendy w katalogu bieżącym powinien pojawić się plik o standardowej nazwie `a.out`.  Uruchamiamy go, poprzedzając jego nazwę kropką i ukośnikiem:

```bash
> ./a.out
```

Sesja z powyższym programem może więc wyglądać następująco:

 ```txt
 > vim pierwszy.cpp
 > g++ pierwszy.cpp 
 > ls -l
 razem 20
 -rwxr-xr-x 1 zkoza zkoza 15808 02-07 21:04 a.out
 -rw-r--r-- 1 zkoza zkoza    75 02-07 21:03 pierwszy.cpp
 > ./a.out 
 Witaj świecie!
 ```

Najpierw uruchomiłem edytor (tu: `vim`) i za jego pomocą w pliku `pierwszy.cpp` zapisałem kod źródłowy programu w języku C++. Następnie komendą `ls -l` sprawdziłem, czy w katalogu bieżącym pojawił się plik wykonywalny. Notabene, to, że `a.out` jest plikiem wykonywalnym wynika z pojawienia się literek `x` w ciągu znaków ` -rwxr-xr-x`, choć to temat na inny wykład. Na koniec uruchomiłem program `a.out`, co spowodowało wyświetlenie w konsoli napisu `Witaj świecie!`.

Jeżeli chcemy plik wykonywalny nazwać inaczej niż `a.out`, możemy posłużyć się opcją `-o`:

```txt
> g++ pierwszy.cpp -o pierwszy 
```

Teraz plik wykonywalny będzie nazywał się `pierwszy` i uruchamiać go będziemy poleceniem `./pierwszy`:

 ```txt
 > g++ pierwszy.cpp -o pierwszy
 > ls -l
 razem 36
 -rwxr-xr-x 1 zkoza zkoza 15808 02-07 21:04 a.out
 -rwxr-xr-x 1 zkoza zkoza 15808 02-07 21:16 pierwszy
 -rw-r--r-- 1 zkoza zkoza    75 02-07 21:03 pierwszy.cpp
 > ./pierwszy 
 Witaj świecie!
 ```

#### 3. Podstawowe narzędzia

Pisanie programów w zwykłym edytorze tekstu i kompilowanie go komendami wydawanymi z konsoli nie ma dziś większego sensu poza sytuacjami naprawdę awaryjnymi. Współczesne komputery są bowiem na tyle potężne, że z łatwością mogą wspomóc nas w pisaniu programów. Podstawowym narzędziem programisty, ułatwiającym nam pracę nad kodem, jest [zintegrowane środowisko programistyczne](https://pl.wikipedia.org/wiki/Zintegrowane_%C5%9Brodowisko_programistyczne). 

##### 3.1. Zintegrowane środowisko programistyczne

Zintegrowane środowiska programistyczne to prawdziwe kombajny, ułatwiające programiście wykonywanie wielu rutynowych zadań. Wśród cech dobrego zintegrowanego środowiska programistycznego dla języka C++ wymienić warto:

- Kolorowanie składni
- Inteligentne autouzupełnianie
- Automatyczne i konfigurowalne formatowanie (*indendation*) kodu źródłowego, w tym możliwość powiązania formatu z narzędziami zewnętrznymi
- Zintegrowana wyszukiwarka tekstu oraz miejsc deklaracji lub użycia funkcji, klas, zmiennych itp.
- Narzędzia do refaktoryzacji kodu (np. automatycznej zmiany nazwy zmiennej w każdym miejscu jej wystąpienia w kodzie)
- Integracja z systemami kontroli wersji, np. git, perforce, mercurial itp.
- Pełna integracja z debuggerem
- Integracja z systemem przeprowadzania testów automatycznych
- Integracja z narzędziami [programowania wizualnego](https://pl.wikipedia.org/wiki/Programowanie_wizualne)
- Możliwość dowolnego definiowania tzw. łańcuchów narzędzi (*toolkits*), czyli zestawów programów wykorzystywanych do kompilacji programów, środowisk, w jakich są uruchamiane i flag kompilacji     
- Istnienie licencji bezpłatnej dla celów edukacyjnych lub innych zastosowań niekomercyjnych
- Możliwość definiowania własnych makr, skrótów klawiaturowych oraz skryptów uruchamiających zewnętrzne programy
- Możliwość edytowania, debugowania i uruchamiania kodu rezydującego na maszynach zewnętrznych lub lokalnie w kontenerach (np. poprzez protokół SSH) 
- Dostępność na wielu platformach (np. Linux, Windows, OS X) 
- Integracja z wieloplatformowym systemem definiowania projektów C++, przede wszystkim z systemem `cmake`
- Integracja z systemami agentowymi LLM (zdalnymi lub lokalnymi)

Istnieje kilka programów spełniających większość lub nawet wszystkie z powyższych kryteriów. Należą do nich m.in.:

- [Qt Creator](https://pl.wikipedia.org/wiki/Qt_Creator) - posiada wszystko, co trzeba. Moje ulubione środowisko do programowania w C++.
- [CLion](https://pl.wikipedia.org/wiki/CLion) - komercyjny program z darmową licencję studencką. Oparty jest na CMake, jego interfejs jest  podobny do wielu innych popularnych produktów firmy JetBrains, co upraszcza naukę.
- [Visual Studio Code](https://pl.wikipedia.org/wiki/Visual_Studio_Code) - wymaga intensywnej konfiguracji, bo to jest uniwersalny edytor, który każdy sobie konfiguruje, instalując odpowiednie wtyczki. Bardzo popularny, bo obsługuje mnóstwo języków programowania. Niestety, wielu studentów nie potrafi go sobie skonfigurować i korzysta z niewielkiego ułamka jego możliwości. Ponadto VS Code domyślnie wykorzystuje własny system budowania aplikacji, co sprawia kłopoty przy przenoszeniu programów studenckich na inne platformy.   

Ja od lat korzystam z programu QtCreator, bo jest on idealnie dopasowany do programowania w C++. Każdy używa tego, co zna i lubi. Każdy edytor lub środowisko programistyczne wymaga miesięcy pracy z nim, by w miarę dokładnie poznać jego możliwości, stąd też nikt nie lubi zmieniać swojego IDE. Dlatego warto od razu zacząć przygodę z C++ od środowiska, w którym będzie się pracować przez lata i którego nie będzie potrzeby porzucać ze względu na brak potrzebnych udogodnień. Każdy z trzech powyższych zintegrowanych środowisk programistycznych jest używany w zastosowaniach profesjonalnych, spełnia więc powyższy warunek i jest godny polecenia. Nie polecam jednak pomysłów w rodzaju `code::blocks`. Tego rodzaju programy są łatwe na początku, ale szybko okazują się być ślepą uliczką.    

###### 3.1.1 Qt Creator

Qt Creator to potężne narzędzie zarówno pod względem oferowanych możliwości, jak i miejsca, jakie zajmuje na naszym dysku. Moim zdaniem – mieć go warto. Dość szczegółowy opis instalacji i konfiguracji tego narzędzia (w wersji z 2025 r.) znajduje się w [tutaj](./01-qtcreator.md). 

###### 3.1.2 CMake

CMake to system budowania projektów opracowany specjalnie dla grupy języków C i C++.  Opis używania tego narzędzia na poziomie podstawowym znajduje się w [tutaj](./01-cmake.md).

