# Wstęp

Niniejsze repozytorium zawiera materiały pomocnicze do zajęć *Praktyczny wstęp do programowania* dla studentów kierunku [ISSP](https://www.facebook.com/InformatykaStosowanaWFA/) na Uniwersytecie Wrocławskim.

***Materiały te z pewnością zawsze będą niepełne***. Nawet gdybym kiedyś mógł i chciał napisać kolejną [książkę o C++](https://helion.pl/ksiazki/jezyk-c-pierwsze-starcie-zbigniew-koza,jcppps.htm#section4_shift), to zanim bym te notatki uzupełnił w zadowalającym stopniu, język C++ zmieni się na tyle, że robotę trzeba by zaczynać niemal od początku.

### Jak się uczyć C++?

Języka C++ uczymy się mniej więcej tak, jak języka angielskiego lub gry na fortepianie. Uczymy się  trochę i staramy się to "trochę" stosować w swoich programach / grze na fortepianie. A potem więcej i więcej, tyle, ile będzie nam potrzebne i tyle, ile jesteśmy w stanie. Żeby dobrze grać na fortepianie, trzeba naprawdę dużo na nim grać. Podobnie, nie nauczymy się programować z książek, instrukcji użytkownika, bryków czy blogów. Jednak tak jak zajęcia z teorii muzyki pomagają pianiście zrozumieć strukturę granych przez siebie utworów muzycznych, tak lektura podręczników czy choćby przedstawionych tu materiałów pomaga uporządkować swoją wiedzę i po prostu lepiej i szybciej programować.

Językiem angielskim można się posługiwać, znając tylko kilka tysięcy słów i kilka podstawowych "prawd gramatycznych". Z programowaniem jest tak samo. Jeśli po ok. roku nauki czegoś jeszcze o programowaniu się nie wie, to znaczy, że pewnie dotąd nie było to potrzebne, czyli strata niewielka. Ja staram się tu poruszać tematy naprawdę ważne i mające mające możliwie szerokie zastosowanie niezależnie od używanego języka. 

W niniejszym kursie używam języka C++.  Oczywiście w wersji uproszczonej, czyli jego podzbioru  dostosowanego do możliwości początkujących programistów. 

Dlaczego C++? 

- Bo od połowy lat 90. ub. wieku jest on używany powszechnie wszędzie tam, gdzie wymagana jest wysoka wydajność i niezawodność kodu. 
- Bo jest dość ściśle, jak na język wysokiego poziomu, związany ze sprzętem, na którym jest uruchamiany, co ułatwia zrozumienie uniwersalnych zasad programowania komputerów.
- Bo język C++ (lub ściśle z nim związany język C) jest używany w wielu ogólnych podręcznikach programowania (np. w podręczniku Cormena *[Wstęp do algorytmów](https://ksiegarnia.pwn.pl/Wprowadzenie-do-algorytmow,1041498749,p.html)*).
- Bo na językach C/C++ wzorowano projekty wielu innych języków programowania, jak C#, Java czy Objective C i są one podstawowymi językami w kilku ważnych technologiach (np. [embedded](https://en.wikipedia.org/wiki/Embedded_software), [GPGPU](https://en.wikipedia.org/wiki/General-purpose_computing_on_graphics_processing_units), [MPI](https://pl.wikipedia.org/wiki/Message_Passing_Interface), grafika). 
- Bo nie są to pierwsze zajęcia z programowania i studenci powinni poznać zupełnie inne podejście do programowania niż to, które poznali bądź poznają na zajęciach z takich technologii, jak Python,  JavaScript czy Matlab.
- Bo go nieźle znam, więc pewnie mogę go uczyć bez obawy, że komuś zaszkodzę.

*Praktyczny wstęp do programowania*, jak sama nazwa wskazuje, nie jest jednak kursem języka C++. To jest kurs programowania, w którym język C++ jest tylko narzędziem. Narzędziem, które należy jednak choć trochę poznać.

Zarówno programowania, jak i języków programowania uczymy się tak, jak języków obcych (i nawet języka ojczystego) - przez całe życie. Początkowo ledwo dukając niezbyt zrozumiałe formułki i stopniowo nabierając wprawy. Z dzieckiem można się dogadać po ok. dwóch latach nauki, po czterech latach komunikacja zwykle jest już płynna. Nie inaczej jest z programowaniem i nauką języków programowania, zwłaszcza jeśli uczy się kilku takich języków naraz i zachodzi znane z nauki języków naturalnych zjawisko [interferencji](https://pl.wikipedia.org/wiki/Transfer_j%C4%99zykowy).

### Zalecana literatura

Liczba materiałów do nauki programowania w C++ jest gigantyczna. Trudno mi doradzić, które z nich są odpowiednie dla osób (w miarę) początkujących. Na pewno należy unikać materiałów, które przedstawiają C++ w wersji wcześniejszej niż C++11 i nie kupować niczego poniżejC++17. W czasach, gdy podstawową metodą zdobywania wiedzy była lektura książek, studenci chwalili podręcznik Jerzego Grębosza

-  Jerzy Grębosz, [Opus Magnum C++](https://ifj.edu.pl/private/grebosz/opus.html).

To na pewno dobry podręcznik, ma jednak jedną wadę: 3 tomy, łącznie 1605 stron lektury, a do tego [uzupełnienie do standardu C++17](https://ifj.edu.pl/private/grebosz/misja_spis_tresci.pdf) liczące sobie, bagatela, kolejne 265 stron.

Dawno, dawno temu napisałem niespełna 300-stronicowy podręcznik, którego uważna lektura wówczas dawała duże szanse na pomyślne przejście rozmowy kwalifikacyjnej podczas aplikowania o pracę:

-  Zbigniew Koza, [Język C++. Pierwsze starcie](https://helion.pl/ksiazki/jezyk-c-pierwsze-starcie-zbigniew-koza,jcppps.htm).

Niestety, dziś zawartość tej książki to dużo za mało, w dodatku przedstawia ona "stary" C++ w wersji z roku 1998. Może jednak, dzięki zwięzłości i skoncentrowaniu na najważniejszych cechach języka, komuś się jeszcze przydać. Tak podstawowe aspekty języka, jak czas życia obiektu, wskaźnik, referencja, klasa, funkcja, funkcja wirtualna, iterator, kontener, algorytm czy obiekt funkcyjny - nie zmieniły się ani o jotę od momentu wprowadzenia ich do języka.

Materiałem referencyjnym, czyli dosłownie przedstawiającym standard(y) języka wraz z przykładami użycia jest serwis CppReference:

- [cppreference.com](https://en.cppreference.com/w/).

Jedyną jego wadą jest to, że standard opisywany jest językiem mocno technicznym, nieraz trudnym do zrozumienia nawet dla mnie, a cóż dopiero dla osób początkujących.

Każdy programista korzysta z serwisu StackOverflow

- [StackOverflow](https://stackoverflow.com/).

Wątpię, czy istnieje pytanie związane z programowaniem na podstawowym lub średnim poziomie, które nie posiada tam już co najmniej jednej trafiającej w sedno odpowiedzi.

Kanały na YouTube:

- [Cherno](https://www.youtube.com/playlist?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb) - w tej chwili 101 krótkich filmów, widziałem kilka, autor wie, o czym mówi
- Niestety, nie polecam [kursu Mirosława Zelenta](https://www.youtube.com/channel/UCzn6vAfspIcagLax1fck_jw), co nie znaczy, że na początku nie ma sensu z niego korzystać. Co nie ma sensu to udawanie, że na ten kurs nie natrafisz. Trafisz, bo jest tego bardzo dużo i jest to po polsku. Jeśli uważasz, że to kurs dla ciebie, to OK. Nie mam zaufania do ekspertów od wszystkiego, wiele "prawd" przedstawionych w tamtych kursie jest powierzchownych, nieprecyzyjnych. Dla osób początkujących to może jednak nie mieć znaczenia. Wasz wybór.  

Inne materiały:

- [Kurs C++0x](https://cpp0x.pl/kursy/Kurs-C++/1). Zaleta: po polsku, autor zwykle wie, o czym pisze, ale treść tego serwisu w ciągu 10 lat była chyba rzadko odświeżana, tymczasem od momentu jego powstania C++ zdążył się nieco rozrosnąć.  

Bieżący "kurs" **nie jest** pełnym kursem C++. To raczej zwięzły materiał do powtórki przed zajęciami/egzaminem. Pomysł, by zastąpić tymi materiałami samodzielne rozwiązywanie zadań w laboratorium komputerowym bądź udział w wykładzie z pewnością nie jest dobry. 

### Warunki zaliczenia przedmiotu

- Podstawą uzyskania zaliczenia jest obecność na zajęciach oraz rozwiązanie dostatecznej liczby zadań

- Szczegółowe zasady podaje osoba prowadząca ćwiczenia

### Egzamin

Kiedyś był pisemny, ale odkąd zauważyłem, że wielu studentów ma kłopoty z jasnym wysławianiem się pisemnym, jest ustny. Zwykle trwa 2 dni (w sensie: studenci dzielni są na 2 grupy).

#### Sztuczny

W 2026 r. nie można udawać, że Sztuczny (AI) nie potrafi generować użytecznego kodu w dowolnym języku programowania. Sam, pisząc skrypty w `bash`-u, którego znam tylko podstawy, pomagam sobie zapytaniami do sztucznego. Zwykle jego odpowiedzi są poprawne, czasami odpisuje nie na temat i muszę przeprosić się z wujkiem Googlem, czasami porady Sztucznego są po prostu błędne. 

Istnieją komercyjne wersje Sztucznego dostosowane do generowania kodu. Wg ich twórców, platformy te wkrótce wyeliminują z rynku większość programistów "białkowych". Pożyjemy, zobaczymy. Póki co, ten kod generowany jest na podstawie danych treningowych zaczerpniętych z internetu, w tym publicznych repozytoriów oprogramowania, jak GitHub czy SourceForge. Wklejanie kodu wygenerowanego przez Sztucznego w wielu przypadkach równoważne jest więc z plagiatem. I to jest moje stanowisko odnośnie korzystania ze Sztucznego na tych zajęciach. Można go prosić o wytłumaczenie jakichś aspektów programowania - wtedy streści nam zawartość kilku stron internetowych tak, jakby sam był ich autorem. 
