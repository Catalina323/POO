/* Tema 2 POO
 
	CERINTE GENERALE TEMA 2:
Separarea codului din clase in fisiere header (.h/.hpp etc.) si surse (.cpp etc.)
clasele mici si legate intre ele se pot afla in aceeasi pereche de fisiere header-sursa
FARA using namespace std in fisiere .h la nivel global

- mosteniri
- functii virtuale (pure); functiile virtuale vor fi apelate prin pointeri la clasa de baza
- pointerii la clasa de baza vor fi atribute ale altei clase, nu doar niste pointeri/referinte
in main
- apelarea constructorului din clasa de baza
- smart pointers
- dynamic_cast
- suprascris cc/op= pentru copieri/atribuiri corecte
- exceptii:
   - ierarhie proprie (cu baza std::exception sau derivata din std::exception)
   - utilizare cu sens: de exemplu, throw in constructor, try/catch in main
- functii si atribute statice
- STL
- fara variabile globale
- cat mai multe const, testat/apelat tot codul public de interes din main
- implementarea a doua functionalitati noi specifice temei; pot fi folosite functii virtuale
in acest scop

	CERINTA ALEASA:

Tema 8. Sa se defineasca clasa Contract care contine membrii privati
- nrContract(numar contract)
- anul(anul semnarii contractului de cumparare)
- beneficiar(numele cumparatorului / beneficiarului)
- furnizor(nume vanzator / ofertant / furnizor)
- valoare(valoarea totala a produsului)
Sa se deriveze clasa ContractInchiriere din Contract avand in plus ca membru privat
- perioada(perioada contractului exprimata in numar luni)
Definiti clasa Dosar care contine un vector de pointeri la obiecte de tip ContractInchiriere 
si un numar de contracte de inchiriere.

Se citesc contractele din dosar, se afiseaza si se cere sa se calculeze valoarea incasata
pentru fiecare contract in functie de perioada, respectiv valoarea totala incasata
*/


#include <iostream>

class Contract	//Baza
{protected:
	int nr_contract;
	int an;
	std::string nume_cumparator;
	std::string nume_furnizor;
	int valoare_totala;

public:
	Contract() = default;
	
	Contract(const int nr_contract,const int an,const std::string& nume_cumparator,const std::string& nume_furnizor,const int valoare_totala)
	{
		this->nr_contract = nr_contract;
		this->an = an;
		this->nume_cumparator = nume_cumparator;
		this->nume_furnizor = nume_furnizor;
		this->valoare_totala = valoare_totala;
		//std::cout << "constructor cu parametru contract" << std::endl;
	}
	virtual ~Contract(){}

	friend std::istream& operator>>(std::istream&, Contract&);
	friend std::ostream& operator<<(std::ostream&, Contract&);

	virtual void Afis()
	{
		std::cout << nr_contract << " " << an << " " << nume_cumparator << " " << nume_furnizor << " " << valoare_totala << " ";
	}

};

std::istream& operator>>(std::istream& in, Contract& c)
{
	std::cout << "numar contract: ";
	in >> c.nr_contract;
	std::cout << "an: ";
	in >> c.an;
	std::cout << "nume cumparator: ";
	in >> c.nume_cumparator;
	std::cout << "nume furnizor: ";
	in >> c.nume_furnizor;
	std::cout << "valoarea totala: ";
	in >> c.valoare_totala;

	return in;
}

std::ostream& operator<<(std::ostream& out, Contract& c)
{
	out << c.nr_contract << " " << c.an << " " << c.nume_cumparator << " " << c.nume_furnizor << " " << c.valoare_totala;

	return out;
}


class ContractInchiriere : public Contract	//Derivata
{
	int durata;		// exprimata in nr luni

public:
	ContractInchiriere() = default;
	
	ContractInchiriere(const int nr_contract, const int an,const std::string& nume_cumparator,const std::string& nume_furnizor,const int valoare_totala, int durata)
	{
		this->nr_contract = nr_contract;
		this->an = an;
		this->nume_cumparator = nume_cumparator;
		this->nume_furnizor = nume_furnizor;
		this->valoare_totala = valoare_totala;
		this->durata = durata;
		//std::cout << "constructor cu parametrii contract inchiriere" << std::endl;
	}
	~ContractInchiriere(){}

	friend std::istream& operator>>(std::istream&, ContractInchiriere&);
	friend std::ostream& operator<<(std::ostream&, ContractInchiriere&);

	void Afis()
	{
		Contract::Afis();
		std::cout << durata;
	}

};

std::istream& operator>>(std::istream& in, ContractInchiriere& c)
{
	std::cout << "numar contract: ";
	in >> c.nr_contract;
	std::cout << "an: ";
	in >> c.an;
	std::cout << "nume cumparator: ";
	in >> c.nume_cumparator;
	std::cout << "nume furnizor: ";
	in >> c.nume_furnizor;
	std::cout << "valoarea totala: ";
	in >> c.valoare_totala;
	std::cout << "durata: ";
	in >> c.durata;

	return in;
}

std::ostream& operator<< (std::ostream& out, ContractInchiriere& c)
{
	out << c.nr_contract << " " << c.an << " " << c.nume_cumparator << " " << c.nume_furnizor << " " << c.valoare_totala << " " << c.durata;
	return out;
}


class Dosar
{
	ContractInchiriere * v = new ContractInchiriere[100];
	int numar_contr;

public:

	Dosar() = default;

	void citire()
	{
		std::cout << "Numar contracte: ";
		std::cin >> numar_contr;

		for (int i = 0;i < numar_contr;i++)
		{
			std::cin >> v[i];
		}
	}
};


int main()
{
	//Contract c1;
	//ContractInchiriere c2;
	//Contract c3(2, 3, "ba", "bf", 5);
	//ContractInchiriere c4(1, 2, "a", "b", 3, 4);
	//c3.Afis();
	//c4.Afis();
	//std::cin >> c2;
	//std::cout << c2;
	// Aici testez virtual ul de la Afis() din Contract :)
	/*
	ContractInchiriere* c5 = new ContractInchiriere;
	std::cin >> *c5;
	Contract* c6 = c5;
	c6->Afis();
	*/

	Dosar d;
	d.citire();


	return 0;
}