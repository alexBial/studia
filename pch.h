#ifndef PCH_H
#define PCH_H

#include <string> 
#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <map>
#include <windows.h>

static float global_cpm = 1;
class Produkt
{
	std::string nazwa;

	
	int bialko;
	int wegle;
	int tluszcz;
public:
	int wartosc; //dla funkcji dodajacej kcal'orie 

	Produkt();
	void show();
	friend class Losowanie;
	friend class Pszczolka;
};
class Posilek
{
public:
	Posilek();
	Produkt talerz[3];
	void show();
	friend class Losowanie;
};
class Sniadanie : public Posilek
{
public:
	Sniadanie();
};
class Obiad : public Posilek
{
public:
	Obiad();
};
class Kolacja : public Posilek
{
public:
	Kolacja();
};

class User_interface
{
public:
	User_interface(int = 1, int = 1, bool = 1, int = 1, int = 1);
	~User_interface();
	void start();
private:
	friend class Cpm;
	friend class Ograniczenia_i_cel;
	int wiek;
	float akt_fiz;
	int plec;  //0 =kobieta , 1 = mezczyzna
	int wzrost;
	int waga;
};

class Cpm
{
	
public:
	int _cpm;
	Cpm(User_interface);
	int get_cpm();
	friend class Pszczolka;
};

class Ograniczenia_i_cel
{
	std::string nazwa;
	
	int bialko;
	int wegle;
	int tluszcz;
	float dopuszczalnyOdchyl = 0.2;
public:
	int wartosc;
	Ograniczenia_i_cel();
	Ograniczenia_i_cel(User_interface, Cpm);
	void wypisz_cel();
	void pobierz_odchyl();
	bool sprawdz_ogr(const Pszczolka&);
	int sprawdz_cel(const Pszczolka&);
};


class Jadlospis
{
	Sniadanie sniadanie;
	Obiad obiad;
	Kolacja kolacja;
	public:
	float dzienne_kalorie = 0;
	friend class Pszczolka;
	Jadlospis();
	void show();	
};

class Pszczolka
{	public:
	Jadlospis jadlospis;
	int wartosc;
	int bialko;
	int wegle;
	int tluszcze;
	int odchyl;
	void policz_odchyl();
	friend class Ograniczenia_i_cel;
	Pszczolka();
	int zwroc_odchyl();
	void pokaz_wartosci();
	void zmien_jadlospis();
	void zmien_sniadanie(Ograniczenia_i_cel &);
	void zmien_obiad(Ograniczenia_i_cel&);
	void zmien_kolacje(Ograniczenia_i_cel&);
};

class Populacja
{

	int liczba_zwiadowcow;
	int liczba_elit;
	int liczba_plebsy;
	Ograniczenia_i_cel ograniczenia;

public:
	std::map<int, Pszczolka> populacja;
	Populacja(Ograniczenia_i_cel);
	void sprawdz_sasiedztwo();
};

class Rozwiazania
{
	Jadlospis najlepsze;
};

class Losowanie
{
	void load(Produkt& Comp);
	int losuj(int maximum);
	void wyborEtapI(Produkt& Comp, int pierwszySkladnik);
	void wyborEtapDwaI(Produkt& Comp, int pierwszySkladnikDwa);
	void wyborEtapTrzyI(Produkt& Comp, int pierwszySkladnikTrzy);
	void wyborEtapII(Produkt& Comp, int pierwszySkladnik);
	void wyborEtapDwaII(Produkt& Comp, int pierwszySkladnikDwa);
	void wyborEtapTrzyII(Produkt& Comp, int pierwszySkladnikTrzy);
	void wyborEtapIII(Produkt& Comp, int pierwszySkladnik);
	void wyborEtapDwaIII(Produkt& Comp, int pierwszySkladnikDwa);
	void wyborEtapTrzyIII(Produkt& Comp, int pierwszySkladnikDwaTrzy);

	friend class Sniadanie;
	friend class Kolacja;
	friend class Obiad;
};
float operator+(Posilek posilek1, Posilek posilek2);
float operator+(float kalorie, Posilek posilek1);
void funkcja_celu(Ograniczenia_i_cel ogr, Pszczolka psz);

#endif //PCH_H
