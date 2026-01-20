# Habit Tracker

Aplikacja desktopowa Windows do śledzenia codziennych, tygodniowych i miesięcznych nawyków z liczeniem streków i statystykami.

## Możliwości

- ✅ Tworzenie wielu profili użytkowników
- ✅ Dodawanie nawyków z konfigurowalnymi właściwościami:
  - **Typ:** Dobry / Zły
  - **Trudność:** Zwykły / Łatwy / Średni / Trudny
  - **Częstotliwość:** Dzienny / Tygodniowy / Miesięczny
- ✅ Automatyczne śledzenie streków
- ✅ Zapisywanie najlepszego streka
- ✅ Automatyczny zapis postępów
- ✅ Przegląd statystyk
- ✅ Reset streka przy pominięciu okresu

---
## Uruchamianie 

1. **Skonfiguruj ustawienia projektu:**
   - Kliknij prawym na projekt → Właściwości
   - Właściwości konfiguracji → Ogólne: 
     - Standard języka C++: `ISO C++17/20 Standard (/std:c++17)`
   - Właściwości konfiguracji → Konsolidator → System:
     - Podsystem: `Windows (/SUBSYSTEM:WINDOWS)`


## Pierwsze uruchomienie
Obecnie w folderze /saves załadowane są przykładowe pliki z danymi do testów
1. Uruchom `HabitTracker.exe`
2. Folder `saves` zostanie utworzony automatycznie
3. Kliknij **"Create new profile"** aby rozpocząć

### Tworzenie profilu

1. Kliknij **"Create new profile"**
2. Wpisz nazwę profilu (np. "Jan")
3. Kliknij **"SAVE"**
4. Utworzy się plik tekstowy z nazwą podanego profilu w którym zapisywane będą twoje nawyki

### Dodawanie nawyku

1. Kliknij **"Add new habit"**
2. Wpisz nazwę nawyku (np. "Ćwiczenia")
3. Wybierz opcje:
   - Typ: Good (Dobry) / Bad (Zły)
   - Trudność: Common / Easy / Medium / Hard
   - Częstotliwość: Daily / Weekly / Monthly
4. Kliknij **"Create habit"**

### Oznaczanie wykonania nawyku

1. W menu głównym kliknij checkbox (X) obok nawyku
2. Licznik streka zwiększy się automatycznie
3. Przycisk zostanie zablokowany do następnego okresu: 
   - **Daily** - do następnego dnia
   - **Weekly** - do następnego tygodnia
   - **Monthly** - do następnego miesiąca

### Przeglądanie statystyk

1. Kliknij przycisk **"Stats"**
2. Zobaczysz:
   - Łączną liczbę nawyków
   - Procent wykonania
   - Najlepsze streki

### Zmiana profilu

1. Kliknij **"Change Profile"**
2. Aktualny postęp zostanie zapisany automatycznie
3. Wybierz inny profil lub utwórz nowy

### Lokalizacja plików zapisu

```
HabitTracker. exe
└── saves/
    ├── Adam.txt
    ├── Oliwia.txt
    └── Tomek.txt
```

### Struktura pliku

Każda linia reprezentuje jeden nawyk w formacie rozdzielonym średnikami:

```
Nazwa;Typ;Trudność;Częstotliwość;OstatnioWykonano;AktualnyStreak;NajlepszyStreak
```

### Opis pól

| Pole | Wartości | Opis |
|------|----------|------|
| Nazwa | tekst | Nazwa nawyku |
| Typ | `G` / `B` | Good (Dobry) / Bad (Zły) |
| Trudność | `C` / `E` / `M` / `H` | Common / Easy / Medium / Hard |
| Częstotliwość | `D` / `W` / `M` | Daily / Weekly / Monthly |
| OstatnioWykonano | timestamp | Unix timestamp ostatniego wykonania |
| AktualnyStreak | liczba | Aktualny streak |
| NajlepszyStreak | liczba | Najlepszy streak w historii |

---

## 📄 Przykładowe pliki

### Przykładowy plik wejściowy: `saves/Jan.txt`

```
Ćwiczenia;G;H;D;1737504000;14;21
Czytanie;G;E;D;1737504000;8;15
Medytacja;G;M;D;1737417600;5;10
Bez papierosów;B;H;D;1737504000;30;30
Nauka hiszpańskiego;G;M;W;1737244800;4;6
Przegląd miesięczny;G;C;M;1735689600;3;5
```

### Wyjaśnienie przykładu

| Nawyk | Typ | Trudność | Częstotliwość | Ostatnio | Aktualny | Najlepszy |
|-------|-----|----------|---------------|----------|----------|-----------|
| Ćwiczenia | Dobry | Trudny | Dzienny | 22. 01.2025 | 14 dni | 21 dni |
| Czytanie | Dobry | Łatwy | Dzienny | 22.01.2025 | 8 dni | 15 dni |
| Medytacja | Dobry | Średni | Dzienny | 21.01.2025 | 5 dni | 10 dni |
| Bez papierosów | Zły | Trudny | Dzienny | 22.01.2025 | 30 dni | 30 dni |
| Nauka hiszpańskiego | Dobry | Średni | Tygodniowy | 19.01.2025 | 4 tyg.  | 6 tyg. |
| Przegląd miesięczny | Dobry | Zwykły | Miesięczny | 01.01.2025 | 3 mies. | 5 mies. |

### Przykładowy plik wyjściowy (po użyciu aplikacji)

Po wykonaniu nawyku "Ćwiczenia" w dniu 23.01.2025:

```
Ćwiczenia;G;H;D;1737590400;15;21
Czytanie;G;E;D;1737504000;8;15
Medytacja;G;M;D;1737417600;5;10
Bez papierosów;B;H;D;1737504000;30;30
Nauka hiszpańskiego;G;M;W;1737244800;4;6
Przegląd miesięczny;G;C;M;1735689600;3;5
```

### Przykładowe statystyki (wyjście)

```
═══════ STATYSTYKI NAWYKÓW ═══════

Łączna liczba nawyków: 6
Wykonane dziś: 4/6 (66%)
Najlepszy aktywny streak: 30 (Bez papierosów)

══════ TOP STREKI ══════

1. Bez papierosów - 30 dni - REKORD!
2. Ćwiczenia - 15 dni
3. Czytanie - 8 dni
```

---

## ⚠️ Rozwiązywanie problemów

### "Could not open save file"

- Sprawdź czy folder `saves` istnieje
- Sprawdź uprawnienia do zapisu
- Upewnij się, że nazwa profilu nie zawiera znaków specjalnych

---
## Autor

Adam Słodownik

- GitHub: Adam01077