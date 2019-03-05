// pch.cpp: plik zrodłowy odpowiadajacy wstepnie skompilowanemu nagłowkowi, niezbedny do powodzenia kompilacji
#include "pch.h"


User_interface::User_interface(int n_wiek, int n_akt_fiz, bool n_plec, int n_wzrost, int n_waga)
{
	wiek = n_wiek;
	akt_fiz = n_akt_fiz;
	plec = n_plec;
	wzrost = n_wzrost;
	waga = n_waga;
}

User_interface::~User_interface()
{
	//dtor
}

void User_interface::start()
{
	do
	{
		std::cout <<"\n\n                                           Podaj swoj wiek: " << std::endl;
		std::cin >> wiek;
		if ((wiek <= 0) || (wiek >= 120)) Beep(300, 500);		
	} while ((wiek <= 0) || (wiek >= 120));
	do
	{
		

		std::cout << "\n\n                            Podaj swoja aktywnosc fizyczna (od 1 do 6),gdzie: " << std::endl;
		std::cout << "\n         1		brak aktywnosci, praca siedzaca";
		std::cout << "\n         2		niska aktywnosc (praca siedzaca i 1-2 treningi w tygodniu)";
		std::cout << "\n         3		srednia aktywnosc (praca siedzaca i treningi 3-4 razy w tygodniu)";
		std::cout << "\n         4		wysoka aktywnosc (praca fizyczna i 3-4 treningi w tygodniu)";
		std::cout << "\n         5		bardzo wysoka aktywnosc (osoby codziennie trenujace)";
		std::cout << "\n         6		bardzo wysoka aktywnosc (zawodowi sportowcy) \n";

		std::cin >> akt_fiz;
		if ((akt_fiz < 1) || (akt_fiz > 6)) Beep(300, 500);
	} while ((akt_fiz < 1) || (akt_fiz > 6));
	akt_fiz = 1 + (0.2*akt_fiz);

	do
	{
		

		std::cout << "\n\n                              Podaj swoja plec (0 kobieta, 1 mezczyzna): " << std::endl;
		std::cin >> plec;
		if ((plec != 1) && (plec != 0)) Beep(300, 500);
	} while ((plec != 1) && (plec != 0));
	
	do
	{
		std::cout << "\n\n                                        Podaj swoj wzrost(cm): " << std::endl;
		std::cin >> wzrost;
		if ((wzrost > 250) || (wzrost < 20)) Beep(300, 500);
	} while ((wzrost>250) || (wzrost < 20));
	
	do
	{
		
		std::cout << "\n\n                                        Podaj swoja wage: " << std::endl;
		std::cin >> waga;
		if ((waga > 150) || (waga < 1)) Beep(300, 500);
	} while ((waga > 150) || (waga < 1));
	

}

// *****************************************************************************************

Cpm::Cpm(User_interface a)
{
	int dodatek;
	if (a.plec == 0)
		dodatek = -161;
	else
		dodatek = 5;

	float _bmr = (10 * a.waga) + (6.25 * a.wzrost) + (4.92 * a.wiek) + dodatek;
	_cpm = _bmr * a.akt_fiz * 1.1;
	global_cpm = _cpm;
	
}

int Cpm::get_cpm()
{
	return _cpm;
}

//*********************************************************************************************
Jadlospis::Jadlospis()
{
	sniadanie = Sniadanie();
	obiad = Obiad();
	kolacja = Kolacja();
	dzienne_kalorie = sniadanie + obiad + kolacja;
}

void Jadlospis::show()
{
	std::cout << "\n\t                                            SNIADANIE\n" << std::endl;
	sniadanie.show();
	std::cout << "\n\t                                              OBIAD\n" << std::endl;
	obiad.show();
	std::cout << "\n\t                                              KOLACJA\n" << std::endl;
	kolacja.show();

}

void funkcja_celu(Ograniczenia_i_cel ogr,Pszczolka psz)
{
	std::fstream plik;

	plik.open("funkcja_celu.txt", std::ios::app);
	
	plik << ogr.sprawdz_cel(psz) << "\n";


	plik.close(); //obowiązkowo należy zamknąć plik

	
}

//*****************************************************************************************

Pszczolka::Pszczolka()
{
	tluszcze = 0;
	wegle = 0;
	bialko = 0;
	wartosc = 0;
	jadlospis = Jadlospis();
	policz_odchyl();
}

void Pszczolka::policz_odchyl()
{
	wartosc = 0;
	tluszcze = 0;
	wegle = 0;
	bialko = 0;
	for (int i = 0; i < 3; i++)
	{
		wartosc = wartosc + jadlospis.sniadanie.talerz[i].wartosc + jadlospis.kolacja.talerz[i].wartosc + jadlospis.obiad.talerz[i].wartosc;
		tluszcze = tluszcze + jadlospis.sniadanie.talerz[i].tluszcz + jadlospis.kolacja.talerz[i].tluszcz + jadlospis.obiad.talerz[i].tluszcz;
		wegle = wegle + jadlospis.sniadanie.talerz[i].wegle + jadlospis.kolacja.talerz[i].wegle + jadlospis.obiad.talerz[i].wegle;
		bialko = bialko + jadlospis.sniadanie.talerz[i].bialko + jadlospis.kolacja.talerz[i].bialko + jadlospis.obiad.talerz[i].bialko;
	};
	tluszcze = tluszcze *global_cpm/1500;
	wegle = wegle * global_cpm/1500;
	bialko = bialko * global_cpm/1500;
	wartosc = wartosc *global_cpm/1500;
}

void Pszczolka::zmien_jadlospis()
{
	jadlospis = Jadlospis();
}

void Pszczolka::zmien_sniadanie(Ograniczenia_i_cel & ogr)
{
	bool wynik = 0;
	while (!wynik)
	{
		jadlospis.sniadanie = Sniadanie();
		policz_odchyl();
		wynik = ogr.sprawdz_ogr(*this);
	}

}

void Pszczolka::zmien_obiad(Ograniczenia_i_cel &ogr)
{
	bool wynik = 0;
	while (!wynik)
	{
		jadlospis.obiad = Obiad();
		policz_odchyl();
		wynik = ogr.sprawdz_ogr(*this);
	}

}
void Pszczolka::zmien_kolacje(Ograniczenia_i_cel &ogr)
{
	bool wynik = 0;
	while (!wynik)
	{
		jadlospis.kolacja = Kolacja();
		policz_odchyl();
		wynik = ogr.sprawdz_ogr(*this);
	}

}

void Pszczolka::pokaz_wartosci()
{
	float spr[] = { bialko,wegle,tluszcze };
	bool wynik = 1;
	for (int i = 0; i <= 2; i++)
	{
		std::cout << "\n                                            Dostarczna wartosc: " << spr[i] << std::endl;
	}

}

int Pszczolka::zwroc_odchyl()
{
	return odchyl;
}

//**********************************************************************

Produkt::Produkt()
{
	wartosc = 0;
	wegle = 0;
	tluszcz = 0;
	bialko = 0;
}

void Produkt::show()
{
	if ((wartosc != 0) || (wegle != 0) || (bialko != 0) || (tluszcz != 0))
	{
		std::cout << "\t                                  Nazwa produktu:  " << nazwa << std::endl;
		std::cout << "\t                   Wartosc energetyczna:                      " << (global_cpm / 1500)*wartosc << " kcal" << std::endl;
		std::cout << "\t                   Weglowodany:                               " << (global_cpm / 1500)*wegle << " g" << std::endl;
		std::cout << "\t                   Bialko:                                    " << (global_cpm / 1500)*bialko << " g" << std::endl;
		std::cout << "\t                   Tluszcz:                                   " << (global_cpm / 1500)*tluszcz << " g" << std::endl;
		std::cout << std::endl;
	}
	
};

Posilek::Posilek()
{
}

void Posilek::show()
{
	talerz[0].show();
	talerz[1].show();
	talerz[2].show();
}

Populacja::Populacja(Ograniczenia_i_cel cel)
{

	do
	{
		std::cout << "\n\n                                        Podaj liczbe pszczol-zwiadowcow(10-100): " << std::endl;
		std::cin >> liczba_zwiadowcow;
	} while ((liczba_zwiadowcow > 100) || (liczba_zwiadowcow < 10));
	
	do
	{
		std::cout << "\n\n                                        Podaj liczbe pszczol elitarnych: " << std::endl;
		std::cin >> liczba_elit;
			if (liczba_elit < 1) std::cout << "\n\n                                        Liczba elit musi byc conajmniej rowna 1"<<std::endl;
	} while ((liczba_elit > liczba_zwiadowcow) || (liczba_elit < 1));

	do
	{
		std::cout << "\n\n                                        Podaj liczbe pszczol odrzuconych: " << std::endl;
		std::cin >> liczba_plebsy;
	} while ((liczba_plebsy > (liczba_zwiadowcow-liczba_elit)) || (liczba_plebsy < 0));
	
	ograniczenia = cel;

	for (int i = 0; i < liczba_zwiadowcow; i++)
	{
		Pszczolka temp;
		bool wynik = 0;
		while (!wynik)
		{
			temp = Pszczolka();
			wynik = cel.sprawdz_ogr(temp);
		}

		int roznica = cel.sprawdz_cel(temp);
		populacja[roznica] = std::move(temp);
	}
	std::cout << "\n\n                    Pamietaj, ze kazdy produkt nalezy spozyc w ilosci " << global_cpm/15 << " gram" << std::endl;//(cpm/1500)*100
}


void Populacja::sprawdz_sasiedztwo()
{
	std::map<int, Pszczolka> nowa;
	int ranking = 1;

		for (auto iter = populacja.begin(); iter != populacja.end(); ++iter)
		{


			if (ranking <= liczba_elit)
			{
				Pszczolka najlepsza = iter->second;
				Pszczolka temp = iter->second;
				for (int i = 0; i < 10; i++)
				{
					temp.zmien_sniadanie(ograniczenia);
					if (ograniczenia.sprawdz_cel(temp) < ograniczenia.sprawdz_cel(najlepsza))
						najlepsza = temp;
					else
						temp = najlepsza;
					temp.zmien_obiad(ograniczenia);
					if (ograniczenia.sprawdz_cel(temp) < ograniczenia.sprawdz_cel(najlepsza))
						najlepsza = temp;
					else
						temp = najlepsza;
					temp.zmien_kolacje(ograniczenia);
					if (ograniczenia.sprawdz_cel(temp) < ograniczenia.sprawdz_cel(najlepsza))
						najlepsza = temp;
					else
						temp = najlepsza;
				}
				najlepsza.policz_odchyl();
				int roznica = ograniczenia.sprawdz_cel(najlepsza);
				nowa[roznica] = najlepsza;
			}


			else if (ranking > liczba_elit && ranking <= (liczba_zwiadowcow - liczba_plebsy))
			{
				Pszczolka najlepsza = iter->second;
				Pszczolka temp = iter->second;
				for (int i = 0; i < 3; i++)
				{
					temp.zmien_sniadanie(ograniczenia);
					if (ograniczenia.sprawdz_cel(temp) < ograniczenia.sprawdz_cel(najlepsza))
						najlepsza = temp;
					else
						temp = najlepsza;
					temp.zmien_obiad(ograniczenia);
					if (ograniczenia.sprawdz_cel(temp) < ograniczenia.sprawdz_cel(najlepsza))
						najlepsza = temp;
					else
						temp = najlepsza;
					temp.zmien_kolacje(ograniczenia);
					if (ograniczenia.sprawdz_cel(temp) < ograniczenia.sprawdz_cel(najlepsza))
						najlepsza = temp;
					else
						temp = najlepsza;
				}
				najlepsza.policz_odchyl();
				int roznica = ograniczenia.sprawdz_cel(najlepsza);
				nowa[roznica] = najlepsza;
			}
			else
			{
				Pszczolka temp = Pszczolka();
				bool wynik = ograniczenia.sprawdz_ogr(temp);
				do
				{
					temp = Pszczolka();
					wynik = ograniczenia.sprawdz_ogr(temp);
				} while (!wynik);
				
				temp.policz_odchyl();
				int roznica = ograniczenia.sprawdz_cel(temp);
				nowa[roznica] = temp;
			}
			ranking++;
		}
	populacja = nowa;
	
	
}

Kolacja::Kolacja()
{
	Losowanie los;
	Produkt skladnik1_kolacja;
	int pierwszySkladnikTrzy = rand() % 6 + 1;


	los.wyborEtapTrzyI(skladnik1_kolacja, pierwszySkladnikTrzy);
	talerz[0] = skladnik1_kolacja;

	Produkt skladnik2_kolacja;
	los.wyborEtapTrzyII(skladnik2_kolacja, pierwszySkladnikTrzy);
	talerz[1] = skladnik2_kolacja;

	if (pierwszySkladnikTrzy == 1 || pierwszySkladnikTrzy == 2)
	{
		Produkt skladnik3_kolacja;
		los.wyborEtapTrzyIII(skladnik3_kolacja, pierwszySkladnikTrzy);
		talerz[2] = skladnik3_kolacja;
	}
	else
	{
		talerz[2] = Produkt();
	}
}

Sniadanie::Sniadanie()
{
	Losowanie los;
	Produkt skladnik1_sniadanie;
	int pierwszySkladnikDwa = rand() % 6 + 1;


	los.wyborEtapDwaI(skladnik1_sniadanie, pierwszySkladnikDwa);
	talerz[0] = skladnik1_sniadanie;

	Produkt skladnik2_sniadanie;
	los.wyborEtapDwaII(skladnik2_sniadanie, pierwszySkladnikDwa);
	talerz[1] = skladnik2_sniadanie;

	if (pierwszySkladnikDwa == 1 || pierwszySkladnikDwa == 2)
	{
		Produkt skladnik3_sniadanie;
		los.wyborEtapDwaIII(skladnik3_sniadanie, pierwszySkladnikDwa);
		talerz[2] = skladnik3_sniadanie;
	}
	else
	{
		talerz[2] = Produkt();
	}
}

Obiad::Obiad()
{
	Losowanie los;
	Produkt skladnik1_obiad;
	int pierwszySkladnik = rand() % 6 + 1;


	los.wyborEtapI(skladnik1_obiad, pierwszySkladnik);
	talerz[0] = skladnik1_obiad;


	if (pierwszySkladnik != 6)
	{
		Produkt skladnik2_obiad;
		los.wyborEtapII(skladnik2_obiad, pierwszySkladnik);
		talerz[1] = skladnik2_obiad;

	}
	else
	{
		talerz[1] = Produkt();
	}
	if (pierwszySkladnik != 5 && pierwszySkladnik != 6)
	{
		Produkt skladnik3_obiad;
		los.wyborEtapIII(skladnik3_obiad, pierwszySkladnik);
		talerz[2] = skladnik3_obiad;
	}
	else
	{
		talerz[2] = Produkt();
	}
}

//****************************************************************************************************************************

void Losowanie::load(Produkt& Comp)
{
	std::string dane;
	std::fstream plik;
	plik.open("menu.txt", std::ios::in);

	while (!plik.eof())
	{
		getline(plik, dane);
		Comp.nazwa = dane;

		getline(plik, dane);
		Comp.wartosc = atoi(dane.c_str());

		getline(plik, dane);
		Comp.wegle = atoi(dane.c_str());

		getline(plik, dane);
		Comp.bialko = atoi(dane.c_str());

		getline(plik, dane);
		Comp.tluszcz = atoi(dane.c_str());
	}

	plik.close();
}

int Losowanie::losuj(int maximum)
{
	int pierwszySkladnik = rand() % maximum + 1;
	return pierwszySkladnik;
}
void Losowanie::wyborEtapI(Produkt& Comp, int pierwszySkladnik)
{
	std::string dane;
	std::fstream plik;
	switch (pierwszySkladnik)
	{
	case 1:
		plik.open("Obiadmieso.txt", std::ios::in);
		break;
	case 2:
		plik.open("Obiadvegan.txt", std::ios::in);
		break;
	case 3:
		plik.open("Obiadmakaronkluski.txt", std::ios::in);
		break;
	case 4:
		plik.open("Obiadmakaronkluski.txt", std::ios::in);
		break;
	case 5:
		plik.open("Obiadnalesnikipierogi.txt", std::ios::in);
		break;
	case 6:
		plik.open("Obiadpierogibezdodatkow.txt", std::ios::in);
		break;
	}
	getline(plik, dane);
	int iloscProduktow = atoi(dane.c_str());
	iloscProduktow = losuj(iloscProduktow);


	for (int i = 0; i < iloscProduktow; i++)
	{
		getline(plik, dane);
		Comp.nazwa = dane;

		getline(plik, dane);
		Comp.wartosc = atoi(dane.c_str());

		getline(plik, dane);
		Comp.wegle = atoi(dane.c_str());

		getline(plik, dane);
		Comp.bialko = atoi(dane.c_str());

		getline(plik, dane);
		Comp.tluszcz = atoi(dane.c_str());
	}

	plik.close();
}
void Losowanie::wyborEtapDwaI(Produkt& Comp, int pierwszySkladnikDwa)
{
	std::string dane;
	std::fstream plik;
	switch (pierwszySkladnikDwa)
	{
	case 1:
		plik.open("pieczywo.txt", std::ios::in);
		break;
	case 2:
		plik.open("pieczywo.txt", std::ios::in);
		break;
	case 3:
		plik.open("pieczywo.txt", std::ios::in);
		break;
	case 4:
		plik.open("pieczywo.txt", std::ios::in);
		break;
	case 5:
		plik.open("platki.txt", std::ios::in);
		break;
	case 6:
		plik.open("platki.txt", std::ios::in);
		break;
	}
	getline(plik, dane);
	int iloscProduktow = atoi(dane.c_str());
	iloscProduktow = losuj(iloscProduktow);


	for (int i = 0; i < iloscProduktow; i++)
	{
		getline(plik, dane);
		Comp.nazwa = dane;

		getline(plik, dane);
		Comp.wartosc = atoi(dane.c_str());

		getline(plik, dane);
		Comp.wegle = atoi(dane.c_str());

		getline(plik, dane);
		Comp.bialko = atoi(dane.c_str());

		getline(plik, dane);
		Comp.tluszcz = atoi(dane.c_str());
	}

	plik.close();
}
void Losowanie::wyborEtapTrzyI(Produkt& Comp, int pierwszySkladnikTrzy)
{
	std::string dane;
	std::fstream plik;
	switch (pierwszySkladnikTrzy)
	{
	case 1:
		plik.open("pieczywo.txt", std::ios::in);
		break;
	case 2:
		plik.open("pieczywo.txt", std::ios::in);
		break;
	case 3:
		plik.open("pieczywo.txt", std::ios::in);
		break;
	case 4:
		plik.open("pieczywo.txt", std::ios::in);
		break;
	case 5:
		plik.open("platki.txt", std::ios::in);
		break;
	case 6:
		plik.open("platki.txt", std::ios::in);
		break;
	}
	getline(plik, dane);
	int iloscProduktow = atoi(dane.c_str());
	iloscProduktow = losuj(iloscProduktow);


	for (int i = 0; i < iloscProduktow; i++)
	{
		getline(plik, dane);
		Comp.nazwa = dane;

		getline(plik, dane);
		Comp.wartosc = atoi(dane.c_str());

		getline(plik, dane);
		Comp.wegle = atoi(dane.c_str());

		getline(plik, dane);
		Comp.bialko = atoi(dane.c_str());

		getline(plik, dane);
		Comp.tluszcz = atoi(dane.c_str());
	}

	plik.close();
}
void Losowanie::wyborEtapII(Produkt& Comp, int pierwszySkladnik)
{
	std::string dane;
	std::fstream plik;
	switch (pierwszySkladnik)
	{
	case 1:
		plik.open("Obiadmiesododatek.txt", std::ios::in);
		break;
	case 2:
		plik.open("Obiadmiesododatek.txt", std::ios::in);
		break;
	case 3:

		plik.open("Obiadmakaronkluskidodatek.txt", std::ios::in);
		break;
	case 4:
		plik.open("Obiadmakaronzserem.txt", std::ios::in);
		break;
	case 5:
		plik.open("Obiadowoce.txt", std::ios::in);
		break;
	case 6:
		return;
	}

	getline(plik, dane);
	int iloscProduktow = atoi(dane.c_str());
	iloscProduktow = losuj(iloscProduktow);


	for (int i = 0; i < iloscProduktow; i++)
	{
		getline(plik, dane);
		Comp.nazwa = dane;

		getline(plik, dane);
		Comp.wartosc = atoi(dane.c_str());

		getline(plik, dane);
		Comp.wegle = atoi(dane.c_str());

		getline(plik, dane);
		Comp.bialko = atoi(dane.c_str());

		getline(plik, dane);
		Comp.tluszcz = atoi(dane.c_str());
	}

	plik.close();
}
void Losowanie::wyborEtapDwaII(Produkt& Comp, int pierwszySkladnikDwa)
{
	std::string dane;
	std::fstream plik;
	switch (pierwszySkladnikDwa)
	{
	case 1:
		plik.open("dodatek.txt", std::ios::in);
		break;
	case 2:
		plik.open("dodatek.txt", std::ios::in);
		break;
	case 3:

		plik.open("nutelledzemy.txt", std::ios::in);
		break;
	case 4:
		plik.open("nutelledzemy.txt", std::ios::in);
		break;
	case 5:
		plik.open("mleko.txt", std::ios::in);
		break;
	case 6:
		plik.open("mleko.txt", std::ios::in);
		break;
	}

	getline(plik, dane);
	int iloscProduktow = atoi(dane.c_str());
	iloscProduktow = losuj(iloscProduktow);


	for (int i = 0; i < iloscProduktow; i++)
	{
		getline(plik, dane);
		Comp.nazwa = dane;

		getline(plik, dane);
		Comp.wartosc = atoi(dane.c_str());

		getline(plik, dane);
		Comp.wegle = atoi(dane.c_str());

		getline(plik, dane);
		Comp.bialko = atoi(dane.c_str());

		getline(plik, dane);
		Comp.tluszcz = atoi(dane.c_str());
	}

	plik.close();
}
void Losowanie::wyborEtapTrzyII(Produkt& Comp, int pierwszySkladnikTrzy)
{
	std::string dane;
	std::fstream plik;
	switch (pierwszySkladnikTrzy)
	{
	case 1:
		plik.open("dodatek.txt", std::ios::in);
		break;
	case 2:
		plik.open("dodatek.txt", std::ios::in);
		break;
	case 3:
		plik.open("nutelledzemy.txt", std::ios::in);
		break;
	case 4:
		plik.open("nutelledzemy.txt", std::ios::in);
		break;
	case 5:
		plik.open("mleko.txt", std::ios::in);
		break;
	case 6:
		plik.open("mleko.txt", std::ios::in);
		break;
	}

	getline(plik, dane);
	int iloscProduktow = atoi(dane.c_str());
	iloscProduktow = losuj(iloscProduktow);


	for (int i = 0; i < iloscProduktow; i++)
	{
		getline(plik, dane);
		Comp.nazwa = dane;

		getline(plik, dane);
		Comp.wartosc = atoi(dane.c_str());

		getline(plik, dane);
		Comp.wegle = atoi(dane.c_str());

		getline(plik, dane);
		Comp.bialko = atoi(dane.c_str());

		getline(plik, dane);
		Comp.tluszcz = atoi(dane.c_str());
	}

	plik.close();
}
void Losowanie::wyborEtapIII(Produkt& Comp, int pierwszySkladnik)
{
	std::string dane;
	std::fstream plik;
	switch (pierwszySkladnik)
	{
	case 1:
		plik.open("Obiadsurowka.txt", std::ios::in);
		break;
	case 2:
		plik.open("Obiadsurowka.txt", std::ios::in);
		break;
	case 3:

		plik.open("Obiadsurowka.txt", std::ios::in);
		break;
	case 4:
		return;
		break;
	case 5:
		return;
		break;
	case 6:
		return;
		break;
	}
	getline(plik, dane);
	int iloscProduktow = atoi(dane.c_str());
	iloscProduktow = losuj(iloscProduktow);


	for (int i = 0; i < iloscProduktow; i++)
	{
		getline(plik, dane);
		Comp.nazwa = dane;

		getline(plik, dane);
		Comp.wartosc = atoi(dane.c_str());

		getline(plik, dane);
		Comp.wegle = atoi(dane.c_str());

		getline(plik, dane);
		Comp.bialko = atoi(dane.c_str());

		getline(plik, dane);
		Comp.tluszcz = atoi(dane.c_str());
	}

	plik.close();
}
void Losowanie::wyborEtapDwaIII(Produkt& Comp, int pierwszySkladnikDwa)
{
	std::string dane;
	std::fstream plik;
	switch (pierwszySkladnikDwa)
	{
	case 1:
		plik.open("parowkijajka.txt", std::ios::in);
		break;
	case 2:
		plik.open("parowkijajka.txt", std::ios::in);
		break;
	case 3:
		return;
		break;
	case 4:
		return;
		break;
	case 5:
		return;
		break;
	case 6:
		return;
		break;
	}
	getline(plik, dane);
	int iloscProduktow = atoi(dane.c_str());
	iloscProduktow = losuj(iloscProduktow);


	for (int i = 0; i < iloscProduktow; i++)
	{
		getline(plik, dane);
		Comp.nazwa = dane;

		getline(plik, dane);
		Comp.wartosc = atoi(dane.c_str());

		getline(plik, dane);
		Comp.wegle = atoi(dane.c_str());

		getline(plik, dane);
		Comp.bialko = atoi(dane.c_str());

		getline(plik, dane);
		Comp.tluszcz = atoi(dane.c_str());
	}

	plik.close();
}
void Losowanie::wyborEtapTrzyIII(Produkt& Comp, int pierwszySkladnikDwaTrzy)
{
	std::string dane;
	std::fstream plik;
	switch (pierwszySkladnikDwaTrzy)
	{
	case 1:
		plik.open("parowkijajka.txt", std::ios::in);
		break;
	case 2:
		plik.open("parowkijajka.txt", std::ios::in);
		break;
	case 3:
		return;
		break;
	case 4:
		return;
		break;
	case 5:
		return;
		break;
	case 6:
		return;
		break;
	}
	getline(plik, dane);
	int iloscProduktow = atoi(dane.c_str());
	iloscProduktow = losuj(iloscProduktow);


	for (int i = 0; i < iloscProduktow; i++)
	{
		getline(plik, dane);
		Comp.nazwa = dane;

		getline(plik, dane);
		Comp.wartosc = atoi(dane.c_str());

		getline(plik, dane);
		Comp.wegle = atoi(dane.c_str());

		getline(plik, dane);
		Comp.bialko = atoi(dane.c_str());

		getline(plik, dane);
		Comp.tluszcz = atoi(dane.c_str());
	}

	plik.close();
}

//********************************************************************************************************]

Ograniczenia_i_cel::Ograniczenia_i_cel(User_interface user, Cpm cpm)
{
	float kal_bialko;
	float kal_wegle;
	float kal_tluszcz;

	kal_tluszcz = (cpm.get_cpm() / 4);
	wartosc = cpm.get_cpm();
	bialko = user.waga ;
	kal_bialko = bialko * 4;
	tluszcz = kal_tluszcz / 9;
	kal_wegle = wartosc - kal_bialko - kal_tluszcz;
	wegle = kal_wegle / 4;
}

void Ograniczenia_i_cel::wypisz_cel()
{
	std::cout << "Wymagane dzienne spozycie kcal wynosi:       " << wartosc <<"kcal"<< std::endl;
	std::cout << "Wymagane dzienne spozycie bialka wynosi:     " << bialko <<"g"<< std::endl;
	std::cout << "Wymagane dzienne spozycie wegli wynosi:      " << wegle <<"g"<< std::endl;
	std::cout << "Wymagane dzienne spozycie tluszczu wynosi:   " << tluszcz <<"g"<< std::endl;
}
void Ograniczenia_i_cel::pobierz_odchyl()
{
	do
	{
		std::cout << "Wpisz odchyl od wymaganej wartosci kcal(od 0 do 1):" << std::endl;
		std::cin >> dopuszczalnyOdchyl;
	} while ((dopuszczalnyOdchyl <= 0) || (dopuszczalnyOdchyl >= 1));
	
}
bool Ograniczenia_i_cel::sprawdz_ogr(const Pszczolka& obj)
{
	float rzecz[] = { obj.bialko, obj.wegle, obj.tluszcze };
	float spr[] = { bialko,wegle,tluszcz };
	bool wynik = 1;
	for (int i = 0; i <= 2; i++)
	{
		if (rzecz[i] < (spr[i] - (spr[i] * dopuszczalnyOdchyl)) || rzecz[i]> (spr[i] + (spr[i] * dopuszczalnyOdchyl)))
			wynik = 0;
	}
	return wynik;
}

int Ograniczenia_i_cel::sprawdz_cel(const Pszczolka& pszczolka)
{
	int roznica = abs(pszczolka.wartosc - wartosc);
	return roznica;
}
Ograniczenia_i_cel::Ograniczenia_i_cel()
{}
// Ogolnie rzecz biorac, zignoruj ten plik, ale miej go pod reka, jesli uzywasz wstepnie skompilowanych nagłowkow.
float operator+(Posilek posilek1, Posilek posilek2)
{
	float dzienne_kalorie = 0;
	for (int i = 0; i < 3; i++)
	{
		dzienne_kalorie = dzienne_kalorie + posilek1.talerz[i].wartosc;
	};
	for (int i = 0; i < 3; i++)
	{
		if (posilek2.talerz[i].wartosc!=0)	dzienne_kalorie = dzienne_kalorie + posilek2.talerz[i].wartosc;
	};
	return dzienne_kalorie;
}
float operator+(float kalorie, Posilek posilek1)
{
	float dzienne_kalorie = kalorie;
	for (int i = 0; i < 3; i++)
	{
		if (posilek1.talerz[i].wartosc != 0)	dzienne_kalorie = dzienne_kalorie + posilek1.talerz[i].wartosc;
	};
	return dzienne_kalorie;

}