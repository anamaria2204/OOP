#include "domeniu.h"

const string Pix::get_brand() const {
	return brand;
}

const string Pix::get_culoare() const {
	return culoare;
}

float Pix::get_pret() const {
	return pret;
}

bool cmp_brand(Pix& p1, Pix& p2) {
	return p1.get_brand() < p2.get_brand();
}

bool cmp_pret(Pix& p1, Pix& p2) {
	return p1.get_pret() > p2.get_pret();
}