# BlackJack-Cpp
Prosty projekt gry Blackjack napisanej w języku C++, działającej w konsoli.

🎴 Blackjack C++ Console Game

Prosty projekt gry Blackjack napisanej w języku C++, działającej w konsoli.
Gracz może obstawiać pieniądze, dobierać karty, sprawdzać saldo i grać dowolną liczbę rund.
Gra została stworzona jako projekt edukacyjny — idealna do nauki podstaw logiki, funkcji i losowości w C++.

⸻

🕹️ Funkcje gry

✅ Losowe rozdanie kart (z pełną talią 13 wartości)
✅ Obsługa salda i stawek gracza
✅ Dobieranie kart (hit/stand)
✅ Automatyczna gra krupiera (dobiera do 17)
✅ Obsługa asa jako 1 lub 11
✅ Powtarzanie rund bez restartu gry
✅ Prosty system wygranych, przegranych i remisów
✅ Komunikaty w języku polskim

⸻

💻 Technologie
	•	Język: C++
	•	Standard: C++11+
	•	Środowisko: dowolny kompilator (G++, MSVC, CLion, Code::Blocks itp.)
  
⸻

⚙️ Uruchomienie
	1.	Sklonuj repozytorium:
git clone https://github.com/<twoj-uzytkownik>/blackjack-cpp.git
 	2.	Wejdź do folderu projektu:
cd blackjack-cpp
	3.	Skompiluj program:
  g++ main.cpp -o blackjack
  4. Uruchom: 
  ./blackjack

  🧩 Struktura kodu

Plik główny: main.cpp
Zawiera funkcje:
	•	rozdaj() – rozpoczęcie rundy
	•	wartoscKarty() – ustalanie wartości karty
	•	nazwaKarty() – zwraca nazwę karty
	•	sprawdzWynik() – logika gry i sprawdzanie zwycięzcy
	•	sprawdzSaldo() – obsługa salda i kontynuacji gry

⸻

📈 Pomysły na rozwój
	•	🃏 Wprowadzenie klas (class BlackjackGame)
	•	💾 Zapis i wczytywanie stanu gry (saldo, statystyki)
	•	🧠 Ulepszone AI krupiera (soft 17, strategie)
	•	🎨 Kolory i efekty konsolowe
	•	🎮 Tryb dla 2 graczy
	•	🪄 Interfejs graficzny (SFML / SDL)
