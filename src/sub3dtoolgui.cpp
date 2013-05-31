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
    ui->setupUi(this);

    if(this->checkTool() < 0)
    {
        this->initGui(false);
        QMessageBox::critical(this, "sub3dtool-gui", tr("No sub3dtool command found"));
    }
    else
        this->initGui(true);

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

void sub3dtoolgui::initGui(bool toolFound)
{
    if(!toolFound)
    {
        ui->buttonConvert->setEnabled(false);
    }

    char *defaultDir = getenv("HOME");
    if(defaultDir != NULL)
    {
        ui->lineEditFileIn->setText(QString(defaultDir) + "/");
        ui->lineEditFileOut->setText(QString(defaultDir) + "/");
    }
    else
    {
        ui->lineEditFileIn->setText("/");
        ui->lineEditFileOut->setText("/");
    }
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
    ui->button3DTB->setChecked(false);
    ui->button3DN3D->setChecked(false);
}

void sub3dtoolgui::change3DModeTB()
{
    ui->button3DSBS->setChecked(false);
    ui->button3DN3D->setChecked(false);
}

void sub3dtoolgui::change3DModeN3D()
{
    ui->button3DSBS->setChecked(false);
    ui->button3DTB->setChecked(false);
}
