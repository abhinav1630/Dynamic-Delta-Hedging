//
// Created by Abhinav Agrawal on 10/5/22.
//

#ifndef MID_TERM_STOCK_H
#define MID_TERM_STOCK_H


class Stock{

private:
    double spot_price;
    double mu;
    double interest_rate;

public:
    Stock();
    ~Stock();
    Stock(double, double, double );

    double getSpot(){
        return spot_price;
    }
    double getMean(){
        return mu;
    }

    double getInterestRate(){
        return interest_rate;
    }

    void setSpot(double S){
        spot_price = S;
    }

    void setMean(double mu){
        this -> mu = mu;
    }

    void setInterestRate(double int_rate){
        interest_rate = int_rate;
    }

};
#endif //MID_TERM_STOCK_H
