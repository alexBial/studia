// StayFit.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.cpp"
#include "pch.h"

int main()
{
	User_interface user;
	
	
	int again;

	do
	{
		system("cls");
		user.start();
		Cpm cpm(user);
		Ograniczenia_i_cel ogr(user, cpm);
		ogr.pobierz_odchyl();
		ogr.wypisz_cel();
		
		do {
			Populacja pop(ogr);

			int iteracje = 0;
			std::cout << "wybierz liczbe iteracji dla algorytmu:";
			std::cin >> iteracje;


			for (int i = 0; i < iteracje; i++)
			{
				pop.sprawdz_sasiedztwo();
				auto iter = pop.populacja.begin();
				funkcja_celu(ogr, (iter->second));
			}
			int ile;
			std::cout << "\n\n                                   Ile menu chcesz otrzymac?" << std::endl;
			std::cin >> ile;
			std::cout << std::endl;
			auto iter = pop.populacja.begin();
			for (int hehe = 0; hehe < ile; hehe++)
			{
				iter->second.jadlospis.show();

				
				std::cout << "\n Odchyl:  " << ogr.sprawdz_cel(iter->second);
				std::cout << "\n Laczna wartosc kalorii: " << iter->second.wartosc;
				std::cout << "\n\n________________________________________________________________________________________________________________________________\n\n";
				++iter;
			}
			
			std::cout <<"\n\n			                    wpisz 1 aby ponownie wybrac diete" << std::endl;
			std::cin >> again;

		} while (again == 1);
		
		std::cout <<	"\n\n                    wpisz 1 aby zmienic swoje parametry" << std::endl;
		std::cin >> again;

	} while (again == 1);
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
