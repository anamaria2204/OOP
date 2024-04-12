#include <functional>
#include <algorithm>
#include <assert.h>
#include "service.h"
#include <sstream>

using std::ostream;
using std::stringstream;

void OfertaService::adauga(const string& denumire, const string& destinatie, const string& tip, float pret) {
	Oferta o{ denumire, destinatie, tip, pret };
	val.valideaza(o);
	repo.store(o);
}

void OfertaService::stergere(const int pozitie) {
	const auto& oferte = repo.getAll();
	int ok = 0;
	for (int i = 0; i < oferte.size(); i++) {
		if (i == pozitie) {
			repo.sterge(oferte[i]);
			ok = 1;
		}
	}
	if (ok == 0)
		throw(OfertaServiceException("Oferta dorita nu exista in lista ofertelor existente"));

}

void OfertaService::modificare(int pozitie, const string& denumire_noua, const string& destinatie_noua,
	const string& tip_nou, const float pret_nou) {
	const auto& oferte = repo.getAll();
	int ok = 0;
	for (int i = 0; i < oferte.size(); i++) {
		if (i == pozitie) {
			repo.modifica(oferte[i], denumire_noua, destinatie_noua, tip_nou, pret_nou);
			ok = 1;
		}
	}
	if (ok == 0)
		throw(OfertaServiceException("Oferta dorita nu exista in lista ofertelor existente"));

}

const Oferta& OfertaService::cautare(const string& denumire_data, 
	const string& destinatie_data) const {
	return repo.cauta(denumire_data, destinatie_data);
}

ostream& operator<<(ostream& out, const OfertaServiceException& ex) {
	out << ex.msg;
	return out;
}
