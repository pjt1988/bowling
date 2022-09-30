#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QVector>
#include <QThread>
#include <string>

#include "utils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class Worker : public QThread {
    Q_OBJECT
public:
    Worker() = default;
    void run();

signals:
    void boardChangedFirst(const QVector<bool>& vec, ResultType result);
    void boardChangedSecond(const QVector<bool>& vec, ResultType result);
    void finished(QString info);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getUserInput();

public slots:
    void onBoardChangedFirst(const QVector<bool>& vec, ResultType result);
    void onBoardChangedSecond(const QVector<bool>& vec, ResultType result);
    void onFinished(QString info);

private:
    int _score;
    int _game;
    std::string _comment;

    Ui::MainWindow *ui;
    Worker* worker;
    QTextEdit* totalscore;
    QTextEdit* gamecounter;
    QTextEdit* game1;
    QTextEdit* game2;
    QTextEdit* comment;

    void update(int score, const std::string& comment, int game);
};
#endif // MAINWINDOW_H
