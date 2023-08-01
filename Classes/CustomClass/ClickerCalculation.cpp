//
//  ClickerCalculation.cpp
//  TapStar-mobile
//
//  Created by Tarek Saazeb on 9/23/19.
//

#include "ClickerCalculation.h"
#include "AppDelegate.h"
#include <cstring>

#define CutOffPoint 100

#pragma mark- Init Method

ClickerCalculation::~ClickerCalculation()
{
    
}

ClickerCalculation::ClickerCalculation()
{
    
}

ClickerCalculation* ClickerCalculation::create()
{
    ClickerCalculation* ret = new ClickerCalculation();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool ClickerCalculation::init()
{
   return true;
}

string ClickerCalculation::getIterationForAbbreviation(int extentionSize)
{
    switch(extentionSize)
    {
        case 1:
            return "K";
            
        case 2:
            return "M";
            
        case 3:
            return "B";
            
        case 4:
            return "t";
            
        case 5:
            return "q";
            
        case 6:
            return "Q";
            
        case 7:
            return "s";
            
        case 8:
            return "S";
            
        case 9:
            return "o";
            
        case 10:
            return "n";
            
        case 11:
            return "d";
            
        case 12:
            return "U";
            
        case 13:
            return "D";
            
        case 14:
            return "T";
            
        case 15:
            return "Qt";
            
        case 16:
            return "Qd";
            
        case 17:
            return "Sd";
            
        case 18:
            return "St";
            
        case 19:
            return "O";
            
        case 20:
            return "N";
            
        case 21:
            return "v";
            
        case 22:
            return "c";
    }
    return "c";
}

string ClickerCalculation::getAbbreviationForValue(string amount,string amount_exp)
{
    vector<string> *arrStr=AppDelegate::componentSeparatedByString(amount, "e");
    if(arrStr->size()==2)
        return amount;
    
    string value=amount;
    
    string exp=CustomMath::addition(to_string(MAX((int)amount.size(), 0)), amount_exp);
    
    if(stoi(exp)>3)
    {
        int exp_modulas=stoi(exp)%3;
        int extentionSize=(stoi(exp))/3;

        for(int i=(int)amount.size();i<10;i++)
        {
            value=value+"0";
        }
        
        if(exp_modulas==0)
        {
            value.insert(3,".");
            value=value.substr(0,6);
            extentionSize=extentionSize-1;
        }
        else if(exp_modulas==1)
        {
            value.insert(1,".");
            value=value.substr(0,4);
        }
        else if(exp_modulas==2)
        {
            value.insert(2,".");
            value=value.substr(0,5);
        }
        
        if(extentionSize>=1 && extentionSize<22)
        {
            value=value+""+ClickerCalculation::getIterationForAbbreviation(extentionSize);
        }
        else
        {
            value=value+"e"+exp;
        }
    }
    else
    {
        for(int i=0;i<stoi(amount_exp);i++)
        {
            value=value+"0";
        }
    }
    
   /* if(amount_exp=="0")
    {
        //if(amount.size()>5)
        {
            string exp=to_string(MAX((int)amount.size(), 0));
            if(stoi(exp)>3)
            {
                value.insert(1,".");
                value=value.substr(0,4);
                if(value.length()==2)
                {
                    value=value+"0";
                }
                
                int extentionSize=(stoi(exp))/3;
                
                if(extentionSize>=1 && extentionSize<22)
                {
                    value=value+""+ClickerCalculation::getIterationForAbbreviation(extentionSize);
                }
                else
                {
                    value=value+"e"+exp;
                }
            }
        }
    }
    else
    {
        string exp=CustomMath::addition(to_string(MAX((int)amount.size(), 0)), amount_exp);
        CCLOG("exp %s",exp.c_str());
        if(stoi(exp)>3)
        {
            value.insert(1,".");
            value=value.substr(0,4);
            
            if(value.length()==2)
            {
                value=value+"0";
            }
            
            int extentionSize=(stoi(exp))/3;
            
            if(extentionSize>=1 && extentionSize<22)
            {
                value=value+" "+ClickerCalculation::getIterationForAbbreviation(extentionSize);
            }
            else
            {
                value=value+"e"+exp;
            }
        }
        else
        {
            for(int i=0;i<stoi(amount_exp);i++)
            {
                value=value+"0";
            }
        }
    }*/
    
    return value;
}

string ClickerCalculation::getAbbreviationForValue(vector<string> *arrAmount)
{
    string amount="0";
    string amount_exp="0";
    
    if(arrAmount->size()==2)
    {
        amount=arrAmount->at(0);
        amount_exp=arrAmount->at(1);
    }
    else if(arrAmount->size()==1)
    {
        amount=arrAmount->at(0);
        amount_exp="0";
    }
    
    return ClickerCalculation::getAbbreviationForValue(amount,amount_exp);
}

string ClickerCalculation::getStringValueForData(string strNumber)
{
    vector<string> *arrNumber=AppDelegate::componentSeparatedByString(strNumber, "e");

    return ClickerCalculation::getStringValueForData(arrNumber);
}

string ClickerCalculation::getStringValueForData(vector<string> *arrNumber)
{
//    if(arrNumber->size()==0)
//        return "0";
    
    string strNumber=arrNumber->at(0);
    
    if(arrNumber->size()==2)
    {
        for (int i = 0; i < stoi(arrNumber->at(1)); i++) {
            strNumber=strNumber+"0";
        }
    }
    
    return strNumber;
}

#pragma mark- Math

vector<string> *ClickerCalculation::getDataSet(vector<string> *arrNumber1, vector<string> *arrNumber2)
{
    string strNumber1="0";
    string strExp1="0";
    string strNumber2="0";
    string strExp2="0";
    
    if(arrNumber1->size()==1 && arrNumber2->size()==1)
    {
        strNumber1=arrNumber1->at(0);
        strExp1="0";
        strNumber2=arrNumber2->at(0);
        strExp2="0";
    }
    else if(arrNumber1->size()==2 && arrNumber2->size()==1)
    {
        strNumber1=arrNumber1->at(0);
        strExp1=arrNumber1->at(1);
        strNumber2=arrNumber2->at(0);
        strExp2="0";
    }
    else if(arrNumber1->size()==1 && arrNumber2->size()==2)
    {
        strNumber1=arrNumber1->at(0);
        strExp1="0";
        strNumber2=arrNumber2->at(0);
        strExp2=arrNumber2->at(1);
    }
    else if(arrNumber1->size()==2 && arrNumber2->size()==2)
    {
        strNumber1=arrNumber1->at(0);
        strExp1=arrNumber1->at(1);
        strNumber2=arrNumber2->at(0);
        strExp2=arrNumber2->at(1);
    }
    vector<string> *arrNumber=new vector<string>();
    arrNumber->push_back(strNumber1);
    arrNumber->push_back(strExp1);
    arrNumber->push_back(strNumber2);
    arrNumber->push_back(strExp2);
    
    return arrNumber;
}

bool ClickerCalculation::isSmaller(string _strNumber1, string _strNumber2)
{
    vector<string> *arrNumber1=AppDelegate::componentSeparatedByString(_strNumber1, "e");
    vector<string> *arrNumber2=AppDelegate::componentSeparatedByString(_strNumber2, "e");
    
    return ClickerCalculation::isSmaller(arrNumber1, arrNumber2);
}

bool ClickerCalculation::isSmaller(vector<string> *arrNumber1, vector<string> *arrNumber2)
{
    vector<string> *dataSet=ClickerCalculation::getDataSet(arrNumber1,arrNumber2);
    
    string strNumber1="0";
    string strExp1="0";
    string strNumber2="0";
    string strExp2="0";
    
    if(dataSet->size()==4)
    {
        strNumber1=dataSet->at(0);
        strExp1=dataSet->at(1);
        strNumber2=dataSet->at(2);
        strExp2=dataSet->at(3);
    }
    
    int length1=(int)strNumber1.length()+stoi(strExp1);
    int length2=(int)strNumber2.length()+stoi(strExp2);
    
    if(length1<length2)
    {
        return true;
    }
    else if(length1>length2)
    {
        return false;
    }
    else
    {
        if(strExp1!=strExp2)
        {
            return CustomMath::isSmaller(strExp1, strExp2);
        }
        else
        {
            return CustomMath::isSmaller(strNumber1, strNumber2);
        }
    }
}

vector<string>* ClickerCalculation::addition(string _strNumber1, string _strNumber2)
{
    vector<string> *arrNumber1=AppDelegate::componentSeparatedByString(_strNumber1, "e");
    vector<string> *arrNumber2=AppDelegate::componentSeparatedByString(_strNumber2, "e");
    
    vector<string> *answer=ClickerCalculation::addition(arrNumber1, arrNumber2);
    
    return answer;
}

vector<string>* ClickerCalculation::addition(vector<string> *arrNumber1, vector<string> *arrNumber2)
{
    //CCLOG("---------------------------------------------------");
    vector<string> *answer=new vector<string>();
    
    vector<string> *dataSet=ClickerCalculation::getDataSet(arrNumber1,arrNumber2);
    
    string strNumber1="0";
    string strExp1="0";
    string strNumber2="0";
    string strExp2="0";
    
    if(dataSet->size()==4)
    {
        strNumber1=dataSet->at(0);
        strExp1=dataSet->at(1);
        strNumber2=dataSet->at(2);
        strExp2=dataSet->at(3);
    }
    
    string addition="0";
    string exp="0";
 
    int length1=(int)strNumber1.length()+stoi(strExp1);
    int length2=(int)strNumber2.length()+stoi(strExp2);
    
    //CCLOG("strNumber1 %s strExp1 %s",strNumber1.c_str(),strExp1.c_str());
    //CCLOG("strNumber2 %s strExp2 %s",strNumber2.c_str(),strExp2.c_str());
    //CCLOG("length1 %d length2 %d",length1,length2);
    
    if(length1<CutOffPoint && length2<CutOffPoint)
    {
        strNumber1=ClickerCalculation::getStringValueForData(arrNumber1);
        strNumber2=ClickerCalculation::getStringValueForData(arrNumber2);
        
        addition=CustomMath::addition(strNumber1, strNumber2);
        exp="0";
    }
    else if(length1>CutOffPoint && length2<CutOffPoint)
    {
        addition=strNumber1;
        exp=strExp1;
    }
    else if(length1<CutOffPoint && length2>CutOffPoint)
    {
        addition=strNumber2;
        exp=strExp2;
    }
    else
    {
        if(length1>=length2)
        {
            int length=length1;
            
            addition="0";
            exp=strExp1;
            
            while (true)
            {
                length=length-length2;
                if(length<0)
                    break;
                
                addition=CustomMath::addition(addition,strNumber1);
                addition=CustomMath::addition(addition,strNumber2);
            }
            
            if(addition.length()>strNumber1.length())
            {
                int extra=(int)addition.length()-(int)strNumber1.length();
                
                addition=addition.substr(0,addition.length()-extra);
                exp=CustomMath::addition(exp, to_string(extra));
            }
        }
        else
        {
            int length=length2;
            
            addition="0";
            exp=strExp2;
            
            while (true)
            {
                length=length-length1;
                if(length<0)
                    break;
                
                addition=CustomMath::addition(addition,strNumber1);
                addition=CustomMath::addition(addition,strNumber2);
            }
            
            if(addition.length()>strNumber2.length())
            {
                int extra=(int)addition.length()-(int)strNumber2.length();
                
                addition=addition.substr(0,addition.length()-extra);
                exp=CustomMath::addition(exp, to_string(extra));
            }
        }
    }
    //CCLOG("addition %s exp %s",addition.c_str(),exp.c_str());
    
    answer->push_back(addition);
    answer->push_back(exp);
    
    return answer;
}


vector<string>* ClickerCalculation::subtraction(string _strNumber1, string _strNumber2)
{
    vector<string> *arrNumber1=AppDelegate::componentSeparatedByString(_strNumber1, "e");
    vector<string> *arrNumber2=AppDelegate::componentSeparatedByString(_strNumber2, "e");
    
    vector<string> *answer=ClickerCalculation::subtraction(arrNumber1, arrNumber2);
    
    return answer;
}

vector<string>* ClickerCalculation::subtraction(vector<string> *arrNumber1, vector<string> *arrNumber2)
{
    vector<string> *answer=new vector<string>();
    
    vector<string> *dataSet=ClickerCalculation::getDataSet(arrNumber1,arrNumber2);
    
    string strNumber1="0";
    string strExp1="0";
    string strNumber2="0";
    string strExp2="0";
    
    if(dataSet->size()==4)
    {
        strNumber1=dataSet->at(0);
        strExp1=dataSet->at(1);
        strNumber2=dataSet->at(2);
        strExp2=dataSet->at(3);
    }
    
    if(ClickerCalculation::isSmaller(arrNumber1, arrNumber2))
    {
        string temp=strNumber1;
        strNumber1=strNumber2;
        strNumber2=temp;
        
        temp=strExp1;
        strExp1=strExp2;
        strExp2=strExp1;
    }
    
    //CCLOG("---------------------------------------------------");
    
    string subtraction="0";
    string exp="0";
    
    int length1=(int)strNumber1.length()+stoi(strExp1);
    int length2=(int)strNumber2.length()+stoi(strExp2);
    
//    CCLOG("strNumber1 %s strExp1 %s",strNumber1.c_str(),strExp1.c_str());
//    CCLOG("strNumber2 %s strExp2 %s",strNumber2.c_str(),strExp2.c_str());
//    CCLOG("length1 %d length2 %d",length1,length2);
    
    if(length1<CutOffPoint && length2<CutOffPoint)
    {
        strNumber1=ClickerCalculation::getStringValueForData(arrNumber1);
        strNumber2=ClickerCalculation::getStringValueForData(arrNumber2);
        
        subtraction=CustomMath::subtraction(strNumber1, strNumber2);
        exp="0";
    }
    else if(length1>CutOffPoint && length2<CutOffPoint)
    {
        subtraction=strNumber1;
        exp=strExp1;
    }
    else
    {
        int length=length1;
        
        subtraction=strNumber1;
        exp=strExp1;
        
        while (true)
        {
            length=length-length2;
            if(length<0)
                break;
            
            if(ClickerCalculation::isSmaller(strNumber1, subtraction))
            {
                if(exp!="0")
                    exp=CustomMath::subtraction(exp,"1");
                subtraction=strNumber1;
            }
            else
                subtraction=CustomMath::subtraction(strNumber1,subtraction);
            
            if(ClickerCalculation::isSmaller(strNumber2, subtraction))
            {
                if(exp!="0")
                    exp=CustomMath::subtraction(exp,"1");
                
                subtraction=strNumber2;
            }
            else
                subtraction=CustomMath::subtraction(strNumber2,subtraction);
        }
    }
    
    //CCLOG("subtraction %s exp %s",subtraction.c_str(),exp.c_str());
    
    if(subtraction=="0" && exp!="0")
        subtraction="1";
    
    answer->push_back(subtraction);
    answer->push_back(exp);
    
    return answer;
}

vector<string>* ClickerCalculation::multiplication(string _strNumber1, string _strNumber2)
{
    vector<string> *arrNumber1=AppDelegate::componentSeparatedByString(_strNumber1, "e");
    vector<string> *arrNumber2=AppDelegate::componentSeparatedByString(_strNumber2, "e");
    
    vector<string>* answer=ClickerCalculation::multiplication(arrNumber1, arrNumber2);
    
    return answer;
}

vector<string>* ClickerCalculation::multiplication(vector<string> *arrNumber1, vector<string> *arrNumber2)
{
    vector<string> *answer=new vector<string>();
    
    vector<string> *dataSet=ClickerCalculation::getDataSet(arrNumber1,arrNumber2);
    
    string strNumber1="0";
    string strExp1="0";
    string strNumber2="0";
    string strExp2="0";
    
    if(dataSet->size()==4)
    {
        strNumber1=dataSet->at(0);
        strExp1=dataSet->at(1);
        strNumber2=dataSet->at(2);
        strExp2=dataSet->at(3);
    }
    
//    CCLOG("---------------------------------------------------");
//
//    CCLOG("strNumber1 %s strExp1 %s",strNumber1.c_str(),strExp1.c_str());
//    CCLOG("strNumber2 %s strExp2 %s",strNumber2.c_str(),strExp2.c_str());
    
    string multiplication="0";
    string exp="0";
    if(strExp1=="0" && strExp2=="0")
    {
        
        multiplication=CustomMath::multiplication(strNumber1, strNumber2);
        exp="0";
    }
    else
    {
        int maxLength=(int)strNumber1.length();
        
        if(strNumber1.length()<strNumber2.length())
            maxLength=(int)strNumber2.length();
        
        multiplication=CustomMath::multiplication(strNumber1, strNumber2);
        exp=CustomMath::addition(strExp1, strExp2);
        
        if(multiplication.length()>maxLength)
        {
            int extra=(int)multiplication.length()-maxLength;
            
            multiplication=multiplication.substr(0,multiplication.length()-extra);
            exp=CustomMath::addition(exp, to_string(extra));
        }
    }
    
    answer->push_back(multiplication);
    answer->push_back(exp);
    
    return answer;
}

vector<string>* ClickerCalculation::division(string number, long long divisor)
{
    vector<string> *arrNumber=AppDelegate::componentSeparatedByString(number, "e");
    vector<string>* division=ClickerCalculation::division(arrNumber, divisor);
    
    return division;
}

vector<string>* ClickerCalculation::division(vector<string> *arrNumber, long long divisor)
{
    vector<string> *arrDivisor=new vector<string>();
    arrDivisor->push_back(to_string(divisor));
    arrDivisor->push_back("0");
    
    vector<string> *answer=ClickerCalculation::division(arrNumber, arrDivisor);

    return answer;
}

vector<string>* ClickerCalculation::division(string number, string strDivisor)
{
    vector<string> *arrNumber=AppDelegate::componentSeparatedByString(number, "e");
    vector<string> *arrDivisor=AppDelegate::componentSeparatedByString(strDivisor, "e");
    vector<string>* division=ClickerCalculation::division(arrNumber, arrDivisor);
    
    return division;
}

vector<string>* ClickerCalculation::division(vector<string> *arrNumber, vector<string> *arrDivisor)
{
    vector<string> *answer=new vector<string>();
    
    string strNumber="0";
    string strExp="0";
    
    vector<string> *dataSet=ClickerCalculation::getDataSet(arrNumber,arrDivisor);
    
    string strNumber1="0";
    string strExp1="0";
    string strNumber2="0";
    string strExp2="0";
    
    if(dataSet->size()==4)
    {
        strNumber1=dataSet->at(0);
        strExp1=dataSet->at(1);
        strNumber2=dataSet->at(2);
        strExp2=dataSet->at(3);
    }
    
    string division=CustomMath::division(strNumber1, stoll(strNumber2));
    string exp=CustomMath::subtraction(strExp1, strExp2);
    
    if(division=="0")
    {
        if(exp!="0")
        {
            division="1";
            exp=CustomMath::addition(exp,"1");
        }
    }
    
    answer->push_back(division);
    answer->push_back(exp);
    
    return answer;
}

float ClickerCalculation::getPercentage(string strNumber, string strDivisor)
{
    vector<string> *arrNumber=AppDelegate::componentSeparatedByString(strNumber, "e");
    vector<string> *arrDivisor=AppDelegate::componentSeparatedByString(strDivisor, "e");
    float division=ClickerCalculation::getPercentage(arrNumber, arrDivisor);
    
    return division;
}

float ClickerCalculation::getPercentage(vector<string> *arrNumber, vector<string> *arrDivisor)
{
    vector<string> *dataSet=ClickerCalculation::getDataSet(arrNumber,arrDivisor);
    
    string strNumber1="0";
    string strExp1="0";
    string strNumber2="0";
    string strExp2="0";
    
    if(dataSet->size()==4)
    {
        strNumber1=dataSet->at(0);
        strExp1=dataSet->at(1);
        strNumber2=dataSet->at(2);
        strExp2=dataSet->at(3);
    }
    
    if(strExp1!="0")
        return 100;
    
    if(ClickerCalculation::isSmaller(strNumber1, strNumber2)==false)
        return 100;
    
    string answer=CustomMath::multiplication(strNumber1, "100");
    answer=CustomMath::division(answer, stoll(strNumber2));
    float finalAnswer=stof(answer);
    
    return finalAnswer;
}


bool ClickerCalculation::isNumberZero(vector<string> *arrNumber)
{
    if(arrNumber->size()==2)
    {
        if(arrNumber->at(0)=="0" && arrNumber->at(1)=="0")
            return true;
    }
    else if(arrNumber->size()==1)
    {
        if(arrNumber->at(0)=="0")
            return true;
    }
    else if(arrNumber->size()==0)
    {
            return true;
    }
    return false;
}

void ClickerCalculation::showNumber(vector<string> *arrNumber,string strExtra)
{
    if(arrNumber->size()==2)
    {
        CCLOG("%s Number %s exp %s",strExtra.c_str(),arrNumber->at(0).c_str(),arrNumber->at(1).c_str());
    }
    else if(arrNumber->size()==1)
    {
        CCLOG("%s Number %s exp 0",strExtra.c_str(),arrNumber->at(0).c_str());
    }
}

vector<string> *ClickerCalculation::getNewVector(string strNumber1,string strNumber2)
{
    vector<string> *arrNumber=new vector<string>();
    arrNumber->push_back(strNumber1);
    arrNumber->push_back(strNumber2);
    return arrNumber;
}


vector<string> *ClickerCalculation::getNewVector(string strNumber)
{
    vector<string> *arrNumber=new vector<string>();
    arrNumber->push_back(strNumber);
    return arrNumber;
}









