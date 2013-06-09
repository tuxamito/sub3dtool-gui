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

#ifndef SUB3DTOOLGUI_H
#define SUB3DTOOLGUI_H

#include <QWidget>

#include "s3tdata.h"

namespace Ui {
class sub3dtoolgui;
}

class sub3dtoolgui : public QWidget
{
    Q_OBJECT
    
public:
    explicit sub3dtoolgui(QWidget *parent = 0);
    ~sub3dtoolgui();
    void init();

private slots:
    void getFileIn();
    void getFileOut();
    void change3DModeSBS();
    void change3DModeTB();
    void change3DModeN3D();
    void convert();
    void filesChangedIn();
    void filesChangedOut();
    void setFontSize(QString size);
    void setResolution(QString resolution);
    void setFont(QString font);
    void showAbout();
    void showAdvance();
    void exit();

signals:
    void closeProgram();
    void newStatus(QString);

private:
    Ui::sub3dtoolgui *ui;

    int checkTool();
    void initGui();
    int subtitleConvert(QString inFile, QString outFile, s3tData data);

    bool _isStarted;
    s3tData _data;
    bool _toolFound;
    QFont _fontBold;
    QFont _fontNotBold;

    QString _inFile;
    QString _outFile;
};

#endif // SUB3DTOOLGUI_H
