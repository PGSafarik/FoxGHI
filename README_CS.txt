Fox Gnome Human Interface library (foxGHI)  22/02/2025
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
 * Window.EnableBorder    - Povolí/zakáže obkreslování okrajů okna tenkou černou linkou
 * Window.SelfControl     - Povolí/zakáže vlastni obsluhu správy stavu okna
 * Window.WMControl       - Povolí/zakáže rámování Window managerem (včetně obsluhy stavu okna)
 * Header.EnableColorize  - Povolí/zakáže dobarvováni GUI potomku Header baru
 * Header.BaseColorOffset - Nastavuje miru ztmaveni basove barvy header baru (v %). Rozmezi
                            hodnot je od 0 - 100, pricemz 0 ztmaveni zakaze. Vychozi nastaveni je 20.
 * Header.TitleFont       - Použije nastaveny font k zobrazeni titulku, je-li povolen
 * Header.SubTitleFont    - Zadaný font bude využit k zobrazení doplňujícího textu hlavního titulku,
                           je-li povolen a nastaven.
 * Controller.Hidden      - Zobrazí/skryje ovládací tlačítka okna na HeaderBaru

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
(FXWindowController) a wraper pro ovládání nastavení FoxGHI (ControllPanel). 

Jak bylo řečeno výše, cílem teto knihovny není duplikovat Gnome 3, nicméně při implementaci těchto 
objektů se snažím vycházet z Gnome 3 Standardu "GHI - Gnome Human Interface", podle něhož tato
knihovna získala také svůj název.
 
Vezměte prosím na vědomí, že knihovna je v současné době ve vývoji a může se kdykoli změnit.


2. PŘEKLAD A INSTALACE
========================
Závislosti:
  Foxtoolkit 1.7.84 - GUI Framework http://fox-toolkit.org/ftp/fox-1.7.84.tar.gz

Dodatečné závislosti pro kompilaci  
  cmake >= 3.10
  
Po stažení projektu z Githubu (a případném rozbaleni) přejděte do složky s projektem a zadejte následující 
sekvenci příkazu:
  mkdir build
  cd build && cmake .. 
  make
  sudo make install
  
Po uspěšné kompilaci a sestaveni projektu bude výsledná knihovna a hlavičkové soubory nainstalováný do 
adresáře /opt/foxghi/0.4/  

3. ZNÁME CHYBY A BUGY
======================    
1. 19/01/2023 - Nektere WM  zobrazuji zakazany dekoracni ram, pokud je nastavena ikona aplikace.
  Od Foxlib verze 1.7.81 je-li nastavena ikona okna, nektere WM a DE (konkretne to mam potvrzene u  
  KDE a Cinnamonu) NERESPEKTUJI pozadavek na skryti dekoracniho ramu. Bohuzel s tim v tento moment nemohu 
  delat nic jineho, nez pridat do uzivatelskych nastaveni volbu vypinajici ikonu okna, dale preddefinovane 
  profily vychozich nastaveni. Pro vyvojare pribude moznost prednastaveni bezne masky top-level okna, ktera 
  se pouzije, kdyz uzivatel aktivuje volbu spravovani okna window managerem. 

4. STAV PROJEKTU A PLÁNY DO BUDOUCNA
======================================
Současná verze: 25.02 0.5.0.0 ALPHA

FoxGHI v tuto chvíli implementuje základní funkcionalitu o kterou mi šlo - tzn. autonomní top-level 
okno s integrovaným headerbarem ve stylu Gnome 3. Nicméně, je ještě co vylepšovat. Z toho důvodu 
mějte prosím  na paměti, že projekt se stále nachází ve vývoji a muže jednak obsahovat bugy a může 
se v průběhu času změnit. 

21/05/2023 Zmena vychoziho instalacniho adresare
Od teto verze se bude FoxGHI vychozi adresar install/path/foxghi/MAJOR.MINOR/, tedy nebude se pridavat subadresar s vyvojovou verzi, 
ktery zpusoboval potize s nastavenim knihovny v ld.cache pri aktualizaci vyvojovych nebo opravnych verzi   

20/05/2023 Implementace Side Bar widgetu je prozatim odložena na neurčito.

18/05/2023 Opraven nepřijemný bug nefunkčniho tlačitka maximalizace okna, ktery se projevoval v u nekterych WM. 
Ukazalo se, ze tuto funkcionalitu ovlivnuji decoracni priznaky tridy FXTopWindow.

02/03/2023 Třída FXPrimaryWindow umožňuje předdefinovat příznaky dekoraci pro FXTopWindow, ktere se použijí při
aktivaci klasicke zpravy okna.

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

20/11/2024
Přidání verze projektu do knihovny a rozšíření možnosti nastavení dobarveni (ztmavení/zesvetleni) Header baru v registrech
Foxlib.

22/02/2025
Reorganizace projektu. Jednotlive hlavicky (a odpovidajici implementacni soubory ) jsou roztrideny do adresaru nekolika
kategorii : Core, Widgets a Windows, pro snazsi orientaci v projektu a dalsi vyvoj. Vsechny hlavicky z dane katogorie
jsou nasledne seskupeny v odpovidajicim hlavickovem souboru (napr. Core.h) a ty jsou vsechny includovany do centralniho
hlavickoveho souboru knihovny (fxghi.h). Pokud byl v klientskem projektu vyuzivan, nemela by tato zmena samotna znamenat
zadne nepredvidatelne potize.

Verze projektu se nyni zadava pri vyvoji primo do CMakeList.txt. Veskere soubory nejak navazujici na verzovaci udaje
(include/Core/version.h a src/foxghiM.M.B.conf) jsou od ted generovany az pri prvni kompilaci projektu.

Zvyseni cisla vyvojove verze (0.5.0.0)

23/02/2025
Dokoncena funkce kolorizace  - dobarvovani, tj. moznost ztmaveni/zesvetleni header baru oproti systemove zakladni barve
panelu a nasledne nastveni takto upravene hodnoty do vsech potomku header baru. Odpovidajici volby byly implementovany
do ControllPanel, takze si tuto vlastnost muze uzivatel nasledne pro kazdou aplikaci vyuzivajici FXGHI nastavit podle
sveho uvazeni.

V nejbližší budoucnosti bude
  0) Preddefinovane zakladni profily nastaveni FoxGHI
  1) Vytvořena dokumentace ke knihovně
  2) Příklady & testy
  3) Implementace kontextu a jejich prepinani v header baru

5. AUTOR A LICENCE
=====================
Copyright (C) 2019 - 2023 Pavel Šafařík <drakarax@seznam.cz> alias D.A.Tiger
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

