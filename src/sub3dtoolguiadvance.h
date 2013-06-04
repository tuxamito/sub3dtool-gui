#ifndef SUB3DTOOLGUIADVANCE_H
#define SUB3DTOOLGUIADVANCE_H

#include <QWidget>

namespace Ui {
class sub3dtoolguiAdvance;
}

class sub3dtoolguiAdvance : public QWidget
{
    Q_OBJECT
    
public:
    explicit sub3dtoolguiAdvance(QWidget *parent = 0);
    ~sub3dtoolguiAdvance();
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void accept();
    void cancel();
    void reset();
    void changeColorPrimary();
    void changeColorSecondary();
    void changeColorOutline();
    void changeColorBack();

private:
    Ui::sub3dtoolguiAdvance *ui;
};

#endif // SUB3DTOOLGUIADVANCE_H
