Fox Gnome Human Interface library (foxGHI)  22/11/2022 
============================================================

Obsah:
  1. Základní informace
  2. Překlad a instalace
  3. Známé chyby a bugy
  4. Stav projektu a plány do budoucna
  5. Autor a licence
  6. Internet

Screenshot1: https://github.com/PGSafarik/FXGHI/blob/master/doc/images/screenshot.png
Screenshot2: https://github.com/PGSafarik/FXGHI/blob/master/doc/images/ControlPanel

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

FoxGHI nabízí několik standardních voleb ve FOX Registrech, jejichž prostřednictvím lze ovlivnit
chovaní a vzhled většiny widgetu v teto knihovně. Jsou sdruženy do skupiny "FoxGHI" a název volby 
se skládá z identifikátoru objektu a nazvu vlastnosti, oddělené tečkou. Nastaveni je vidět i na 
ilustračním screenshotu k projektu. Možnosti jsou následující:
 * Window.EnableBorder   - Povolí/zakáže obkreslování okrajů okna tenkou černou linkou
 * Window.SelfControl    - Povolí/zakáže vlastni obsluhu správy stavu okna
 * Window.WMControl      - Povolí/zakáže rámování Window managerem (včetně obsluhy stavu okna)
 * Header.EnableColorize - Povolí/zakáže dobarvováni Header baru a jeho potomků 
 * Header.TitleFont      - Použije nastaveny font k zobrazeni titulku, je-li povolen
 * Header.SubTitleFont   - Zadaný font bude využit k zobrazení doplňujícího textu hlavního titulku, 
                           je-li povolen a nastaven.
 * Controller.Hidden     - Zobrazí/skryje ovládací tlačítka okna na HeaderBaru 

K usnadnění konfigurace knihovny, FoxGHI nabízí třídu ControlPanel, která implementuje GUI wraper 
FoxGHI konfigurace. ControlPanel je navržen tak, aby jej bylo snadné integrovat do libovolného projektu 
využívajícího FoxGHI, nebo, bude-li to vývojář považovat za vhodné, ji lze využít v samostatné 
konfigurační utilitě. Ukázkou jak lze s touto třídou pracovat je program FoxGHICP v adresáři utility 
projektu. Tato malá utilitka je tak poskytována též jako nezávislý nástroj pro konfiguraci ve stylu 
FOX Control Panel. 
 
Cílem teto knihovny není vytvořit kompletní „Gnome 3-Like style“ pro Fox, pouze implementovat jen
některé - podle mého názoru - inovativní a zajímavé techniky z tohoto prostředí, které chci sám 
používat ve svých vlastních projektech. V tuto chvíli je implementováno Primarni  a sekundarni okno 
(FXPrimaryWindow, FXSecondaryWindow), Header bar (FXWindowHeader), Panel pro ovládání okna 
(FXWindowController) a wraper pro ovládání nastavení FoxGHI (FXGHI_ControllPanel). 

Jak bylo řečeno výše, cílem teto knihovny není duplikovat Gnome 3, nicméně při implementaci těchto 
objektů se snažím vycházet z Gnome 3 Standardu "GHI - Gnome Human Interface", podle něhož tato
knihovna získala také svůj název.
 
Vezměte prosím na vědomí, že knihovna je v současné době ve vývoji a může se kdykoli změnit.


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
Současná verze: 0.3.1 ALPHA

FoxGHI v tuto chvíli implementuje základní funkcionalitu o kterou mi šlo - tzn. autonomní top-level 
okno s integrovaným headerbarem ve stylu Gnome 3. Nicméně, je ještě co vylepšovat. Z toho důvodu 
mějte prosím  na paměti, že projekt se stále nachází ve vývoji a muže jednak obsahovat bugy a může 
se v průběhu času změnit. 

09/10/2022 Dokončen základní koncept konfigurace FoxGHI
FoxGHI nyní poskytuje možnost standardně nastavovat chování jednotlivých widgetů v rámci teto knihovny. 
Samozřejmě, že jak se bude knihovna vyvíjet, přibudou další volby. V plánu je třída formuláře, jehož 
prostřednictvím bude možné měnit chování FoxGHI přímo v aplikaci. Tentýž formulář bude využit na 
vytvoření samostatné utilitky pro nastaveni FoxGHI aka FOX Control Panel. 

18/10/2022 Donkoncovani kontrolniho panelu
Zbyva vyresit vychozi hodnoty a jakym zpusobem bude trida CP dostupna v knihovne

29/10/2022 Dokoncena implementace tridy FXGHI_ControlPanel 
Třída poskytující GUI pro nastaveni vlastností FoxGHI je dokončena a integrována do knihovny. Nyní
už budou pouze přibývat případné konfigurační volby s tím, jak bude postupovat vývoj projektu. S touto třídou
byla také dokončena konfigurační utilita FoxGHICP. Odebírám tedy tento bod ze seznamu plánovaných cílů vývoje.

30/10/2022 Zakladní koncept dokovacich boxu 
Přidána třída horizontálního panelu, koncipovaná pro tvorbu malych komplexnich widgetu (Boxu) do 
Header Baru. Jeji použití je zamýšleno jako pro sdružení několika podobných prvku s podobným zaměřením 
(např. toolboxy) nebo samostatné widgety, kde je výhodné použití nějakého dokovacího podkladu (třeba 
menu).

22/11/2022
Sladeni nazvu trid a odpovidajicich souboru s GHI a Foxtoolkitem (v ramci moznosti)

V nejbližší budoucnosti bude 
  0) verzování knihovny 
  1) Dokovací boxy pro FXWindowHeader.
  2) Vytvořena dokumentace ke knihovně 
  3) Příklady & testy
  4) Postrani subpanel tzv. "side bar" 

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
  KDE iconove tema Oxygen:            https://github.com/KDE/oxygen-icons 
  Blog autora (CZ):                   http://bfuplusplus.blogspot.cz/

=== KONEC ===

