## 11.1 Krótkie wprowadzenie do SFML

SFML (ang. *Simple and Fast Multimedia Library*) to wieloplatformowa, darmowa biblioteka oferująca dostęp do różnorodnych multimediów, wykorzystywana głównie przez twórców (niezbyt skomplikowanych) gier. Jest też stosunkowo prosta w obsłudze, dlatego dobrze nadaje się do nauki programowania aplikacji multimedialnych w C++, co obejmuje też [aplikacje sterowane zdarzeniami](https://en.wikipedia.org/wiki/Event-driven_programming), co z kolei obejmuje aplikacje z graficznym interfejsem użytkownika (GUI, *graphical user interface*). Jest też wykorzystywana na różnych zajęciach na naszym Wydziale, co tym bardziej uzasadnia możliwie wczesne omawianie tej biblioteki i związanych z nią technologii.

SFML składa się z kilku modułów:

- **System** – zawiera m.in. typy (klasy) służące do obsługi napisów, wektorów, wielowątkowości i zegarów.

- **Window** – zawiera funkcje umożliwiające tworzenie i obsługę okien, w tym obsługę grafiki w systemie OpenGL. Zawiera też funkcje do obsługi różnych urządzeń wejścia, np. joysticków. 
- **Graphics** – moduł obsługujący operacje graficzne (2D), włącznie z ich akceleracją sprzętową.
- **Audio – funkcje do obsługi odtwarzania i nagrywania dźwięku**
- **Network** – obsługa protokołów sieciowych (TCP,  UDP, HTTP, FTP.

Uwaga. SFML posiada wiele wersji. Aktualną wersją w momencie pisania tych słów jest 3.0, jednak w Sieci można znaleźć wiele podręczników, blogów i bibliotek napisanych z myślą o wersjach wcześniejszych, np. 2.5 i 2.6. Programy napisane w SFML 2.5 z reguły nie współpracują z biblioteką w wersji 3.0, w której zastosowano wiele nowoczesnych i nieoczywistych dla nowicjuszy cech języka C++.  Należy mieć to na uwadze podczas poszukiwania informacji o SFML - liczne programy przykładowe dostępne w sieci nie będą działać bez umiejętnego dostosowania kodu.   

#### 11.1 Instalacja SFML

- Użytkownicy WIndows i MacOS powinni skorzystać ze strony: https://www.sfml-dev.org/download/sfml/3.0.0/

- Użytkownicy systemu Linux mogą również z niej skorzystać, ale chyba najlepiej jest zainstalować tę bibliotekę za pomocą swojego ulubionego [menedżera pakietów](https://en.wikipedia.org/wiki/List_of_software_package_management_systems) (`apt`, `pamac` itp.)

#### 11.2 Dalsza lektura 

- Podstawowym źródłem informacji o bibliotece SFM jest strona https://www.sfml-dev.org/. 
- Wiele programów przykładowych dystrybuowanych jest wraz z samą biblioteką na stronie w serwisie GitHub, https://github.com/SFML/SFML. 
- Dodatkowe informacje można znaleźć w społecznościowym serwisie typu wiki, https://github.com/SFML/SFML/wiki/. 

