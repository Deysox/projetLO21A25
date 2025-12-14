//
// Created by GAUTIER--BONNEAU on 13/12/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_init.h" resolved

#include "init.h"
#include "ui_init.h"
#include <QComboBox>
#include<QLineEdit>
#include <QmessageBox>


init::init(QWidget* parent) :
    QWidget(parent), ui(new Ui::init)
{
    ui->setupUi(this);
    connect(ui->spinBoxNb, QOverload<int>::of(&QSpinBox::valueChanged),this, &init::updateUInb);

    connect(ui->ButtonValidate,&QPushButton::clicked,this, &init::OnValidateclicked);

}


void init::updateUInb()
{

        //supprimons les elemetn précédents du layout :
    QLayoutItem *child;
    while ((child = ui->layouteditname->takeAt(0)) != nullptr) {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }


    int nbplayer=ui->spinBoxNb->value();
    QStringList variante;
    if (nbplayer==1)
    {
        variante={"no variant available at the moment"};
        QLabel *info=new QLabel("Quel niveau",this);
        ui->layouteditname->addWidget(info);
        spinlevel=new QSpinBox(this);
        spinlevel->setMinimum(1);
        spinlevel->setMaximum(4);
        spinlevel->setValue(1);
        ui->layouteditname->addWidget(spinlevel);

    }
    else if (nbplayer>1 && nbplayer<=4)
    {
        QList<QLineEdit*> playersEdit;
        for (int i = 0; i < nbplayer; i++) {
            QLineEdit *edit = new QLineEdit(QString("Player %1").arg(i+1), this);
            ui->layouteditname->addWidget(edit);
            playersEdit.append(edit);
        }
        variante={"version etendu", "new variante almost launch"};

    }

    BoxVariante = new QComboBox(this);
    BoxVariante->addItems(variante);
    ui->layouteditname->addWidget(BoxVariante);

}

void init::OnValidateclicked()
{
    int nbplayer=ui->spinBoxNb->value();
    QString variante=BoxVariante->currentText();
    if (nbplayer==1)
    {
        int level=spinlevel->value();
        emit init::sologameparametersReady(variante,level );
        QString message = "Nombre de joueurs : " + QString::number(level) +
                          "\nVariante : " + variante ;
        QMessageBox::information(this, "Player Turn", message);

    }else if (nbplayer>1&& nbplayer<=4){
        int myplayer=ui->spinBoxNb->value();

        QStringList names;
        for (int i = 0; i < myplayer; i++) {
            QLineEdit *edit = qobject_cast<QLineEdit*>(ui->layouteditname->itemAt(i)->widget());
            if (edit)
                names.append(edit->text());
        }
        emit init::gameparametersReady(myplayer,variante, names );//int nbPlayers, QString variante, QStringList names);
        QString message = "Nombre de joueurs : " + QString::number(nbplayer) +
                          "\nVariante : " + variante +
                          "\nNoms : " + names.join(", ");
        QMessageBox::information(this, "Player Turn", message);
    }
    this-> close();
}


init::~init()
{
    delete ui;
}