/*!
 * Name: Mukti Flora Rahman
 * Course name: Programmeringsmetodik, 6 hp
 * Date: 2020-11-03
 * Assignment: Sudoku project
 * File: board.cpp
 *
 *
 *
 */

#include "board.h"
#include "functions.h"
#include <QFile>
#include <QIODevice>
#include <QStringList>
#include <algorithm>
#include <QDebug>


/*!
 * Konstruktor
 * anropar readFile
 */

Board::Board(QString file)
    : m_fileName(file)
{
    readFile();
}

/*!
 * Funktion för att läsa en sudoku textfil
 */

void Board::readFile()
{
    QFile file(m_fileName);
  //  qDebug() << m_fileName;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       // qDebug() << "The file is not open.";
        return;
    }

    while(!file.atEnd())
    {
       QString line = file.readLine();
     //  qDebug() << line;
       QStringList elements = line.split(" ");
       std::transform(elements.begin(), elements.end(), std::back_inserter(m_numbers), ConvertStringToInt());
    }

}

/*!
 * returnerar hela m_numbers vektorn
 */

QVector<int> Board::getNumbers()
{
    return m_numbers;
}
