//
// Created by Abhinav Agrawal on 10/6/22.
//

#ifndef MID_TERM_BSM_PART2_H
#define MID_TERM_BSM_PART2_H

#include <vector>
#include <map>
#include <string>
class BSM_Part2{

public:
    BSM_Part2();
    ~BSM_Part2();


    double implied_volatility(double price_from_file, double interest_rate, double spot, double strike, bool isCall,
                              double time_to_maturity);


    void portfolioPnL(std::vector<double> interest_rate, std::vector<double> stock_price, double strike,
                        bool isCall, std::vector<double> time_to_maturity, std:: vector <double>,
                                std:: map<std :: string, double >);
};

#endif //MID_TERM_BSM_PART2_H
