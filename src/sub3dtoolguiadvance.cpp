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
    this->modifyData();
    this->close();
}

void sub3dtoolguiAdvance::cancel()
{
    this->close();
}

void sub3dtoolguiAdvance::reset()
{
    this->setGUI();
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

struct s3tColor sub3dtoolguiAdvance::getLineEditColor(QLineEdit *line)
{
    struct s3tColor c;
    QPalette pal = line->palette();
    QColor _c = pal.color(line->backgroundRole());

    c.r = _c.red();
    c.g = _c.green();
    c.b = _c.blue();

    return c;
}

void sub3dtoolguiAdvance::setGUI()
{
    if(_data == NULL)
        return;

    this->setLineEditColor(ui->lineColorPrimary, &_data->cPrimary);
    this->setLineEditColor(ui->lineColorSecondary, &_data->cSecondary);
    this->setLineEditColor(ui->lineColorOutline, &_data->cOutline);
    this->setLineEditColor(ui->lineColorBack, &_data->cBack);

    ui->spinMarginLeft->setValue(_data->marginL);
    ui->spinMarginRight->setValue(_data->marginR);
    ui->spinMarginVertical->setValue(_data->marginV);

    ui->spinOutline->setValue(_data->outline);
    ui->spinShadow->setValue(_data->shadow);

    switch(_data->alignment)
    {
    case TL:
        ui->radioAlignTL->setChecked(true);
        break;
    case T:
        ui->radioAlignT->setChecked(true);
        break;
    case TR:
        ui->radioAlignTR->setChecked(true);
        break;
    case L:
        ui->radioAlignL->setChecked(true);
        break;
    case C:
        ui->radioAlignC->setChecked(true);
        break;
    case R:
        ui->radioAlignR->setChecked(true);
        break;
    case BL:
        ui->radioAlignBL->setChecked(true);
        break;
    case B:
        ui->radioAlignB->setChecked(true);
        break;
    case BR:
        ui->radioAlignBR->setChecked(true);
        break;
    default:
        break;
    }

    switch(_data->border)
    {
    case bShadow:
        ui->radioBorderShadow->setChecked(true);
        break;
    case bBox:
        ui->radioBorderBox->setChecked(true);
        break;
    default:
        break;
    }
}

void sub3dtoolguiAdvance::modifyData()
{
    if(_data == NULL)
        return;

    _data->cPrimary = getLineEditColor(ui->lineColorPrimary);
    _data->cSecondary = getLineEditColor(ui->lineColorSecondary);
    _data->cOutline = getLineEditColor(ui->lineColorOutline);
    _data->cBack = getLineEditColor(ui->lineColorBack);

    _data->marginL = ui->spinMarginLeft->value();
    _data->marginR = ui->spinMarginRight->value();
    _data->marginV = ui->spinMarginVertical->value();

    _data->outline = ui->spinOutline->value();
    _data->shadow = ui->spinShadow->value();

    if(ui->radioAlignTL->isChecked())
        _data->alignment = TL;
    else if(ui->radioAlignT->isChecked())
        _data->alignment = T;
    else if(ui->radioAlignTR->isChecked())
        _data->alignment = TR;
    else if(ui->radioAlignL->isChecked())
        _data->alignment = L;
    else if(ui->radioAlignC->isChecked())
        _data->alignment = C;
    else if(ui->radioAlignR->isChecked())
        _data->alignment = R;
    else if(ui->radioAlignBL->isChecked())
        _data->alignment = BL;
    else if(ui->radioAlignB->isChecked())
        _data->alignment = B;
    else if(ui->radioAlignBR->isChecked())
        _data->alignment = BR;

    if(ui->radioBorderShadow->isChecked())
        _data->border = bShadow;
    else if(ui->radioBorderBox->isChecked())
        _data->border = bBox;
}
