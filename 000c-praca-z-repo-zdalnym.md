# Git

## 4. Praca z repozytorium zdalnym (podstawy)

### 3.5. Komendy służące do synchronizacji repozytorium zdalnego z lokalnym (i odwrotnie)

#### 4.1. Aktualizacja serwera o zmiany wprowadzone lokalnie

Aby przekazać do serwera informację o naszych zmianach w repozytorium, posługujemy się poleceniem `git push`, czyli niejako „wypychamy” zmiany na serwer. 

![](/home/zkoza/Pulpit/Dydaktyka/aaa_pwdp/github/pwdp/img/00/git-push.png)

#### 4.2. Aktualizacja repozytorium lokalnego o zmiany dokonane na serwerze

Zwykle pracujemy w grupach (lub na różnych komputerach). W takim przypadku stan repozytorium przechowywanego na serwerze może ulec modyfikacji w każdej chwili, przy czym zmiany mogą dotyczyć także plików, nad którymi sami pracujemy. Do uaktualnienia repozytorium o zmiany, jakie zaszły na serwerze, służy komenda `git pull`. Jeżeli nad projektem pracujemy sami, zawsze na tym samym komputerze, repozytorium przechowywane na serwerze nie może nas „wyprzedzić”, `git pull` jest zasadniczo zbędne:

![](/home/zkoza/Pulpit/Dydaktyka/aaa_pwdp/github/pwdp/img/00/git-pull-proste.png)

Jest to jednak rzadki przypadek. Środowisko git zostało zaprojektowane do pracy w zespołach. O specyfice pracy zespołowej traktuje kolejny rozdział.  