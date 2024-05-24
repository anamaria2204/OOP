#pragma once
#include <string>

using std::string;

class Pix {

private:
	string brand;
	string culoare;
	float pret;

public:

	Pix(string brand, string culoare, float pret) : brand{ brand }, culoare{ culoare }, pret{ pret } {};

	Pix() = default;

	//getters

	const string get_brand() const;
	const string get_culoare() const;
	float get_pret() const;
};

bool cmp_brand(Pix& p1, Pix& p2);
bool cmp_pret(Pix& p1, Pix& p2);