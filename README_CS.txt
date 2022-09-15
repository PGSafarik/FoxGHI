Fox Gnome Human Interface library (foxGHI)  15/09/2022 
============================================================

Obsah:
  1. Základní informace
  2. Překlad a instalace
  3. Známé chyby a bugy
  4. Stav projektu a plány do budoucna
  5. Autor a licence
  6. Internet
  
1. ZÁKLADNÍ INFORMACE:
=======================
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

Screenshot: https://github.com/PGSafarik/FXGHI/blob/master/doc/images/01.png

2. PŘEKLAD A INSTALACE
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

3. ZNÁME CHYBY A BUGY
======================
1. 10/09/2022 - Nefunkcni tlacitko "Maximize" - otevřene
  Na některých WM a DE (např. Gnome, Cinnamon) nemusí fungovat tlačítko maximalizace. Pravděpodobně 
  jde o chybnou komunikaci mezi aplikaci a WM, nebo chybu v nastavení WM.   

4. STAV PROJEKTU A PLÁNY DO BUDOUCNA
======================================
FoxGHI v tuto chvili implementuje základní funkcionalitu o kterou mi šlo - tzn. autonomní top-level 
okno s integrovaným headerbarem ve stylu Gnome 3. Nicméně, je ještě co vylepšovat. Z toho důvodu 
mějte prosím  na paměti, že projekt se stále nachází ve vývoji a muže jednak obsahovat bugy a může 
se v průběhu času změnit. 

V nejblyžší budoucnosti bude 
  1) Vytvořena dokumentace ke knihovně 
  2) Příklady & testy
  3) verzovazni knihovny  
  4) integrační boxy pro FXWindowHeader.

5. AUTOR A LICENCE
=====================
Copyright (C) 2019 - 2022 Pavel Šafařík <drakarax@seznam.cz> alias D.A.Tiger
všechna práva vyhrazena.

Tento soubor je součástí foxGHI.

foxGHI je svobodný software: můžete jej redistribuovat a/nebo upravovat za podmínek GNU Lesser General Public License, 
jak byla zveřejněna Free Software Foundation, buď verze 3 licence, nebo (dle vašeho uvážení) jakékoli 
pozdější verze.

foxGHI je distribuován v naději, že bude užitečný, ale BEZ JAKÉKOLI ZÁRUKY; dokonce bez předpokládané 
záruky PRODEJNOSTI nebo VHODNOSTI PRO KONKRÉTNÍ ÚČEL. Další podrobnosti najdete v GNU Lesser General Public License.

Spolu s foxGHI byste měli obdržet kopii GNU Lesser General Public License. Pokud ne, podívejte se na <https://www.gnu.org/licenses/>.

6. INTERNET: 
===============
  Webové stránky Foxtoolkitu:         http://fox-toolkit.org/
  Gnome Human Interace Guidelines:    https://developer.gnome.org/hig/
  Blog autora (CZ):                   http://bfuplusplus.blogspot.cz/

=== KONEC ===

