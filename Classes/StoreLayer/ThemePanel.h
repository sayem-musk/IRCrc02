//
//  ThemePanel.h
//  IRC-mobile
//
//  Created by Tarek Saazeb on 3/25/20.
//

#ifndef ThemePanel_h
#define ThemePanel_h

#include "cocos2d.h"
#include "../StoreLayer/StorePanel.h"
#include "../CustomClass/AlertView.h"

USING_NS_CC;

class ThemePanel : public StorePanel,TableViewDataSource,TableViewDelegate,AlertViewDelegate
{
public:
#pragma mark- Init Method
    ~ThemePanel();
    ThemePanel();
    static ThemePanel* create();
    virtual bool init();
    void removeFromParentAndCleanup(bool cleanup);
    
#pragma mark- Load TableView
    TableView *myTableView;
    void loadTableView();
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    virtual Size cellSizeForTable(TableView *table);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual void tableCellHighlight(TableView* table, TableViewCell* cell);
    virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);
    virtual void tableCellWillRecycle(TableView* table, TableViewCell* cell);
    
    void themeCallBack(cocos2d::Ref *pSender);
    void loadStage(ScreenData *screenData);

#pragma mark- AlertView
    void alertViewCallBack(int tag,int buttonIndex);
};

#endif /* ThemePanel_h */
