//
// Created by Abhinav Agrawal on 10/5/22.
//

#ifndef MID_TERM_OPTION_H
#define MID_TERM_OPTION_H

class Option{

public:

    Option();
    ~Option();
    Option(double , bool, double );

    double getSigma(){
        return volatility;
    }

    double getStrike(){
        return strike_price;
    }

    bool isCallOption(){
        return isCall;
    }


private:
    void init();
double strike_price;
bool isCall;
double volatility;



};


#endif //MID_TERM_OPTION_H
