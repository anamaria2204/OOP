#include "repo.h"
#include <fstream>
#include <exception>

using std::ifstream;
using std::ofstream;
using std::exception;

void Repo::store(const Pix& h) {
	if(h.get_brand() != "" && h.get_culoare() != "" && h.get_pret() > 0)
	lista_pixuri.push_back(h);
}

vector<Pix>& Repo::get_all() {
	return lista_pixuri;
}

void RepoFile::load_from_file() {
	ifstream in(file_name);
	if (!in.is_open()) {
		throw exception();
	}
	while (!in.eof()) {
		string brand;
		in >> brand;
		string culoare;
		in >> culoare;
		float pret;
		in >> pret;
		Pix p{ brand.c_str(), culoare.c_str(), pret };
		Repo::store(p);
		if (in.eof()) {
			break;
		}
	}
	in.close();
}

void RepoFile::write_to_file() {
	ofstream out(file_name);
	if (!out.is_open())
		throw exception();
	for (auto p : get_all()) {
		if (p.get_brand() != "" && p.get_culoare() != "" && p.get_pret() > 0) {
			out << p.get_brand() << " "
				<< p.get_culoare() << " "
				<< p.get_pret() << "\n";
		}
	}
	out.close();
}