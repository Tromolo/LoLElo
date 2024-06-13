League of legends stats

Otvarame subory s match stats , id a prezyvkami hracov a output .html ktory potom zobrazujeme s udajmi o zapase a hracov
Tieto subory su validne prvy co bol poskytnuty pri projekte so zapasmi, a prezyvky ktore som si sam dorobil podla ID ktore hrali v zapasoch. 

Mame osetrene nevalidne inputy , vzdy musia byt 3 subory pri spusteni.
Mame osetrene takisto nevalidne udaje v tychto suboroch  - Nezacal zapas , Dostatok hracov v time presne 3 , KDA vo forme 2;1;1 pre kazdeho hraca K/D/A, ci ma zapas vysledok, ktory tim vyhral
kontrola ci nehraju proti sebe hraci s rovnakymi id, ci nie su hraci s rovnakym id v jednom time , ci kazdy hrac ma priradenu prezyvku , ci chyba nejaky hrac.

Nacitame data z .txt suborov do struktur ZaznamHry; a Hrac;

Funckie do zapisu html stranky - celkovy vypis statistik kazdeho hraca v zapasoch , Nickname, Kills, Assists, Deaths, Played Matches, Wins , Losses, Red team , Blue Team
Z poctu hier ktore hral dokopy. 
Hracov s najviac killami vyberame top 6 hracov.
Hraci ktori maju najviac vyhier. 
A vyratanie kills/death ratio kazdeho hraca ktory hral
Tieto udaje su v samostatnych tabulkach na nasom .html subore pre lepsiu prehladnost  + som pouzil bootstrap na formatovanie a vzhlad html stranky. Pomocoo bootstrap CSS. Su tu odkazy na subory css a JS. 

Projekt spustame pomocou Makefile.

v terminali sa presunieme do folderu kde mame nas projekt ulozeny.
make
ten vygeneruje nas main subor 
a pomocou 
make run 
spustime projekt a vytvorime nas pozadovany output v html stranke lol-stats.html ktory sa aj zobrazi.
 
