# Git

## 5. Git a praca w zespole

Praca w zespole to domyślny tryb pracy w środowisku git. Mam ona pewną bardzo charakterystyczną specyfikę, którą nieco żartobliwie nazwałbym tendencją do występowania zjawiska znanego w informatyce jako [wyścig](https://en.wikipedia.org/wiki/Race_condition#In_software) (*nota bene*, nie mogę pojąć, że tak ważne pojęcie nie jest opisane w polskiej Wikipedii w kontekście oprogramowania komputerowego – październik 2026). Wyścig to zjawisko polegające na tym, że co najmniej dwa niezależne „byty”, np. programy, wątki programów, agenci AI, ludzie – usiłują jednocześnie modyfikować ten sam zasób, nie mając „świadomości”, że robią to (w pewnym sensie) jednocześnie. W przypadku git-a tym zasobem jest po prostu repozytorium. Chodzi o to, że jeżeli w zespole pracuje co najmniej kilka osób, to nie można odseparować zasobów (tu: po prostu plików), które twórcy oprogramowania mogą podczas wykonywania swoich zadań modyfikować. Te same osoby mogą w tym samym czasie chcieć zmienić zawartość tych samych plików, nie wiedząc o sobie nic nawzajem. Jak rozstrzygnąć, czyja zmiana jest ważniejsza? Jak w ogóle włączyć te pozornie chaotycznie wykonywane zmiany do głównego repozytorium tak, by nie wprowadzić do niego błędów?

Rozpoczną od scenariusza podstawowego, z którym początkujący użytkownik git-a styka się najczęściej: konflikt przy próbie wykonania operacji `git pull` (czyli ściągnięcia na swój komputer aktualnej wersji zdalnego repozytorium).

### 5.1. Konflikt podczas operacji `git pull`

Jeżeli operacja `git pull` nie może dojść do skutku, to zwykle dlatego, że ktoś zmienił zawartość repozytorium w taki sposób, że jego pobranie na nasz komputer nadpisałoby zmiany, które sami niedawno zrobiliśmy. W takim przypadku mamy tzw konflikt (a raczej konflikty, bo zwykle takich konfliktujących zmian jest wiele) . Mamy teraz dwa przypadki: łatwy (rozwiązanie konfliktów można zautomatyzować) i nieco trudniejszy (rozwiązanie konfliktów wymaga decyzji człowieka).

#### 5.1.1. Konflikty rozwiązywane automatycznie

Przypuśćmy, że będąc w pracy, zmieniłem w tym pliku którego zawartość właśnie czytasz, tytuł z „Git” na „Git jest git” i zapisałem tę zmianę na serwerze – np. edytując ten plik bezpośrednio na serwerze. Jednocześnie po przyjściu do domu zapomniałem o tym i dopisałem jakiś tekst na końcu. Następnie, cały czas pracując na domowym komputerze, próbuję te zmiany zapisać na serwer. Efekt jest jak na rysunku poniżej:

![](./img/00/git-push-failed.png)

Git komunikuje, że nie może wykonać operacji `git push`, gdyż zdalne repozytorium zawiera zmiany, których nie ma w repozytorium lokalnym. Sugeruje też, by wykonać `git pull` a dopiero później `git push`.    Próbujemy. Po chwili otwiera się domyślny (dla git) edytor, a w nim komunikat

```txt 
Merge branch 'main' of github.com:zkoza/pwdp
# Podaj komunikat zapisu, żeby wyjaśnić, dlaczego to scalenie jest konieczne,
# zwłaszcza jeśli scala zaktualizowaną gałąź nadrzędną z gałęzią tematyczną.
#
# Lines starting with '#' will be ignored, and an empty message aborts
# the commit.
```

Oznacza on, że git przystępuje do automatycznego włączania zmian z repozytorium zdalnego do repozytorium lokalnego. Migawka, którą w tym celu utworzy, będzie typu „merge” (po polsku: „scalanie”). Taka migawka ma 2 przodków. W edytorze mamy przygotowany domyślny dla scalania komunikat „Merge branch 'main' of github.com:zkoza/pwdp” – cała reszta zostanie podczas scalania odrzucona. Możemy wstrzymać scalanie, kasując ten komunikat. Tym razem postanawiamy jednak dokończyć scalanie – w tym celu po prostu zapisujemy plik w bieżącej postaci. Git wyświetli nowy komunikat:

![](/home/zkoza/Pulpit/Dydaktyka/aaa_pwdp/github/pwdp/img/00/git-pull-prosty-ok.png)

Oznacza on, że scalanie zakończyło się pomyślnie. Widzimy też, że zmiany objęły w pliki. W jednym dodano 18 wierszy i usunięto 3, w drugim dodano 1 wiersz i usunięto też 1 (liczba plusików i minusików jest proporcjonalna do liczby dodanych i usuniętych wierszy w każdym pliku). To wszystko. Zsynchronizowaliśmy zmiany uwidocznione w serwerze zdalnym z lokalnymi, tworząc nową migawkę. Możemy ją wepchnąć na serwer poleceniem `git push`. Aby teraz zobaczyć zmiany w repozytorium zdalnym za pomocą przeglądarki, zwykle należy odświeżyć jej widok.   

#### 5.1.2. Konflikty rozwiązywane ręcznie

W powyższym przykładzie zmiany na serwerze dotyczyły różnych miejsc tego samego pliku. Takie zmiany łatwo „rozwiązać” automatycznie. Prawdziwy problem („wyścig”) pojawia się, gdy zmiany dotykają tych samych wierszy naszych plików. Spróbujmy dokonać ponownej edycji pierwszego wiersza bieżącego pliku, na serwerze i lokalnie, za każdym razem inaczej zmieniając jego treść.     

 

 

 
