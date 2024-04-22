/*!
 * Name: Mukti Flora Rahman
 * Course name: Programmeringsmetodik, 6 hp
 * Date: 2020-11-03
 * Assignment: Sudoku project
 * File: functions.h
 *
 *
 *
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QString>
#include <QLineEdit>
#include <QValidator>
#include <QRegExpValidator>



/**
 * Gör om string till ett heltal
 */

class ConvertStringToInt
{
public:
   int operator()(QString value)
   {
       return value.toInt();
   }

};

/**
 * Kontrollerar vilka rutor som ska vara ifyllda
 *
 */

class FillValues
{
public:
     QLineEdit *operator()(int value, QLineEdit* le)
     {
         if(value!=0)
         {
             le->setText(QString::number(value));
         }
         else
         {
             le->setText("");
         }
        return le;
     }
};

/**
 * Validerar att texten i rutorna är siffror från 1-9
 * med MaxLength 1, dvs. bara att tecken är tillåtet per ruta.
 */

class OnlyNumbers
{

public:
    QLineEdit* operator()(QLineEdit* le)
    {
        QString singleNumber = "[1-9]";
        QRegExp regNumber(singleNumber);
        QRegExpValidator* validNumber = new QRegExpValidator(regNumber);
        le->setValidator(validNumber);
        le->setMaxLength(1);


        return le;
    }

};

/**
 * @brief The FindLineEditValue class
 */

class FindLineEditValue
{
  QString m_needle;
 public:
    FindLineEditValue(QString needle)
        : m_needle(needle)
    {

    }
//jämför värdet med m_needle
    bool operator()(QLineEdit* le)
    {
       int x = QString::compare(le->text(),m_needle, Qt::CaseInsensitive);
       return x == 0;
    }

 private:



};

/**
 * @brief The SumOfNumbers class
 */

class SumOfNumbers
{

public:
    int operator()(int value, QLineEdit* le)
    {
        value += le->text().toInt();
        return value;
    }

};

/**
 * @brief The Reset class
 * överlagring av funktionsoperatorn med typ QLineEdit*
 * sätter variabeln lineEdit till tom sträng och returnerar värdet
 *
 */

class Reset
{
public:
    QLineEdit* operator()(QLineEdit* lineEdit)
    {
           lineEdit->setText("");
           return lineEdit;
    }



};

class MapNumbers
{
public:

};

#endif // FUNCTIONS_H
