# Git

## 3. Podstawy pracy z repozytorium lokalnym

### 3.1. Wprowadzenie

Załóżmy, że za pomocą `git init` lub `git clone` utworzyliśmy w swoim komputerze repozytorium lokalne.  Od tej chwili możemy w nim w dotychczasowy sposób dodawać nowe pliki (i katalogi) oraz modyfikować bądź usuwać pliki istniejące. Nie będzie to miało żadnego wpływu na stan repozytorium lokalnego. Ten stan możemy zmienić wyłącznie poprzez komendy programu `git`. Ich podstawowa składnia jest prosta:

```txt
git <komenda> [-opcja] ... [-opcja] [--opcja] ... [--opcja] [argument_1] [argument_2] ... [argument_n]
```

Czyli polecenie git wymaga podania komendy (np. `add`) i opcjonalnej listy opcji (rozpoznajemy je po jednym lub dwóch dywizach na początku ich nazwy) oraz równie opcjonalnej listy argumentów. Zwyczajowo opcje z jednym dywizem to formy skrócone, jednoliterowe, np. `git -h`  to to samo co `git --help`. 

### 3.2. Komendy niemodyfikujące repozytorium 

Zaczniemy od rzeczy najłatwiejszych i najbezpieczniejszych:  komend systemu `git` służących do uzyskiwania informacji o stanie repozytorium, w tym o jego historii. Do najważniejszych należą:

- `git log`
- `git status`
- `git diff`
- `git config list`

Kilka przykładów ich zastosowania na repozytorium, które w tej chwili czytasz:

- `git log`:
  ![](/home/zkoza/Pulpit/Dydaktyka/aaa_pwdp/github/pwdp/img/00/git-log.png)
  Komenda ta wyświetla listę dostępnych migawek wraz z ich krótkim opisem. Widzimy, kto jest autorem każdej z nich i kiedy została dodana do repozytorium. Widzimy też skróty SHA1 każdej z nich (ciągi znaków szesnastkowych po słowie „commit”). Widzimy też, że do ostatniej z migawek można się odwołać za pomocą „wskaźników” / „referencji” `HEAD` (na gałęzi `main`), `origin/main` oraz `origin/HEAD`. Powyższy zrzut ekranu przedstawia tylko niewielki wycinek logu tego repozytorium – dwa wpisy z trzydziestu siedmiu. 

- `git status`:

  ![](/home/zkoza/Pulpit/Dydaktyka/aaa_pwdp/github/pwdp/img/00/git-status.png)

  Widzimy, że do indeksu dodano dotąd jeden plik: `cpp/w11/sfml30/sfml.cpp`. Od utworzenia poprzedniej migawki zmieniono 4 pliki, w tym `000-git.md`, czyli plik, który w tej chwili czytasz. W obszarze roboczym znajduje się też sporo plików nieśledzonych, a nawet całe katalogi. Jednym z nich jest `img/00`, w którym znajdują się obrazki wyświetlane na tej stronie.

- `git diff`. 

  Polecenie `git status` poinformowało nas, że od czasu utworzenia ostatniej migawki, w naszym projekcie zmianie uległ m.in. plik `pgm0.cpp` znajdujący się w podkatalogu `cpp/w04/pgm/`. Aby sprawdzić, co to za zmiany, wystarczy wydać polecenie `git diff cpp/w04/pgm/pgm0.cpp`:

  ![](./img/00/git-diff.png)

  Tutaj zmiany zaznaczone są kolorem: wiersze dodane wyświetlane są na zielono (i są poprzedzone znakiem `+`), wiersze usuwane – na czerwono (poprzedzone są znakiem `-`, a wiersze niezmienione - na biało. Dodatkowo niektóre wiersze zaczynają się od pary wyświetlanych na niebiesko znaków `@`, po których znajdują się pewne liczby. Jest to informacja o zmianach zapisana w formacie [Universal diff](https://en.wikipedia.org/wiki/Diff#Unified_format).

- `git config list`:

  ![](./img/00/git-config-list.png)

  Ta opcja pozwala zorientować się w aktualnej konfiguracji repozytorium. Na powyższym zrzucie ekranu najważniejsze są informacje na końcu tej listy: repozytorium połączone jest z serwisem GitHub (a nie np. Codeberg).  

### 3.3. Komendy modyfikujące repozytorium

Większość komend modyfikujących repozytorium dotyczy modyfikacji indeksu, czyli pliku, w którym zapisywana jest kolejna migawka. Najczęściej wykorzystywanym poleceniem z tej grupy jest `git add`. Przypuśćmy, że chcemy przygotować do utrwalenia w postaci migawki zmiany w pliku, który czytasz. W tym celu wydajemy polecenie

```txt
git add 000c-praca-z-repo-lokalnym.md
```

Dodaje ono do indeksu plik `000c-praca-z-repo-lokalnym.md` w jego bieżącym stanie. Jedną komendą można dodać do indeksu kilka plików naraz, np.:

   

 



