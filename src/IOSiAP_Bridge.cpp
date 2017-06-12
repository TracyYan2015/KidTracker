//
//  IOSiAP_Bridge.cpp
//  KidTracer
//
//  Created by Bian Wu on 10/8/14.
//
//
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"
#include "Util.h"
#include "SceneController.h"

#include "IOSiAP_Bridge.h"


IOSiAP_Bridge::IOSiAP_Bridge()
{
    iap = new IOSiAP();
    iap->delegate = this;
}

IOSiAP_Bridge::~IOSiAP_Bridge()
{
    delete iap;
}

void IOSiAP_Bridge:: restoreCompletedTransactions()
{
    iap->restoreTransactions();
}

void IOSiAP_Bridge:: requestProducts(void)
{
    std::vector<std::string> vec1;
    //productIdentifier = "com.elf.iaptest.ElfIAPTest4"; //----iap product id
    //vec1.push_back(productIdentifier);
    vec1.push_back("com.elf.iaptest.product1");
    vec1.push_back("com.elf.iaptest.product2");
    vec1.push_back("com.elf.iaptest.product3");
    vec1.push_back("com.elf.iaptest.product4");
    vec1.push_back("com.elf.iaptest.product5");
    vec1.push_back("com.elf.iaptest.product6");
    vec1.push_back("com.elf.iaptest.product7");
    vec1.push_back("com.elf.iaptest.product8");
    
    vec1.push_back("com.elf.iaptest.elfproduct1");
    vec1.push_back("com.elf.iaptest.elfproduct2");
    vec1.push_back("com.elf.iaptest.product_libao");
    
    
    iap->requestProducts(vec1);
    
}

void IOSiAP_Bridge::onRequestProductsFinish(void)
{
    //std::string str = "com.elf.iaptest.ElfIAPTest4";
    int quantity = 1;
    //必须在onRequestProductsFinish后才能去请求iAP产品数据。
    IOSProduct *product = iap->iOSProductByIdentifier(productIdentifier);
    // 然后可以发起付款请求。
    if(product)
    {
        iap->paymentWithProduct(product, quantity);
    }
}

void IOSiAP_Bridge::onRequestProductsError(int code)
{
    //这里requestProducts出错了，不能进行后面的所有操作。
    log("IAP FALE1");
}

void IOSiAP_Bridge::onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity)
{
    //---修改付款成功逻辑
    if (event == IOSIAP_PAYMENT_PURCHAED) {
        //coven0202
        if(this->productIdentifier == identifier)
        {
        //付款成功了，可以吧金币发给玩家了。
        //log("IAP SUCCESS");
        //_st->test();   //_st 为设置模块所在类，test方法用于设置已购买产品标志并更新数据文件，动态删除商店中已买产品选项，并动态加载简笔画图鉴窗口内容
            _setup->afterJBHGouMai(gouMaiJBHSetID);
        }
    }
    else if(event == IOSIAP_PAYMENT_FAILED)
        log("IAP Fail");
    else if (event == IOSIAP_PAYMENT_RESTORED)
    {
        log("IAP RESTORED");
    }
}

void IOSiAP_Bridge::purchasedProducts(std::string products)
{
    //恢复购买
    
    
    //简笔画
    if(products == "com.elf.iaptest.product1")
    {
        CCLOG("restore test4");
        _setup->afterJBHGouMai(1);
    }
    else if(products == "com.elf.iaptest.product2")
    {
        CCLOG("restore test5");
        _setup->afterJBHGouMai(2);
    }
    else if(products == "com.elf.iaptest.product3")
    {
        CCLOG("restore test6");
        _setup->afterJBHGouMai(3);
    }
    else if(products == "com.elf.iaptest.product4")
    {
        CCLOG("restore test7");
        _setup->afterJBHGouMai(4);
    }
    else if(products == "com.elf.iaptest.product5")
    {
        CCLOG("restore test4");
        _setup->afterJBHGouMai(5);
    }
    else if(products == "com.elf.iaptest.product6")
    {
        CCLOG("restore test5");
        //_setup->afterJBHGouMai(6);
    }
    else if(products == "com.elf.iaptest.product7")
    {
        CCLOG("restore test6");
        //_setup->afterJBHGouMai(7);
    }
    else if(products == "com.elf.iaptest.product8")
    {
        CCLOG("restore test7");
        //_setup->afterJBHGouMai(8);
    }
    
    
    //精灵
    else if(products == "com.elf.iaptest.elfproduct1")
    {
        CCLOG("restore test6");
        _setup->afterJBHGouMai(9);
    }
    else if(products == "com.elf.iaptest.elfproduct2")
    {
        CCLOG("restore test7");
        _setup->afterJBHGouMai(10);
    }
    
    
    //礼包
    else if(products == "com.elf.iaptest.product_libao")
    {
        CCLOG("restore test7");
        _setup->afterJBHGouMai(11);
    }
    
}