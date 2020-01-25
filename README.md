# MceditBackend - Co jak gdzie z czym?
## Klasy bazowe
Te z [tego projektu](https://github.com/Guslarz/PO-project).
__Wszyscy muszą korzystać z tych samych klas bazowych!__ Bez tego ciężko byłoby zrealizować jakąkolwiek komunikację między backendem a toolem.
##### BaseTool
Wasz tool dziedziczy z tej klasy.
__Po co ten wirtualny destruktor?__ A no po to, żeby, jeśli w swoim toolu napiszecie destruktor, po czym stworzycie instancję swojego toola pod wskaźnikiem (lub referencją) typu BaseTool
