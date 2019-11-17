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

Klient musí být spuštěn s více parametry. Jeden z nejdůležitějších argumentů programu je hostname, nebo port.
<br>
Syntax pro spuštění klienta:<br>

``./isaclient -H <HOST> -p <PORT> <COMMAND>``

Kde <br>
``<HOST>`` značí hostname, nebo IP adresu serveru, který čeká na požadavky od klientů.<br>
``<PORT>`` značí port, na kterém čeká server.<br>
``<COMMAND>`` Příkazy, podle kterých je generován request. 

#####COMMAND
Vypíše seznam všech nástěnek <br>
``
boards					GET /boards
``
<br>
Přidá nástěnku 'name' <br>
``
board add <name>			POST /boards/<name>
``
<br>
Smaže nástěnku 'name'<br>
``
board delete <name>			DELETE /boards/<name>
``
<br>
Vypíše všechny položky nástěnky 'name' <br>
``
board list <name>			GET /board/<name>
``
<br>
Přidá položku do nástěnky 'name' s obsahem 'content'<br>
``
item add <name> <content>		POST /board/<name>
``
<br>
Smaže položku z nástěnky 'name' podle 'id'.<br>
``
item delete <name> <id>			DELETE /board/<name>/<id>
``
<br>
Aktualizuje obsah položky v nástěnce 'name' podle 'id'.<br>
``
item update <name> <id> <content>	PUT /board/<name>/<id>
``
<br>






