//facem o miniaplicatie shaormerie
//o sa avem un nr fix de oameni care pot sta la coada pt shaorma (cu object pool) x
//fiecare om poate sa aleaga unul din mai multe tipuri de shaorma din meniul shaormeriei (factory) x
//ar merge un builder pt extra chestii in shaorma (daca am timp)
//functia care adaufa chestii poate sa fie template   !! si aici sa vad daca mai merge !!
// + meniu interactiv :)

#include <iostream>
#include <vector>


//object pool
class client {
private:
	bool loc = false;

public:
	void open() { loc = true; }
	void close() { loc = false; }
	bool free() const { return !loc; }
	~client() { close(); }
};

class coada {
private:
	static const int nr = 4;
	std::vector<client> vect{ nr };

public:
	client get_loc()
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
};



class shaorma {

	std::string carnita;
	std::string cartofi;
	std::string sos;
	std::string legume;

public:
	
	shaorma(std::string carnita, std::string cartofi, std::string sos, std::string legume)
	{
		this->carnita = carnita;
		this->cartofi = cartofi;
		this->legume = legume;
		this->sos = sos;
	}
};


//factory
class shaorma_menu {

public:
	static shaorma cu_de_toate() { return shaorma("pui", "pai", "salata", "usturoi"); }
	static shaorma vegana() { return shaorma("soia", "pai", "castraveti", "ketchup"); }
	static shaorma casei() { return shaorma("pui", "pai", "rosii", "chilli"); }
	static shaorma traditionala() { return shaorma("pui", "pai", "varza", "maioneza"); }

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

	


	return 0;
}