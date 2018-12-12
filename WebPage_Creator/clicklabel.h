#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include <QWidget>

class clicklabel : public QLabel
{
    Q_OBJECT

public:
    clicklabel(QWidget *parent=0);
    ~clicklabel();

signals:
     void Clicked();

protected:
    void mouseReleaseEvent( QMouseEvent* );



};

#endif // CLICKLABEL_H
