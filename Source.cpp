#include <iostream>

class prajitura
{
	int pret;
	std::string glazura;
	std::string numePrajitura;

public:
	prajitura()
	{
		//std::cout << "constructor default"<<std::endl;
	}
	
	prajitura(const int Pret, const std::string& Glazura, const std::string& numePraj)
	{
		pret = Pret;
		glazura = Glazura;
		numePrajitura = numePraj;
		std::cout << "constructor predefinit" << std::endl;
	}

	prajitura(const prajitura& p)

		: glazura(p.glazura), pret(p.pret), numePrajitura(p.numePrajitura)
	{
		std::cout << "constructor de copiere" << std::endl;
	}
	
	~prajitura()
	{
		//std::cout << "destructor" << std::endl;
	}
	
	void setnumePrajitura(const std::string& numePr)
	{
		numePrajitura = numePr;
	}

	std::string getnumePrajitura()const
	{
		return numePrajitura;
	}

	int getPretPrajitura()const
	{
		return pret;
	}
	
	prajitura& operator=(const prajitura& numeP)
	{
		std::cout << "operator =" << std::endl;
		numePrajitura = numeP.numePrajitura;
		glazura = numeP.glazura;
		pret = numeP.pret;
		return *this;
	}
	
	friend std::ostream& operator<<(std::ostream&, prajitura&);
	friend std::istream& operator>>(std::istream&, prajitura&);

 };

std::ostream& operator<<(std::ostream& out, prajitura& other)
{
	out << other.numePrajitura << " " << other.glazura << " " << other.pret << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, prajitura& other)
{
	std::cout << "Nume Prajitura: ";
	in >> other.numePrajitura;
	std::cout << "Glazura: ";
	in >> other.glazura;
	std::cout << "Pret: ";
	in >> other.pret;
	return in;
}


class comanda
{
	int idComanda;
	int nrPrajituri;
	prajitura produs[20];
	std::string numeCumparator;
	std::string adresaLivare;
	
public:

	int pretComanda()const
	{
		int local = 0;
		for (int i = 1;i <= nrPrajituri;i++)
		{
			local += produs[i].getPretPrajitura();
		}

		return local;
	}

	friend std::istream& operator>>(std::istream&, comanda&);
	friend std::ostream& operator<<(std::ostream&, comanda&);

};

std::istream& operator>>(std::istream& in, comanda& other)
{
	std::cout << "Id Comanda: ";
	in >> other.idComanda;
	std::cout << "Nume Cumparator: ";
	in >> other.numeCumparator;
	std::cout << "Adresa Livrare: ";
	in >> other.adresaLivare;
	std::cout << "Nr Prajituri: ";
	in >> other.nrPrajituri;
	std::cout << "Produse: ";

	for (int i = 1;i <= other.nrPrajituri;i++)
	{
		std::cout << "Prajitura " << i << " :" << std::endl;
		in >> other.produs[i];
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, comanda& other)
{
	out << other.idComanda << " " << other.numeCumparator << " " << other.adresaLivare<<" "<<other.nrPrajituri<<std::endl;
	
	for (int i = 1;i <= other.nrPrajituri;i++)
	{
		out << other.produs[i]<<std::endl;
	}

	return out;
}


class cofetarie
{
	std::string numeCofetarie;
	std::string adresaCofetarie;
	int nrAngajati;
};

int main()
{
	prajitura p1;
	prajitura p2(10, "capsune, mere, pere", "tort");
	std::cout<<p2.getnumePrajitura()<<std::endl;
	p2.setnumePrajitura("savarina");
	std::cout<<p2.getnumePrajitura()<<std::endl;
	prajitura p3(20, "cirese", "amandina");
	prajitura p4 = p2;
	p1 = p3;
	std::cout << p4.getnumePrajitura() << std::endl;
	std::cout << p4;
	prajitura p5;
	std::cin >> p5;
	std::cout << p5;
	comanda c1;
	std::cin >> c1;
	std::cout <<"Pretul comenzii: "<<c1.pretComanda()<<std::endl;
	std::cout << c1;

	return 0;
}