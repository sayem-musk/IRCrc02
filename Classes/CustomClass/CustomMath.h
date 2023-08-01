//
//  CustomMath.h
//  MUSK-mobile
//
//  Created by Tarek Saazeb on 9/16/19.
//

#ifndef CustomMath_h
#define CustomMath_h

#include <stdio.h>
#include "IncludeAndroid.h"

using namespace std;

class CustomMath
{
public:
#pragma mark- Init Method
    ~CustomMath();
    CustomMath();
    static CustomMath* create();
    virtual bool init();
    
    static bool isSmaller(string strNumber1, string strNumber2);
    static string addition(string strNumber1, string strNumber2);
    static string subtraction(string strNumber1, string strNumber2);
    static string multiplication(string strNumber1, string strNumber2);
    static string division(string number, long long divisor);
    static string modulus(string number, long long divisor);
    static string power(float base, int exponent);
};

#endif /* CustomMath_h */
