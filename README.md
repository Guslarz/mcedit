# MceditBackend - Co jak gdzie z czym?
## Klasy bazowe
Te z [tego projektu](https://github.com/Guslarz/PO-project).

__Wszyscy muszą korzystać z tych samych klas bazowych!__ Bez tego ciężko byłoby zrealizować jakąkolwiek komunikację między backendem a toolem.
## BaseTool
Wasz tool dziedziczy z tej klasy.

##### Po co ten wirtualny destruktor?

A no po to, żeby, jeśli w swoim toolu napiszecie destruktor, po czym stworzycie instancję swojego toola pod wskaźnikiem (lub referencją) typu BaseTool poza destruktorem BaseToola (pustym bo klasa abstrakcyjna (niezawierająca pól) XD) wykonał się też ten wasz. I tyle.

##### Entries
Po co to? Głównie na tych entries opiera się komunikacja między toolem a backendem. 

Chcesz powiedzieć backendowi że plik otwarty przez twojego toola nie jest zapisany (po edycji)? Ustawiasz mu entry (IS_SAVED, wartość NO). 

Chcesz dowiedzieć się jaki klawisz został ostatnio wciśnięty? Backend informuje Cię o tym ustawiając odpowiednią wartość pod entry KEY.

Czemu `getEntry` i `setEntry` są nie dość, że wirtualne, to i abstrakcyjne? Bo tak. Jak kogoś poniesie inwencja twórcza to sobie je implementuje jak mu się podoba, jak nie to kopiuje ode mnie z TestTool.  Dodatkowo klasa `UndefinedEntry` to exception w przypadku, gdy ktoś odwołuje się do entry, którego wartość nie została wcześniej ustawiona (wywołuje `getEntry("jakiesEntry")`, kiedy nie było wcześniej `setEntry("jakesEntry", "jakasWartosc")`.

`getEntry` przyjmuje tylko jeden parametr - nazwę entry, np. `tool->getEntry("KEY")` pobierze wartość entry "KEY", ewentualnie wywali `UndefinedEntry`, jeśli nie jest zdefiniowane.

`setEntry` przyjmuje dwa parametry - nazwę entry i wartość, jaką ma mu ustawić np. `tool->setEntry("KEY", "<CTRL+C">)`.

W jednej i drugiej funkcji paramterem (parametrami) są stringi, to magiczne `const std::string&` oznacza, że zostają przekazane jako referencja - bez niej wartość ta byłaby kopiowana i dodatkowo jest const, a więc w ciele funkcji nie możemy zmienić wartości w tym stringu.

##### assignWindow
Tool nie korzysta z `stdscr`, tylko z okna które przypisuje mu backend. Jak chcecie sobie je rozbić na kilka okien polecam funkcję `derwin`.

Czemu musi być to okno od backendu? Ano bo:
- to backend obsługuje wstępnie `\<RESIZE\>`, a więc zmianę rozmiaru terminala, co może wiązać się z usunięciem obecnego okna i utworzeniem nowego. Toola tylko o tym informuje, żebyście mogli znowu wyświetlić to co ma być wyświetlone.
- backend może potrzebować dostępu do waszego okna, np. jeśli musi wyświetlić coś nad nim (alert, menu itp.), a po schowaniu tego elementu prawidłowo wyświetlić to, co zasłaniał.

## BaseBackend
No backendy z tego dziedziczą.

##### Wskaźnik na BaseTool i konstruktor (w klasie abstrakcyjnej???)
Tak tylko chciałem narzucić, żeby każdy backend ogarnął, że musi mieć jakiś dostęp do toola (np. przez wskaźnik), który z niego korzysta, żeby mógł mu przypisywać okno (wyżej), albo korzystać z jego `entries` (też wyżej).

##### Witrualny destruktor
Na tej samej zasadzie co w toolu.

##### Bind
Przypisanie przez toola wywołania pewnej funkcji do... czegoś (gdzieś dalej więcej o tym). To jak interpretowany będzie pierwszy argument (string) zależy od konkretnego backendu. Drugim argumentem jest obiekt `std::function\<void()\>` czyli praktycznie cokolwiek (zwykłą funkcja, lambda, metoda po użyciu `std::bind`), byleby zwracało void i nie brało argumentów. Ostatni argument to jakiś krótki opis danego binda.

##### Start
Backend żeby prawidłowo działał musi gdzieś w sobie zawierać pętlę (przynajmniej mi nie przychodzi do głowy inne sensowne rozwiązanie), w której w skrócie pobiera informację o tym co się stało (wciśnięty klawisz, kliknięcie myszki, zmiana rozmiaru) i jakoś na to reaguje. Trzeba go w takim razie poinformować, kiedy dodane zostały wszystkie bindy i może zacząć właściwe działanie. To właśnie robi `start`.

## Własna implementacja toola
Pliki `main.cpp`, `TestTool.h` i `TestTool.cpp` nie są częścią mojego backendu, ale pozwalają jakoś go w działaniu przetestować. `main.cpp` pokazuje przede wszystkim jak to wszysto połączyć (bindy, start). Klasa `TestTool` to taki przykładowy tool, parę metod ma, pokazuje jak działa samo korzystanie z okna, z entries i o co chodzi z tymi bindami z parametrem i bindem `\<EDITION\>`.

##### A o co?
Parametry są dość przydatne. Jeśli np. wasz tool chce pobrać nazwę pliku do otwarcia nie musicie pisać całego pobierania tej wartości. Robicie binda, który jako parametr pobierze od użytkownika tą wartość i zapisze pod wskazanym przez was `entry`. Następnie wywołuje się określony przez was handler, w którym możecie zakładać, że wartość ta została ustawiona.

A `\<EDITION\>`? Jak już wspominałem backend działa w pewnej pętli pobierając wciśnięty klawisz/kliknięcie myszki/zmianę rozmiaru. Jeśli nie powoduje to wyjścia z trybu edycji (np. w wyniku kliknięcia na element w menu) backend zapisuje odpowiednią wartość jako `entry` KEY i wywołuje handler `\<EDITION\>`. Czyli jest to w skrócie tak jakby fragment tej głównej pętli działania backendu, w którym tool może w końcu coś zrobić.

## Własna implementacja backendu
Wszystkiego tu nie opiszę, polecam po prostu popatrzeć w kod.

## Disclaimer
Proszę olać wszelkie błędy interpunkcyjne, ortograficzne etc.
