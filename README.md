# Maticová kalkulačka

## Specifikace

Úkolem je vytvořit kalkulačku pro práci s maticemi.

Maticová kalkulačka obsahuje **binární** operace:
- Sčítání matice (X = ADD A B)
- Odečítání matice (X = SUB A B)
- Násobení skalárem / maticí (X = MUL a A / X = MUL A B)
- Sloučení matic zprava / zdola (X = JOINRIGHT A B / X = JOINDOWN A B)
- Oříznutí matic (X = TRIM A row col off_x off_y)
- Umocňování matic (X = EXP A a)

A také **unární** operace:
- Transpozice matice (X = TRANS A)
- Výpočet inverzní matice (pouze pro čtvercové) (X = INV A)
- Výpočet determinantu matice (pouze pro čtvercové) (X = DET A)
- Určení hodnosti matice (X = RANK A)
- Provedení Gaussovy eliminační metody (X = GEM A)

Pro efektivnější práce kalkulačka dokáže rozlišovat mezi dvěma typy matic:
- Řídká matice (s převahou nulových prvků (> 50% nul) ) - bude používat efektivnější datový typ - mapa
- Hustá matice (s převahou nenulových prvků (> 50% nenul) ) - 2D pole
- Jednotková matice (jedničky na hlavní diagonále)

Kromě toho bude uživatel moci pracovat s obsahem matic:
- Načtení matice (+ načtení matic ze souboru) (SCAN X / IMPORT filename)
- Vymazání matice (+ vymazání všech matic) (DEL X / DELALL)
- Uložení matic do souboru (+ uložení všech matic do souboru) (EXPORT filename X / EXPORTALL filename)
- Zobrazení matic v konzoli (+ zobrazení všech matic v konzoli) (PRINT X / PRINTALL)

Práce se soubory:
- Pokud zadaný na výstup soubor neexistuje, bude vytvořen.
- Pokud zadaný na výstup soubor obsahuje data, budou smazány.
- Soubor se uloží do adresáře "export", který je ve stejném adresáři jako program.
- Pro import matici, musí být soubor správně formátován jako v ukázkách.
- Pokud je zadán neexistující nebo nesprávně formátovaný soubor, program zobrazí chybové hlášení.
- Pro import matici, soubor musí být v adresáři "export", který je ve stejném adresáři jako program.

Komunikace probíhá pomocí konzoly (CLI).
Funguje to tak, že uživatel zadá příkaz nebo několik příkazů na jednom řádku (např. A = GEM MUL Y ADD Z X)
Pak třída Parser ty příkazy zpracuje. V případě chyby program zpracování výrazu ukončí a uživateli zobrazí chybové hlášení se stručným popisem.
Uživatel může program ukončit příkazem EXIT nebo QUIT.
Uživatel může také použít příkaz HELP, který vypíše všechny možné příkazy.

Konfigurační třída Commands obsahuje všechny možné příkazy.


## Polymorfismus

Hlavně polymorfismus se používá u abstraktní třídy Matrix, z níž se dědí třídy SpareMatrix, DenseMatrix a IdentityMatrix.
Třída Matrix používá virtuální metody:
- getVal - pro získání hodnoty matice
- rank - pro výpočet hodnosti matice
- determinant - pro výpočet determinantu matice
- clone - hluboká kopie matice
- print - výpis matice
- printToFile - vypis matice ve formátu pro uložení do souboru


Také polymorfismus je použit u abstraktní třídy Operation, od které se dědí BinaryOperation a všechny unární operace (např. Transpozice, Inverze atd.)
Všechny binární operace (Sčítání, Odečítání atd.) budou zděděny z třídy BinaryOperation.
Třída Operation používá virtuální metodu execute (provedení nějaké operace).


Kromě toho polymorfismus je použit u abstraktní třídy Export, která se používá pro exportní formáty (textový, binární atd.).
Prozatím bude export implementován pouze jako textový soubor - zděděná třída TextExport (v budoucnu je možné rozšířit).
Třída Export používá virtuální metody:
- exportData pro výstup dat v požadovaném formátu.
- importData pro načtení dat ze souboru


Nakonec, polymorfismus je použit u abstraktní třídy UserInterface, která se používá pro různá uživatelská rozhraní.
Prozatím uživatelské rozhraní bude implementováno pouze v konzoli - zděděná třída ConsoleUI.
Třída UserInterface používá virtuální metody:
- showText - zobrazení textu na obrazovce
- getInput - načtení vstupu
