/*!
 * Name: Mukti Flora Rahman
 * Course name: Programmeringsmetodik, 6 hp
 * Date: 2020-11-03
 * Assignment: Sudoku project
 *
 *
 *
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"
#include "functions.h"
#include <QDebug>
#include <QString>
#include <QFileDialog>

/*!
 * Koppla från Qt applikationen till GUI
 * Konfiguration för ui
 *
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // konfiguration för ui
}

/*!
 * Destruktor för programmet
 * Eftersom det skapas på hypen
 *
 *
 *
 */

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * Run-funktionen
 * Börjar med att lagra en variabel med sökväg
 * Till rätt textfil
 * Anropar func. displayText, sen till mapNumbers.
 * Kör std::transform
 * Kopierar hel vektor, till början av vektorn
 * Anropar predikat OnlyNumbers för att sätta siffror 1-9
 * Försöker få tillgång till m_numbers, privat variabel
 * med getNumbers
 * Kopierar över till vektor m_numbers till m_lineEditVec
 * Anropar predikat FillValues
 */


void MainWindow::run()

{

    mapNumbers();
    //går igenom vektorn m_lineEditVec, anropar predikat OnlyNumbers
    // det får bara vara siffror mellan 1-9 i varje ruta
    // och bara 1 siffra
    std::transform(m_lineEditVec.begin(), m_lineEditVec.end(), m_lineEditVec.begin(), OnlyNumbers());

    QString filename="/home/mukti/metodikprojekt2/veryEasy.txt";
    readNewSudoku(filename);
}

/*!
 *Funktion för att läsa in ny sudoku fil
 * Kräver att skapa ett nytt board objekt
 * anropar konstruktorn
 * tar element från m_numbers i board klassen och lägger in det i m_numbers som tillhör mainwindow klassen via getNumbers
 *
 */


void MainWindow::readNewSudoku(QString filename)
{
    //QString filename="/home/mukti/metodikprojekt2/veryEasy.txt";
    Board *board = new Board(filename);

    QString endOfFilename = parseFilename(filename); //parsar filnamnet
    displayText(endOfFilename);

    m_numbers = board->getNumbers();
    std::transform(m_numbers.begin(), m_numbers.end(), m_lineEditVec.begin(),m_lineEditVec.begin(), FillValues());
}


/*!
 * @brief MainWindow::parseFilename
 * @param filename
 * @return
 * funktion som parsar filnamnet
 * delar upp filnamnet så att man får sista delen av filnamnet
 * filnamnet skrivs sedan ut i rutan i sudoku
 */
QString MainWindow::parseFilename(QString filename)
{
    QStringList filenameParts = filename.split("/");
    int fileItems = filenameParts.size();
    int lastIndex = fileItems - 1;

    return filenameParts[lastIndex];
}

/*!
 * Visar text i soduku rutan
 */

void MainWindow::displayText(QString text)
{
    ui->display->setPlainText(text);
}

/*!
 * Kopplar från vektorn med QLineEdit till vektorn med m_numbers.
 * försökte göra std::transform, lite svårt att hitta lösning
 */

void MainWindow::mapNumbers()
{
    m_lineEditVec.resize(81);
    //std::transform(m_lineEditVec.begin(), m_lineEditVec.end(), m_lineEditVec.begin(), MapNumbers());
    for(int lineEdit = 0; lineEdit < 81; lineEdit++)
    {
      m_lineEditVec[lineEdit] = ui->centralWidget->findChild<QLineEdit*>("lineEdit_" + QString::number(lineEdit));
    }
}

/*!
 * Quit-knapp för sudoku, avslutar Sudoku programmet
 * anropar quit()
 */

void MainWindow::on_quit_clicked()
{
    qDebug() << "Quit Sudoku.";
    QApplication::quit();
}

/*!
 * Check solution - knapp
 * När man klickar på knappen i sudoku anropas funktionen
 * checkSolution
 */

void MainWindow::on_checkSolution_clicked()
{

    qDebug() << "i Check solution.";
    checkSolution();
}

void MainWindow::on_playAgain_clicked()
{
    playAgain();
    qDebug() << "i Play Again.";
}

/*!
 * m_numbers.clear() nollställer alla vektorer.
 * läser in en ny text-fil via QString filename.
 * std::tranform för att kopiera över vektorn till början av vektorn
 * Anropar predikat Reset()
 */


void MainWindow::playAgain()
{


    m_numbers.clear();
    m_numbers.resize(0);

  std::transform(m_lineEditVec.begin(), m_lineEditVec.end(), m_lineEditVec.begin(), Reset());

  //QFileDialog är tillför att välja en fil, dyker upp en prompt där man får välja en fil
  QString filename = QFileDialog::getOpenFileName(
    this,"Open Document", "puzzles", "Document files (*txt)");
    readNewSudoku(filename);
  //  qDebug() << filename;


}

/*!
 * Här är alla lösningsfunktioner
 * Funktion som kollar ifall lösningen är korrekt
 * lagrar en text-sträng i en QString variabel som heter text.
 * lagrar controlHumanSolution() i bool isValid
 * if-sats, ifall isValid är true.
 * lägger man till "It is correct."
 * ifall isValid är false
 * skrivs det ut på skärmen tillsammans med text, "It is not correct."
 */

void MainWindow::checkSolution()
{
    QString text = "";
    bool isValid = controlHumanSolution();

    if(isValid)
    {
        text+= "\n It is correct.";
    }
    else
    {
        text+= "\n It is not correct.";

    }
    displayText(text);
}


/**
 * Funktion som kontrollerar ifall angiven lösning är korrekt
 * En QVector skapar med 9 poster
 * Fyller vektorn med std::iota
 * Första if-sats för att kontrollera ifall
 * det finns tomma sudoku rutor
 * Andra if-sats för att kontrollera
 * ifall angiven siffra är giltig
 * Tredje if-sats för att se ifall 1-9
 * finns i rad
 * Fjärde if-sats för att se ifall 1-9
 * finns i kolumn
 */

bool MainWindow::controlHumanSolution()
{
    m_oneToNine.resize(9);
    std::iota(m_oneToNine.begin(), m_oneToNine.end(), 1);

    if(areAnySquaresEmpty())
    {
        displayText("There are empty squares in the sudoku. Please fill in the squares.");

        return false;
    }

    if(!validSum())
    {
        displayText("The sum is not valid. Please try again.");

        return false;
    }


    if(!validRow())
    {
        displayText("The row given is incorrect. Please try again.");

        return false;
    }

    if(!validCol())
    {
        displayText("The column given is incorrect. Please try again.");

        return false;
    }

    if(!validBox())
    {
        displayText("The box given is incorrect. Please try again.");

        return false;
    }

    return true;

}

/**
 * Funktionen för att kontrollera ifall det finns någon tom ruta
 * Skapar en QString needle
 * anropar std::find_if för att gå igenom hela m_lineEditVec för att hitta värdet på needle
 * lagrar detta i variabels theFind
 * returnerar theFind
 */

bool MainWindow::areAnySquaresEmpty()
{
    QString needle = "";
    auto theFind = std::find_if(m_lineEditVec.begin(), m_lineEditVec.end(), FindLineEditValue(needle));
    return theFind != m_lineEditVec.end();
}

/**
 * Funktion kontrollerar som ifall summan för hela sudoku är korrekt
 */


bool MainWindow::validSum()
{
    int totalSum = std::accumulate(m_lineEditVec.begin(), m_lineEditVec.end(), 0, SumOfNumbers());
    //displayText(QString::number(totalSum));
    return totalSum == 405;
}

/**
 * Skapar en QVector rowvec
 * kollar rad för rad
 */

bool MainWindow::validRow()

{
    QVector<int> rowVec;

    for (int row = 0; row < 9; row++)
    {
        rowVec.clear();
        rowVec.resize(0);
        for (int col = 0; col < 9; col++)
        {
            rowVec.push_back(m_lineEditVec[row*9 + col]->text().toInt());
        }
        if(!std::is_permutation(rowVec.begin(), rowVec.end(), m_oneToNine.begin()))
        {
            qDebug() << "Row::There was no permutation." << row;
           return false;
        }
    }
    return true;
}

/**
 * Skapar en QVector colvec
 * kollar kolumn för kolumn
 */

bool MainWindow::validCol()

{
    QVector<int> colVec;
    for (int col = 0; col < 9; col++)
    {
        colVec.clear();
        colVec.resize(0);
        for (int row = 0; row < 9; row++)
        {
            colVec.push_back(m_lineEditVec[row*9 + col]->text().toInt());

        }
        if(!std::is_permutation(colVec.begin(), colVec.end(), m_oneToNine.begin()))
        {
            qDebug() << "Col::There was no permutation." << col;

            return false;
        }
    }
    return true;
}

/**
 * Kontrollerar ifall varje box i Sudoku är giltigt
 *
 *
 */

bool MainWindow::validBox()
{
    QVector<int> basBoxIndex{0,1,2,9,10,11,18,19,20};
    QVector<int> boxVec;

    for (int index = 0; index < 3; index++)
    {
        boxVec.clear();
        boxVec.resize(0);

        for (int baseIndex = 0 ; baseIndex < 9; baseIndex++)
        {
            boxVec.push_back(m_lineEditVec[index*3 + basBoxIndex[baseIndex]]->text().toInt());
        }

        if(!std::is_permutation(boxVec.begin(), boxVec.end(), m_oneToNine.begin()))
        {
            qDebug() << "Box::There was no permutation." << index;


            return false;
        }else{
            qDebug() << "There was a permutation.";
        }
    }
    for (int index = 0; index < 3; index++)
    {
        boxVec.clear();
        boxVec.resize(0);

        for (int baseIndex = 0 ; baseIndex < 9; baseIndex++)
        {
            boxVec.push_back(m_lineEditVec[index*3+27 + basBoxIndex[baseIndex]]->text().toInt());
        }

        if(!std::is_permutation(boxVec.begin(), boxVec.end(), m_oneToNine.begin()))
        {
            qDebug() << "Box::There was no permutation." << index;


            return false;
        }else{
            qDebug() << "There was a permutation.";
        }
    }
    for (int index = 0; index < 3; index++)
    {
        boxVec.clear();
        boxVec.resize(0);

        for (int baseIndex = 0 ; baseIndex < 9; baseIndex++)
        {
            boxVec.push_back(m_lineEditVec[index*3+54 + basBoxIndex[baseIndex]]->text().toInt());
        }

        if(!std::is_permutation(boxVec.begin(), boxVec.end(), m_oneToNine.begin()))
        {
            qDebug() << "Box::There was no permutation." << index;


            return false;
        }else{
            qDebug() << "There was a permutation.";
        }
    }
    return true;
}




