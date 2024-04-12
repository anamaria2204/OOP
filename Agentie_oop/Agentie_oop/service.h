#pragma once

#include "domeniu.h"
#include "repo.h"
#include <string>
#include <vector>

#include <functional>
#include "validator.h"

using std::vector;
using std::function;

class OfertaService {
	OfertaRepo& repo;
	OfertaValidator& val;

public:
	OfertaService(OfertaRepo& repo, OfertaValidator& val) :repo{ repo }, val{ val } {
	}
	//nu permitem copierea de obiecte PetStore
	OfertaService(const OfertaService& ot) = delete;
	/*
	 returneaza toate ofertele in ordinea in care au fost adaugate
	*/
	const vector<Oferta>& getAll() noexcept {
		return repo.getAll();
	}
	/*
	Adauga o noua oferta
	arunca exceptie daca: nu se poate salva, nu este valid
	*/
	void adauga(const string& denumire, const string& destinatie, const string& tip, float pret);

	/*
	Sterge o oferta din lista
	arunca exceptie daca oferta nu este in lista
	*/

	void stergere(const int pozitie);

	/*
	Modifica o oferta din lista de oferte
	arunca exceptie daca oferta nu este in lista 
	*/
	void modificare(int pozitie, const string& denumire_noua, const string& destinatie_noua,
		const string& tip_nou, const float pret_nou);

	/*
	Cauta o oferta in lista de oferte
	arunca exceptie daca oferta nu este in lista
	*/
	const Oferta& cautare(const string& denumire_data, const string& destinatie_data) const;

};

class OfertaServiceException {
	string msg;
public:
	OfertaServiceException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const OfertaServiceException& ex);
};

ostream& operator<<(ostream& out, const OfertaServiceException& ex);
