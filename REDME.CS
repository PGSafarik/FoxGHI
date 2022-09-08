Fox Gnome Human Interface library (foxGHI)  08/09/2022 
============================================================

GENERAL INFO:
================
Tato velmi mala knihovna rozsiruje GUI Framework FOX o několik dodatečných tříd, s jejichž pomocí
lze používat top-level okna bez dekorace s tzv. Header Barem. 

Header Bar je malá lišta v horní části okna, která v sobe integruje vlastnosti titulkoveho pruhu, 
vcetne hlavnich ovladacích tlacitek, jako je ikonifikace, maximalizace, obnova, zavreni okna, a 
pripadne dalsi. Umoznuje take pohyb s oknem pomoci mysi. Stejne jako titulkovy pruh okna muze 
zobrazovat nazev aplikace a nejaky dodatecny text. Dále poskytuje prostor pro nastrojová tlacitka, 
ruzne ukazatele a podobne, ve sve podstate lze pouzit temer jakykoliv widget. Casto Header bar 
obsahuje take tlacitko s roletovym hlavnim menu aplikace. 

Cilem teto knihovny neni vytvorit kompletni Gnome 3-Like style pro Fox, pouze implementovat jen
nektere - podle meho nazoru - inovativni a zajimave technyky z tohoto prostredi. V tuto chvili
Je implementovano Simple Window  (FXGWindow), Header bar (FXWindowHeader) a Panel pro ovladani 
okna (FXWindowController). 

Jak bylo řečeno výše, cilem teto knihovny neni duplikovat Gnome 3, nicmen pri implementaci techto 
objektu se snazim vychazet z Gnome 3 Standardu "GHI - Gnome Human Interface", podle nehoz tato
knihovna ziskala take svuj název.

Upozornuji, ze knihovna je v soucasne dobe ve vyvji a muze se kdykoliv zmenit, i kdyz existuje 
urcita snaha, aby se tak nedelo, nicmene v tuto chvili to zarucit nelze

Preklad a instalace.
========================
Zavislosti:
  Foxtoolkit 1.7.76 - GUI Famework http://fox-toolkit.org/ftp/fox-1.7.76.tar.gz

Zavislosti pro kompilaci  
  cmake >= 3.10
  
Po stazeni projektu z Githubu (a pripadnem rozbaleni) prejdete do slozky s projektem a zadejte nasledujici 
sekvenci prikazu:
  mkdir build
  cd build && cmake .. 
  make
  sudo make install
  
Po uspesne kompilaci a sestaveni projektu bude vysledna knihovna a hlavickove soubory nainstalovana do 
adresare /opt/foxGHI/0.1/1/  

Autor a Licence
===================
Pavel Šafařík <drakarax@seznam.cz>

Tento soubor je součástí foxGHI.

foxGHI je svobodný software: můžete jej redistribuovat a/nebo upravovat za podmínek GNU General Public License, 
jak byla zveřejněna Free Software Foundation, buď verze 3 licence, nebo (dle vašeho uvážení) jakékoli 
pozdější verze.

foxGHI je distribuován v naději, že bude užitečný, ale BEZ JAKÉKOLI ZÁRUKY; dokonce bez předpokládané 
záruky PRODEJNOSTI nebo VHODNOSTI PRO KONKRÉTNÍ ÚČEL. Další podrobnosti najdete v GNU General Public License.

Spolu s foxGHI byste měli obdržet kopii GNU General Public License. Pokud ne, podívejte se na <https://www.gnu.org/licenses/>.

=== KONEC ===

