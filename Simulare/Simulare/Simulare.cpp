#include "Simulare.h"
#include <string>

using std::to_string;

void Simulare::initgui() {

	this->setWindowTitle("Aplicatie ~ firma pixuri");

	QHBoxLayout* main_ly = new QHBoxLayout;
	setLayout(main_ly);

	//list layout
	QVBoxLayout* list_ly = new QVBoxLayout;
	main_ly->addLayout(list_ly);

	QLabel* list_lbl = new QLabel{ "Lista de pixuri" };
	list_lbl->setAlignment(Qt::AlignCenter);

	list_ly->addWidget(list_lbl);
	list_ly->addWidget(lista_pixuri);

	vector<Pix>& pixuri = serv.get_all();
	load_list(pixuri);

	//layout operatii
	QVBoxLayout* op_ly = new QVBoxLayout;
	QFormLayout* formly = new QFormLayout;

	formly->addRow(new QLabel{ "Brand: " }, txt_brand);
	formly->addRow(new QLabel{ "Culoare: " }, txt_culoare);
	formly->addRow(new QLabel{ "Pret:" }, txt_pret);

	op_ly->addLayout(formly);

	QLabel* sort_lbl = new QLabel{ "Tipuri de sortare" };
	sort_lbl->setAlignment(Qt::AlignCenter);
	op_ly->addWidget(sort_lbl);

	QHBoxLayout* sort_ly = new QHBoxLayout;
	sort_ly->addWidget(btn_sort_b);
	sort_ly->addWidget(btn_sort_p);
	sort_ly->addWidget(btn_nesort);
	op_ly->addLayout(sort_ly);

	main_ly->addLayout(op_ly);

}

void Simulare::sorteaza_brand() {
	vector<Pix> pixuri = serv.sorteaza_brand();
	load_list(pixuri);
}

void Simulare::sorteaza_pret() {
	vector<Pix> pixuri = serv.sorteaza_pret();
	load_list(pixuri);
}

void Simulare::nesortate() {
	load_list(serv.get_all());
}

void Simulare::load_list(vector<Pix>& pixuri) {
	lista_pixuri->clear();
	for (const auto& p : pixuri) {
		float pret = p.get_pret();
		string pret_s = to_string(pret);
		lista_pixuri->addItem(QString::fromStdString(p.get_brand() + " " + pret_s + "\n"));
	}

}

void Simulare::connectsignals() {
	QObject::connect(btn_sort_b, &QPushButton::clicked, this, &Simulare::sorteaza_brand);
	QObject::connect(btn_sort_p, &QPushButton::clicked, this, &Simulare::sorteaza_pret);
	QObject::connect(btn_nesort, &QPushButton::clicked, this, &Simulare::nesortate);
}
