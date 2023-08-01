//
//  AlertView.h
//  MUSK
//
//  Created by Tarek Saazeb on 6/12/16.
//
//

#ifndef AlertView_h
#define AlertView_h

#include "cocos2d.h"
#include "extensions/ExtensionExport.h"

USING_NS_CC;
using namespace std;

class CC_EX_DLL AlertViewDelegate
{
public:
    virtual ~AlertViewDelegate();
    virtual void alertViewCallBack(int tag,int buttonIndex);
};


class AlertView : public Node
{
public:
    AlertViewDelegate *alertViewDelegate;
    vector<string> *buttonsTitle;
    string title;
    string message;
    int tag;
    Menu *buttonMenu;
    
    ~AlertView();
    AlertView();
    static AlertView* create(string _title,string _message,AlertViewDelegate *pDelegate);
    virtual bool init(string _title,string _message,AlertViewDelegate *pDelegate);
    bool onTouchBegan(Touch*, Event*);
    void addButtonWithTitle(string _buttonsTitle);
    void buttonCallBack(Ref* pSender);
    void show();
};

#endif /* AlertView_h */
