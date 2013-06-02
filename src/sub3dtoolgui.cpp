#include "sub3dtoolgui.h"
#include "ui_sub3dtoolgui.h"

#include <QProcess>
#include <QMessageBox>
#include <QFileDialog>

#define SUB3DTOOLNAME "sub3dtool"

sub3dtoolgui::sub3dtoolgui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sub3dtoolgui)
{
    _isStarted = false;

    ui->setupUi(this);

    _toolFound = (this->checkTool() >= 0);

    if(!_toolFound)
        QMessageBox::critical(this, "sub3dtool-gui", tr("No sub3dtool command found"));

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

    arguments << "--screen " + _data.resolution;

    arguments << "--font " + _data.font;

    arguments << "--fontsize" + QString::number(_data.fontSize);

    arguments << "-o " + _data.outFile;
    arguments << _data.inFile;

    tool.start(SUB3DTOOLNAME, arguments);

    if (!tool.waitForStarted())
    {
        //ERROR starting the tool
    }


    if (!tool.waitForFinished())
    {
        //ERROR during execution of the tool
    }
}
