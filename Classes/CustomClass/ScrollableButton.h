//
//  ScrollableButton.h
//  MUSK
//
//  Created by Tarek Saazeb on 3/13/17.
//
//

#ifndef ScrollableButton_h
#define ScrollableButton_h

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class ScrollableButton : public Node
{
public:
    enum class State
    {
        Normal,
        Selected,
    };

    bool colorEnable;
    Color3B originalColor;
    Color3B buttonTapColor;
    string strNormal;
    string strSelected;
    
    Sprite *btnSprite;
    
    ~ScrollableButton();
    ScrollableButton();
    static ScrollableButton* create(string normalImage,string selectedImage);
    bool init(string normalImage,string selectedImage);
    void removeFromParentAndCleanup(bool cleanup);
    
#pragma mark- Image
    void setImage(string strImageName,ScrollableButton::State controlState);
    
#pragma mark- Callback
    ccMenuCallback callback;
    void setCallback(const ccMenuCallback& _callback);
    
#pragma mark- Touch
    bool isDraging;
    
    void setTouchEnable();
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);
    
    void setButtonColor(const cocos2d::Color3B &color);
    void setButtonColorEnable(const cocos2d::Color3B &color);
};

#endif /* ScrollableButton_h */






