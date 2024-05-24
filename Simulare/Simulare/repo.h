#pragma once
#include "domeniu.h"
#include <vector>

using std::vector;


class Repo {
	vector<Pix> lista_pixuri;

public:

	Repo(vector<Pix>& lista_pixuri) :lista_pixuri{ lista_pixuri } {};

	Repo() = default;

	virtual void store(const Pix& p);

	//get all pixuri
	virtual vector<Pix>& get_all();

};

class RepoFile : public Repo {
	string file_name;
	void load_from_file();
	void write_to_file();

public:

	RepoFile(string file_name) : Repo(), file_name{ file_name } {
		load_from_file();
	};

	void store(const Pix& p) override {
		Repo::store(p);
		write_to_file();
	}

};