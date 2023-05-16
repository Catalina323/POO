//facem o miniaplicatie shaormerie
//o sa avem un nr fix de oameni care pot sta la coada pt shaorma (cu object pool) x
//fiecare om poate sa aleaga unul din mai multe tipuri de shaorma din meniul shaormeriei (factory) x
//ar merge un builder pt extra chestii in shaorma (daca am timp)
//functia care adaufa chestii poate sa fie template   !! si aici sa vad daca mai merge !!
// + meniu interactiv :)

#include <iostream>
#include <vector>

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

};

//factory
class shaorma_menu {

public:
	static shaorma cu_de_toate() { return shaorma("pui", "pai", "salata", "usturoi"); }
	static shaorma vegana() { return shaorma("soia", "pai", "castraveti", "ketchup"); }
	static shaorma casei() { return shaorma("porc", "pai", "rosii", "chilli"); }
	static shaorma traditionala() { return shaorma("pui", "pai", "varza", "maioneza"); }

};

class client
{
	shaorma s;
public:
	client(shaorma s) { this->s = s; }
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
				std::cout << "5 - fa-ti propria shaorma!" << std::endl;

				int opt2;
				std::cin >> opt2;

				switch (opt2)
				{
				case 1:
				{
					client cl(shaorma_menu::cu_de_toate());
					std::cout << "Ati comandat:" << std::endl;
					shaorma_menu::cu_de_toate().afis();

					break;
				}
				case 2:
				{
					client cl(shaorma_menu::vegana());
					std::cout << "Ati comandat:" << std::endl;
					shaorma_menu::vegana().afis();
					break;
				}
				case 3:
				{
					client cl(shaorma_menu::casei());
					std::cout << "Ati comandat:" << std::endl;
					shaorma_menu::casei().afis();
					break;
				}
				case 4:
				{
					client cl(shaorma_menu::traditionala());
					std::cout << "Ati comandat:" << std::endl;
					shaorma_menu::traditionala().afis();
					break;
				}
				case 5:
				{






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
