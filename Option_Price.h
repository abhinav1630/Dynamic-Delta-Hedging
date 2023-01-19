//
// Created by Abhinav Agrawal on 10/5/22.
//

#ifndef MID_TERM_OPTION_PRICE_H
#define MID_TERM_OPTION_PRICE_H
#include "Option.h"
#include "Stock.h"
# include <vector>

using namespace std;
class Option_Price{

public:

    Option_Price();
    ~Option_Price();

    std:: vector<double> BSM_Price(Stock &s, Option &o, double);


    vector<double>
    BSM_Price_iv(double spot, double strike, bool isCall, double interest_rate, double volatilty, double ttm);

};

#endif //MID_TERM_OPTION_PRICE_H
