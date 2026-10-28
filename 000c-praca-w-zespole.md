# Git

## 5. Git a praca w zespole

Praca w zespole to domyślny tryb pracy w środowisku git. Mam ona pewną bardzo charakterystyczną specyfikę, którą nieco żartobliwie nazwałbym tendencją do występowania zjawiska znanego w informatyce jako [wyścig](https://en.wikipedia.org/wiki/Race_condition#In_software) (*nota bene*, nie mogę pojąć, że tak ważne pojęcie nie jest opisane w polskiej Wikipedii w kontekście oprogramowania komputerowego - październik 2026). Wyścig to zjawisko polegające na tym, że co najmniej dwa niezależne „byty”, np. programy, wątki programów, agenci AI, ludzie – usiłują jednocześnie modyfikować ten sam zasób. W przypadku git-a tym zasobem jest po prostu repozytorium. Chodzi o to, że jeżeli w zespole pracuje co najmniej kilka osób, to nie można odseparować zasobów (tu: po prostu plików), które twórcy oprogramowania mogą podczas wykonywania swoich zadań zmodyfikować. Te same osoby mogą w tym samym czasie chcieć zmienić zawartość tych samych plików, nie wiedząc o sobie nic nawzajem. Jak rozstrzygnąć, czyja zmiana jest ważniejsza? Jak w ogóle włączyć te pozornie chaotycznie wykonywane zmiany do głównego repozytorium tak, by nie wprowadzić do niego błędów?

Rozpoczną od scenariusza podstawowego, z którym początkujący użytkownik git-a styka się najczęściej: konflikt przy próbie wykonania operacji `git pull` (czyli ściągnięcia na swój komputer aktualnej wersji zdalnego repozytorium).



Ciąg dalszy nastąpi…. 

 

 