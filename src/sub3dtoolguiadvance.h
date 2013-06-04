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

#ifndef SUB3DTOOLGUIADVANCE_H
#define SUB3DTOOLGUIADVANCE_H

#include <QWidget>
#include <QLineEdit>

#include "s3tdata.h"

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

    void shareData(s3tData *data);

private slots:
    void accept();
    void cancel();
    void reset();
    void changeColorPrimary();
    void changeColorSecondary();
    void changeColorOutline();
    void changeColorBack();

private:
    void setGUI();
    void modifyData();
    void setLineEditColor(QLineEdit *line, struct s3tColor *color);
    struct s3tColor getLineEditColor(QLineEdit *line);

    Ui::sub3dtoolguiAdvance *ui;

    s3tData *_data;
};

#endif // SUB3DTOOLGUIADVANCE_H
