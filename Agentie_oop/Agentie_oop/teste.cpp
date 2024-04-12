#include "teste.h"
#include "domeniu.h"
#include "repo.h"
#include "assert.h"
#include "validator.h"
#include "service.h"
#include <sstream>

void test_domeniu() {
	Oferta o{ "calatorie", "Maldive", "sejur", 2000 };
	assert(o.get_denumire() == "calatorie");
	assert(o.get_destinatie() == "Maldive");
	assert(o.get_tip() == "sejur");
	assert(o.get_pret() == 2000);
	o.set_denumire("vacanta");
	assert(o.get_denumire() == "vacanta");
	o.set_destinatie("Mamaia");
	assert(o.get_destinatie() == "Mamaia");
	o.set_tip("voiaj");
	assert(o.get_tip() == "voiaj");
	o.set_pret(1500);
	assert(o.get_pret() == 1500);
}

void test_cmp_denumire() {
	Oferta o1{ "calatorie", "Maldive", "sejur", 2000 };
	Oferta o2{ "vacanta", "Mamaia", "mare", 1500 };
	assert(comp_denumire(o1, o2) == 1);
	assert(comp_denumire(o2, o1) == 0);
}

void test_cmp_destinatie() {
	Oferta o1{ "calatorie", "Maldive", "sejur", 2000 };
	Oferta o2{ "vacanta", "Mamaia", "mare", 1500 };
	assert(comp_destinatie(o1, o2) == 1);
	assert(comp_destinatie(o2, o1) == 0);
}


void test_validator() {
	Oferta o{ "", "", "", -2000 };
	OfertaValidator v;
	try {
		v.valideaza(o);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("vida") >= 0);
	}
}


void test_adauga_repo() {
	OfertaRepo repo;
	repo.store(Oferta { "calatorie", "Maldive", "sejur", 2000 });

	assert(repo.getAll().size() == 1);
	try {
		repo.store(Oferta{ "calatorie", "Maldive", "vacanta", 2000 });
		assert(false);
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}
	assert(repo.getAll().size() == 1);

}

void test_sterge_repo() {
	OfertaRepo repo;
	repo.store(Oferta{ "calatorie", "Maldive", "sejur", 2000 });
	assert(repo.getAll().size() == 1);
	repo.sterge(Oferta{ "calatorie", "Maldive", "sejur", 2000 });
	assert(repo.getAll().size() == 0);
	try {
		repo.sterge(Oferta{ "calatorie", "Maldive", "vacanta", 2000 });
		assert(false);
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}
}

void test_modifica_repo() {
	OfertaRepo repo;
	repo.store(Oferta{ "calatorie", "Maldive", "sejur", 2000 });
	repo.store(Oferta{ "vacanta", "Timisoara", "sejur", 1200 });
	assert(repo.getAll().size() == 2);
	Oferta o{ "vacanta", "Timisoara", "sejur", 1200 };
	repo.modifica(o, "calatorie", "Sibiu", "vacanta", 1000);
	assert(repo.getAll()[1].get_denumire() == "calatorie");
	try {
		repo.modifica(o, "calatorie", "Sibiu", "vacanta", 1000);
		assert(false);
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}
}

void test_cauta_repo() {
	OfertaRepo repo;
	repo.store(Oferta{ "calatorie", "Maldive", "sejur", 2000 });
	repo.store(Oferta{ "vacanta", "Timisoara", "sejur", 1200 });
	assert(repo.getAll().size() == 2);
	Oferta o1{ "vacanta", "Timisoara", "sejur", 1200 };
	assert(repo.cauta("vacanta", "Timisoara") == o1);
	try {
		repo.cauta("vacanta", "Maldive");
		assert(false);
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}

}

void test_adauga_service() {
	OfertaRepo rep;
	OfertaValidator val;
	OfertaService ctr{ rep,val };
	ctr.adauga("calatorie", "Maldive", "vacanta", 2000);
	assert(ctr.getAll().size() == 1);

	//adaug ceva invalid
	try {
		ctr.adauga("", "", "", -2000);
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
	try {
		ctr.adauga("calatorie", "Maldive", "vacanta", 2000);
		assert(false);
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}

}

void test_sterge_service() {
	OfertaRepo rep;
	OfertaValidator val;
	OfertaService ctr{ rep,val };
	ctr.adauga("calatorie", "Maldive", "vacanta", 2000);
	ctr.adauga("vacanta", "Mamaia", "sejur", 2100);

	ctr.stergere(0);
	assert(ctr.getAll().size() == 1);

	try {
		ctr.stergere(2);
		assert(false);
	}
	catch (const OfertaServiceException&) {
		assert(true);
	}
}

void test_modifica_service() {
	OfertaRepo rep;
	OfertaValidator val;
	OfertaService ctr{ rep,val };
	ctr.adauga("calatorie", "Maldive", "vacanta", 2000);
	ctr.adauga("vacanta", "Mamaia", "sejur", 2100);

	ctr.modificare(0, "vacanta", "Timisoara", "sejur", 1200);
	assert(ctr.getAll()[0].get_denumire() == "vacanta");
	assert(ctr.getAll()[0].get_destinatie() == "Timisoara");
	try {
		ctr.modificare(3, "vacanta", "Timisoara", "sejur", 1200);
		assert(false);
	}
	catch (const OfertaServiceException&) {
		assert(true);
	}
}

void test_cauta_service() {
	OfertaRepo rep;
	OfertaValidator val;
	OfertaService ctr{ rep,val };
	ctr.adauga("calatorie", "Maldive", "vacanta", 2000);
	ctr.adauga("vacanta", "Mamaia", "sejur", 2100);
	Oferta o1{ "calatorie", "Maldive", "vacanta", 2000 };
	assert(ctr.cautare("calatorie", "Maldive") == o1);

	try {
		ctr.cautare("calatorie", "Mamaia");
		assert(false);
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}
}