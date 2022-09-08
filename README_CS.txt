Fox Gnome Human Interface library (foxGHI)  08/09/2022 
============================================================

ZÁKLADNÍ INFORMACE:
===================
Tato velmi malá knihovna rozšiřuje GUI Framework FOX o několik dodatečných tříd, s jejichž pomocí
lze používat top-level okna bez dekorace s tzv. Header barem. 

Header bar je malá lišta v horní části okna, která v sobě integruje vlastnosti titulkového pruhu, 
včetně hlavních ovladacích tlačítek, jako je ikonifikace, maximalizace, obnova, zavření okna, a 
případně další. Umožňuje též pohyb s oknem pomoci myši. Stejně jako titulkový pruh okna může 
zobrazovat název aplikace a libovolný dodatečný text. Dále poskytuje prostor pro nástrojová tlačítka, 
různé ukazatele a podobně, ve své podstatě lze použít téměř jakýkoliv widget. o Header bar často
obsahuje také tlačítko s roletovým hlavním menu aplikace. 

Cílem teto knihovny není vytvořit kompletní „Gnome 3-Like style“ pro Fox, pouze implementovat jen
některé - podle mého názoru - inovativní a zajímavé techniky z tohoto prostředí. V tuto chvíli
Je implementováno Simple Window  (FXGWindow), Header bar (FXWindowHeader) a Panel pro ovládání 
okna (FXWindowController). 

Jak bylo řečeno výše, cílem teto knihovny není duplikovat Gnome 3, nicméně při implementaci těchto 
objektů se snažím vycházet z Gnome 3 Standardu "GHI - Gnome Human Interface", podle něhož tato
knihovna získala také svůj název.

Upozorňuji, ze knihovna je v současné době ve vývoji a může se kdykoliv změnit,
i když existuje 
určitá snaha, aby se tak nedělo, nicméně v tuto chvíli to zaručit nelze

Překlad a instalace.
========================
Závislosti:
  Foxtoolkit 1.7.76 - GUI Framework http://fox-toolkit.org/ftp/fox-1.7.76.tar.gz

Dodatečné závislosti pro kompilaci  
  cmake >= 3.10
  
Po stažení projektu z Githubu (a případném rozbaleni) přejděte do složky s projektem a zadejte následující 
sekvenci příkazu:
  mkdir build
  cd build && cmake .. 
  make
  sudo make install
  
Po uspěšné kompilaci a sestaveni projektu bude výsledná knihovna a hlavičkové soubory nainstalováný do 
adresáře /opt/foxGHI/0.1/1/  

Autor a Licence
===================
Copyright (C) 2019 - 2022 Pavel Šafařík <drakarax@seznam.cz>
všechna práva vyhrazena.

Tento soubor je součástí foxGHI.

foxGHI je svobodný software: můžete jej redistribuovat a/nebo upravovat za podmínek GNU Lesser General Public License, 
jak byla zveřejněna Free Software Foundation, buď verze 3 licence, nebo (dle vašeho uvážení) jakékoli 
pozdější verze.

foxGHI je distribuován v naději, že bude užitečný, ale BEZ JAKÉKOLI ZÁRUKY; dokonce bez předpokládané 
záruky PRODEJNOSTI nebo VHODNOSTI PRO KONKRÉTNÍ ÚČEL. Další podrobnosti najdete v GNU Lesser General Public License.

Spolu s foxGHI byste měli obdržet kopii GNU Lesser General Public License. Pokud ne, podívejte se na <https://www.gnu.org/licenses/>.

=== KONEC ===

