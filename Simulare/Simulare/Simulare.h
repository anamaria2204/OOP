#pragma once
#include <qmainwindow.h>
#include <qpushbutton.h>
#include <qwindow.h>
#include <qline.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qboxlayout.h>
#include "service.h"
#include <qlineedit.h>
#include <qformlayout.h>
#include <qdebug.h>
#include <qlistwidget.h>

class Simulare : public QWidget
{

private:

	Service& serv;
	
	QListWidget* lista_pixuri = new QListWidget;

	QPushButton* btn_sort_b = new QPushButton{ "Sorteaza brand" };
	QPushButton* btn_sort_p = new QPushButton{ "Sorteza pret" };
	QPushButton* btn_nesort = new QPushButton{ "Nesortate" };

	QLineEdit* txt_brand = new QLineEdit;
	QLineEdit* txt_culoare = new QLineEdit;
	QLineEdit* txt_pret = new QLineEdit;

	void initgui();
	void connectsignals();
	void load_list(vector<Pix>& pixuri);
	void sorteaza_brand();
	void sorteaza_pret();
	void nesortate();


public:
	Simulare(Service& serv) : serv{ serv } {
		initgui();
		connectsignals();
	}
};
