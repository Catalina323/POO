#pragma once
#include <vector>
#include <stdexcept>
#include <typeinfo>

class Contract	//Baza
{
protected:
	int nr_contract;
	int an;
	std::string nume_cumparator;
	std::string nume_furnizor;
	int valoare_totala;
	

public:
	Contract() = default;
	Contract(const int nr_contract, const int an, const std::string& nume_cumparator, const std::string& nume_furnizor, const int valoare_totala)
	{
		this->nr_contract = nr_contract;
		this->an = an;
		this->nume_cumparator = nume_cumparator;
		this->nume_furnizor = nume_furnizor;
		this->valoare_totala = valoare_totala;
		//std::cout << "constructor cu parametru contract" << std::endl;
	}
	virtual ~Contract() {}

	friend std::istream& operator>>(std::istream&, Contract&);
	friend std::ostream& operator<<(std::ostream&, Contract&);

	virtual int getNrContract()
	{
		return nr_contract;
	}

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

	ContractInchiriere(const int nr_contract, const int an, const std::string& nume_cumparator, const std::string& nume_furnizor, const int valoare_totala, int durata)
	{
		this->nr_contract = nr_contract;
		this->an = an;
		this->nume_cumparator = nume_cumparator;
		this->nume_furnizor = nume_furnizor;
		this->valoare_totala = valoare_totala;
		this->durata = durata;
		//std::cout << "constructor cu parametrii contract inchiriere" << std::endl;
	}
	~ContractInchiriere() {}

	friend std::istream& operator>>(std::istream&, ContractInchiriere&);
	friend std::ostream& operator<<(std::ostream&, ContractInchiriere&);

	void Afis()
	{
		Contract::Afis();
		std::cout << durata;
	}
	int getNrContract()
	{
		return nr_contract;
	}

	int getDurata()
	{
		return durata;
	}

	int getValoare()
	{
		return valoare_totala;
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
	std::vector < std::shared_ptr<Contract>> v;
	int numar_contr;
	static int nr;

public:

	Dosar() = default;

	void AdaugareContract()
	{
		//nr++;
		std::cout<< "Dati tipul de contract pe care vreti sa il cititi ('contract' sau 'contract_inchiriere'): " << std::endl;
		std::string opt;
		try
		{
			std::cin >> opt;

			if (opt == "contract")
			{
				nr++;
				std::shared_ptr<Contract> x = std::make_shared<Contract>();
				std::cin >> *x;
				v.push_back(x);
			}
			else
				if (opt.compare("contract_inchiriere") == 0)
				{
					nr++;
					std::shared_ptr<ContractInchiriere> x = std::make_shared<ContractInchiriere>();
					std::cin >> *x;
					v.push_back(x);
				}
				else
					throw std::invalid_argument("Introduceti una din cele 2 variante propuse: 'contract' sau 'contract inchiriere'");

		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}

	}

	void citire()
	{
		std::cout << "Numar contracte: ";
		std::cin >> numar_contr;

		for (int i = 0;i < numar_contr;i++)
		{
			//nr++;
			std::string optiune;
			std::cout << "Dati tipul de contract pe care vreti sa il cititi ('contract' sau 'contract_inchiriere'): " << std::endl;
			try
			{
				std::cin >> optiune;

				if (optiune == "contract")
				{
					nr++;
					std::shared_ptr<Contract> x = std::make_shared<Contract>();
					std::cin >> *x;
					v.push_back(x);
				}
				else
					if (optiune.compare("contract_inchiriere") == 0)
					{
						nr++;
						std::cout << "citeste contract inchiriere" << std::endl;
						std::shared_ptr<ContractInchiriere> x = std::make_shared<ContractInchiriere>();
						std::cin >> *x;
						v.push_back(x);
					}
					else
					{
						throw std::invalid_argument("Introduceti una din cele 2 variante propuse: 'contract' sau 'contract inchiriere'");
					}
			}
			catch (const std::invalid_argument& e)
			{
				std::cerr << "Error: " << e.what() << std::endl;
				i--;
			}

		}
	}

	void Afis()
	{
		for (int i = 0;i < nr;i++)
		{
			v[i]->Afis();
			std::cout << std::endl;
		}
	}

	void Afis(int x)
	{
		for (int i = 0;i < numar_contr;i++)
		{
			if ((*v[i]).getNrContract() == x)
			{
				v[i]->Afis();
				std::cout << std::endl;
			}
		}
	}

	void valoare_dosar()
	{
		static int suma = 0;

		for (int i = 0;i < nr;i++)
		{
			if (typeid(*v[i]) == typeid(ContractInchiriere))
			{
				ContractInchiriere* c = dynamic_cast<ContractInchiriere*>(v[i].get());
				if (c != nullptr)
				{
					suma += c->getValoare() * c->getDurata();
				}
			}
		}

		std::cout << suma;
	}

	void getNr()
	{
		std::cout << nr;
	}

};

int Dosar::nr = 0;
