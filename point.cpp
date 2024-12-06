#include "point.h"

Point::Point(){
    qDebug() << "`Point` object created";
}

Point::~Point(){
    qDebug() << "`Point` object deleted";
}

void Point::_test(){
    qDebug() << "this is a test call";
}
