# Git

## 6. Git a praca w zespole

Praca w zespole to ten element pracy programisty, który jest najtrudniejszy, gdy z dotyka najbardziej fundamentalnego problemu inżynierii oprogramowania: złożoności tworzonego kodu. Jedną z głównych przyczyn popularności git-a jest to, jak bardzo ułatwia on pracę w zespołach oraz współpracę zespołów. 

### 6.1. Gałęzie

W poprzednim rozdziale przedstawiłem główne sposoby radzenia sobie z konfliktami w repozytorium, w którym ktoś pracuje nad tym samym problemem. W praktyce taka sytuacja zdarza się w programowaniu indywidualnym, ale nie w zespołowym. Dlaczego? Bo jeżeli mamy kilku- (kilkunasto-,…, kilkuset-) osobowy zespół pracowników, to chcemy jak najbardziej odseparować ich stanowiska pracy tak, by sobie nawzajem nie przeszkadzali. W tym celu dzielimy duży problem na mniejsze i przydzielamy je różnym grupom i/lub osobom. Każdemu z takich ,,małych” problemów przypisuje się w repozytorium git-a osobną gałąź (ang. branch). Służy do tego komenda `git branch`:

```txt
> git branch rozdzial-o-pracy-w-zespole
```

Powyższe polecenie utworzy gałąź o nazwie rozdzial-o-pracy-w-zespole. Każdy członek dostecznie dużego zespołu pracującego w dostatecznie bogatej firmie zarządza zadaniami (i przypisanymi im gałęźmi kodu) za pomocą specjalistycznego oprogramowania, np. [Jira](https://pl.wikipedia.org/wiki/JIRA) – ale to osobne zagadnienie, które tu pomijam.

Przypominam, że gałąź to po prostu łatwa dla nas do zapamiętania alternatywna nawa istniejącej migawki w repozytorium. Dokumentacja systemu posługuje się tu terminem „wskaźnik” (na migawkę). Bieżąca gałąź to tak naprawdę identyfikator węzła, z którego wyprowadzać będziemy kolejną migawkę repozytorium. To, co w gicie nazywa się gałęzią, tak naprawdę jest więc tylko jej czubkiem (czy też liściem drzewa, jakie tworzą migawki).         

Listę aktualnie zdefiniowanych gałęzi możemy uzyskać komendą 

```
git branch
```

Np. w moim repozytorium jej efekt wygląda następująco:

![](./img/00/git-branch-0.png)

System gwiazdką wyróżnia gałąź bieżącą, na której pracujemy. Do przechodzenia między gałęziami używamy polecenia `git switch`:

``` 
git switch rozdzial-o-pracy-w-zespole
```

Oto możliwy efekt jej działania:

![](./img/00/git-switch.png)

Jak widać, git poinformował mnie, że przełączyłem gałęzie w chwili, w której w moim obszarze roboczym znajdowały się pliki zmodyfikowane (etykieta „M”), nowe (etykieta „A”), a cześć plików jest z repozytorium usuwana (etykieta „D”). Zmian tych nie zatwierdzono jeszcze poleceniem `git commit`.

Jeżeli teraz wydam polecenie `git branch` to zobaczę, że bieżącą gałęzią jest `rozdzial-o-pracy-w-zespole`:

![](./img/00/git-branch-2.png)

Gałęzie najłatwiej tworzyć na serwerze, wtedy automatycznie zostaną wczytane na nasz komputer podczas wykonywania komendy `git pull`. W przeciwnym wypadku, gdy spróbujemy wypchnąć zmiany na serwer z nowo utworzonej gałęzi, git zwróci błąd, por.:  

```txt
> git add 000f-praca-w-zespole.md
> git commit -m"praca w zespole"
...
> git push 
fatal: The current branch rozdzial-o-pracy-w-zespole has no upstream branch.
To push the current branch and set the remote as upstream, use

    git push --set-upstream origin rozdzial-o-pracy-w-zespole

To have this happen automatically for branches without a tracking
upstream, see 'push.autoSetupRemote' in 'git help config'.

```

Git poinformował nas, w czym problem i jak go najłatwiej można naprawić:

```
> git push --set-upstream origin rozdzial-o-pracy-w-zespole
```

### 6.2. Pull request

Kolejnym tematem fundamentalnym dla pracy w zespole jest tzw. *pull request*. Co to jest i kiedy się go stosuje? Otóż *pull request* (na niektórych platformach, np. GitLab, znany też jako *merge request*) to prośba o włączenie naszej gałęzi do gałęzi nadrzędnej projektu (np. do gałęzi `main` lub `master`). Kiedy się go inicjuje? Oczywiście wtedy, gdy uważamy, że prace nad naszym pod-zadaniem dobiegły końca i na naszym kodzie mucha nie siada. 

Jak zgłasza się *pull request*? Zwykle za pomocą interfejsu WWW na serwerze chmurowym. W serwisach takich jak GitHub czy Git  

