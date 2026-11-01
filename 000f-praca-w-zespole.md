# Git

## 6. Git a praca w zespole

Praca w zespole to ten element pracy programisty, który jest najtrudniejszy, gdy z dotyka najbardziej fundamentalnego problemu inżynierii oprogramowania: złożoności tworzonego kodu. Jedną z głównych przyczyn popularności git-a jest to, jak bardzo ułatwia on pracę w zespołach oraz współpracę zespołów. 

W poprzednim rozdziale przedstawiłem główne sposoby radzenia sobie z konfliktami w repozytorium, w którym ktoś pracuje nad tym samym problemem. W praktyce taka sytuacja zdarza się w programowaniu indywidualnym, ale nie w zespołowym. Dlaczego? Bo jeżeli mamy kilku- (kilkunasto-,…, kilkuset-) osobowy zespół pracowników, to chcemy jak najbardziej odseparować ich stanowiska pracy tak, by sobie nawzajem nie przeszkadzali. W tym celu dzielimy duży problem na mniejsze i przydzielamy je różnym grupom i/lub osobom. Każdemu z takich ,,małych” problemów przypisuje się w repozytorium git-a osobną gałąź (ang. branch). Służy do tego komenda `git branch`:

```txt
> git branch rozdzial-o-pracy-w-zespole
```

Powyższe polecenie utworzy gałąź o nazwie rozdzial-o-pracy-w-zespole. Każdy członek dostecznie dużego zespołu pracującego w dostatecznie bogatej firmie zarządza zadaniami (i przypisanymi im gałęźmi kodu) za pomocą specjalistycznego oprogramowania, np. [Jira](https://pl.wikipedia.org/wiki/JIRA) – ale to osobne zagadnienie, które tu pomijam. 

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
```

