//
// Created by Abhinav Agrawal on 10/5/22.
//
#include "Stock.h"

Stock :: Stock(){}



Stock :: Stock(double spot, double mean, double ir){
    spot_price = spot;
    mu = mean;
    interest_rate = ir;
}

Stock :: ~Stock(){}




