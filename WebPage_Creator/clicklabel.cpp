#include "clicklabel.h"


clicklabel::clicklabel(QWidget *parent): QLabel(parent){


}

clicklabel::~clicklabel()
{
}

void clicklabel::mouseReleaseEvent(QMouseEvent *)
{
    emit Clicked();
}

