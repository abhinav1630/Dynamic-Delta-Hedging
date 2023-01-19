//
// Created by Abhinav Agrawal on 10/5/22.
//

#ifndef MID_TERM_SIMULATED_PRICE_H
#define MID_TERM_SIMULATED_PRICE_H
# include "Stock.h"
#include "Option.h"


class Simulated_Price{

public:
    Simulated_Price();
    ~Simulated_Price();
    double price_simulate(int, Stock s,  double, double, Option o);

};

#endif //MID_TERM_SIMULATED_PRICE_H
