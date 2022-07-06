#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QSaveFile>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    currentFile.clear();
    ui->textEdit->setText(QString());
    setWindowTitle("Nouveau fichier");
    //connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, &MainWindow::showCursorPos);
}

void MainWindow::showCursorPos()
{
    int line = ui->textEdit->textCursor().blockNumber()+1;
    int pos = ui->textEdit->textCursor().columnNumber()+1;
    ui->statusbar->showMessage(QString("Ln %1, Col %2").arg(line).arg(pos));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered() // Action nouveau fichier
{
    currentFile.clear();
    ui->textEdit->setText(QString());
    setWindowTitle("Nouveau fichier");
}

void MainWindow::on_actionExit_triggered() // Action quitter l'application
{
    QApplication::exit();
}

void MainWindow::on_actionOpen_triggered() // Action pour ouvrir un fichier
{
    // Opens a dialog that allows you to select a file to open
       QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir...","","Fichier texte (*.txt);;Tous les fichiers (*.*)");
       // An object for reading and writing files
       QFile file(fileName);
       // Store the currentFile name
       currentFile = fileName;
       // Try to open the file as a read only file if possible or display a
       // warning dialog box
       if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
           return;
       }
       // Set the title for the window to the file name
       setWindowTitle(fileName);
       // Interface for reading text
       QTextStream in(&file);
       // Copy text in the string
       QString text = in.readAll();
       // Put the text in the textEdit widget
       ui->textEdit->setText(text);
       // Ferme le fichier
       file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    // Opens a dialog for saving a file
        QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer sous...","Nouveau fichier","Fichier texte (*.txt);;Tous les fichiers (*.*)");
        // An object for reading and writing files
        QFile file(fileName);
        // Try to open a file with write only options
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            return;
        }
        // Store the currentFile name
        currentFile = fileName;
        // Set the title for the window to the file name
        setWindowTitle(fileName);
        // Interface for writing text
        QTextStream out(&file);
        // Copy text in the textEdit widget and convert to plain text
        QString text = ui->textEdit->toPlainText();
        // Output to file
        out << text;
        // Close the file
        file.close();
        //QMessageBox::about(this, "Sauvegarde", "le fichier à été sauvegarder sous " + fileName);
        ui->statusbar->showMessage(QString("Sauvegarder sous " + fileName));
}

void MainWindow::on_actionSave_triggered() // save
{
    QString fileName;
    // If we don't have a filename from before, get one.
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Enregistrer sous...","Nouveau fichier","Fichier texte (*.txt);;Tous les fichiers (*.*)");
        if (fileName.isEmpty())
            return;
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
    ui->statusbar->showMessage(QString("Sauvegarder sous " + fileName));
}

//QDesktopServices::openUrl(QUrl::fromLocalFile("<path_to_your_file>"));

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}
void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}
void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}
void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}
void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionInfo_triggered()
{
    QMessageBox::about( this, "à propos",
        "<h4>Lestyleau-Notepad à propos</h4>\n\n"
    "Copyright 2022-2022. "
    "For technical support, Github\n"
    "<a href=\"https://github.com/LeStyleau\">https://github.com/LeStyleau</a>" );
}

void MainWindow::on_actionTips_triggered()
{
    QString Tips_text;
    Tips_text = "WIP";
    QMessageBox::about(this, "Work in progress", Tips_text);
}

void MainWindow::on_actionFont_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, QFont("Segoe UI", 12), this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}

void MainWindow::on_actionAlways_on_top_triggered(bool checked) // always on top
{
    Qt::WindowFlags flags = this->windowFlags();
    if(checked) //
    {
        this->setWindowFlags(flags | (Qt::WindowStaysOnTopHint));
        this->show();
    }
    else
    {
        this->setWindowFlags(flags ^ (Qt::WindowStaysOnTopHint));
        this->show();
    }
}

void MainWindow::on_actionFullsreen_triggered() // mettre le notepad en plein écran
{
    isFullScreen() ? showNormal() : showFullScreen(); // est ? oui : non
}

void MainWindow::on_actionQt_triggered()
{
    QMessageBox::aboutQt(this);
}


void MainWindow::on_actionAide_triggered()
{
    QMessageBox::warning(this,"","");
}
