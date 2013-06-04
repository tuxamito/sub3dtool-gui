/****************************************************************************/
/*  Copyright (C) 2013 Daniel Rubio Bonilla <danielrubiob_at_gmail_._com>   */
/*                                                                          */
/*  This file is part of sub3dtool-gui.                                     */
/*                                                                          */
/*  sub3dtool-gui is free software: you can redistribute it and/or modify   */
/*  it under the terms of the GNU General Public License as published by    */
/*  the Free Software Foundation, either version 3 of the License, or       */
/*  (at your option) any later version.                                     */
/*                                                                          */
/*  sub3dtool-gui is distributed in the hope that it will be useful,        */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            */
/*  GNU General Public License for more details.                            */
/*                                                                          */
/*  You should have received a copy of the GNU General Public License       */
/*  along with sub3dtool-gui. If not, see <http://www.gnu.org/licenses/>.   */
/****************************************************************************/

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

    _data = NULL;

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
    c = nc.getColor(QColor(_data->cPrimary.r, _data->cPrimary.g, _data->cPrimary.b));

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
    c = nc.getColor(QColor(_data->cSecondary.r, _data->cSecondary.g, _data->cSecondary.b));

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
    c = nc.getColor(QColor(_data->cOutline.r, _data->cOutline.g, _data->cOutline.b));

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
    c = nc.getColor(QColor(_data->cBack.r, _data->cBack.g, _data->cBack.b));

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

void sub3dtoolguiAdvance::shareData(s3tData *data)
{
    _data = data;

    this->setGUI();
}

void sub3dtoolguiAdvance::setLineEditColor(QLineEdit *line, struct s3tColor *color)
{
    QColor c(color->r, color->g, color->b);
    QPalette pal = line->palette();
    pal.setColor(line->backgroundRole(), c);
    line->setPalette(pal);
}

void sub3dtoolguiAdvance::setGUI()
{
    this->setLineEditColor(ui->lineColorPrimary, &_data->cPrimary);
    this->setLineEditColor(ui->lineColorSecondary, &_data->cSecondary);
    this->setLineEditColor(ui->lineColorOutline, &_data->cOutline);
    this->setLineEditColor(ui->lineColorBack, &_data->cBack);
}
