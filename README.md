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

##### assignWindow
Tool nie korzysta z `stdscr`, tylko z okna które przypisuje mu backend. Jak chcecie sobie je rozbić na kilka okien polecam funkcję `derwin`.

Czemu musi być to okno od backendu? Ano bo:
- to backend obsługuje wstępnie \<RESIZE\>, a więc zmianę rozmiaru terminala, co może wiązać się z usunięciem obecnego okna i utworzeniem nowego. Toola tylko o tym informuje, żebyście mogli znowu wyświetlić to co ma być wyświetlone.
- backend może potrzebować dostępu do waszego okna, np. jeśli musi wyświetlić coś nad nim (alert, menu itp.), a po schowaniu tego elementu prawidłowo wyświetlić to, co zasłaniał.

## BaseBackend
No backendy z tego dziedziczą.

##### Wskaźnik na BaseTool i konstruktor (w klasie abstrakcyjnej???)
Tak tylko chciałem narzucić, żeby każdy backend ogarnął, że musi mieć jakiś dostęp do toola (np. przez wskaźnik), który z niego korzysta, żeby mógł mu przypisywać okno (wyżej), albo korzystać z jego `entries` (też wyżej).

##### Witrualny desturktor
Na tej samej zasadzie w toolu.

## Własna implementacja

## Disclaimer
Proszę olać wszelkie błędy interpunkcyjne, ortograficzne etc.
