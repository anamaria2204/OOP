#include "service.h"
#include <algorithm>

using std::sort;

vector<Pix> Service::sorteaza_brand() {
	auto copie = rep.get_all();
	sort(copie.begin(), copie.end(), cmp_brand);
	return copie;
}

vector<Pix> Service::sorteaza_pret() {
	auto copie = rep.get_all();
	sort(copie.begin(), copie.end(), cmp_pret);
	return copie;
}
