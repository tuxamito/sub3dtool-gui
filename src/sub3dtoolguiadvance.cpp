#include "sub3dtoolguiadvance.h"
#include "ui_sub3dtoolguiadvance.h"

#include <QColorDialog>

sub3dtoolguiAdvance::sub3dtoolguiAdvance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sub3dtoolguiAdvance)
{
    ui->setupUi(this);

    ui->lineColorPrimary->installEventFilter(this);
    ui->lineColorSecondary->installEventFilter(this);
    ui->lineColorOutline->installEventFilter(this);
    ui->lineColorBack->installEventFilter(this);

    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
}

sub3dtoolguiAdvance::~sub3dtoolguiAdvance()
{
    delete ui;
}

void sub3dtoolguiAdvance::accept()
{
    this->close();
}

void sub3dtoolguiAdvance::cancel()
{
    this->close();
}

void sub3dtoolguiAdvance::reset()
{

}

void sub3dtoolguiAdvance::changeColorPrimary()
{
    QColorDialog nc;
    QColor c;
    c = nc.getColor();

    if(c.isValid())
    {
        QPalette pal = ui->lineColorPrimary->palette();
        pal.setColor(ui->lineColorPrimary->backgroundRole(), c);
        ui->lineColorPrimary->setPalette(pal);
    }
}

void sub3dtoolguiAdvance::changeColorSecondary()
{
    QColorDialog nc;
    QColor c;
    c = nc.getColor();

    if(c.isValid())
    {
        QPalette pal = ui->lineColorSecondary->palette();
        pal.setColor(ui->lineColorSecondary->backgroundRole(), c);
        ui->lineColorSecondary->setPalette(pal);
    }
}

void sub3dtoolguiAdvance::changeColorOutline()
{
    QColorDialog nc;
    QColor c;
    c = nc.getColor();

    if(c.isValid())
    {
        QPalette pal = ui->lineColorOutline->palette();
        pal.setColor(ui->lineColorOutline->backgroundRole(), c);
        ui->lineColorOutline->setPalette(pal);
    }
}

void sub3dtoolguiAdvance::changeColorBack()
{
    QColorDialog nc;
    QColor c;
    c = nc.getColor();

    if(c.isValid())
    {
        QPalette pal = ui->lineColorBack->palette();
        pal.setColor(ui->lineColorBack->backgroundRole(), c);
        ui->lineColorBack->setPalette(pal);
    }
}

bool sub3dtoolguiAdvance::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->lineColorPrimary) {
        if(event->type() == QEvent::MouseButtonDblClick) {
            this->changeColorPrimary();
            return true;
        } else {
            return false;
        }
    } else if(obj == ui->lineColorSecondary) {
        if(event->type() == QEvent::MouseButtonDblClick) {
            this->changeColorSecondary();
            return true;
        } else {
            return false;
        }
    } else if(obj == ui->lineColorOutline) {
        if(event->type() == QEvent::MouseButtonDblClick) {
            this->changeColorOutline();
            return true;
        } else {
            return false;
        }
    } else if(obj == ui->lineColorBack) {
        if(event->type() == QEvent::MouseButtonDblClick) {
            this->changeColorBack();
            return true;
        } else {
            return false;
        }
    } else {
        // pass the event on to the parent class
        return this->parent()->eventFilter(obj, event);
    }
}
