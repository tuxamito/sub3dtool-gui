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
#include <QDirIterator>
#include <QDebug>

#include "sub3dtoolguiadvance.h"

#define SUB3DTOOLNAME "sub3dtool"
#define MYNAME "sub3dtool-gui"

#define VERSION "0.1.82"
#define DATE "27.06.2013"

sub3dtoolgui::sub3dtoolgui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sub3dtoolgui)
{
    _isStarted = false;

    ui->setupUi(this);

    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    ui->table->hideColumn(0);
    this->updateFileTable();

    _fi = 0;
}

sub3dtoolgui::~sub3dtoolgui()
{
    delete ui;
}

void sub3dtoolgui::init()
{
    _toolFound = (this->checkTool() >= 0);

    if(!_toolFound)
        QMessageBox::critical(this, MYNAME, tr("No sub3dtool command found"));

    this->initGui();

    _isStarted = true;
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
        emit(newStatus(QString(SUB3DTOOLNAME) + QString(" ") + tr("found")));
    else
        emit(newStatus(QString(SUB3DTOOLNAME) + QString(" ") + tr("not found")));

    char *defaultDir = getenv("HOME");
    if(defaultDir != NULL)
    {
        this->_inFile = QString(defaultDir) + "/";
        this->_outFile = QString(defaultDir) + "/";
    }
    else
    {
        this->_inFile = "/";
        this->_outFile = "/";
    }

    ui->lineEditFileIn->setText(this->_inFile);
    ui->lineEditFileOut->setText(this->_outFile);

    _fontBold = ui->label3DSBS->font();
    _fontBold.setBold(true);
    _fontNotBold = ui->label3DSBS->font();
    _fontNotBold.setBold(false);

    switch(_data.transformation3d)
    {
    case N3D:
        ui->button3DSBS->setChecked(false);
        ui->button3DTB->setChecked(false);
        ui->button3DN3D->setChecked(true);
        ui->label3DSBS->setFont(_fontNotBold);
        ui->label3DTB->setFont(_fontNotBold);
        ui->label3DN3D->setFont(_fontBold);
        break;
    case SBS:
        ui->button3DSBS->setChecked(true);
        ui->button3DTB->setChecked(false);
        ui->button3DN3D->setChecked(false);
        ui->label3DSBS->setFont(_fontBold);
        ui->label3DTB->setFont(_fontNotBold);
        ui->label3DN3D->setFont(_fontNotBold);
        break;
    case TB:
        ui->button3DSBS->setChecked(false);
        ui->button3DTB->setChecked(true);
        ui->button3DN3D->setChecked(false);
        ui->label3DSBS->setFont(_fontNotBold);
        ui->label3DTB->setFont(_fontBold);
        ui->label3DN3D->setFont(_fontNotBold);
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

void sub3dtoolgui::filesChangedIn()
{
    this->_inFile = ui->lineEditFileIn->text();
    if(this->_inFile.endsWith(".srt"))
    {
        this->_outFile = this->_inFile;
        this->_outFile.chop(3);
        this->_outFile += "ass";
        ui->lineEditFileOut->setText(this->_outFile);
    }
}

void sub3dtoolgui::filesChangedOut()
{
    this->_outFile = ui->lineEditFileOut->text();
}

void sub3dtoolgui::getFileIn()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Original Subtitles"), ui->lineEditFileIn->text(),
                                                    tr("All Subtitles (*.srt *.ass *.ssa);;SubRip Subtitles (*.srt);;SubStation Alpha Subtitles(*.ass *.ssa);;All Files(*.*)"));

    if(fileName != "")
    {
        ui->lineEditFileIn->setText(fileName);
        this->filesChangedIn();
    }
}

void sub3dtoolgui::getFileOut()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Converted Subtitles"), ui->lineEditFileOut->text(),
                                                    tr("All Subtitles (*.srt *.ass *.ssa);;SubRip Subtitles (*.srt);;SubStation Alpha Subtitles(*.ass *.ssa);;All Files(*.*)"));

    if(fileName != "")
    {
        ui->lineEditFileOut->setText(fileName);
        this->filesChangedOut();
    }
}

void sub3dtoolgui::change3DModeSBS()
{
    if(_data.transformation3d == SBS)
        ui->button3DSBS->setChecked(true);
    else
    {
        _data.transformation3d = SBS;
        ui->button3DTB->setChecked(false);
        ui->button3DN3D->setChecked(false);

        ui->label3DSBS->setFont(_fontBold);
        ui->label3DTB->setFont(_fontNotBold);
        ui->label3DN3D->setFont(_fontNotBold);
    }
}

void sub3dtoolgui::change3DModeTB()
{
    if(_data.transformation3d == TB)
        ui->button3DTB->setChecked(true);
    else
    {
        _data.transformation3d = TB;
        ui->button3DSBS->setChecked(false);
        ui->button3DN3D->setChecked(false);

        ui->label3DSBS->setFont(_fontNotBold);
        ui->label3DTB->setFont(_fontBold);
        ui->label3DN3D->setFont(_fontNotBold);
    }
}

void sub3dtoolgui::change3DModeN3D()
{
    if(_data.transformation3d == N3D)
        ui->button3DN3D->setChecked(true);
    else
    {
        _data.transformation3d = N3D;
        ui->button3DSBS->setChecked(false);
        ui->button3DTB->setChecked(false);

        ui->label3DSBS->setFont(_fontNotBold);
        ui->label3DTB->setFont(_fontNotBold);
        ui->label3DN3D->setFont(_fontBold);
    }
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

int sub3dtoolgui::subtitleConvert(QString inFile, QString outFile, s3tData data)
{
    QProcess tool;
    QStringList arguments;

    switch(data.transformation3d)
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
    arguments << data.resolution;
    arguments << "--font";
    arguments << data.font;
    arguments << "--fontsize";
    arguments << QString::number(data.fontSize);

    arguments << "--color-primary";
    arguments << "0x" + QString::number(data.cPrimary.r, 16) +
                 QString::number(data.cPrimary.g, 16) + QString::number(data.cPrimary.b, 16);

    arguments << "--color-2nd";
    arguments << "0x" + QString::number(data.cSecondary.r, 16) +
                 QString::number(data.cSecondary.g, 16) + QString::number(data.cSecondary.b, 16);

    arguments << "--color-outline";
    arguments << "0x" + QString::number(data.cOutline.r, 16) +
                 QString::number(data.cOutline.g, 16) + QString::number(data.cOutline.b, 16);

    arguments << "--color-back";
    arguments << "0x" + QString::number(data.cBack.r, 16) +
                 QString::number(data.cBack.g, 16) + QString::number(data.cBack.b, 16);

    arguments << "--outline";
    arguments << QString::number(data.outline);

    arguments << "--shadow";
    arguments << QString::number(data.shadow);

    switch(data.alignment)
    {
    case TL:
        arguments << "--align-top";
        arguments << "--align-left";
        break;
    case T:
        arguments << "--align-top";
        arguments << "--align-center";
        break;
    case TR:
        arguments << "--align-top";
        arguments << "--align-right";
        break;
    case L:
        arguments << "--align-middle";
        arguments << "--align-left";
        break;
    case C:
        arguments << "--align-middle";
        arguments << "--align-center";
        break;
    case R:
        arguments << "--align-middle";
        arguments << "--align-right";
        break;
    case BL:
        arguments << "--align-bottom";
        arguments << "--align-left";
        break;
    case B:
        arguments << "--align-bottom";
        arguments << "--align-center";
        break;
    case BR:
        arguments << "--align-bottom";
        arguments << "--align-right";
        break;
    default:
        break;
    }

    arguments << "--margin-left";
    arguments << QString::number(data.marginL);
    arguments << "--margin-right";
    arguments << QString::number(data.marginR);
    arguments << "--margin-vertical";
    arguments << QString::number(data.marginV);

    arguments << "-o";
    arguments << outFile;
    arguments << inFile;

    tool.start(SUB3DTOOLNAME, arguments);

    if (!tool.waitForStarted())
        return -501;

    if (!tool.waitForFinished())
        return -502;

    int code = tool.exitCode();

    return code;
}

void sub3dtoolgui::analyzeToolCodeSingleFile(int code)
{
    switch(code)
    {
    case -501:
        QMessageBox::critical(this, MYNAME, tr("ERROR starting the tool"));
        break;
    case -502:
        QMessageBox::critical(this, MYNAME, tr("ERROR executing the tool"));
        break;
    default:
        QMessageBox::critical(this, MYNAME, tr("ERROR tool reported error: %1").arg(QString::number(code)));
        break;
    }
}

void sub3dtoolgui::analyzeToolCodeManyFiles(int code, QString file, QList<int> *errorShow)
{
    int answer;

    if(errorShow->contains(code))
        return;

    switch(code)
    {
    case -501:
        answer = QMessageBox::critical(this, MYNAME, tr("ERROR starting the tool when converting file:<br>%1").arg(file), QMessageBox::Ignore, QMessageBox::Ok);
        break;
    case -502:
        answer = QMessageBox::critical(this, MYNAME, tr("ERROR executing the tool when converting file:<br>%1").arg(file), QMessageBox::Ignore, QMessageBox::Ok);
        break;
    default:
        answer = QMessageBox::critical(this, MYNAME, tr("ERROR tool reported error: %1<br>when converting file:<br>%2").arg(QString::number(code)).arg(file), QMessageBox::Ignore, QMessageBox::Ok);
        break;
    }

    if(answer == QMessageBox::Ignore)
    {
        errorShow->append(code);
    }
}

void sub3dtoolgui::convertSingleFile()
{
    if(!QFileInfo(this->_inFile).exists())
    {
        QMessageBox::critical(this, MYNAME, tr("ERROR: The file\n%1\ndoes not exist.").arg(this->_inFile));
        return;
    }

    if(QFileInfo(this->_inFile).isDir())
    {
        QMessageBox::critical(this, MYNAME, tr("ERROR:\n%1\nis a directory, not a file.").arg(this->_inFile));
        return;
    }

    if(this->_outFile == this->_inFile)
    {
        int ret = QMessageBox::question(this, MYNAME, tr("Original subtitle will be overwritten! Continue?"), QMessageBox::Yes, QMessageBox::No);
        if(ret == QMessageBox::No)
            return;
    }
    else if(QFileInfo(this->_outFile).exists())
    {
        if(QFileInfo(this->_outFile).isFile())
        {
            int ret = QMessageBox::question(this, MYNAME, tr("The destination file already exists! Continue?"), QMessageBox::Yes, QMessageBox::No);
            if(ret == QMessageBox::No)
                return;
        }
        else
        {
            QMessageBox::critical(this, MYNAME, tr("ERROR:\n%1\nis a directory, not a file.").arg(this->_inFile));
            return;
        }
    }

    int code = this->subtitleConvert(this->_inFile, this->_outFile, this->_data);
    if(code)
    {
        this->analyzeToolCodeSingleFile(code);
    }
    else
    {
        QMessageBox::information(this, MYNAME, tr("Subtitles successfully converted!"));
    }
}

void sub3dtoolgui::convertManyFiles()
{
    int answer;
    bool ignoreExists = false;
    bool ignoreDirs = false;
    bool ignoreOverwrite = false;
    bool ignoreReplace = false;
    bool ignoreDirsOut = false;
    bool execute;

    QList<int> errorShow;

    int correct = 0;
    QList<struct s3tSubConf>::iterator i;

    for(i=_files.begin(); i!=_files.end(); ++i)
    {
        execute = true;

        if(!QFileInfo((*i).inFile).exists())
        {
            if(!ignoreExists)
            {
                answer = QMessageBox::critical(this, MYNAME, tr("ERROR: The file\n%1\ndoes not exist.").arg((*i).inFile), QMessageBox::Ignore, QMessageBox::Ok, QMessageBox::Cancel);
                if(answer == QMessageBox::Ignore)
                    ignoreExists = true;
                else if(answer == QMessageBox::Cancel)
                    return;
            }
            execute = false;
        }

        if(QFileInfo((*i).inFile).isDir())
        {
            if(!ignoreDirs)
            {
                answer = QMessageBox::critical(this, MYNAME, tr("ERROR:\n%1\nis a directory, not a file.").arg((*i).inFile), QMessageBox::Ignore, QMessageBox::Ok, QMessageBox::Cancel);
                if(answer == QMessageBox::Ignore)
                    ignoreDirs = true;
                else if(answer == QMessageBox::Cancel)
                    return;
            }
            execute = false;
        }

        if((*i).inFile == (*i).outFile)
        {
            if(!ignoreOverwrite)
            {
                answer = QMessageBox::question(this, MYNAME, tr("Original subtitle<br>%1<br>will be overwritten! Continue?").arg((*i).inFile), QMessageBox::Yes, QMessageBox::YesToAll, QMessageBox::No);
                if(answer == QMessageBox::YesToAll)
                    ignoreOverwrite = true;
                else if(answer == QMessageBox::No)
                    execute = false;
            }
        }
        else if(QFileInfo((*i).outFile).exists())
        {
            if(QFileInfo((*i).outFile).isFile())
            {
                if(!ignoreReplace)
                {
                    answer = QMessageBox::question(this, MYNAME, tr("The destination file<br>%1<br>already exists and will be overwritten! Continue?").arg((*i).inFile), QMessageBox::Yes, QMessageBox::YesToAll, QMessageBox::No);
                    if(answer == QMessageBox::YesToAll)
                        ignoreReplace = true;
                    else if(answer == QMessageBox::No)
                        execute = false;
                }
            }
            else
            {
                if(!ignoreDirsOut)
                {
                    answer = QMessageBox::critical(this, MYNAME, tr("ERROR:\n%1\nis a directory, not a file.").arg((*i).inFile), QMessageBox::Ignore, QMessageBox::Ok, QMessageBox::Cancel);
                    if(answer == QMessageBox::Ignore)
                        ignoreDirsOut = true;
                    else if(answer == QMessageBox::Cancel)
                        return;
                }
                execute = false;
            }
        }

        if(execute)
        {
            int code = this->subtitleConvert((*i).inFile, (*i).outFile, this->_data);
            if(code)
                this->analyzeToolCodeManyFiles(code, (*i).inFile, &errorShow);
            else
                correct++;
        }
    }

    QMessageBox::information(this, MYNAME, tr("%1 out of %2 subtitles files successfully converted!").arg(correct).arg(_files.size()));
}

void sub3dtoolgui::convert()
{
    if(ui->tabFilesSelect->currentIndex() == 0)
    {
        this->convertSingleFile();
    }
    else if (ui->tabFilesSelect->currentIndex() == 1)
    {
        this->convertManyFiles();
    }
}

void sub3dtoolgui::showAbout()
{
    QString str;
    str = QString("<center>%1 %2 - %3<br>(c)2013 Daniel Rubio Bonilla<br>danielrubiob@gmail.com<br>GPL v3</center>").arg(MYNAME).arg(VERSION).arg(DATE);
    QMessageBox::about(this, MYNAME, str);
}

void sub3dtoolgui::showAdvance()
{
    sub3dtoolguiAdvance *nw;
    nw = new sub3dtoolguiAdvance();

    nw->shareData(&_data);

    nw->setWindowModality(Qt::ApplicationModal);
    nw->show();
}

void sub3dtoolgui::exit()
{
    emit closeProgram();
}

void sub3dtoolgui::updateFileTable()
{
    QList<struct s3tSubConf>::iterator i;
    int _i = 0;

    ui->table->clearContents();
    ui->table->setRowCount(_files.size());

    for(i=_files.begin(); i!=_files.end(); ++i)
    {
        QTableWidgetItem *newItem0 = new QTableWidgetItem(QString::number((*i).index));
        QTableWidgetItem *newItem1 = new QTableWidgetItem((*i).inFile);
        QTableWidgetItem *newItem2 = new QTableWidgetItem((*i).outFile);
        ui->table->setItem(_i, 0, newItem0);
        ui->table->setItem(_i, 1, newItem1);
        ui->table->setItem(_i, 2, newItem2);
        ++_i;
    }

    ui->table->resizeColumnsToContents();
}

void sub3dtoolgui::removeMultipleFiles()
{        
    QList<QTableWidgetItem *> elements = ui->table->selectedItems();
    QList<int> rows;

    QList<QTableWidgetItem *>::iterator i;
    for(i=elements.begin(); i!=elements.end(); ++i)
    {
        int r = (*i)->row();
        if(rows.indexOf(r) == -1)
            rows.append(r);
    }

    QSet<int> rowList = rows.toSet();
    QSet<int>::iterator j;
    for(j=rowList.begin(); j!=rowList.end(); ++j)
    {
        QTableWidgetItem *e = (ui->table->item((*j), 0));
        unsigned long long code = e->text().toULongLong();
        this->removeFileFromList(code);
    }

    this->updateFileTable();
}

bool sub3dtoolgui::removeFileFromList(unsigned long long index)
{
    int j = 0;
    QList<struct s3tSubConf>::iterator i;
    for(i=_files.begin(); i!=_files.end(); ++i)
    {
        if((*i).index == index)
        {
            _files.removeAt(j);
            return true;
        }
        j++;
    }
    return false;
}

bool sub3dtoolgui::addFileToList(struct s3tSubConf nf)
{
    QList<struct s3tSubConf>::iterator i;
    for(i=_files.begin(); i!=_files.end(); ++i)
    {
        if((*i).inFile == nf.inFile)
            return false;
    }

    _files.append(nf);
    return true;
}

void sub3dtoolgui::addMultipleFiles()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Original Subtitles"), ui->lineEditFileIn->text(),
                                                          tr("All Subtitles (*.srt *.ass *.ssa);;SubRip Subtitles (*.srt);;SubStation Alpha Subtitles(*.ass *.ssa);;All Files(*.*)"));

    while(!fileNames.isEmpty())
    {
        struct s3tSubConf nf;
        nf.inFile = fileNames.takeFirst();
        if(nf.inFile.endsWith(".srt"))
        {
            nf.outFile = nf.inFile;
            nf.outFile.chop(3);
            nf.outFile += "ass";
        }
        else if(nf.inFile.endsWith(".ass") || nf.inFile.endsWith(".ssa"))
        {
            nf.outFile = nf.inFile;
        }
        nf.index = _fi++;
        this->addFileToList(nf);
    }

    this->updateFileTable();
}

void sub3dtoolgui::addMultipleDir()
{
    QDirIterator *dirIt;

    QString dirName = QFileDialog::getExistingDirectory(this, tr("Select a directory with subtitles"), ui->lineEditFileIn->text());

    int ret = QMessageBox::question(this, MYNAME, tr("The directory has subdirectories. Do you want to add subtitle files in subdirectories?"), QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::Yes)
    {
        dirIt = new QDirIterator(dirName, QDirIterator::Subdirectories);
    }
    else
    {
        dirIt = new QDirIterator(dirName, QDirIterator::NoIteratorFlags);
    }

    while (dirIt->hasNext())
    {
        dirIt->next();
        if (QFileInfo(dirIt->filePath()).isFile())
        {
            struct s3tSubConf nf;
            nf.inFile = dirIt->filePath();
            if(nf.inFile.endsWith(".srt"))
            {
                nf.outFile = nf.inFile;
                nf.outFile.chop(3);
                nf.outFile += "ass";
            }
            else if(nf.inFile.endsWith(".ass") || nf.inFile.endsWith(".ssa"))
            {
                nf.outFile = nf.inFile;
            }
            nf.index = _fi++;
            this->addFileToList(nf);
        }
    }

    this->updateFileTable();
}
