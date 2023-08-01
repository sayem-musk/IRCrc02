//
//  ClickerCalculation.h
//  TapStar-mobile
//
//  Created by Tarek Saazeb on 9/23/19.
//

#ifndef ClickerCalculation_h
#define ClickerCalculation_h

using namespace std;
#include "IncludeAndroid.h"

class ClickerCalculation
{
public:
#pragma mark- Init Method
    ~ClickerCalculation();
    ClickerCalculation();
    static ClickerCalculation* create();
    virtual bool init();
    
    static string getIterationForAbbreviation(int extentionSize);
    static string getAbbreviationForValue(string amount,string amount_exp);
    static string getAbbreviationForValue(vector<string> *arrAmount);
    
    static string getStringValueForData(string strNumber);
    static string getStringValueForData(vector<string> *arrNumber);
    
    static vector<string> *getDataSet(vector<string> *arrNumber1, vector<string> *arrNumber2);
    
    static bool isSmaller(string _strNumber1, string _strNumber2);
    static bool isSmaller(vector<string> *arrNumber1, vector<string> *arrNumber2);
    
    static vector<string> *addition(string _strNumber1, string _strNumber2);
    static vector<string> *addition(vector<string> *arrNumber1, vector<string> *arrNumber2);
    
    static vector<string> *subtraction(string _strNumber1, string strNumber2);
    static vector<string> *subtraction(vector<string> *arrNumber1, vector<string> *arrNumber2);
    
    static vector<string> *multiplication(string _strNumber1, string _strNumber2);
    static vector<string> *multiplication(vector<string> *arrNumber1, vector<string> *arrNumber2);
    
    static vector<string> *division(string number, long long divisor);
    static vector<string> *division(vector<string> *arrNumber, long long divisor);
    
    static vector<string> *division(string number, string strDivisor);
    static vector<string> *division(vector<string> *arrNumber, vector<string> *divisor);
    
    static float getPercentage(string number, string divisor);
    static float getPercentage(vector<string> *arrNumber, vector<string> *arrDivisor);
    
    static bool isNumberZero(vector<string> *arrNumber);
    static void showNumber(vector<string> *arrNumber,string strExtra="");
    
    static vector<string> *getNewVector(string strNumber1,string strNumber2);
    static vector<string> *getNewVector(string strNumber);
};

#endif /* ClickerCalculation_h */
