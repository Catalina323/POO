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
#include <vector>
#include "tema.h"

int main()
{
	// UPDATE: UN DOSAR POATE SA CUPRINDA AMBELE TIPURI DE CONTRACTE (SIMPLU SI DE INCHIRIERE)

	//Contract c1;
	//ContractInchiriere c2;
	//Contract c3(2, 3, "ba", "bf", 5);
	//c1 = c3;
	//std::cout << c1 << std::endl;
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

	int op;
	Dosar d;

	while (true)
	{
		std::cout << "Cititi un dosar nou? (da = '1' sau nu = '2')" << std::endl;

		try
		{
			std::cin >> op;
			switch (op)
			{
			case(1):
			{
				std::cout << "Cititi contractele din dosar: " << std::endl;
				d.citire();

				std::cout << "Ce doriti sa faceti in continuare?" << std::endl;
				std::cout << "'1'= afisati toate contractele" << std::endl;
				std::cout << "'2'= cititi nr contractului pe care doriti sa il afisati" << std::endl;
				std::cout << "'3'= afisasti valoarea dosarului" << std::endl;
				std::cout << "'4'= adaugati contract" << std::endl;
				std::cout << "'5'= afisati numarul de contracte din dosar" << std::endl;;
				std::cout << "'6'= iesire" << std::endl;

				int op2;
				bool ok = true;
				while (ok)
				{
					try
					{
						std::cin >> op2;
						switch (op2)
						{
						case(1):
						{
							std::cout << "Contractele citite sunt: " << std::endl;
							d.Afis();
							break;
						}
						case(2):
						{
							int nr;
							std::cout << "introduceti nr dosarului pe care doriti sa il afisati:";
							std::cin >> nr;
							d.Afis(nr);
							break;
						}
						case(3):
						{
							std::cout << "Valoarea dosarului este: " << std::endl;
							d.valoare_dosar();
							break;
						}
						case(4):
						{
							d.AdaugareContract();
							break;
						}
						case(5):
						{
							std::cout << "numarul de contracte din dosar este: ";
							d.getNr();
							break;
						}
						case(6):
							ok = false;
							break;
						default:
							throw std::invalid_argument("Introduceti doar '1' '2' '3' '4' '5' sau '6'");
						}
					}
					catch (const std::invalid_argument& e)
					{
						std::cerr << "Error: " << e.what() << std::endl;
					}
				}
				break;
			}
			case(2):
				return 0;
			default:
				throw std::invalid_argument("Introduceti doar '1' sau '2'");
			}
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}

	return 0;
}
