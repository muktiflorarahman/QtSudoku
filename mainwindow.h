/*!
 * Name: Mukti Flora Rahman
 * Course name: Programmeringsmetodik, 6 hp
 * Date: 2020-11-03
 * Assignment: Sudoku project
 * File: mainwindow.h
 *
 *
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * @brief The MainWindow class
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void run();
    void displayText(QString text);
    void mapNumbers();
    void checkSolution();
    bool controlHumanSolution();
    bool areAnySquaresEmpty();
    bool validSum();
    bool validRow();
    bool validCol();
    bool validBox();
    void playAgain();
    void readNewSudoku(QString filename);
    QString parseFilename(QString filename);



private slots:
    void on_quit_clicked();


    void on_checkSolution_clicked();

    void on_playAgain_clicked();

private:
    Ui::MainWindow *ui;
    QVector<int> m_numbers;
    QVector<QLineEdit *> m_lineEditVec;
    QPushButton m_exitButton;
    QVector<int> m_oneToNine;
};
#endif // MAINWINDOW_H


