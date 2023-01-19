//
// Created by Abhinav Agrawal on 10/5/22.
//

#include "Option.h"

Option::Option() {}
Option::~Option() {}

Option :: Option(double strike, bool call, double sigma){
    strike_price = strike;
    isCall = call;
    volatility = sigma;
}
