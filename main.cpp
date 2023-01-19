#include <iostream>
#include "Option.h"
#include "Simulated_Price.h"
#include "Option_Price.h"
#include "Stock.h"
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include "BSM_Part2.h"
#include "Unit_Test.h"
#define vec(x) vector <double> x;
#define mp(x) map<string, double> x;

using namespace std;

double dateDifference(string, string);

vector <double> timeToMaturity(string expiry_date, map<string, double> interest_rate){

    vector<double> timeTomaturity;
    double ans;

    std:: map<string, double>::iterator ite;

    for(ite = interest_rate.begin();ite!= interest_rate.end();ite++){

        ans = dateDifference(ite ->first, expiry_date);
        timeTomaturity.push_back(ans);

    }
    return timeTomaturity;
}

std::tm ttmd(int day, int month, int year)
{
    std::tm tm = {0};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    return tm;
}


vector<double> map_to_vector(map<string, double> ir){
    vector<double> ans;
    map<string, double>::iterator it;


    for (it = ir.begin();it!= ir.end();it++){
        ans.push_back(it->second);
    }

    return ans;
}

double dateDifference (string date_1, string date_2) {
    string day_1 = date_1.substr(8, 2);
    string month_1 = date_1.substr(5, 2);
    string year_1 = date_1.substr(0, 4);
    string day_2 = date_2.substr(8, 2);
    string month_2 = date_2.substr(5, 2);
    string year_2 = date_2.substr(0, 4);

    std::tm tm1 = ttmd(stoi(day_1), stoi(month_1), stoi(year_1));
    std::tm tm2 = ttmd(stoi(day_2), stoi(month_2), stoi(year_2));

    std::time_t time1 = std::mktime(&tm1);
    std::time_t time2 = std::mktime(&tm2);

    return std::difftime(time2, time1) / (365*60*60*24);

}

map<string, double> file_read_option(string start_date, string end_date, string strike, string option_type, string expiry ) {

    ifstream infile("./op_GOOG.csv");
    if(infile.fail()){
        cout<<"Couldnt open file"<<endl;
    }
    mp(price);
    string datee, exp_date, cp_flag, strike_price, best_bid, best_offer;
    string line;
    int ite=0;

    for (; getline(infile, line); ite++) {

        if (ite < 1) {
            continue;
        }

        stringstream curr_line(line);
        string date;
        getline(curr_line, date, ',');
        datee = date;
        double mm = dateDifference(start_date, datee);
        if (dateDifference(start_date, datee) < 0)
            continue;
        if (dateDifference(end_date, datee) > 0)
            break;

        getline(curr_line, exp_date, ',');
        exp_date = exp_date;
        getline(curr_line, cp_flag, ',');
        cp_flag = cp_flag;
        getline(curr_line, strike_price, ',');
        strike_price = strike_price;

        if ((strike_price == strike) && (cp_flag == option_type) && (dateDifference(exp_date, expiry) == 0)) {

            getline(curr_line, best_bid, ',');
            double bid = std::stod(best_bid);
            getline(curr_line, best_offer, ',');
            double ask = std::stod(best_offer);

            price.insert(make_pair(datee, 0.5 * (bid + ask)));

        } else
            continue;

    }

    infile.close();
    return price;
}


map<string, double> ratesFromTheDate(string start_date, string end_date){
    ifstream infile("./interest.csv");

    if(infile.fail()){
        cout<<"Couldnt open file ir"<<endl;
    }

    mp(ans);
    string line;
    string datee;
    int ite =0;

    for(;getline(infile, line); ite++){
//        cout<<"abcc"<<endl;
        if (ite <1){
            continue;
        }
        string line_from_file;
        double rate ;
        stringstream current_line(line);
        getline(current_line, line_from_file, ',');
        datee = line_from_file;

        if (dateDifference(start_date, datee) <0){
            continue;
        }
        if (dateDifference(end_date, datee) >0){
            break;
        }
        getline(current_line, line_from_file, ',');
        rate = std:: stod(line_from_file);


        ans.insert(make_pair(datee, rate));
//        cout<<rate<<endl;
    }
    infile.close();
    return ans;
}
map<string, double> priceFromDate(string start_date, string end_date){
    ifstream infile("./sec_GOOG.csv");

    if(infile.fail()){
        cout<<"Couldnt open file google"<<endl;
    }

    map<string, double> ans;
    string line;
    string datee;
    int ite=0;

    for(;getline(infile, line); ite++){


        if (ite <1){
            continue;
        }

        string line_from_file;
        double rate ;
        stringstream current_line(line);
        getline(current_line, line_from_file, ',');
        datee = line_from_file;

        if (dateDifference(start_date, datee) <0){
            continue;
        }
        if (dateDifference(end_date, datee) >0){
            break;
        }
        getline(current_line, line_from_file, ',');
        rate = std:: stod(line_from_file);

        ans.insert(make_pair(datee, rate));
//        cout<<rate<<endl;
    }
    infile.close();
    return ans;
}



int main() {

    cout<<"Results of Unit Test Case"<<endl;
    BSM_Part2 bsmPart2{};

    Unit_Test ut{};
    ut.runTest();

    Stock stock{100, 0.05, 0.025};
    Option option{105, true, 0.24};
    int N = 100;
    int n_paths = 1000;
    double time_to_maturity = 0.4;

    Option_Price op{};

//
//    double price = op.BSM_Price(stock, option, time_to_maturity).front();
//    double delta = op.BSM_Price(stock, option, time_to_maturity).back();

    Simulated_Price sp{};

    std::cout << "Simulation of Part 1 started!" << std::endl;
    sp.price_simulate(n_paths, stock, time_to_maturity, N, option);
    std::cout << "Simulation of Part 1 ended!" << std::endl;
    std::cout << "Files have been created!" << std::endl;
    std::cout << "Starting Part 2" << std::endl;
    ifstream infile1("./op_GOOG.csv");
    ifstream infile2("./sec_GOOG.csv");
    ifstream infile3("./interest.csv");
    int ite = 0;
    string line;

    bool isCall = true;
    string startDate;
    string end_window;
    string option_type;
    string strike_price;
    string exp_date;

    double ans = ratesFromTheDate("2011-01-03", "2011-01-11").size();
    BSM_Part2 bp{};
    double k = bp.implied_volatility(44.2,0.0019,532.4,500, true,0.20274);


    double diff = dateDifference("2011-07-05", "2011-09-17");
//    cout<<diff;

//    cout<<anss;

    startDate = "2011-07-05";
    end_window = "2011-07-29";
    exp_date = "2011-09-17";
    strike_price = "500";
//    cout << "Please enter the start date" << endl;
//    cout << "Please enter the end date" << endl;
//    cout << "Enter the expiry date of the option" << endl;
//    cout << "Enter the strike price of the option" << endl;
//
//    cin >> startDate;
//    cin >> end_window;
//    cin >> exp_date;
//    cin >> strike_price;

    map<string, double> ir = ratesFromTheDate(startDate, end_window);
    map<string , double> stock_rate = priceFromDate(startDate, end_window);
    map<string, double> option_price = file_read_option(startDate, end_window,
                                                  strike_price, "C", exp_date);



    bsmPart2.portfolioPnL(map_to_vector(ir), map_to_vector(stock_rate),
                          std:: stod(strike_price), isCall,
                          timeToMaturity(exp_date, ir), map_to_vector(option_price),
                          ir);

    cout<<"Part 2 finished"<<endl;
    cout<<"Result.csv file created"<<endl;
}


