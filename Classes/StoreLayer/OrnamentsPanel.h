//
//  OrnamentsPanel.h
//  IRC-mobile
//
//  Created by Tarek Saazeb on 5/6/20.
//

#ifndef OrnamentsPanel_h
#define OrnamentsPanel_h

#include "cocos2d.h"
#include "../StoreLayer/StorePanel.h"

USING_NS_CC;

class OrnamentsPanel : public StorePanel,TableViewDataSource,TableViewDelegate
{
public:
#pragma mark- Init Method
    ~OrnamentsPanel();
    OrnamentsPanel();
    static OrnamentsPanel* create();
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
    
    void setButtonInfo(TableViewCell *cell,int tag,int levelid);
    void updateCallBack(cocos2d::Ref *pSender);
};

#endif /* OrnamentsPanel_h */
