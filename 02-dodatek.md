#### 2.6 Co robić, jeżeli nie mamy dostatecznie nowego kompilatora

Może się zdarzyć i zaprawdę zdarza się, że gdzieś, np. na naszej pracowni, nie mamy dostępu do dostatecznie nowego kompilatora. Nie mamy więc możliwości korzystania z `std::format` czy `std::print`. Rozwiązań jest kilka. Najprościej byłoby zastąpić je wywołaniami starszych funkcji biblioteki standardowej C++. Sęk w tym, że ten tradycyjny interfejs jest nieporęczny i tylko dlatego wspominam `std::format` i `std::print`, że są to pierwsze naprawdę nowoczesne i przyjazne użytkownikowi elementy systemu obsługi wejścia i wyjścia w C++. Tradycyjny interfejs jest na tyle przekombinowany i nieprzydatny poza C++, że zwykle w ogóle o nim nie wspominam na zajęciach! Spróbujmy więc uciec do przodu i znaleźć atrakcyjną alternatywę dla `std::format`. Jest nią niewątpliwie jej pierwowzór, czyli biblioteka [fmtlib](https://github.com/fmtlib/fmt).  Jej opis znajduje się w poniższym linku:

- Biblioteka [fmtlib](02-fmtlib.md)

