#include "teste.h"
#include <assert.h>

void test_domeniu() {
	Pix p1{ "BIC","albastru", 10 };
	assert(p1.get_brand() == "BIC");
	assert(p1.get_culoare() == "albastru");
	assert(p1.get_pret() == 10);
	Pix p2{ "Faber castel", "rosu", 12 };
	assert(cmp_brand(p1, p2) == 1);
	assert(cmp_brand(p2, p1) == 0);
	assert(cmp_pret(p1, p2) == 0);
	assert(cmp_pret(p2, p1) == 1);
}

void test_repo() {
	vector<Pix> pixuri;
	Repo rep{ pixuri };
	RepoFile repo { "teste_repo.txt" };
	Pix p1{ "BIC","albastru", 10 };
	Pix p2{ "Faber castel", "rosu", 12 };
	repo.store(p1);
	repo.store(p2);
	assert(repo.get_all().size() == 2);
}

void test_service() {
	vector<Pix> pixuri;
	Repo rep{ pixuri };
	RepoFile repo{ "teste_service.txt" };
	Service serv{ repo };
	Pix p1{ "BIC","albastru", 10 };
	Pix p2{ "Faber castel", "rosu", 12 };
	repo.store(p1);
	repo.store(p2);
	assert(serv.get_all().size() == 2);
	auto rez = serv.sorteaza_brand();
	assert(rez[0].get_brand() == "BIC");
	auto rez_p = serv.sorteaza_pret();
	assert(rez_p[0].get_brand() == "Faber castel");
}