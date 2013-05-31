#ifndef SUB3DTOOLGUI_H
#define SUB3DTOOLGUI_H

#include <QWidget>

namespace Ui {
class sub3dtoolgui;
}

class sub3dtoolgui : public QWidget
{
    Q_OBJECT
    
public:
    explicit sub3dtoolgui(QWidget *parent = 0);
    ~sub3dtoolgui();

private slots:
    void getFileIn();
    void getFileOut();
    void change3DModeSBS();
    void change3DModeTB();
    void change3DModeN3D();

private:
    Ui::sub3dtoolgui *ui;

    int checkTool();
    void initGui(bool toolFound);
};

#endif // SUB3DTOOLGUI_H
