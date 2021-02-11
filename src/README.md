#PacManClone
Autor: Šimon Matouš

## téma z Progtestu

Implementujte klasickou hru Pacman proti počítači (můžete naimplementovat i jiné varianty).

Hra musí splňovat následující funkcionality:

1. Dodržování základních pravidel, sbírání bonusů, míncí (teček), třešniček, teleporty, atp.
2. Je implementováno několik druhů AI duchů (fungující i zároveň - např. duchové se liší barvou, znakem).
3. Lze načítat mapy ze souboru (bludiště + pozice bonusů a duchů).
4. Konfigurovatelná obtížnost hry ze souboru (rychlost duchů, délka trvání jednotlivých módů hry, pravděpodobnost přidání nového bonusu do mapy, ...)
5. Škálovatelná obtížnost duchů (více strategií duchů dle obtížnost, dle různého chování)

Kde lze využít polymorfismus? (doporučené)

- Rozdělení hráčů: hráč, duch (různé druhy umělé inteligence)
- Mód hry: klasický (duchové chodí dle svých strategií), zběsilý (duchové pronásledují hráče), nezranitelný (duchové jsou pomalejší, dají se zabít)
- Herní políčko: zem, stěna, bod, bonus (změna módu), třešnička (více bodů), teleport
- Uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé varianty), ...

Další informace

- https://cs.wikipedia.org/wiki/Pac-Man
- http://programujte.com/clanek/2011010500-chovani-duchu-ve-hre-pac-man-cast-1/
- http://programujte.com/clanek/2011010500-chovani-duchu-ve-hre-pac-man-cast-2/

##----------------------------------------------------------------------------------------------------------------------------------------------

## Zadání hry PacmanClone

 Uživatel spustí hru PacmanClone a pomocí příkazů jí bude schopný ovládat .
 nejdříve vybere obtížnost:
- 'easy' je jednoduchá obtížnost, kdy duchové budou pomalejší než hráč a budou mít špatné strategie pohybu
- 'medium' je střední obtížnost, kdy duchové budou mít klasické strategie podle hry Pacman 
- 'hard' je těžká obtížnost, kdy duchové pujdou přímo za hráčem
- '[filename]' načte soubor s obtížností, ktere si vytvoří uživatel
- 'classic' načte klasickou mapu z pacmana 
- '[filename]' načte mapu ze souboru
- 'w','s','a','d' se pacman pohybuje nahoru,dolu,doleva,doprava
- 'exit' vypne program v menu
- [ESC] vypne program ve hře
Pravidla hry budou stejná jako u klasického pacmana.
Hrací plocha bude moct vypadat například následovně.
---------------------------
Press [ESC] to exit:

	  PACMAN

 score : 60
 lives : C C C
 time  : 950

##########T#####T##########
##########.#.#.#.##......o#
##########.#.#.#.##.#######
T.B    C..................T
#######.##.#.#.#.#=########		
#o......##.#.#.#.#WQHZ#####
##########T#####T##########
collectibles left: 51
---------------------------

Znaky reprezentuji:
prazdne misto = ' '
bonus = 'B'
teleport = 'T'
zeď = '#'
velka tecka = 'o'
tečka = '.'
Pacman = 'C'
dveře = '='

Inky (modrý duch) = 'W' / 'w'
Pinky(růžový duch) = 'P' / 'p'
Blinky(červený duch) = 'R' / 'r'
Clyde(žlutý/oranžový duch) = 'Q' / 'q'

(malé písmeno u ducha reprezentuje stav po sebraní velké tečky, kdy je zranitelný)

##----------------------------------------------------------------------------------------------------------------------------------------------

Třída CApplication se stará o spuštění hry, vybrání obtížnosti a případně možnost hrát znova.Dále volá třídu CSession, která se stará o načtení mapy a běh aktuální hry. Dále třída CPacman obsahuje pohyby pacmana. CMap obsahuje informace o velikosti a rozpoložení aktuální mapy a také uchovává číslo 'm_Collectibles', což je počet sebratelných předmětů, které musí být všechny pacmanem sebrány, aby uživatel hru vyhrál.

### Kde mám polymorfismus?

Polymorfismus využívám u třídy CGhostConfig, která má jednu abstraktní metodu Strategy.Dvanáct implementací CRedGhostHard, CBlueGhostHard, CPinkGhosHard, COrangeGhostHard, CRedGhostMedium, CBlueGhostMedium, CPinkGhostMedium, COrangeGhostMedium,CRedGhostEasy, CBlueGhostEasy, CPinkGhostEasy a COrangeGhostEasy přetěžují tuhle metodu. Každý zduchů má svojí vlastní strategii v honění pacmana.

Polymorfní volání je ve třídě CSession. Dostane od uživatele číslo, které reprezentuje vybranou obtížnost a spáruje se se správnou úrovní a strategií a použije se správná CGhost... classa a správná metoda Strategy.