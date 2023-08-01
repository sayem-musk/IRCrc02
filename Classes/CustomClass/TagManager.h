//
//  TagManager.hpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 5/13/20.
//

#ifndef TagManager_h
#define TagManager_h

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class TagManager : public Node
{
public:
    static vector<int> *getAdSearchOrder();
    static int getAnalyticsService();
    static vector<int> *getDefaultAdsSearchOrder();
};

#endif /* TagManager_h */
