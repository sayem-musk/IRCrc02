//
//  CustomMath.cpp
//  MUSK-mobile
//
//  Created by Tarek Saazeb on 9/16/19.
//

#include "CustomMath.h"
#include "AppDelegate.h"

#pragma mark- Init Method

CustomMath::~CustomMath()
{
    
}

CustomMath::CustomMath()
{
    
}

CustomMath* CustomMath::create()
{
    CustomMath* ret = new CustomMath();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool CustomMath::init()
{
    return false;
}

bool CustomMath::isSmaller(string strNumber1, string strNumber2)
{
    // Calculate lengths of both string
    long n1 = strNumber1.length(), n2 = strNumber2.length();
    
    if (n1 < n2)
        return true;
    if (n2 < n1)
        return false;
    
    for (int i=0; i<n1; i++)
    {
        if (strNumber1[i] < strNumber2[i])
            return true;
        else if (strNumber1[i] > strNumber2[i])
            return false;
    }
    
    return false;
}

string CustomMath::addition(string strNumber1, string strNumber2)
{
    //CCLOG("strNumber1 %s",strNumber1.c_str());
    //CCLOG("strNumber2 %s",strNumber2.c_str());
    
    if (strNumber1.length() > strNumber2.length())
    swap(strNumber1, strNumber2);
    
    string answer = "";
    
    long n1 = strNumber1.length(), n2 = strNumber2.length();
    long diff = n2 - n1;
    
    int carry = 0;
    
    for (long i=n1-1; i>=0; i--)
    {
        int sum = ((strNumber1[i]-'0') +
                   (strNumber2[i+diff]-'0') +
                   carry);
        answer.push_back(sum%10 + '0');
        carry = sum/10;
    }
    
    for (long i=n2-n1-1; i>=0; i--)
    {
        int sum = ((strNumber2[i]-'0')+carry);
        answer.push_back(sum%10 + '0');
        carry = sum/10;
    }
    
    if (carry)
        answer.push_back(carry+'0');
    
    reverse(answer.begin(), answer.end());
    
    return answer;
}

string CustomMath::subtraction(string strNumber1, string strNumber2)
{
//    CCLOG("strNumber1 %s",strNumber1.c_str());
//    CCLOG("strNumber2 %s",strNumber2.c_str());
    
    if (isSmaller(strNumber1, strNumber2))
        swap(strNumber1, strNumber2);
    
    string answer = "";
    
    long n1 = strNumber1.length(), n2 = strNumber2.length();
    
    reverse(strNumber1.begin(), strNumber1.end());
    reverse(strNumber2.begin(), strNumber2.end());
    
    int carry = 0;
    
    for (int i=0; i<n2; i++)
    {
        int sub = ((strNumber1[i]-'0')-(strNumber2[i]-'0')-carry);
        
        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
        carry = 0;
        
        answer.push_back(sub + '0');
    }
    
    for (long i=n2; i<n1; i++)
    {
        int sub = ((strNumber1[i]-'0') - carry);
        
        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
        carry = 0;
        
        answer.push_back(sub + '0');
    }
    
    while(answer[answer.length()-1]=='0')
    {
        answer = answer.substr(0, answer.length()-1);
    }
    
    reverse(answer.begin(), answer.end());
    if(answer.length()==0)
        answer="0";
    
    return answer;
}

string CustomMath::multiplication(string strNumber1, string strNumber2)
{
//    CCLOG("strNumber1 %s",strNumber1.c_str());
//    CCLOG("strNumber2 %s",strNumber2.c_str());
    
    long len1 = strNumber1.length();
    long len2 = strNumber2.length();
    
    if (len1 == 0 || len2 == 0)
        return "0";
    
    vector<int> result(len1 + len2, 0);
    
    int i_n1 = 0;
    int i_n2 = 0;
    
    for (long i=len1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = strNumber1[i] - '0';
        
        i_n2 = 0;
        
        for (long j=len2-1; j>=0; j--)
        {
            int n2 = strNumber2[j] - '0';
            
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;
            carry = sum/10;
            result[i_n1 + i_n2] = sum % 10;
            i_n2++;
        }
        
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
        i_n1++;
    }
    
    long i = result.size() - 1;
    while (i>=0 && result[i] == 0)
        i--;
    
    if (i == -1)
        return "0";
    
    string answer = "";
    
    while (i >= 0)
        answer += to_string(result[i--]);
    
    return answer;
}

string CustomMath::division(string number, long long divisor)
{
    //CCLOG("strNumber1 %s",number.c_str());
    //CCLOG("strNumber2 %lld",divisor);
    
    string answer;
    
    int idx = 0;
    long long temp = number[idx] - '0';
    while (temp < divisor)
    {
        temp = temp * 10 + (number[++idx] - '0');
    }
    
    while (number.size() > idx)
    {
        answer += (temp / divisor) + '0';
        
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }
    
    if (answer.length() == 0)
        return "0";
    return answer;
}

string CustomMath::modulus(string number, long long divisor)
{
    string division=CustomMath::division(number,divisor);
    string multiplication=CustomMath::multiplication(division, to_string(divisor));
    string answer=CustomMath::subtraction(number, multiplication);
    
    return answer;
}

string CustomMath::power(float base, int exponent)
{
//    CCLOG("-----------------");
//    CCLOG("base %f exponent %d",base,exponent);
    string finalValue="0";
    while(true)
    {
        int exponentToCalculate=exponent;
        if(exponent>95)
            exponentToCalculate=95;
        
        //CCLOG("base %f exponent %d",base,exponent);
        //CCLOG("(1+((+10)/(+1))) "+(1+((+10)/(+1))));
        float currentValue=pow(base,exponentToCalculate);
        //CCLOG("currentValue---1 %f",currentValue);
        
        currentValue=floor((currentValue+0.5))*100;
        int value=(int)currentValue;
        //CCLOG("currentValue---2 %d",value);
        finalValue=CustomMath::addition(finalValue,to_string(value));
        //CCLOG("finalValue---1 %s",finalValue.c_str());
        finalValue=CustomMath::division(finalValue,100);
        //CCLOG("finalValue---2 %s",finalValue.c_str());
        
        exponent=exponent-exponentToCalculate;
        
        //CCLOG("exponent %d",exponent);
        
        if(exponent==0)
            break;
    }
    //CCLOG("finalValue %s",finalValue.c_str());
    
    
    return finalValue;
}





