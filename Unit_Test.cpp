//
// Created by Abhinav Agrawal on 10/14/22.
//
# include "Unit_Test.h"



#include "Unit_Test.h"
#include <iostream>
#include <fstream>
#include "Option.h"
#include "Stock.h"
#include <string>
#include "Option_Price.h"
#include "BSM_Part2.h"

Unit_Test::Unit_Test() {}

Unit_Test::~Unit_Test() {}

void BS_Price_Test() {

    Option_Price op;
    double underlying_price = 630;
    double strike_price = 600;
    double interest_rate = 0.002;
    double time_to_maturity = 0.0822;
    double sigma = 0.3;

    double actual_bs_price = 39.45;

    double calculated_bs_price = op.BSM_Price_iv(underlying_price, strike_price, true,interest_rate,sigma, time_to_maturity).front();

    if (abs(calculated_bs_price - actual_bs_price) < 0.2) {
        cout << "Black Scholes Option Price function returns correct value" << endl;
    } else {
        cout << "Black Scholes Option Price function does not return correct value" << " " << calculated_bs_price << endl;
    }

}

void BS_Delta_Test() {

    Option_Price op;
    double underlying_price = 630;
    double strike_price = 600;
    double interest_rate = 0.002;
    double time_to_maturity = 0.0822;
    double sigma = 0.3;
    double actual_bs_delta = 0.729;
    double calculated_bs_delta = op.BSM_Price_iv(underlying_price, strike_price, true,interest_rate,sigma, time_to_maturity).back();

    if (abs(calculated_bs_delta - actual_bs_delta) < 0.2) {
        cout << "Black Scholes Option Delta function returns correct value" << endl;
    } else {
        cout << "Black Scholes Option Delta function does not return correct value" << " " << calculated_bs_delta << endl;
    }
}

void IV_Test() {
    BSM_Part2 pl;
    double option_target_price = 40;
    double underlying_price = 630;
    double strike_price = 600;
    double bank_rate = 0.002;
    double time_to_maturity = 0.0822;

    double vol_real_ans = 0.3089;
    double our_ans = pl.implied_volatility(option_target_price, bank_rate, underlying_price,strike_price, true, time_to_maturity);

    if (abs(our_ans - vol_real_ans) < 0.05) {
        cout << "Implied Volatility function returns correct value" << endl;
    } else {
        cout << "Implied Volatility function does not return correct value" << endl;
    }

}
void Unit_Test::runTest() {
    BS_Price_Test();
    BS_Delta_Test();
    IV_Test();
}

