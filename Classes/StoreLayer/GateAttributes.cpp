//
//  GateAttributes.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 3/17/20.
//

#include "GateAttributes.h"
#include "AppDelegate.h"
#include "../DBClasses/DBAttributesInfo.h"

#pragma mark- Init Method

GateAttributes::~GateAttributes()
{
    
}

GateAttributes::GateAttributes()
{
    
}

GateAttributes* GateAttributes::create()
{
    GateAttributes* ret = new GateAttributes();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool GateAttributes::init()
{
    if(StorePanel::initWithSmallWindow())
    {
        loadSmallBackground(folderImagesGateAttributes+"bg-gate-attributes.png");
        
        //loadTitle("GATE");
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

void GateAttributes::removeFromParentAndCleanup(bool cleanup)
{
    appDelegate->gHud->showInterstitialAd();
    StorePanel::removeFromParentAndCleanup(cleanup);
}

#pragma mark- TableView

void GateAttributes::loadTableView()
{
    myTableView=TableView::create(this, Size(508*appDelegate->deviceScaleFloat,450*appDelegate->deviceScaleFloat));
    myTableView->setDirection(ScrollView::Direction::VERTICAL);
    myTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    myTableView->setPosition(Point(appDelegate->winSize.width/2-436*appDelegate->deviceScaleFloat/2,appDelegate->winSize.height/2-530*appDelegate->deviceScaleFloat/2));
    myTableView->setDelegate(this);
    this->addChild(myTableView,15);
    myTableView->reloadData();
}

Size GateAttributes::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return cellSizeForTable(table);
}

Size GateAttributes::cellSizeForTable(TableView *table)
{
    return Size(440*appDelegate->deviceScaleFloat,140*appDelegate->deviceScaleFloat);
}

ssize_t GateAttributes:: numberOfCellsInTableView(TableView *table)
{
    return 3;
}

TableViewCell* GateAttributes:: tableCellAtIndex(TableView *table, ssize_t idx)
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
    int tag=TypeCustomerFrequency;
    string strName="Customer Frequency";
    int levelid=1;
    string strBtnName="btn-customer-frequency.png";
    
    switch (idx)
    {
        case 0:
        {
            tag=TypeCustomerFrequency;
            strName="Customer\nFrequency";
            levelid=screenData->myScreen->customer_frequency_level;
            strBtnName=folderImagesGateAttributes+"btn-customer-frequency.png";
        }
            break;
            
        case 1:
        {
            tag=TypeStationCapacity;
            strName="Resturant\nCapacity";
            levelid=screenData->myScreen->station_capacity_level;
            strBtnName=folderImagesGateAttributes+"btn-station-capacity.png";
        }
            break;
            
        case 2:
        {
            tag=TypeQueueCapacity;
            strName="Queue\nCapacity";
            levelid=screenData->myScreen->queue_capacity_level;
            strBtnName=folderImagesGateAttributes+"btn-queue-capacity.png";
        }
            break;
            
        default:
            break;
    }
    
    Size cellSize=tableCellSizeForIndex(table,idx);
    
    Sprite *imgCellBackground=Sprite::create(folderImagesGateAttributes+"bg-gate-attributes-cell.png");
    imgCellBackground->setScale(appDelegate->deviceScaleFloat);
    imgCellBackground->setPosition(Point(imgCellBackground->getScaleX()*imgCellBackground->getContentSize().width/2, imgCellBackground->getScaleY()*imgCellBackground->getContentSize().height/2));
    cell->addChild(imgCellBackground);
    
    Sprite *imgIcon=Sprite::create(folderImagesIconAttributes+"i-attributes-"+to_string(tag)+".png");
    //imgIcon->setScale(60*appDelegate->deviceScaleFloat/imgIcon->getContentSize().width);
    imgIcon->setScale(appDelegate->deviceScaleFloat);
    imgIcon->setPosition(imgIcon->getScaleX()*imgIcon->getContentSize().width/2+30*appDelegate->deviceScaleFloat,cellSize.height/2-5*appDelegate->deviceScaleFloat);
    cell->addChild(imgIcon);
    
    Label *lblTitle=StorePanel::createLabel(strName, 30*appDelegate->deviceScaleFloat);
    lblTitle->setDimensions(imgCellBackground->getScaleX()*imgCellBackground->getContentSize().width, imgCellBackground->getScaleY() * imgCellBackground->getContentSize().height);
    lblTitle->setPosition(Point(cellSize.width/2-10*appDelegate->deviceScaleFloat, cellSize.height/2 + 15*appDelegate->deviceScaleFloat));
    lblTitle->setColor(Color3B::BLACK);
    lblTitle->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
    cell->addChild(lblTitle);
    
    Label *lblCurrentValue=StorePanel::createLabel("strCurrentValue", 30*appDelegate->deviceScaleFloat);
    lblCurrentValue->setName("lblCurrentValue");
    lblCurrentValue->setDimensions(imgCellBackground->getScaleX()*imgCellBackground->getContentSize().width, imgCellBackground->getScaleY() * imgCellBackground->getContentSize().height);
    lblCurrentValue->setPosition(lblTitle->getPosition()+Point(0*appDelegate->deviceScaleFloat,-55*appDelegate->deviceScaleFloat));
    lblCurrentValue->setColor(Color3B::BLACK);
    lblCurrentValue->enableBold();
    lblCurrentValue->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
    cell->addChild(lblCurrentValue);
    
    Label *lblNextValue=StorePanel::createLabel("strNextValue", 30*appDelegate->deviceScaleFloat);
    lblNextValue->setName("lblNextValue");
    lblNextValue->setDimensions(imgCellBackground->getScaleX()*imgCellBackground->getContentSize().width, imgCellBackground->getScaleY() * imgCellBackground->getContentSize().height);
    lblNextValue->setPosition(lblCurrentValue->getPosition()+Point(50*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
    lblNextValue->setColor(Color3B::GREEN);
    lblNextValue->enableBold();
    lblNextValue->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
    cell->addChild(lblNextValue);
    
    ScrollableButton *btnUpdateCallBack=StorePanel::createScrollableButton(strBtnName);
    //btnUpdateCallBack->setScale(appDelegate->deviceScaleFloat);
    btnUpdateCallBack->setPosition(cellSize.width-btnUpdateCallBack->getScaleX()*btnUpdateCallBack->getContentSize().width/2-30*appDelegate->deviceScaleFloat,cellSize.height/2-5*appDelegate->deviceScaleFloat);
    btnUpdateCallBack->setTag(tag);
    btnUpdateCallBack->setCallback(CC_CALLBACK_1(GateAttributes::updateCallBack, this));
    cell->addChild(btnUpdateCallBack);
    
    Size buttonSize=Size(btnUpdateCallBack->getScaleX()*btnUpdateCallBack->getContentSize().width/2, btnUpdateCallBack->getScaleY()*btnUpdateCallBack->getContentSize().height/2);
    
    Sprite *imgCoins=Sprite::create(folderImagesResourcesBar+"r-"+to_string(coinsIndex)+".png");
    imgCoins->setName("imgCoins");
    imgCoins->setScale(40*appDelegate->deviceScaleFloat/imgCoins->getContentSize().width);
    imgCoins->setPosition(btnUpdateCallBack->getPosition()+Point(-30*appDelegate->deviceScaleFloat,buttonSize.height/2-20*appDelegate->deviceScaleFloat));
    cell->addChild(imgCoins);
    
    Label *lblBuyPrice=StorePanel::createLabel("strBuyPrice", 20*appDelegate->deviceScaleFloat);
    lblBuyPrice->setName("lblBuyPrice");
    lblBuyPrice->setDimensions(buttonSize.width, buttonSize.height);
    //lblBuyPrice->setPosition(imgCoins->getPosition()+Point(imgCoins->getScaleX()*imgCoins->getContentSize().width/2+0*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
    lblBuyPrice->setPosition(imgCoins->getPosition()+Point(buttonSize.width/2+imgCoins->getScaleX()*imgCoins->getContentSize().width/2+5*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
    lblBuyPrice->setColor(Color3B::BLACK);
    lblBuyPrice->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
    cell->addChild(lblBuyPrice);
    
    Label *lblMax=StorePanel::createLabel("MAX", 20*appDelegate->deviceScaleFloat);
    lblMax->setName("lblMax");
    lblMax->setDimensions(buttonSize.width, buttonSize.height);
    lblMax->setPosition(btnUpdateCallBack->getPosition()+Point(0*appDelegate->deviceScaleFloat, 0*appDelegate->deviceScaleFloat));
    lblMax->setColor(Color3B::BLACK);
    lblMax->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
    cell->addChild(lblMax);
    
    setButtonInfo(cell,tag,levelid);
    
    return cell;
}

void GateAttributes::tableCellTouched(TableView* table, TableViewCell* cell)
{
    //int idx=(int)cell->getIdx();
    //
    //DBProduct *productInfo=allProductList->at(idx)->productInfo;
    //if(!productInfo->disable)
    //  this->buttonClicked((int)cell->getIdx());
}

void GateAttributes::tableCellHighlight(TableView* table, TableViewCell* cell)
{
    
}

void GateAttributes::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
    
}

void GateAttributes::tableCellWillRecycle(TableView* table, TableViewCell* cell)
{
    
}

void GateAttributes::setButtonInfo(TableViewCell *cell,int tag,int levelid)
{
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    vector<string> *arrBuyPrice=screenData->getPriceForType(tag);
    //ClickerCalculation::showNumber(arrBuyPrice,"Tag ");

    DBAttributesInfo *currentAttributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(tag,levelid);
    DBAttributesInfo *nextAttributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(tag,levelid+1);
    
    Label *lblCurrentValue=(Label*)cell->getChildByName("lblCurrentValue");
    Label *lblNextValue=(Label*)cell->getChildByName("lblNextValue");
    
    Sprite *imgCoins=(Sprite*)cell->getChildByName("imgCoins");
    Label *lblBuyPrice=(Label*)cell->getChildByName("lblBuyPrice");
    
    Label *lblMax=(Label*)cell->getChildByName("lblMax");
    
    if(ClickerCalculation::isNumberZero(arrBuyPrice))
    {
        imgCoins->setVisible(false);
        lblBuyPrice->setVisible(false);
        lblMax->setVisible(true);
        
        string strCurrentValue=currentAttributesInfo->attributes_effect+"";
        lblCurrentValue->setString(strCurrentValue);
        
        lblNextValue->setString("");
    }
    else
    {
        imgCoins->setVisible(true);
        lblBuyPrice->setVisible(true);
        lblMax->setVisible(false);
        
        string strBuyPrice=ClickerCalculation::getAbbreviationForValue(arrBuyPrice);
        lblBuyPrice->setString(strBuyPrice);
        
        string strCurrentValue=currentAttributesInfo->attributes_effect+"          ";
        lblCurrentValue->setString(strCurrentValue);
        
        string strNextValue=ClickerCalculation::getAbbreviationForValue(ClickerCalculation::subtraction(nextAttributesInfo->attributes_effect,currentAttributesInfo->attributes_effect));
        Label *lblNextValue=(Label*)cell->getChildByName("lblNextValue");
        lblNextValue->setString("+"+strNextValue);
    }
    
}

void GateAttributes::updateCallBack(cocos2d::Ref *pSender)
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
            case TypeCustomerFrequency:
            {
                cellIndex=0;
                screenData->myScreen->customer_frequency_level++;
                levelid=screenData->myScreen->customer_frequency_level;
            }
                break;
            case TypeStationCapacity:
            {
                cellIndex=1;
                screenData->myScreen->station_capacity_level++;
                levelid=screenData->myScreen->station_capacity_level;
            }
                break;
            case TypeQueueCapacity:
            {
                cellIndex=2;
                screenData->myScreen->queue_capacity_level++;
                levelid=screenData->myScreen->queue_capacity_level;
            }
                break;
                
            default:
                break;
        }
        screenData->myScreen->updateDatabase();

        TableViewCell *cell=myTableView->cellAtIndex(cellIndex);
        setButtonInfo(cell,tag,levelid);
        
        appDelegate->gnode->setHumanSchedule();
    }
}

