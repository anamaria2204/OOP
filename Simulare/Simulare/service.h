#pragma once
#include "repo.h"

class Service {
	Repo& rep;

public:
	Service(Repo& rep) : rep{ rep } {};

	vector<Pix>& get_all() {
		return rep.get_all();
	}

	vector<Pix> sorteaza_brand();

	vector<Pix> sorteaza_pret();
	
};