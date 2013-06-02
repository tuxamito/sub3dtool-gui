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

#include "sub3dtoolgui.h"
#include "ui_sub3dtoolgui.h"

#include <QProcess>
#include <QMessageBox>
#include <QFileDialog>

#define SUB3DTOOLNAME "sub3dtool"
#define MYNAME "sub3dtool-gui"
#define VERSION "0.0.0"

sub3dtoolgui::sub3dtoolgui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sub3dtoolgui)
{
    _isStarted = false;

    ui->setupUi(this);

    _toolFound = (this->checkTool() >= 0);

    if(!_toolFound)
        QMessageBox::critical(this, MYNAME, tr("No sub3dtool command found"));

    this->initGui();

    _isStarted = true;
}

sub3dtoolgui::~sub3dtoolgui()
{
    delete ui;
}

int sub3dtoolgui::checkTool()
{
    QProcess tool;
    tool.start(SUB3DTOOLNAME, QStringList());

    if (!tool.waitForStarted())
        return -2;

    if (!tool.waitForFinished())
        return -3;

    return 0;
}

void sub3dtoolgui::initGui()
{
    ui->buttonConvert->setEnabled(_toolFound);
    if(_toolFound)
        ui->labelInfo->setText(QString(SUB3DTOOLNAME) + QString(" ") + tr("found"));
    else
        ui->labelInfo->setText(QString(SUB3DTOOLNAME) + QString(" ") + tr("not found"));

    ui->lineEditFileIn->setText(_data.inFile);
    ui->lineEditFileOut->setText(_data.outFile);

    switch(_data.transformation3d)
    {
    case N3D:
        ui->button3DSBS->setChecked(false);
        ui->button3DTB->setChecked(false);
        ui->button3DN3D->setChecked(true);
        break;
    case SBS:
        ui->button3DSBS->setChecked(true);
        ui->button3DTB->setChecked(false);
        ui->button3DN3D->setChecked(false);
        break;
    case TB:
        ui->button3DSBS->setChecked(false);
        ui->button3DTB->setChecked(true);
        ui->button3DN3D->setChecked(false);
        break;
    }

    QStringList resolutions;
    resolutions << "3840x2160" <<"1920x1080" << "1280x720" << "720x576" << "720x480";
    ui->comboResolution->addItems(resolutions);
    ui->comboResolution->setCurrentIndex(ui->comboResolution->findText(_data.resolution));

    QStringList fontSizes;
    fontSizes << "144" << "118" << "96" << "78" << "64" << "52" << "42" << "34"
              << "28" << "24" << "18" << "14";
    ui->comboFontSize->addItems(fontSizes);
    ui->comboFontSize->setCurrentIndex(ui->comboFontSize->findText(QString::number(_data.fontSize)));

    ui->fontComboBox->setCurrentIndex(ui->fontComboBox->findText(_data.font));
}

void sub3dtoolgui::filesChanged()
{
    _data.inFile = ui->lineEditFileIn->text();
    _data.outFile = ui->lineEditFileOut->text();
}

void sub3dtoolgui::getFileIn()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Original Subtitles"), ui->lineEditFileIn->text(),
                                                    tr("All Subtitles (*.srt *.ass *.ssa);;SubRip Subtitles (*.srt);;SubStation Alpha Subtitles(*.ass *.ssa);;All Files(*.*)"));

    if(fileName != "")
        ui->lineEditFileIn->setText(fileName);
}

void sub3dtoolgui::getFileOut()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Converted Subtitles"), ui->lineEditFileOut->text(),
                                                    tr("All Subtitles (*.srt *.ass *.ssa);;SubRip Subtitles (*.srt);;SubStation Alpha Subtitles(*.ass *.ssa);;All Files(*.*)"));

    if(fileName != "")
        ui->lineEditFileOut->setText(fileName);
}

void sub3dtoolgui::change3DModeSBS()
{
    _data.transformation3d = SBS;
    ui->button3DTB->setChecked(false);
    ui->button3DN3D->setChecked(false);
}

void sub3dtoolgui::change3DModeTB()
{
    _data.transformation3d = TB;
    ui->button3DSBS->setChecked(false);
    ui->button3DN3D->setChecked(false);
}

void sub3dtoolgui::change3DModeN3D()
{
    _data.transformation3d = N3D;
    ui->button3DSBS->setChecked(false);
    ui->button3DTB->setChecked(false);
}

void sub3dtoolgui::setFontSize(QString size)
{
    if(_isStarted)
        _data.fontSize = size.toInt();
}

void sub3dtoolgui::setResolution(QString resolution)
{
    if(_isStarted)
        _data.resolution = resolution;
}

void sub3dtoolgui::setFont(QString font)
{
    if(_isStarted)
        _data.font = font;
}

void sub3dtoolgui::convert()
{
    QProcess tool;
    QStringList arguments;

    switch(_data.transformation3d)
    {
    case N3D:
        arguments << "--no3d";
        break;
    case SBS:
        arguments << "--3dsbs";
        break;
    case TB:
        arguments << "--3dtb";
        break;
    }

    arguments << "--screen";
    arguments << _data.resolution;
    arguments << "--font";
    arguments << _data.font;
    arguments << "--fontsize";
    arguments << QString::number(_data.fontSize);

    arguments << "-o";
    arguments << _data.outFile;
    arguments << _data.inFile;

    tool.start(SUB3DTOOLNAME, arguments);

    if (!tool.waitForStarted())
    {
        QMessageBox::critical(this, MYNAME, tr("ERROR starting the tool"));
        return;
    }


    if (!tool.waitForFinished())
    {
        QMessageBox::critical(this, MYNAME, tr("ERROR executing the tool"));
        return;
    }

    int code = tool.exitCode();

    if(code)
        QMessageBox::critical(this, MYNAME, tr("ERROR tool reported error: %1").arg(QString::number(code)));
    else
        QMessageBox::information(this, MYNAME, tr("Subtitles converted"));
}

void sub3dtoolgui::showAbout()
{
    QString str;
    str = QString("%1 %2\n(c) Daniel Rubio Bonilla\n<danielrubiob@gmail.com>\nGPL v3").arg(MYNAME).arg(VERSION);
    QMessageBox::about(this, MYNAME, str);
}
