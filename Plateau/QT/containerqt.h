//
// Created by barnab on 17/12/2025.
//

#ifndef AKROPOLIS_CONTAINER_H
#define AKROPOLIS_CONTAINER_H
#include <QWidget>

namespace Barnabe {
    class ContainerQt : public QWidget {
    protected:
        int size;
    public:
        ContainerQt(QWidget* parent, int s = 40) : QWidget(parent), size(s) {


        }
        virtual ~ContainerQt() = default;
        ContainerQt(const ContainerQt&) = delete;
        ContainerQt& operator=(const ContainerQt&) = delete;

        void updateDisplay() {empty(); draw(); update();}

        virtual void draw() = 0;
        virtual void empty() = 0;

    };
}

#endif //AKROPOLIS_CONTAINER_H
