# HTTP nástěnka
 Aplikace umožňuje klientům spravovat nástěnky na serveru pomocí HTTP API. API jim umožňuje prohlížet, přidávat, upravovat a mazat příspěvky na nástěnkách jako i nástěnky samotné. Nástěnka obsahuje seřazený seznam textových příspěvků.
<br>
<br>
Pro správně spuštění aplikace je zapotřebí zkompilovat všechny soubory. Poté spustit server, na kterém se mohou poté klienti dotazovat.

## Kompilace zdrojových souborů
Aby aplikace mohla pracovat, musí se ze všeho nejdříve zkompilovat všechny zdrojové soubory. Aplikace obsahuje Makefile.
Spusťe ve složce této aplikace následující příkaz a aplikace vytvoří **isaserver** a **isaclient** target.

##### Vygeneruje _isaserver_ a _isaclient_ : <r>``make`` nebo `make all`
##### Vygeneruje pouze _isaserver_ : ``make isaserver``
##### Vygeneruje pouze _isaclient_ : ``make isaclient``
##### Smazání všech targetů a .o souborů : ``make clean``

## Server

Následující příkaz vypíše help pro server: <br>
``./isaserver -h``

Tento příkaz spustí samotný server na definovaném portu (PORT): <br>
``./isaserver -p <PORT>``

## Klient




