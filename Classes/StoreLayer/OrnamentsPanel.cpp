//
//  OrnamentsPanel.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 5/6/20.
//

#include "OrnamentsPanel.h"
#include "AppDelegate.h"
#include "../DBClasses/DBAttributesInfo.h"
#include "../GameLayer/Ornaments.h"

#pragma mark- Init Method

OrnamentsPanel::~OrnamentsPanel()
{
    
}

OrnamentsPanel::OrnamentsPanel()
{
    
}

OrnamentsPanel* OrnamentsPanel::create()
{
    OrnamentsPanel* ret = new OrnamentsPanel();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool OrnamentsPanel::init()
{
    if(StorePanel::initWithSmallWindow())
    {
        loadSmallBackground(folderImagesOrnamentsPanel+"bg-ornaments-panel.png");
        
        //loadTitle("Theme");
        //titleLabel->setColor(Color3B::BLACK);
        //titleLabel->setPosition(Point(this->getContentSize().width/2,appDelegate->winSize.height/2+imgBackground->getScale()*imgBackground->getContentSize().height/2-titleLabel->getDimensions().height/2));
        
        loadCrossButton();
        btnCross->setPosition(Point(imgBackground->getScaleX()*imgBackground->getContentSize().width/2-btnCross->getScale()*btnCross->getContentSize().width/2-5*appDelegate->deviceScaleFloat,imgBackground->getScaleY()*imgBackground->getContentSize().height/2-btnCross->getScale()*btnCross->getContentSize().height/2-10*appDelegate->deviceScaleFloat));
        
        loadTableView();
        
        appDelegate->gHud->setInterstitialAd();
        
        return true;
    }
    return false;
}

void OrnamentsPanel::removeFromParentAndCleanup(bool cleanup)
{
    appDelegate->gHud->showInterstitialAd();
    Node::removeFromParentAndCleanup(cleanup);
}

#pragma mark- TableView

void OrnamentsPanel::loadTableView()
{
    myTableView=TableView::create(this, Size(508*appDelegate->deviceScaleFloat,450*appDelegate->deviceScaleFloat));
    myTableView->setDirection(ScrollView::Direction::VERTICAL);
    myTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    myTableView->setPosition(Point(appDelegate->winSize.width/2-436*appDelegate->deviceScaleFloat/2,appDelegate->winSize.height/2-530*appDelegate->deviceScaleFloat/2));
    myTableView->setDelegate(this);
    this->addChild(myTableView,15);
    myTableView->reloadData();
}

Size OrnamentsPanel::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return cellSizeForTable(table);
}

Size OrnamentsPanel::cellSizeForTable(TableView *table)
{
    return Size(440*appDelegate->deviceScaleFloat,140*appDelegate->deviceScaleFloat);
}

ssize_t OrnamentsPanel:: numberOfCellsInTableView(TableView *table)
{
    return 2;
}

TableViewCell* OrnamentsPanel:: tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell=table->dequeueCell();
    if(!cell)
    {
        cell=new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildrenWithCleanup(true);
    //cell->setScale(appDelegate->deviceScaleFloat);
    
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    int tag=TypeBalloons;
    string strName="Balloons";
    int levelid=1;
    string strBtnName=folderImagesButton+"btn-buy-price.png";
    
    switch (idx)
    {
        case 0:
        {
            tag=TypeBalloons;
            strName="Balloons";
            levelid=screenData->myScreen->balloons_level;
        }
            break;
            
        case 1:
        {
            tag=TypeIceCream;
            strName="Ice Cream";
            levelid=screenData->myScreen->icecream_level;
        }
            break;
            
        case 2:
        {
            tag=TypeFastFood;
            strName="Fast Food";
            levelid=screenData->myScreen->fastfood_level;
        }
            break;
            
        case 3:
        {
            tag=TypeAirShip;
            strName="Air Ship";
            levelid=screenData->myScreen->airship_level;
        }
            break;
            
        default:
            break;
    }
    
    Size cellSize=tableCellSizeForIndex(table,idx);
    
    Sprite *imgCellBackground=Sprite::create(folderImagesOrnamentsPanel+"bg-ornaments-cell.png");
    imgCellBackground->setScale(appDelegate->deviceScaleFloat);
    imgCellBackground->setPosition(Point(imgCellBackground->getScaleX()*imgCellBackground->getContentSize().width/2, imgCellBackground->getScaleY()*imgCellBackground->getContentSize().height/2));
    cell->addChild(imgCellBackground);
    
    Sprite *imgIcon=Sprite::create(folderImagesIconAttributes+"i-attributes-"+to_string(tag)+".png");
    imgIcon->setScale(60*appDelegate->deviceScaleFloat/imgIcon->getContentSize().width);
    imgIcon->setPosition(imgIcon->getScaleX()*imgIcon->getContentSize().width+0*appDelegate->deviceScaleFloat,cellSize.height/2+0*appDelegate->deviceScaleFloat);
    cell->addChild(imgIcon);
    
    Label *lblTitle=StorePanel::createLabelWithBold(strName, 20*appDelegate->deviceScaleFloat);
    lblTitle->setDimensions(imgCellBackground->getScaleX()*imgCellBackground->getContentSize().width, imgCellBackground->getScaleY() * imgCellBackground->getContentSize().height);
    lblTitle->setPosition(imgIcon->getPosition()+Point(imgCellBackground->getScaleX()*imgCellBackground->getContentSize().width/2+imgIcon->getScaleX()*imgIcon->getContentSize().width/2+50*appDelegate->deviceScaleFloat, 20*appDelegate->deviceScaleFloat));
    lblTitle->setColor(Color3B::BLACK);
    lblTitle->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
    cell->addChild(lblTitle);
    
    Label *lblUpdateTitle=StorePanel::createLabel("strUpdateTitle", 20*appDelegate->deviceScaleFloat);
    lblUpdateTitle->setName("lblUpdateTitle");
    lblUpdateTitle->setDimensions(imgCellBackground->getScaleX()*imgCellBackground->getContentSize().width, imgCellBackground->getScaleY() * imgCellBackground->getContentSize().height);
    lblUpdateTitle->setPosition(lblTitle->getPosition()+Point(0*appDelegate->deviceScaleFloat,-30*appDelegate->deviceScaleFloat));
    lblUpdateTitle->setColor(Color3B::GRAY);
    lblUpdateTitle->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
    cell->addChild(lblUpdateTitle);
    
    Label *lblUpdateValue=StorePanel::createLabel("strUpdateValue", 20*appDelegate->deviceScaleFloat);
    lblUpdateValue->setName("lblUpdateValue");
    lblUpdateValue->setDimensions(imgCellBackground->getScaleX()*imgCellBackground->getContentSize().width, imgCellBackground->getScaleY() * imgCellBackground->getContentSize().height);
    lblUpdateValue->setPosition(lblTitle->getPosition()+Point(60*appDelegate->deviceScaleFloat,-30*appDelegate->deviceScaleFloat));
    lblUpdateValue->setColor(Color3B::GREEN);
    lblUpdateValue->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
    cell->addChild(lblUpdateValue);
    
    Sprite *imgUnlock=Sprite::create(folderImagesOrnamentsPanel+"btn-ornaments-panel-unlock.png");
    imgUnlock->setName("imgUnlock");
    imgUnlock->setScale(appDelegate->deviceScaleFloat);
    imgUnlock->setPosition(cellSize.width-90*appDelegate->deviceScaleFloat,cellSize.height/2);
    cell->addChild(imgUnlock);
    
    Size unlockButtonSize=Size(imgUnlock->getScaleX()*imgUnlock->getContentSize().width, imgUnlock->getScaleY()*imgUnlock->getContentSize().height);
    
    Label *lblUnlockLevel=StorePanel::createLabel("Lv."+to_string(screenData->screenInfo->unlock_level), 20*appDelegate->deviceScaleFloat);
    lblUnlockLevel->setName("lblUnlockLevel");
    lblUnlockLevel->setDimensions(unlockButtonSize.width, unlockButtonSize.height);
    lblUnlockLevel->setPosition(imgUnlock->getPosition()+Point(12.5*appDelegate->deviceScaleFloat, -7.5f*appDelegate->deviceScaleFloat));
    lblUnlockLevel->setColor(Color3B::WHITE);
    lblUnlockLevel->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
    cell->addChild(lblUnlockLevel,1);
    
    ScrollableButton *btnUpdateCallBack=StorePanel::createScrollableButton(strBtnName);
    btnUpdateCallBack->setName("btnUpdateCallBack");
    //btnUpdateCallBack->setScale(appDelegate->deviceScaleFloat);
    btnUpdateCallBack->setPosition(cellSize.width-90*appDelegate->deviceScaleFloat,cellSize.height/2);
    btnUpdateCallBack->setTag(tag);
    btnUpdateCallBack->setCallback(CC_CALLBACK_1(OrnamentsPanel::updateCallBack, this));
    cell->addChild(btnUpdateCallBack);
    
    Size buttonSize=Size(btnUpdateCallBack->getScaleX()*btnUpdateCallBack->getContentSize().width, btnUpdateCallBack->getScaleY()*btnUpdateCallBack->getContentSize().height);
    
    Sprite *imgCoins=Sprite::create(folderImagesResourcesBar+"r-"+to_string(coinsIndex)+".png");
    imgCoins->setName("imgCoins");
    imgCoins->setScale(30*appDelegate->deviceScaleFloat/imgCoins->getContentSize().width);
    imgCoins->setPosition(btnUpdateCallBack->getPosition()+Point(-30*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
    cell->addChild(imgCoins);
    
    Label *lblBuyPrice=StorePanel::createLabel("strBuyPrice", 20*appDelegate->deviceScaleFloat);
    lblBuyPrice->setName("lblBuyPrice");
    lblBuyPrice->setDimensions(buttonSize.width, buttonSize.height);
    //lblBuyPrice->setPosition(imgCoins->getPosition()+Point(imgCoins->getScaleX()*imgCoins->getContentSize().width/2+0*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
    lblBuyPrice->setPosition(imgCoins->getPosition()+Point(buttonSize.width/2+imgCoins->getScaleX()*imgCoins->getContentSize().width/2+5*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
    lblBuyPrice->setColor(Color3B::WHITE);
    lblBuyPrice->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
    cell->addChild(lblBuyPrice);
    
    Label *lblMax=StorePanel::createLabel("MAX", 20*appDelegate->deviceScaleFloat);
    lblMax->setName("lblMax");
    lblMax->setDimensions(buttonSize.width, buttonSize.height);
    lblMax->setPosition(btnUpdateCallBack->getPosition()+Point(0*appDelegate->deviceScaleFloat, 0*appDelegate->deviceScaleFloat));
    lblMax->setColor(Color3B::WHITE);
    lblMax->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
    cell->addChild(lblMax);
    
    setButtonInfo(cell,tag,levelid);
    
    return cell;
}

void OrnamentsPanel:: tableCellTouched(TableView* table, TableViewCell* cell)
{
    //    int idx=(int)cell->getIdx();
    //
    //    DBProduct *productInfo=allProductList->at(idx)->productInfo;
    //    if(!productInfo->disable)
    //        this->buttonClicked((int)cell->getIdx());
}

void OrnamentsPanel::tableCellHighlight(TableView* table, TableViewCell* cell)
{
    
}

void OrnamentsPanel::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
    
}

void OrnamentsPanel::tableCellWillRecycle(TableView* table, TableViewCell* cell)
{
    
}

void OrnamentsPanel::setButtonInfo(TableViewCell *cell,int tag,int levelid)
{
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    vector<string> *arrBuyPrice=screenData->getPriceForType(tag);
    
    DBAttributesInfo *attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(tag,levelid+1);
    
    Label *lblUpdateValue=(Label*)cell->getChildByName("lblUpdateValue");
    Label *lblUpdateTitle=(Label*)cell->getChildByName("lblUpdateTitle");
    
    Sprite *imgCoins=(Sprite*)cell->getChildByName("imgCoins");
    Label *lblBuyPrice=(Label*)cell->getChildByName("lblBuyPrice");
    
    Label *lblMax=(Label*)cell->getChildByName("lblMax");
    
    ScrollableButton *btnUpdateCallBack=(ScrollableButton*)cell->getChildByName("btnUpdateCallBack");
    
    Sprite *imgUnlock=(Sprite*)cell->getChildByName("imgUnlock");
    Label *lblUnlockLevel=(Label*)cell->getChildByName("lblUnlockLevel");

    DBUserInfo *userInfo=DBUserInfo::sharedManager();
    
    int nextLevel=(userInfo->screen_id-1)*30+attributesInfo->attributes_level+4;
    
    bool isValueShow=true;
    
    if(userInfo->levelid<nextLevel)
    {
        isValueShow=true;
        
        btnUpdateCallBack->setVisible(false);
        
        imgCoins->setVisible(false);
        lblBuyPrice->setVisible(false);
        lblMax->setVisible(false);
        
        imgUnlock->setVisible(true);
        lblUnlockLevel->setString("Lv."+to_string(nextLevel));
    }
    else
    {
        btnUpdateCallBack->setVisible(true);
        
        imgUnlock->setVisible(false);
        lblUnlockLevel->setString("");
        
        if(ClickerCalculation::isNumberZero(arrBuyPrice))
        {
            imgCoins->setVisible(false);
            lblBuyPrice->setVisible(false);
            lblMax->setVisible(true);
            
            lblUpdateTitle->setString("Max");
            lblUpdateValue->setString("");
            
            isValueShow=false;
        }
        else
        {
            imgCoins->setVisible(true);
            lblBuyPrice->setVisible(true);
            lblMax->setVisible(false);
            
            string strBuyPrice=ClickerCalculation::getAbbreviationForValue(arrBuyPrice);
            lblBuyPrice->setString(strBuyPrice);
            
            isValueShow=true;
        }
    }
    
    if(isValueShow)
    {
        string strUpdateTitle=attributesInfo->attributes_effect;
        string strUpdateValue=attributesInfo->attributes_effect;
        switch (tag)
        {
            case TypeBalloons:
            {
                strUpdateTitle="Queue ";
                strUpdateValue="+"+attributesInfo->attributes_effect;
            }
                break;
                
            case TypeIceCream:
            {
                strUpdateTitle="Ticket ";
                strUpdateValue="+"+attributesInfo->attributes_effect+"%";
            }
                break;
                
            case TypeFastFood:
            {
                strUpdateTitle="Ticket ";
                strUpdateValue="+"+attributesInfo->attributes_effect+"%";
            }
                break;
                
            case TypeAirShip:
            {
                strUpdateTitle="Speed ";
                strUpdateValue="+"+attributesInfo->attributes_effect+"%";
            }
                break;
                
            default:
                break;
        }
        
        lblUpdateTitle->setString(strUpdateTitle);
        lblUpdateValue->setString(strUpdateValue);
    }

    
}

void OrnamentsPanel::updateCallBack(cocos2d::Ref *pSender)
{
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    int tag=((ScrollableButton*)pSender)->getTag();
    
    vector<string> *arrBuyPrice=screenData->getPriceForType(tag);
    
    if(ClickerCalculation::isNumberZero(arrBuyPrice))
    {
        return;
    }
    
    Resources *resources=Resources::sharedManager();
    
    if(resources->checkResourceAvailable(coinsIndex,arrBuyPrice,false))
    {
        resources->subResource(coinsIndex,arrBuyPrice);
        int levelid=1;
        int cellIndex=0;
        switch (tag)
        {
            case TypeBalloons:
            {
                cellIndex=0;
                screenData->myScreen->balloons_level++;
                levelid=screenData->myScreen->balloons_level;
            }
                break;
            case TypeIceCream:
            {
                cellIndex=1;
                screenData->myScreen->icecream_level++;
                levelid=screenData->myScreen->icecream_level;
            }
                break;
            case TypeFastFood:
            {
                cellIndex=2;
                screenData->myScreen->fastfood_level++;
                levelid=screenData->myScreen->fastfood_level;
            }
                break;
            case TypeAirShip:
            {
                cellIndex=3;
                screenData->myScreen->airship_level++;
                levelid=screenData->myScreen->airship_level;
            }
                break;
                
            default:
                break;
        }
        screenData->myScreen->updateDatabase();
        
        TableViewCell *cell=myTableView->cellAtIndex(cellIndex);
        setButtonInfo(cell,tag,levelid);
        
        if(tag==TypeBalloons)
        {
            appDelegate->gnode->setHumanSchedule();
            Ornaments::sharedManager()->loadBallons();
        }
        
        if(tag==TypeIceCream)
            Ornaments::sharedManager()->loadIceCream();
        
        if(tag==TypeIceCream || tag==TypeFastFood)
            appDelegate->gHud->setButtonInfoByTag(TypeTicketPrice);
        
        if(tag==TypeAirShip)
            appDelegate->gHud->setButtonInfoByTag(TypeSpeed);
    }
}




