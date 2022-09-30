#ifndef _UTILS_H_
#define _UTILS_H_

#include <cstdlib>
#include <vector>
#include <iostream>
#include <QString>
#include <QVector>

enum class ResultType {strike, spare, split, random, gutter};

void generatePinVector(std::vector<bool>& pins, bool isFirst, ResultType type);
void printPins(const std::vector<bool>& pins);
QString printPinsAsQString(const QVector<bool>& pins);

QString b2s(bool b);

QString resultTypeToString(const ResultType type);

#endif
