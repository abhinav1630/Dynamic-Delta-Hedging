//
// Created by Abhinav Agrawal on 10/5/22.
//


# include "Option.h"
#include "Option_Price.h"
#include "Stock.h"
#include "Option.h"
# include <math.h>

using namespace std;

Option_Price ::Option_Price() {};
Option_Price ::~Option_Price() {};


double normalCDF(double x){
     return erfc(-x/sqrt(2))/2;
}

std:: vector <double> Option_Price::BSM_Price(Stock &s, Option &o, double ttm ){

    vector <double> ans;
    double delta_of_option;
    double price_of_option;
    double spot_price = s.getSpot();
    double strike_price = o.getStrike();
    double volatility = o.getSigma();
    double interest_rate= s.getInterestRate();

    double d1 = (1 / (volatility * sqrt (ttm))) * (log(spot_price / strike_price)   + (interest_rate + volatility * volatility
                                                                                                 / 2) * ttm);
    double d2 = d1 - volatility * sqrt(ttm);


    if (o.isCallOption()){
        price_of_option = normalCDF(d1) * spot_price - normalCDF(d2) * strike_price * exp(-interest_rate * ttm);
        delta_of_option   = normalCDF(d1);
    }
    else{
        price_of_option  = normalCDF(-d2) * strike_price * exp(-1 * interest_rate * ttm) - normalCDF(-d1) * spot_price;
        delta_of_option = normalCDF(d1) -1;
    }

    ans.push_back(price_of_option);
    ans.push_back(delta_of_option);

    return ans;
}

std :: vector<double> Option_Price::BSM_Price_iv(double spot, double strike, bool isCall, double interest_rate, double volatility
                                    ,double ttm) {



    Option_Price op{};

    double d1 = (1 / (volatility * sqrt (ttm))) * (log(spot / strike)   + (interest_rate + volatility * volatility
                                                                                                       / 2) * ttm);
    double d2 = d1 - volatility * sqrt(ttm);


    double price_of_option;
    double delta_option;
    vector<double> ans;

    if (isCall){
        price_of_option = normalCDF(d1) * spot - normalCDF(d2) * strike * exp(-interest_rate * ttm);
        delta_option   = normalCDF(d1);
    }
    else{
        price_of_option  = normalCDF(-d2) * strike * exp(-1 * interest_rate * ttm) - normalCDF(-d1) * spot;
        delta_option = normalCDF(d1) -1;
    }

    ans.push_back(price_of_option);
    ans.push_back(delta_option);

    return ans;
}

