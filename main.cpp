#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>


using namespace Qt;




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget *mainWindow         = new QWidget();

    mainWindow->setGeometry(200, 200, 500, 200);
    mainWindow->setWindowTitle("QT Mariadb App");

    QGridLayout *gridLayout     = new QGridLayout();

    QLabel  *id                 = new QLabel("#");
    QLabel  *fname              = new QLabel("First Name");
    QLabel  *lname              = new QLabel("Last Name");
    QLabel  *age                = new QLabel("Age");

    gridLayout->addWidget(id,           0, 0, 1, 1, AlignCenter);
    gridLayout->addWidget(fname,        0, 1, 1, 1, AlignCenter);
    gridLayout->addWidget(lname,        0, 2, 1, 1, AlignCenter);
    gridLayout->addWidget(age,          0, 3, 1, 1, AlignCenter);



    QSqlDatabase *db            = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL")); // use mysql database

    db->setHostName("localhost");
    db->setUserName("test");
    db->setPassword("!#@$qwerty");
    db->setDatabaseName("testdb");

    int opened                  = db->open();

    if(opened)
    {
        QSqlQuery *query        = new QSqlQuery();
        query->exec("SELECT * FROM users");

        int ii = 1;

        while(query->next())
        {
            for(int i = 0; i < query->size(); i++)
            {
                QLabel *sample      = new QLabel(query->value(i).toString());

                gridLayout->addWidget(sample, ii, i, 1, 1, AlignCenter);
            }

            ii++;
        }
    }





    mainWindow->setLayout(gridLayout);
    mainWindow->show();




    return a.exec();
}
