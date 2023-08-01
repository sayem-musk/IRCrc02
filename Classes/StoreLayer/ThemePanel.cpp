//
//  ThemePanel.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 3/25/20.
//

#include "ThemePanel.h"
#include "AppDelegate.h"

#pragma mark- Init Method

ThemePanel::~ThemePanel()
{
    
}

ThemePanel::ThemePanel()
{
    
}

ThemePanel* ThemePanel::create()
{
    ThemePanel* ret = new ThemePanel();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool ThemePanel::init()
{
    if(StorePanel::initWithSmallWindow())
    {
        appDelegate->gHud->setInterstitialAd();
        loadSmallBackground(folderImagesGateThemePanel+"bg-theme-panel.png");
        
        //loadTitle("Theme");
        //titleLabel->setColor(Color3B::BLACK);
        //titleLabel->setPosition(Point(this->getContentSize().width/2,appDelegate->winSize.height/2+imgBackground->getScale()*imgBackground->getContentSize().height/2-titleLabel->getDimensions().height/2));
        
        loadCrossButton();
        btnCross->setPosition(Point(imgBackground->getScaleX()*imgBackground->getContentSize().width/2-btnCross->getScale()*btnCross->getContentSize().width/2-5*appDelegate->deviceScaleFloat,imgBackground->getScaleY()*imgBackground->getContentSize().height/2-btnCross->getScale()*btnCross->getContentSize().height/2-10*appDelegate->deviceScaleFloat));
        
        loadTableView();
        
        return true;
    }
    return false;
}

void ThemePanel::removeFromParentAndCleanup(bool cleanup)
{
    appDelegate->gHud->showInterstitialAd();
    Node::removeFromParentAndCleanup(cleanup);
}

#pragma mark- TableView

void ThemePanel::loadTableView()
{
    myTableView=TableView::create(this, Size(508*appDelegate->deviceScaleFloat,450*appDelegate->deviceScaleFloat));
    myTableView->setDirection(ScrollView::Direction::VERTICAL);
    myTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    myTableView->setPosition(Point(appDelegate->winSize.width/2-436*appDelegate->deviceScaleFloat/2,appDelegate->winSize.height/2-530*appDelegate->deviceScaleFloat/2));
    myTableView->setDelegate(this);
    this->addChild(myTableView,15);
    myTableView->reloadData();
}

Size ThemePanel::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return cellSizeForTable(table);
}

Size ThemePanel::cellSizeForTable(TableView *table)
{
    return Size(440*appDelegate->deviceScaleFloat,140*appDelegate->deviceScaleFloat);
}

ssize_t ThemePanel:: numberOfCellsInTableView(TableView *table)
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    return appDelegate->allScreenData->size();
}

TableViewCell* ThemePanel:: tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell=table->dequeueCell();
    if(!cell)
    {
        cell=new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildrenWithCleanup(true);
    //cell->setScale(appDelegate->deviceScaleFloat);
    
    Size cellSize=tableCellSizeForIndex(table,idx);
    
    ScreenData *screenData=appDelegate->allScreenData->at(idx);
    
    string strCellBackground=folderImagesGateThemePanel+"bg-theme-panel-cell.png";
    
    if(appDelegate->selectedScreenIndex==idx)
        strCellBackground=folderImagesGateThemePanel+"bg-theme-panel-cell-active.png";
    
    Sprite *imgCellBackground=Sprite::create(strCellBackground);
    imgCellBackground->setScale(appDelegate->deviceScaleFloat);
    imgCellBackground->setPosition(Point(imgCellBackground->getScaleX()*imgCellBackground->getContentSize().width/2, imgCellBackground->getScaleY()*imgCellBackground->getContentSize().height/2));
    cell->addChild(imgCellBackground);
    
    Sprite *imgIcon=Sprite::create(folderImagesIconTheme+"i-theme-"+to_string(screenData->myScreen->screen_id)+".png");
    imgIcon->setScale(60*appDelegate->deviceScaleFloat/imgIcon->getContentSize().width);
    imgIcon->setPosition(imgIcon->getScaleX()*imgIcon->getContentSize().width/2+10*appDelegate->deviceScaleFloat,cellSize.height/2+0*appDelegate->deviceScaleFloat);
    cell->addChild(imgIcon,1);
    
    int discoveredIndex=-1;
    
    if(screenData->myScreen->is_unlocked==1)
    {
        Label *lblTitle=StorePanel::createLabelWithBold(screenData->screenInfo->screen_name, 22*appDelegate->deviceScaleFloat);
        lblTitle->setDimensions(imgCellBackground->getScaleX()*imgCellBackground->getContentSize().width, imgCellBackground->getScaleY() * imgCellBackground->getContentSize().height);
        lblTitle->setPosition(imgIcon->getPosition()+Point(imgCellBackground->getScaleX()*imgCellBackground->getContentSize().width/2+imgIcon->getScaleX()*imgIcon->getContentSize().width/2+25*appDelegate->deviceScaleFloat, 30*appDelegate->deviceScaleFloat));
        lblTitle->setColor(Color3B::BLACK);
        lblTitle->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
        cell->addChild(lblTitle,1);
        
        /*Sprite *imgCoins=Sprite::create(folderImagesResourcesBar+"r-"+to_string(coinsIndex)+".png");
        imgCoins->setName("imgCoins");
        imgCoins->setScale(40*appDelegate->deviceScaleFloat/imgCoins->getContentSize().width);
        imgCoins->setPosition(Point(cellSize.width/2-120*appDelegate->deviceScaleFloat,cellSize.height/2-20*appDelegate->deviceScaleFloat));
        cell->addChild(imgCoins,1);
        
        Label *lblCoinsPerSec=StorePanel::createLabel(to_string(screenData->myScreen->collect_coins_per_sec)+"/sec", 20*appDelegate->deviceScaleFloat);
        lblCoinsPerSec->setName("lblCoinsPerSec");
        lblCoinsPerSec->setDimensions(cellSize.width, cellSize.height);
        //lblCoinsPerSec->setPosition(imgCoins->getPosition()+Point(imgCoins->getScaleX()*imgCoins->getContentSize().width/2+0*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
        lblCoinsPerSec->setPosition(imgCoins->getPosition()+Point(cellSize.width/2+imgCoins->getScaleX()*imgCoins->getContentSize().width/2+5*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
        lblCoinsPerSec->setColor(Color3B::BLACK);
        lblCoinsPerSec->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
        cell->addChild(lblCoinsPerSec,1);*/
    }
    else
    {
        for (int i=0; i<appDelegate->allScreenData->size(); i++)
        {
            ScreenData *oldScreenData=appDelegate->allScreenData->at(i);
            if(oldScreenData->myScreen->is_unlocked==0 && discoveredIndex==-1)
            {
                discoveredIndex=i;
                break;
            }
        }
        
        string strUnlock="Unlock";
        if(discoveredIndex!=idx)
            strUnlock="Undiscovered";
        
        Label *lblUnlock=StorePanel::createLabelWithBold(strUnlock, 22*appDelegate->deviceScaleFloat);
        lblUnlock->setDimensions(imgCellBackground->getScaleX()*imgCellBackground->getContentSize().width, imgCellBackground->getScaleY() * imgCellBackground->getContentSize().height);
        lblUnlock->setPosition(imgIcon->getPosition()+Point(imgCellBackground->getScaleX()*imgCellBackground->getContentSize().width/2+imgIcon->getScaleX()*imgIcon->getContentSize().width/2+25*appDelegate->deviceScaleFloat, 30*appDelegate->deviceScaleFloat));
        lblUnlock->setColor(Color3B::BLACK);
        lblUnlock->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
        cell->addChild(lblUnlock,1);
    }
    
    ScreenData *selectedScreenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    Point buttonPos=Point(cellSize.width-90*appDelegate->deviceScaleFloat,cellSize.height/2);
    
    if(screenData->myScreen->is_unlocked==1)
    {
        string strImageName=folderImagesGateThemePanel+"btn-theme-panel-ready.png";
        if(screenData->screenInfo->screen_order==selectedScreenData->screenInfo->screen_order)
            strImageName=folderImagesGateThemePanel+"btn-theme-panel-selected.png";
        else
            strImageName=folderImagesGateThemePanel+"btn-theme-panel-ready.png";
        
        ScrollableButton *btnReady=StorePanel::createScrollableButton(strImageName);
        btnReady->setPosition(buttonPos);
        btnReady->setTag((int)idx);
        btnReady->setCallback(CC_CALLBACK_1(ThemePanel::themeCallBack, this));
        cell->addChild(btnReady,1);
    }
    else
    {
        if(discoveredIndex==idx)
        {
            DBUserInfo *userInfo=DBUserInfo::sharedManager();
            
            string strImageName=folderImagesButton+"btn-buy-price.png";
            
            if(userInfo->levelid<screenData->screenInfo->unlock_level)
                strImageName=folderImagesGateThemePanel+"btn-theme-panel-unlock.png";
            
            ScrollableButton *btnUnlock=StorePanel::createScrollableButton(strImageName);
            btnUnlock->setPosition(buttonPos);
            btnUnlock->setTag((int)idx);
            btnUnlock->setCallback(CC_CALLBACK_1(ThemePanel::themeCallBack, this));
            cell->addChild(btnUnlock,1);
            
            if(userInfo->levelid<screenData->screenInfo->unlock_level)
            {
                Size buttonSize=Size(btnUnlock->getScaleX()*btnUnlock->getContentSize().width/2, btnUnlock->getScaleY()*btnUnlock->getContentSize().height/2);
                
                Label *lblUnlockLevel=StorePanel::createLabel("Lv."+to_string(screenData->screenInfo->unlock_level), 20*appDelegate->deviceScaleFloat);
                lblUnlockLevel->setName("lblUnlockLevel");
                lblUnlockLevel->setDimensions(buttonSize.width, buttonSize.height);
                lblUnlockLevel->setPosition(btnUnlock->getPosition()+Point(12.5*appDelegate->deviceScaleFloat, -7.5f*appDelegate->deviceScaleFloat));
                lblUnlockLevel->setColor(Color3B::WHITE);
                lblUnlockLevel->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
                cell->addChild(lblUnlockLevel,1);
            }
            else
            {
                Size buttonSize=Size(btnUnlock->getScaleX()*btnUnlock->getContentSize().width, btnUnlock->getScaleY()*btnUnlock->getContentSize().height);
                
                Sprite *imgCoins=Sprite::create(folderImagesResourcesBar+"r-"+to_string(coinsIndex)+".png");
                imgCoins->setName("imgCoins");
                imgCoins->setScale(30*appDelegate->deviceScaleFloat/imgCoins->getContentSize().width);
                imgCoins->setPosition(btnUnlock->getPosition()+Point(-40*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
                cell->addChild(imgCoins,1);
                
                vector<string> *arrBuyPrice=ClickerCalculation::getNewVector(screenData->screenInfo->unlock_price,screenData->screenInfo-> unlock_price_exp);
                
                Label *lblBuyPrice=StorePanel::createLabel(ClickerCalculation::getAbbreviationForValue(arrBuyPrice), 20*appDelegate->deviceScaleFloat);
                lblBuyPrice->setName("lblBuyPrice");
                lblBuyPrice->setDimensions(buttonSize.width, buttonSize.height);
                //lblBuyPrice->setPosition(imgCoins->getPosition()+Point(imgCoins->getScaleX()*imgCoins->getContentSize().width/2+0*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
                lblBuyPrice->setPosition(imgCoins->getPosition()+Point(buttonSize.width/2+imgCoins->getScaleX()*imgCoins->getContentSize().width/2+5*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
                lblBuyPrice->setColor(Color3B::WHITE);
                lblBuyPrice->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
                cell->addChild(lblBuyPrice,1);
            }
        }
    }
    
    return cell;
}

void ThemePanel:: tableCellTouched(TableView* table, TableViewCell* cell)
{
    //    int idx=(int)cell->getIdx();
    //
    //    DBProduct *productInfo=allProductList->at(idx)->productInfo;
    //    if(!productInfo->disable)
    //        this->buttonClicked((int)cell->getIdx());
}

void ThemePanel::tableCellHighlight(TableView* table, TableViewCell* cell)
{
    
}

void ThemePanel::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
    
}

void ThemePanel::tableCellWillRecycle(TableView* table, TableViewCell* cell)
{
    
}

void ThemePanel::themeCallBack(cocos2d::Ref *pSender)
{
    DBUserInfo *userInfo=DBUserInfo::sharedManager();
    int tag=((MenuItemImage*)pSender)->getTag();
    
    ScreenData *screenData=appDelegate->allScreenData->at(tag);
    ScreenData *selectedScreenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    if(screenData->myScreen->my_screen_id!=selectedScreenData->myScreen->my_screen_id)
    {
        if(screenData->myScreen->is_unlocked==1)
        {
            loadStage(screenData);
        }
        else
        {
            if(userInfo->levelid<screenData->screenInfo->unlock_level)
            {
                string message="This screen is locked." ;
                AlertView *alert=AlertView::create("Can't Unlock???",message,this);
                alert->addButtonWithTitle("OK");
                alert->tag=1;
                alert->show();
            }
            else
            {
                vector<string> *arrBuyPrice=ClickerCalculation::getNewVector(screenData->screenInfo->unlock_price,screenData->screenInfo-> unlock_price_exp);
                Resources *resources=Resources::sharedManager();
                
                if(resources->checkResourceAvailable(coinsIndex,arrBuyPrice,false))
                {
                    resources->subResource(coinsIndex,arrBuyPrice);
                    screenData->unlockScreen();
                    loadStage(screenData);
                }
            }
        }
    }
}

void ThemePanel::loadStage(ScreenData *screenData)
{
    DBUserInfo *userInfo=DBUserInfo::sharedManager();
    
    userInfo->screen_id=screenData->screenInfo->screen_id;
    userInfo->updateDatabase();
    
    appDelegate->selectedScreenIndex=ScreenData::getSelectedScreenIndex();
    
    Resources *resources=Resources::sharedManager();
    resources->loadData(userInfo->screen_id);
    
    this->removeFromParentAndCleanup(true);
    Director::getInstance()->replaceScene(GameNode::createScene());
}

void ThemePanel::alertViewCallBack(int tag,int buttonIndex)
{
    if(tag==1)
    {
    }
    else if(tag==2)
    {
    }
    else if(tag==3)
    {
    }
}










