//
// Created by GAUTIER--BONNEAU on 13/12/2025.
//

#ifndef UNTITLED_INIT_H
#define UNTITLED_INIT_H

#include <QWidget>
#include <QComboBox>
#include <QSpinBox>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class init;
}

QT_END_NAMESPACE

class init : public QWidget
{
    Q_OBJECT

public:
    explicit init(QWidget* parent = nullptr);
    ~init() override;

private:
    Ui::init* ui;
    QComboBox *BoxVariante;
    QSpinBox *spinlevel;
    signals :

    void gameparametersReady(int nbPlayers, QString variante, QStringList names );//au clic
    void sologameparametersReady(QString Variante, int level);

private slots :
void updateUInb();
    void OnValidateclicked();


};


#endif //UNTITLED_INIT_H