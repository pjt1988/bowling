#include "utils.h"

/*
 * Pins are mapped as follows to a bool vector:
 *
 * 	6 7 8 9
 *   3 4 5
 *    1 2
 *     0
 *
 * with True being knocked over pins
 */      
 

void generatePinVector(std::vector<bool>& pins, bool isFirst, ResultType type){

	switch(type){
		case ResultType::strike:
			std::fill(pins.begin(),pins.end(),true);
			break;
		case ResultType::spare:
			std::fill(pins.begin(),pins.end(),true);
			break;
		case ResultType::split:
			//a little boring, but adding randomness seems overkill
			std::fill(pins.begin(),pins.end(),true);
			pins[6] = false;
			pins[9] = false;
			break;
		case ResultType::random:
			if(isFirst){
				for(auto&& pin : pins){
					//60% chance of knocking a pin over
					if(rand() % 100 >= 39)
						pin = true;
				}
			}else  {
				for(auto&& pin : pins){
					//let's say you're a little better on the second throw
					if(!pin && rand() % 100 >= 29)
						pin = true;
				}
			}
			break;
		case ResultType::gutter:
			//do nothing...
			break;
	}

}

void printPins(const std::vector<bool>& pins){
	std::cout << std::endl;
	std::cout << " " << pins[6] << " " << pins[7] << " " << pins[8] << " " << pins[9] << std::endl;
	std::cout << "  " << pins[3] << " " << pins[4] << " " << pins[5] << std::endl;
	std::cout << "   " << pins[1] << " " << pins[2] << std::endl;
	std::cout << "    " << pins[0] << std::endl << std::endl;
}

QString printPinsAsQString(const QVector<bool>& pins){
	QString out = "\n\n";
    out += "  " + b2s(pins[6]) + " " + b2s(pins[7]) + " " + b2s(pins[8]) + " " + b2s(pins[9]) + "\n";
    out += "   " + b2s(pins[3]) + " " + b2s(pins[4]) + " " + b2s(pins[5]) + "\n";
    out += "    " + b2s(pins[1]) + " " + b2s(pins[2]) + "\n";
    out += "     " + b2s(pins[0]) + "\n\n";

  return out;
}

QString resultTypeToString(const ResultType type){
    QString ret = "";
    switch(type){
    case(ResultType::strike):
        ret = "STRIKE!!!";
        break;
    case(ResultType::spare):
        ret = "Spare";
        break;
    case(ResultType::split):
        ret = "Split";
        break;
    case(ResultType::gutter):
        ret = "Gutter Ball";
        break;
    default:
        ret = "Randomly Generated";
    }
    return ret;
}

inline QString b2s(bool b){
  return b ? "X" : "O";
}
