//
//  IOSiAP_Bridge.h
//  KidTracer
//
//  Created by Bian Wu on 10/8/14.
//
//

#ifndef __KidTracer__IOSiAP_Bridge__
#define __KidTracer__IOSiAP_Bridge__

#include <iostream>
#include "IOSiAP.h"
#include "SceneTitle.h"
#include "SceneSetupDialog.h"

class SceneTitle;
class IOSiAP_Bridge : public IOSiAPDelegate
{
public:
    IOSiAP_Bridge();
    ~IOSiAP_Bridge();
    IOSiAP *iap;
    
    void requestProducts();
    void restoreCompletedTransactions();
    virtual void onRequestProductsFinish(void);
    virtual void onRequestProductsError(int code);
    virtual void onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity);
    std::string productIdentifier;
    
    SceneTitle * _st;
    SceneSetupDialog* _setup;
    virtual void purchasedProducts(std::string identifier);
    
    int gouMaiJBHSetID;
    int gouMaiJLID;
};

#endif /* defined(__KidTracer__IOSiAP_Bridge__) */
