//facem o miniaplicatie shaormerie
//o sa avem un nr fix de oameni care pot sta la coada pt shaorma (cu object pool) x
//fiecare om poate sa aleaga unul din mai multe tipuri de shaorma din meniul shaormeriei (factory) x
//ar merge un builder pt extra chestii in shaorma (daca am timp)
//functia care adaufa chestii poate sa fie template   !! si aici sa vad daca mai merge !!
// + meniu interactiv :)

#include <iostream>
#include <vector>
#include<memory>

//object pool
class loc_coada {
private:
	bool loc = false;

public:
	void open() { loc = true; }
	void close() { loc = false; }
	bool free() const { return !loc; }
	~loc_coada() { close(); }
};

class coada {
private:
	static const int nr = 4;
	std::vector<loc_coada> vect{ nr };

public:
	loc_coada& get_loc()
	{
		for (auto& l : vect)
		{
			if (l.free())
			{
				l.open();
				return l;
			}
		}
		throw std::runtime_error("prea multi oameni la coada! asteptati pana se elibereaza un loc!");
	}

	loc_coada& give_loc()
	{
		for (auto& l : vect)
		{
			if (!(l.free()))
			{
				l.close();
				return l;
			}
		}
	}
};


class shaorma {

	std::string carnita;
	std::string cartofi;
	std::string sos;
	std::string legume;

public:

	shaorma() = default;
	~shaorma() { /*std::cout << "destructor shaorma" << std::endl;*/ }
	shaorma(std::string carnita, std::string cartofi, std::string sos, std::string legume)
	{
		this->carnita = carnita;
		this->cartofi = cartofi;
		this->legume = legume;
		this->sos = sos;
	}

	void afis()
	{
		std::cout << "shaorma cu carne de " << carnita << ", cartofi " << cartofi << ", " << legume << " si " << sos;
		std::cout << std::endl;
	}

	
	shaorma& operator=(const shaorma& other)
	{
		carnita=other.carnita;
		cartofi = other.cartofi;
		legume = other.legume;
		sos = other.sos;
		return *this;
	}

};

//factory
class shaorma_menu {

public:
	static shaorma cu_de_toate() { return shaorma("pui", "pai", "salata", "usturoi"); }
	static shaorma vegana() { return shaorma("soia", "pai", "castraveti", "ketchup"); }
	static shaorma casei() { return shaorma("porc", "pai", "rosii", "chilli"); }
	static shaorma traditionala() { return shaorma("pui", "pai", "varza", "maioneza"); }

	~shaorma_menu() { /*std::cout << "destructor shaorma menu" << std::endl;*/ }
};

class paste {
	std::string pasta;
	std::string sos;
public:
	paste() = default;
	~paste() { /*std::cout << "destructor paste" << std::endl;*/ }
	paste(std::string p , std::string s)
	{
		pasta = p;
		sos = s;
	}
	void afis()
	{
		std::cout << pasta << " cu sos de " << sos << std::endl;
	}

};

//factory
class paste_menu {

public:
	static paste spaghete() { return paste("spaghete", "rosii"); };
	static paste pene() { return paste("pene", "parmezan"); }

	~paste_menu() { /*std::cout << "destructor paste menu" << std::endl;*/ }
};


template <typename tip_produs>
class client
{
	std::vector<tip_produs> v;

public:
	

	client(tip_produs p)
	{ 
		this->p = p; 
		
	}
	client() {  };
	
	void cumpara(tip_produs p)
	{
		v.push_back(p);
	}

};



int main()
{
	std::cout << "Buna ziua! :)" << std::endl << "Alegeti shaormeria de unde doriti sa comandati!" << std::endl;
	std::cout << "1 - Dristor" << std::endl;
	std::cout << "2 - Socului" << std::endl;
	std::cout << "3 - Baneasa" << std::endl;
	std::cout << "4 - C&A" << std::endl;
	std::cout << "5 - Shaorma de la Lidl" << std::endl;
	std::cout << "6 - La grasi" << std::endl;

	int n;
	
	bool ok = true;

	//aici alegem shaormeria de unde vrem sa cumparam
	while (ok)
	{
		try {
			std::cin >> n;

			switch (n)
			{
			case 1:
			{
				std::cout << "Bine ati venit la Shaormeria Dristor!" << std::endl;
				ok = false;
				break;
			}
			case 2:
			{
				std::cout << "Bine ati venit la Shaormeria Socului!" << std::endl;
				ok = false;
				break;
			}
			case 3:
			{
				std::cout << "Bine ati venit la Shaormeria Baneasa!" << std::endl;
				ok = false;
				break;
			}
			case 4:
			{
				std::cout << "Bine ati venit la Shaormeria C&A!" << std::endl;
				ok = false;
				break;
			}
			case 5:
			{
				std::cout << "Bine ati venit la raionul cu shaorma de la Lidl!" << std::endl;
				ok = false;
				break;
			}
			case 6:
			{
				std::cout << "Bine ati venit la Shaormeria La grasi!" << std::endl;
				ok = false;
				break;
			}
			default:
			{
				throw std::invalid_argument("Introduceti doar '1' '2' '3' '4' '5' sau '6'");
				break;
			}
			}
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}


	coada c;
	while (true)
	{
		std::cout << "ce doriti sa faceti in continuare?" << std::endl;
		std::cout << "1 - plasati o comanda" << std::endl;
		std::cout << "2 - asteptati pana cand se elibereaza un loc" << std::endl;
		std::cout << "3 - iesire" << std::endl;
		int opt;

		try {
			std::cin >> opt;

			switch (opt)
			{//cazul 1 plasam o comanda
			case 1:
			{try
			{
				loc_coada& x = c.get_loc();

				std::cout << "Meniul nostru:" << std::endl;
				std::cout << "1 - shaorma cu de toate" << std::endl;
				std::cout << "2 - shaorma vegana" << std::endl;
				std::cout << "3 - shaorma casei" << std::endl;
				std::cout << "4 - shaorma traditionala" << std::endl;
				std::cout << "5 - spaghete" << std::endl;
				std::cout << "6 - pene" << std::endl;

				int opt2;
				std::cin >> opt2;

				switch (opt2)
				{
				case 1:
				{
					client<shaorma> cl;
					shaorma_menu sm;
					shaorma s;

					s = sm.cu_de_toate();
					cl.cumpara(s);
					std::cout << "Ati comandat: ";
					shaorma_menu::cu_de_toate().afis();

					break;
				}
				case 2:
				{
					client<shaorma> cl;
					shaorma_menu sm;
					shaorma s;
					s = sm.vegana();
					cl.cumpara(s);
					std::cout << "Ati comandat: " ;
					shaorma_menu::vegana().afis();
					break;
				}
				case 3:
				{
					client<shaorma> cl;
					shaorma_menu sm;
					shaorma s;
					s = sm.casei();
					cl.cumpara(s);
					std::cout << "Ati comandat: " ;
					shaorma_menu::casei().afis();
					break;
				}
				case 4:
				{
					client<shaorma> cl;
					shaorma_menu sm;
					shaorma s;
					s = sm.traditionala();
					cl.cumpara(s);
					std::cout << "Ati comandat: " ;
					shaorma_menu::traditionala().afis();
					break;
				}
				case 5:
				{
					client<paste> cl;
					paste_menu pm;
					paste p;
					p = pm.spaghete();
					cl.cumpara(p);
					std::cout << "Ati comandat: " ;
					paste_menu::spaghete().afis();
					break;
				}
				case 6:
				{
					client<paste> cl;
					paste_menu pm;
					paste p;
					p = pm.pene();
					cl.cumpara(p);
					std::cout << "Ati comandat: " ;
					paste_menu::pene().afis();
					break;
				}
				default:
					break;
				}
			}
			catch (std::runtime_error& e) { std::cout << e.what() << std::endl; }
			break;
			}
			//cazul 2 pleaca cineva din shaormerie
			case 2:
			{
				std::cout << "Cineva si-a ridicat comanda. S-a eliberat un loc in shaormerie :)" << std::endl;
				loc_coada& x = c.give_loc();

				break;
			}
			//cazul 3 iesire
			case 3:
			{
				return 0;
			}
			//cazul default
			default:
				throw std::invalid_argument("Introduceti doar '1' sau '2'");
				break;
			}

		}
		catch (std::invalid_argument& e)
		{
			std::cerr << "Error " << e.what() << std::endl;
		}
	}
	


	return 0;
}
