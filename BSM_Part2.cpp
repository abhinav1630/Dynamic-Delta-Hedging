//
// Created by Abhinav Agrawal on 10/6/22.
//

# include "BSM_Part2.h"
#include "Option_Price.h"
#include "Option.h"
# include <fstream>
# include <ostream>
#include "Simulated_Price.h"
#include <iostream>
# include <math.h>
#include <cmath>

#define fon(i,a,n) for(int i =n;i<a.size();i++)
#define vec(x) vector<double> x;

using namespace std;

BSM_Part2::BSM_Part2() {}
BSM_Part2 ::~BSM_Part2() {}

double BSM_Part2 ::implied_volatility(double price_from_file, double interest_rate, double spot, double strike, bool isCall,
                                      double time_to_maturity) {
    double a = 0.00001;
    double b = 1;

    double x = 0.5 *  (a+b);
    double epsilon = 0.0001;
    Option_Price op{};

    double price_from_BSM = op.BSM_Price_iv(spot, strike, isCall,interest_rate,x, time_to_maturity).front();

    while (abs (price_from_file - price_from_BSM) > epsilon) {

        if (price_from_BSM < price_from_file){
            a = x;
        }
        else{
            b = x;
        }
        x = 0.5 * (a+b);
        price_from_BSM = op.BSM_Price_iv(spot, strike, isCall, interest_rate, x , time_to_maturity).front();
    }
    return x;
}

void BSM_Part2 :: portfolioPnL(vector <double> interest_rate, vector<double> stock_price, double strike,
                                 bool isCall, vector <double> time_to_maturity, vector <double> option_price,
                                 map<string, double> ir){

    vec(implied_vol);
    vec(delta);
//    vec(option_price);
    vec(bank_account);
    vec(hedging_error);
    vec(pnl_with_hedge);

    double hedging_err;
    double portfolio_value;
    vec(pnl);

    hedging_error.push_back(0);
    pnl_with_hedge.push_back(0);
    double delta_t = 1/252;
    Option_Price op{};
//    pnl.push_back(0);
    double hedging_error_timestep;
    double delta_time_step;

    fon(i,interest_rate,0) {
        implied_vol.push_back(implied_volatility(option_price[i], interest_rate[i] / 100,
                                            stock_price[i], strike,
                                            isCall, time_to_maturity[i]));

//      option_price[i] = op.BSM_Price_iv(spot, strike, isCall, interest_rate[i],implied_vol[i],time_to_maturity[i]).front();
        delta_time_step  = op.BSM_Price_iv(stock_price[i], strike, isCall, interest_rate[i] / 100, implied_vol[i],
                                   time_to_maturity[i]).back();
        delta.push_back(delta_time_step);
        pnl.push_back(option_price[0] - option_price[i]);

        if (i == 0) {
            portfolio_value = option_price[0] - delta[0] * stock_price[0];
        } else {
            portfolio_value =
                    delta[i - 1] * stock_price[i] + bank_account[i - 1] * exp(interest_rate[i] / 100 * delta_t) -
                    delta[i] * stock_price[i];

            hedging_err =
                    delta[i - 1] * stock_price[i] + bank_account[i - 1] * exp(interest_rate[i - 1] / 100 * delta_t) -
                    option_price[i];

            hedging_error_timestep = (delta[i-1]*stock_price[i]-option_price[i]+(option_price[i-1]-delta[i-1]*stock_price[i-1])*exp(interest_rate[i-1]*delta_t));
            hedging_error.push_back(hedging_error_timestep);
            pnl_with_hedge.push_back(hedging_err);

        }
        bank_account.push_back(portfolio_value);
    }


    ofstream output;
    output.open("result.csv", std::ios_base::app);

    map<string, double>::iterator itr;
    output << "Date,Stock Price, Option Price, Implied Volatility, Delta, Hedging Error, PNL, PNL with hedge" << endl;
    int i = 0;
    for (itr = ir.begin(); itr != ir.end(); ++itr, i++) {
        output << itr->first << "," << stock_price[i] << "," << option_price[i] << "," << implied_vol[i] << ","
        << delta[i] << "," << hedging_error[i] << "," << pnl[i]<< "," << pnl_with_hedge[i]  << endl;
    }

    output.close();
}



