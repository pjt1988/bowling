#include <thread>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "utils.h"


void Worker::run(){
    std::cout << "Welcome to Bowling! \n Please input your result.." << std::endl << std::endl;

    int gameCounter = 1;
    while(true) {
        std::cout << "This is game " << gameCounter;
        std::cout << " This is your first ball" << std::endl;
        std::string inFirst = "";
        std::getline(std::cin, inFirst);
        std::cout << "in first " << inFirst << std::endl;fflush(stdout);
        std::vector<bool> pins(10,false);
        ResultType res;
        int score = 0;
        if(inFirst == "r"){
            generatePinVector(pins, true, ResultType::random);
            res = ResultType::random;
        } else if(inFirst == "x"){
            generatePinVector(pins, true, ResultType::strike);
            res = ResultType::strike;
        } else if(inFirst == "s"){
            generatePinVector(pins, true, ResultType::split);
            res = ResultType::split;
        } else if(inFirst == "g"){
            generatePinVector(pins, true, ResultType::gutter);
            res = ResultType::gutter;
        } else if(inFirst == "e"){
            std::cout << "Bye.." << std::endl;
            emit finished("Bye");
        } else{
            std::cout << "invalid input. Press \"e\" to exit" << std::endl;
        }
        if(score == 10)
            res = ResultType::strike;
        else if(score == 0)
            res = ResultType::gutter;

        printPins(pins);
        emit boardChangedFirst(QVector<bool>::fromStdVector(pins), res);
        //strikes get fresh pins after the first ball
        if(score == 10 || inFirst == "x"){
            std::fill(pins.begin(),pins.end(),false);
        }


        std::cout << "This is your second ball" << std::endl;
        std::cin.clear();
        std::string inSecond = "";
        std::getline(std::cin, inSecond);
        std::cout << "in second " << inSecond << std::endl;fflush(stdout);

        if(inSecond == "r"){
            generatePinVector(pins, false, ResultType::random);
            res = ResultType::random;
        } else if(inSecond == "/"){
            generatePinVector(pins, false, ResultType::spare);
            res = ResultType::spare;
        } else if(inSecond == "s"){
            generatePinVector(pins, false, ResultType::split);
            res = ResultType::split;
        } else if(inSecond == "x" && inFirst == "x"){ //strikes are only possible if the first ball was a strike
            res = ResultType::strike;
            generatePinVector(pins, false, ResultType::strike);
        } else if(inSecond == "g"){
            res = ResultType::gutter;
            generatePinVector(pins, false, ResultType::gutter);
        } else if(inSecond == "e"){
            std::cout << "Bye.." << std::endl;
            emit finished("Bye");
        } else{
            std::cout << "invalid input. Press \"e\" to exit" << std::endl;
        }
        printPins(pins);
        if(score == 10)
            res = ResultType::spare;
        else if(score == 0)
            res = ResultType::gutter;

        if(++gameCounter == 11)
            gameCounter = 1; //reset

        emit boardChangedSecond(QVector<bool>::fromStdVector(pins), res);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _score(0)
    , _game(1)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: white");
    QWidget::setWindowTitle("Bowling!");
    comment = findChild<QTextEdit*>("comment");
    game1 = findChild<QTextEdit*>("game1");
    game2 = findChild<QTextEdit*>("game2");
    totalscore = findChild<QTextEdit*>("totalscore");
    gamecounter = findChild<QTextEdit*>("gamecounter");
    qRegisterMetaType<ResultType>("ResultType");

    Worker* worker = new Worker;
    connect(worker, SIGNAL(boardChangedFirst(QVector<bool>, ResultType)),
                    SLOT(onBoardChangedFirst(QVector<bool>, ResultType)));
    connect(worker, SIGNAL(boardChangedSecond(QVector<bool>, ResultType)),
                    SLOT(onBoardChangedSecond(QVector<bool>, ResultType)));
    connect(worker, SIGNAL(finished(QString)),
                    SLOT(onFinished(QString)));
    worker->start();


}

MainWindow::~MainWindow()
{
    delete ui;
    delete worker;
}


void MainWindow::onBoardChangedFirst(const QVector<bool>& vec, ResultType res)
{
    if(_game == 1 || _game == 11){
        _score=0;
        _game=1;
        game1->setText("Ball1: \n");
        game2->setText("Ball2: \n");
        totalscore->setText("Total Score: ");
    }
    int score = 0;
    for(const auto& it : vec)
        score += it;
    _score+=score;

    game2->setText("Ball2: \n");
    game1->setText(QString("Ball1: \n  %1").arg(score));

    totalscore->setText(QString("Total Score: %1").arg(_score));
    gamecounter->setText(QString("Game %1").arg(_game));
    
    QString gameText = resultTypeToString(res);
    gameText += printPinsAsQString(vec);

    comment->setText(resultTypeToString(res));
    comment->setAlignment(Qt::AlignCenter);
    comment->append(printPinsAsQString(vec));

    comment->setAlignment(Qt::AlignCenter);
}

void MainWindow::onBoardChangedSecond(const QVector<bool>& vec, ResultType res)
{
    _game++;

    int score = 0;
    for(const auto& it : vec)
        score += it;
    _score+=score;

    game2->setText(QString("Ball2: \n  %1").arg(score));

    totalscore->setText(QString("Total Score: %1").arg(_score+score));

    comment->setText(resultTypeToString(res));
    comment->setAlignment(Qt::AlignCenter);
    comment->append(printPinsAsQString(vec));

    comment->setAlignment(Qt::AlignCenter);
}

void MainWindow::onFinished(QString info)
{
    exit(0);
}

