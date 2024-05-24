#include "Simulare.h"
#include <QtWidgets/QApplication>
#include "teste.h"

void testAll() {
    test_domeniu();
    test_repo();
    test_service();
}

int main(int argc, char *argv[])
{
    testAll();

    QApplication a(argc, argv);
    vector<Pix> pixuri;
    Repo rep{ pixuri };
    RepoFile repo{ "pixuri.txt" };
    Service serv{ repo };
    Simulare app{ serv };

    app.show();
    return a.exec();
}
