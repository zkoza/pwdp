# Git

## 2. Repozytorium 

### 2.1. Co to jest repozytorium?

Repozytorium to rodzaj biblioteki przechowującej wszystkie migawki naszego projektu. W tej analogii migawki to jakby książki, które możemy wypożyczać i zwracać do biblioteki. Możesz też myżleć o repozytorium jak o bardzo specjalistycznej bazie danych przechowującej różne wersje plików.  

Repozytorium znajduje się w podkatalogu `.git` głównego katalogu naszego projektu. Na przykład po wydaniu komendy `tree -L1 -a` w głównym katalogu jednego z moich projektów, otrzymuję następujący wynik:

```txt
├── cpp/
├── .git/
├── .gitignore
├── README.md
└── tex/
```

Oznacza to, że w tym katalogu istnieją dwa pliki (`.gitignore` i `README.md`) oraz trzy podkatalogi (`.git`, `tex` i `cpp`). Wszystko, co znajduje się poza katalogiem `.git`, to przestrzeń robocza projektu. Mogę dowolnie ją modyfikować. Mogę usunąć z niej wszystkie pliki. Nie ma to znaczenia, bo w każdej chwili mogę odtworzyć w tym miejscu stan projektu zapisany w dowolnej migawce przechowywanej w katalogu („bibliotece”) `.git`. 

Jest to pierwsze bardzo ważne rozróżnienie. 

- Katalog `.git` zarządzany jest przez program `git` i raczej nie powinniśmy w nim robić ręcznych modyfikacji (istnieją wyjątki od tej reguły! – dotyczą one np. konfiguracji skryptów wywoływanych automatycznie przez git w określonych sytuacjach).
- Naszą przestrzeń roboczą tworzy reszta plików i katalogów znajdujących się w katalogu głównym projektu (tym, w którym bezpośrednio znajduje się podkatalog `.git`).

### 2.2. Synchronizacja z serwisami w chmurze

Systemy kontroli wersji używane są zwykle w zespołach programistów lub przez pojedyncze osoby korzystające z wielu komputerów (np. prywatnego i służbowego). W takim przypadku pojawia się kwestia synchronizacji pracy wykonywanej na różnych urządzeniach. Do jej przeprowadzenia powszechnie wykorzystuje się rozwiązania chmurowe, zapewniające dostępność serwisu w trybie 24/7 i bezpieczeństwo danych, które w dodatku z zasady są darmowe dla małych projektów. Obecnie (2026 r.) do najpopularniejszych platform oferujących hosting repozytoriów git należą [GitHub](https://github.com/), [GitLab](https://about.gitlab.com/), [BitBucket](https://bitbucket.org/) i [Codeberg](https://codeberg.org/). Trzy pierwsze to bardzo rozbudowane rozwiązania komercyjne, oferujące jednak darmowy hosting repozytoriów git-a dla małych zespołów. Alternatywą jest self-hosting, który zapewnia m.in. [forgejo](https://forgejo.org/) i [gitea](https://about.gitea.com/products/gitea/). Uwaga: jeżeli zależy Ci wyłącznie na hostowaniu repozytorium git-a, wystarczy dostęp do maszyny stale podpiętej do Sieci, ze statycznym IP, z którą możesz łączyć się przez `ssh`. Opisane powyżej serwisy oprócz samego hostowania oferują też mnóstwo dodatkowych usług, jak choćby dostęp (odczyt i modyfikacja) do repozytorium przez przeglądarkę WWW.    

Większość studentów zakłada konto na GitHubie. W firmie możesz się też spotkać z repozytoriami przechowywanymi w serwisie GitLab lub BitBucket. Przez przekorę poniżej przedstawiam kilka szczegółów dotyczących konfiguracji „społecznościowego” serwisu Codeberg. Na każdym innym pracuje się tak samo, jednak każdy posiada własny interfejs użytkownika. Ten z serwisu Codeberg jest wyjątkowo „czysty”.   

#### 2.2.1 Utworzenie konta

W każdym z takich serwisów należy się zarejestrować (utworzyć konto). Dasz radę bez mojej pomocy!

#### 2.2.2. Konfiguracja kluczy SSH (lub GPG)

Następnie warto skonfigurować klucze SSH (lub GPG). Dzięki temu nie będzie potrzeby za każdym razem, gdy łączysz się z serwerem, podawać hasła. W tym celu szukamy menu z ustawieniami. W serwisie Codeberg są one dostępne po kliknięciu ikony w prawym górnym rogu programu:

#### ![](/home/zkoza/Pulpit/Dydaktyka/aaa_pwdp/github/pwdp/img/00/codeberg_settings_menu.png)

Wybieramy w nim opcję „Ustawienia”, a następnie w oknie, które się wyświetli, wybieramy z menu po lewej opcję klucze `SSH / GPG`: 

![](/home/zkoza/Pulpit/Dydaktyka/aaa_pwdp/github/pwdp/img/00/codeberg_settings_menu_lewe.png)

Teraz wracamy do swojego komputera i, jeśli nie mamy jeszcze kluczy SSH (lub GPG - protokół SSH wydaje się jednak łatwiejszy) – generujemy je. Opis sposobu wykonania tej czynności znajduje się m.in. [tutaj](https://docs.codeberg.org/security/ssh-key/). W systemach Linux klucze SSH standardowo znajdują się w podkatalogu `.ssh` katalogu domowego. Następnie klikamy przycisk `Dodaj klucz`. Ujrzymy następujący ekran:

![](/home/zkoza/Pulpit/Dydaktyka/aaa_pwdp/github/pwdp/img/00/codeberg_settings_menu_lewe2.png)

Definiujemy nazwę klucza (może być dowolna) i wklejamy w kolejnym polu swój klucz PUBLICZNY (klucz prywatny zwykle zaczyna się od komunikatu `-----BEGIN OPENSSH PRIVATE KEY-----`, a klucz publiczny to ten drugi…). Klikamy `Dodaj klucz`. I to wszystko. 

Prawie wszystko. Gdy sam przeszedłem powyższą procedurę, po pewnym czasie okazało się, że Codeberg wymaga weryfikacji klucza. Klikamy więc przycisk „Zweryfikuj klucz” i postępujemy zgodnie z instrukcją wyświetlaną na ekranie. 

### 2.3 Instalacja

#### 2.3.1 Instalacja lokalnego środowiska git

Opis lokalnej instalacji systemu git można znaleźć m.in. [w oficjalnej dokumentacji git](https://git-scm.com/install/linux).

#### 2.3.2 Wstępna konfiguracja systemu git

Przed pierwszym użyciem swojej lokalnej instalacji git-a, należy ją skonfigurować. Pełny opis znajduje się m.in. w oficjalnym [tutorialu systemu git](https://git-scm.com/book/ms/v2/Getting-Started-First-Time-Git-Setup). Chodzi o dwa polecenia, w których konfigurujesz swoje imię i nazwisko oraz e-mail:

```git
$ git config --global user.name "imię nazwisko"
$ git config --global user.email bolek_i_lolek@email.pl
```

Te dwie informacje zostaną dołączone do każdej migawki przechowywanej w repozytorium i będą widoczne dla każdego, kto ma do niego dostęp.

## 2.4. Tworzenie i konfiguracja repozytorium

Repozytorium można utworzyć na dwa sposoby: albo na zdalnym serwerze, albo lokalnie na własnym komputerze. 

##### 2.4.1. Tworzenie repozytorium na zdalnym serwerze (poprzez interfejs WWW)

W przypadku serwisu Codeberg, klikamy symbol `+` w menu w prawym górnym rogu i wybieramy jedną z opcji: `nowe repozytorium` lub `nowa migracja` (to drugie tylko jeśli wiesz, o co chodzi). Następnie uzupełniamy niezbędne dane, jak np. nazwa repozytorium.

##### 2.4.2. Tworzenie repozytorium lokalnego (w konsoli)

Aby utworzyć repozytorium lokalnie, należy w wybranym katalogu wykonać polecenie 

```bash   
> git init
```

Spowoduje ono wygenerowanie i inicjalizację katalogu `.git`. 

Uwaga: dopóki nie poczujesz się dość pewnie w pracy z systemem git, zawsze twórz repozytoria na zdalnym serwerze, a następnie klonuj je u siebie (opisuję to nieco dalej). Z kolei do nauki, eksperymentowania. repozytoria tworzone lokalnie nadają się wyśmienicie.   

### 2.4.3. Połączenie z repozytorium zdalnym

#### 2.4.3.1. Połączenie zdalnego repozytorium z lokalnym komputerem: `git clone`

Jeżeli mamy repozytorium zdalne, to chcielibyśmy połączyć je z naszym komputerem. W tym celu wybieramy lokalny katalog i wprowadzamy w nim komendę 

```git  
git clone ADRES_ZDALNEGO_REPO
```

Adres zdalnego repozytorium odczytujemy za pomocą przeglądarki WWW ze strony głównej naszego repozytorium. W poniższym przykładzie nazwa użytkownika to `zzkoza`, nazwa repozytorium to `pwdp`, adres ([URL](https://pl.wikipedia.org/wiki/URL)) repozytorium to `ssh://git@codeberg.org/zzkoza/pwdp.git`.  

![](/home/zkoza/Pulpit/Dydaktyka/aaa_pwdp/github/pwdp/img/00/codeberg_settings_new_repo_clone.png)

Zwykle istnieją co najmniej dwa identyfikatory („adresy”) tego samego repozytorium: jeden obsługiwany poprzez protokół HTTPS, drugi – przez SSH. Jeżeli poprawnie skonfigurował(a/e)ś swoje klucze SSH, wybieraj  identyfikator SSH – alternatywny protokół HTTPS nie wymaga konfiguracji, ale zawsze wymaga uwierzytelniania dostępu (podania hasła), co w warunkach codziennej pracy jest irytujące. Notabene, adres tego samego repozytorium, wykorzystujący jednak protokół HTTPS, to `https://codeberg.org/zzkoza/pwdp.git`. 

Przykładowo, aby zaimportować zdalne repozytorium o adresie `ssh://git@codeberg.org/zzkoza/pwdp.git`,  wydajemy w odpowiednim katalogu naszego systemu plików polecenie

```bash  
> git clone ssh://git@codeberg.org/zzkoza/pwdp.git
```

Spowoduje to utworzenie w tym katalogu podkatalogu zawierającego całe, pobrane z serwera repozytorium (tu: `pwdp,git`).

```txt
> git clone ssh://git@codeberg.org/zzkoza/pwdp.git
Klonowanie do „pwdp”...
remote: Enumerating objects: 422, done.
remote: Counting objects: 100% (422/422), done.
remote: Compressing objects: 100% (243/243), done.
remote: Total 422 (delta 166), reused 422 (delta 166), pack-reused 0 (from 0)
Pobieranie obiektów: 100% (422/422), 2.21 MiB | 1.79 MiB/s, gotowe.
Rozwiązywanie delt: 100% (166/166), gotowe.
```

Przy pierwszym połączeniu z serwerem, możemy też ujrzeć informację, że tego serwera nasz agent SHH nigdy wcześniej nie widział. Wpisujemy „yes” i zatwierdzamy klawiszem Enter. 

```txt  
The authenticity of host 'codeberg.org (217.197.84.140)' can't be established.
ED25519 key fingerprint is: SHA256:mIlx****
This key is not known by any other names.
Are you sure you want to continue connecting (yes/no/[fingerprint])? yes
Warning: Permanently added 'codeberg.org' (ED25519) to the list of known hosts.
```

Po chwili mamy w swoim systemie plików całe repozytorium `pwdp` w osobnym katalogu o nazwie… `pwdp`:

```txt
> tree -L 2 -a
.
└── pwdp/
    ├── 000-git.md
    ├── 00-wstep.md
    ├── 01-cmake.md
    ...
    ├── 11-SFML-shapes-colors.md
    ├── cpp/
    ├── .git
    ├── .gitignore
    ├── img/
    ├── listy/
    ├── README.md
    └── toc.md
```

#### 2.4.3.2. Synchronizacja repozytorium lokalnego ze zdalnym

Czasami sytuacja jest odwrotna: mamy repozytorium lokalne i chcemy je podłączyć do repozytorium zdalnego. Odradzam taką kolejność początkującym (choć nie jest to specjalnie trudne). Na początku zawsze twórz puste repozytoria na zdalnym serwerze, a potem klonuj je na własnej maszynie, a jeśli masz już jakieś pliki, po prostu skopiuj/przenieś je do tego pustego repozytorium (najpierw lokalnie).