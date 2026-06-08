## Lista zadań nr 4

1. (1 pkt.) Napisz program, który będzie generował plik w formacie PGM (tryb ASCII, czyli *plain PGM*) przedstawiający szachownicę o rozmiarze 800 na 800 pikseli z jasnymi i ciemnymi polami o rozmiarze 100 na 100 pikseli. Pole w lewym górnym rogu powinno być jasne.

2. (2 pkt) Napisz program, który będzie wczytywał plik w formacie PGM (ASCII) i automatycznie zamieniał go na tzw. *[ASCII art](https://en.wikipedia.org/wiki/ASCII_art)* stosując metodę, w której przestrzeń kolorów obrazu najpierw konwertuje się do odcieni szarości (ang. *grayscale*), a następnie różnym odcieniom przypisuje się odpowiednie znaki (litery, cyfry itp.). Proponuję na początek zastosować tablicę (napis):

   ```c++        
   " ..,:;!=oxO#%@";
   ```

   W tym napisie kolejne znaki charakteryzują się wzrastającą liczbą pikseli zapalanych w celu wyświetlenia danego [glifu](https://pl.wikipedia.org/wiki/Glif_(typografia)), co odpowiada rosnącej jasności piksela obrazu wejściowego, od czerni (jeżeli tło twojej konsoli jest czarne) do (prawie) bieli.

3. (2 pkt). Do wyboru jeden z dwóch:

   - A) Zapoznaj się z formatem [Plain PPM](https://netpbm.sourceforge.net/doc/ppm.html#plainppm). Przekształć jeden z programów (`pgm0.cpp`, `pgm0a.cpp` itd), które przedstawiłem w opisie formatu PGM ([tutaj](../cpp/w04/pgm)) tak, by na obrazku pojawiły się kolory.

   LUB

   -  B) Napisz program, który zlicza i wyświetla liczbę wierszy, słów i znaków w dowolnym pliku. 

     