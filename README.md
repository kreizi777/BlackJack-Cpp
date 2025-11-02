# BlackJack-Cpp

🎰 BlackJack C++

Prosty, konsolowy BlackJack napisany w języku C++, który pozwala zagrać w klasyczną wersję kasynowej gry karcianej.
Projekt zawiera menu główne, zapis salda, historię gier oraz obsługę podstawowych zasad BlackJacka.

⸻

🧩 Funkcje
	•	🎮 Tryb gry BlackJack — gracz gra przeciwko krupierowi zgodnie z zasadami klasycznej gry.
	•	💾 Zapis i wczytywanie salda — saldo z ostatniej sesji zapisywane jest w pliku saldo.txt.
	•	📊 Historia rozgrywek — wszystkie wyniki i statystyki zapisywane są w pliku statystyki.txt.
	•	🧠 System menu — gracz może rozpocząć nową grę, sprawdzić statystyki lub wyjść.
	•	🃏 Dynamiczne dobieranie kart — system losowania i obliczania sum punktów z uwzględnieniem Asa (1 lub 11).

⸻


🧮 Zasady gry
	•	Celem gry jest uzyskanie sumy kart jak najbliższej 21 punktów (bez przekroczenia).
	•	Figury (J, Q, K) mają wartość 10.
	•	As może mieć wartość 1 lub 11, w zależności od sytuacji.
	•	Jeśli suma kart gracza przekroczy 21 → przegrywa automatycznie.
	•	Krupier dobiera karty, dopóki nie uzyska co najmniej 17 punktów.

⸻

🧠 Technologie
	•	C++17
	•	Operacje na plikach (fstream)
	•	Klasy i metody obiektowe
	•	Losowanie kart (rand(), srand())
	•	Obsługa menu i prosty system stanu gry

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
  
  ⸻

✍️ Autor

Projekt stworzony w celach edukacyjnych – rozwój umiejętności programowania w C++
💡 Autor: [kreizi]


