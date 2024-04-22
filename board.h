/*!
 * Name: Mukti Flora Rahman
 * Course name: Programmeringsmetodik, 6 hp
 * Date: 2020-11-03
 * Assignment: Sudoku project
 * File: board.h
 *
 *
 *
 */

#ifndef BOARD_H
#define BOARD_H
#include <QVector>
#include <QString>

/*!
 * @brief The Board class
 */

class Board
{
public:
    Board(QString file);
    void readFile();
    QVector<int> getNumbers();

private:
    QVector<int> m_numbers;
    QVector<int> m_sqVec;
    QString m_fileName;
};

#endif // BOARD_H
