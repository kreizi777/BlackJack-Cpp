♠️ BlackJack C++
Prosta, konsolowa implementacja klasycznej gry karcianej Blackjack (Oczko) napisana w języku C++. Projekt wykorzystuje programowanie obiektowe (OOP), system zapisu stanu gry do plików oraz zaawansowane generowanie liczb losowych.

Autor: Kacper Wesołowski

📋 Spis treści
O projekcie

Funkcjonalności

Technologie

Instalacja i Uruchomienie

Zasady Gry

Struktura Plików

📖 O projekcie
Celem projektu jest symulacja rozgrywki w Blackjacka z krupierem (komputerem). Gra odbywa się w terminalu i oferuje pełną logikę gry, w tym system zakładów pieniężnych oraz zapisywanie postępów gracza.

Projekt został stworzony z myślą o ćwiczeniu:

Programowania obiektowego (Klasy Karta, Talia, BlackJack).

Obsługi strumieni wejścia/wyjścia (zapis do plików .txt).

Użycia kontenerów STL (vector).

Generowania losowości (std::random, mt19937).

✨ Funkcjonalności
System Profilu i Salda: Gra zapamiętuje nazwę użytkownika oraz stan konta pomiędzy uruchomieniami.

Logika Krupiera: Komputer dobiera karty zgodnie z zasadami kasynowymi (dobiera do 17 punktów).

Inteligentne Asy: Wartość Asa (1 lub 11) zmienia się dynamicznie, aby gracz nie przekroczył 21 punktów.

System Zakładów: Możliwość obstawiania wirtualnych pieniędzy. W przypadku wygranej (Blackjack) stawka mnożona jest x2.5.

Historia Gier: Każda rozgrywka jest logowana w pliku statystyki.txt z datą, wynikiem i stanem punktowym.

Walidacja Danych: Zabezpieczenie przed wprowadzaniem błędnych danych (np. liter zamiast liczb).

🛠 Technologie
Język: C++ (Standard C++11 lub nowszy)

Biblioteki: iostream, vector, fstream, random, ctime, algorithm

🚀 Instalacja i Uruchomienie
Aby uruchomić grę, potrzebujesz kompilatora C++ (np. g++, clang lub MSVC).

Sklonuj repozytorium:

Bash

git clone https://github.com/twoj-nick/blackjack-cpp.git
cd blackjack-cpp
Skompiluj kod:

Bash

g++ main.cpp -o blackjack
Uruchom grę:

Windows:

DOS

blackjack.exe
Linux/macOS:

Bash

./blackjack
🎲 Zasady Gry w tej wersji
Celem jest uzyskanie sumy punktów bliższej 21 niż krupier, ale nie przekraczając tej liczby.

Punktacja kart:

Karty 2-10: wartość nominalna.

Figury (Walet, Dama, Król): 10 punktów.

As: 1 lub 11 punktów (korzystniej dla gracza).

Przebieg:

Gracz otrzymuje 2 odkryte karty.

Krupier otrzymuje 1 odkrytą i 1 zakrytą kartę.

Gracz decyduje: [H]it (dobierz) lub [S]tand (pas).

Jeśli gracz przekroczy 21, przegrywa stawkę.

Jeśli gracz spasuje, krupier odkrywa karty i dobiera, aż uzyska minimum 17 punktów.

Wypłaty:

Wygrana: 2x stawka.

Blackjack (21 w dwóch pierwszych kartach): 2.5x stawka.

Remis: zwrot stawki.

📂 Struktura Plików
Gra automatycznie generuje pliki tekstowe służące do zapisu danych (persistence):

main.cpp - Główny kod źródłowy gry.

profil.txt - Przechowuje nazwę (login) ostatniego gracza.

saldo.txt - Przechowuje aktualny stan konta gracza.

statystyki.txt - Logi z historią rozegranych partii (data, wynik, punkty).
