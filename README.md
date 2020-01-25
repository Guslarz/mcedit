# MceditBackend - Co jak gdzie z czym?
## Klasy bazowe
Te z [tego projektu](https://github.com/Guslarz/PO-project).

__Wszyscy muszą korzystać z tych samych klas bazowych!__ Bez tego ciężko byłoby zrealizować jakąkolwiek komunikację między backendem a toolem.
##### BaseTool
Wasz tool dziedziczy z tej klasy.

__Po co ten wirtualny destruktor?__ A no po to, żeby, jeśli w swoim toolu napiszecie destruktor, po czym stworzycie instancję swojego toola pod wskaźnikiem (lub referencją) typu BaseTool poza destruktorem BaseToola (pustym bo klasa abstrakcyjna (niezawierająca pól) XD) wykonał się też ten wasz. I tyle.

__Entries__ 

Po co to? Głównie na tych entries opiera się komunikacja między toolem a backendem. 

Chcesz powiedzieć backendowi że plik otwarty przez twojego toola nie jest zapisany (po edycji)? Ustawiasz mu entry (IS_SAVED, wartość NO). 

Chcesz dowiedzieć się jaki klawisz został ostatnio wciśnięty? Backend informuje Cię o tym ustawiając odpowiednią wartość pod entry KEY.

Czemu getEntry i SetEntry są nie dość że wirtualne to i abstrakcyjne? Bo tak. Jak kogoś poniesie inwencja twórcza to sobi je implementuje jak mu się podoba, jak nie to kopiuje ode mnie z TestTool.
