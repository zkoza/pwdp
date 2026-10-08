### Lista zadań nr 1

**To nie jest lista na ocenę**. Ta lista to raczej „checklista” umiejętności podstawowych, które należy zdobyć, zanim zacznie się pisać programy w C++. W razie napotkania trudności można więc, a nawet wypada, pytać się koleżanek, kolegów, osoby prowadzące ćwiczenia, wykładowcę, internety i inne wiarygodne źródła informacj. Poniżej, dla zwięzłości poleceń zakładam, że student posługuje się własnym laptopem, jednak wszystkie polecenia można równie dobrze wykonać na komputerach dostępnych w uczelnianych pracowniach komputerowych. Nie trzeba wykonywać wszystkich poleceń – wystarczy skupić się na tych, których nie jesteśmy pewni. W końcu to jest tylko checklista! **Listę można też wykonać wspólnie w grupie**, jednak później każdy powinien być w stanie potwierdzić posiadanie wszystkich poniższych umiejętności, żeby potem zajęcia szły w miarę bezproblemowo.  

1. Zapoznał(a/e)m się z materiałami do pierwszego wykładu. 

2. Umiem wybrać prosty edytor tekstu i napisać w nim prosty (mieszczący się w jednym pliku i niewymagający bibliotek innych niż standardowa biblioteka C++) program w C++; wiem też, jakich edytorów unikać. To może być np. taki [program](../cpp/w01/pierwszy/pierwszy.cpp):
   ```c++
   #include <iostream>
   
   int main()
   {
       std::cout << "Witaj świecie!\n";
   }
   ```

3. W swoim komputerze mam zainstalowany kompilator języka C++. Wiem jak się nazywa i wiem, jak go uruchomić. 

4. Umiem skompilować program z punktu 1. w konsoli, wydając bezpośrednią komendę kompilacji programu.

5. Zainstalował(a/e)m w swoim komputerze zintegrowane środowisko programistyczne (IDE) obsługujące język C++ oraz system budowania programów CMake i potrafię je uruchomić.   

6. Potrafię napisać, skompilować i uruchomić program z punktu 1. w swoim ulubionym IDE. 

7. Potrafię znaleźć w systemie plików plik wykonywalny wygenerowany w poprzednim punkcie przez moje IDE. 

8. Plik wykonywalny z punktu 6. potrafię uruchomić bez korzystania z IDE.  

9. Potrafię załadować do IDE projekt w C++ oparty o system budowania CMake, a następnie go skompilować i uruchomić. Przykład takiego projektu znajduje się [w tym katalogu](../cpp/w01/pierwszy_cmake).

10. Poniższy program ([pobierz pliki](../cpp/w01/checklista)) po uruchomieniu wczytuje z konsoli 2 liczby, po czym wyświetla ich sumę, a ja potrafię go skompilować i uruchomić w moim IDE, wprowadzić te dwie liczby i odczytać wynik. To zadnie nie jest tak proste, jak się wydaje, bo część IDE (np. QtCreator) wymaga specjalnej konfiguracji projektu.  
    ```c++
    #include <iostream>
    
    int main()
    {
        double x = 0.0;
        double y = 0.0;
        std::cout << "podaj x: ";
        std::cin >> x;
        std::cout << "podaj y: ";
        std::cin >> y;
        std::cout << x << " + " << y << " = " << x + y << "\n";
    }
    ```

11. Potrafię uruchomić poniższy program ([pobierz pliki](../cpp/w01/checklista11)) pod kontrolą debuggera. 

    ```c++
    #include <cmath>
    #include <iostream>
    
    int silnia(int k)
    {
        if (k <= 1)
            return 1;
        return k * silnia(k - 1);
    }
    
    int main()
    {
        double suma = 0.0;
        for (int i : {1, 2, 3, 4, 5})
        {
            suma = suma + 1 / silnia(i);
        }
        std::cout << "suma odwrotności silni pięciu kolejnych liczb naturalnych wynosi "
            << suma << "\n";
        std::cout << "spodziewamy się tu liczby bliskiej " << exp(1.0) - 1.0 << "\n";
    }
    ```

    - Potrafię wykonywać go krok po kroku i śledzić stan zmiennych lokalnych.

    - Potrafię definiować punkty przerwań debuggera (ang. ***break points***) i debugować program, poruszając się od jednego punktu przerwań do kolejnego.    

    - Rozumiem, czym podczas debugowania „***step into***„ różni się od „***step over***”.

    - Wiem, jak w moim IDE wyświetlić podczas debugowania tzw. *backtrace* i z grubsza rozumiem, jakie informacje zawiera i jak się w nim poruszać.
      
    - Wiem, że aby komfortowo korzystać z debuggera, muszę program skompilować w odpowiednim trybie i że domyślnie ten tryb w większości IDE nazywa się „Debug” (lub podobnie, np. „Debugowa”).
    
12. Mam jako takie pojęcie, co to jest projekt w kontekście pracy z IDE. 

    - Z grubsza wiem, do czego służą pliki `CMakeLists.txt`
    
    - Potrafię otworzyć w moim IDE plik `CMakeLists.txt` definiujący bieżący projekt i dokonywać w nim prostych edycji

    - W szczególności potrafię w dowolnym projekcie ustawić wymaganą wersję języka na C++17, C++20 lub C++23.
    
    - Potrafię skompilować wczytany w ten sposób program i go uruchomić – w tym pod kontrolą debuggera. 
    
      
    