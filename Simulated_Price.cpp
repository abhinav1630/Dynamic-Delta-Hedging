
//
// Created by Abhinav Agrawal on 10/5/22.
//
# include "Simulated_Price.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <random>
# include <fstream>

# include <ostream>
#include  "Stock.h"
# include "Option_Price.h"


using namespace std;

Simulated_Price ::Simulated_Price() {}
Simulated_Price::~Simulated_Price() {}

//Source: https://stackoverflow.com/questions/28618900/c-generate-random-numbers-following-normal-distribution-within-range
double Simulated_Price :: price_simulate(int paths, Stock s,double time_to_maturity, double N, Option o){

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0,1.0);
    Option_Price op{};
    std:: ofstream file_1;
    std:: ofstream file_2;
    std:: ofstream file_3;

    file_1.open("HedgingError.csv");
    file_2.open("stock_path.csv");
    file_3.open("option_price.csv");

    double delta_T = time_to_maturity/N;

    double simulated_price[int(N)+1];
    double option_price [int(N)+1];
    double delta_option[int(N)+1];
    double hedging_error[int(N) +1];
    double bank_account[int(N) +1];
    double spot_at_zero = s.getSpot();

    simulated_price[0] = spot_at_zero;
    option_price[0] = op.BSM_Price(s, o, time_to_maturity).front();
    delta_option [0] = op.BSM_Price(s, o,time_to_maturity).back();
    bank_account [0] = option_price[0] - delta_option[0] * s.getSpot();

    static double inter_rate = s.getInterestRate();
    static double sig = o.getSigma();

    double rand = distribution(generator);
    file_1 << to_string(hedging_error[0])<<endl;
    while (paths --){
        for (int i = 1;i <= int(N); i++){
            simulated_price[i] = (simulated_price[i-1] +  (s.getMean()*simulated_price[i-1] * delta_T) +
                                  (simulated_price[i-1] * sig* sqrt(delta_T)* distribution(generator)));
//         cout<<simulated_price[i];




            s.setSpot(simulated_price[i]);
            option_price[i] = op.BSM_Price(s, o, time_to_maturity- (i+1) * delta_T).front();

            delta_option[i] = op.BSM_Price(s, o, time_to_maturity-(i+1) * delta_T).back();
            bank_account[i] = delta_option[i-1]*simulated_price[i] + bank_account[i-1]*exp(s.getInterestRate()*delta_T) -
                              delta_option[i]*simulated_price[i];

            hedging_error[i] = delta_option[i-1] * simulated_price[i] + bank_account[i-1] * exp(s.getInterestRate() * delta_T) -
                               option_price[i];
//         file_1<< hedging_error[i]<<",";
            file_2 <<simulated_price[i]<<",";
            file_3 <<option_price[i-1]<<",";

            double kk = hedging_error[i];

        }
        file_1 << to_string(hedging_error[int(N)-1])<<endl;
        file_2 << endl;
        file_3 <<  endl;
    }
}









