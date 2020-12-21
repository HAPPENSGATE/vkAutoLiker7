
/* -*- C++ -*- */

/****************************************************************************
** Copyright (c) quickfixengine.org  All rights reserved.
**
** This file is part of the QuickFIX FIX Engine
**
** This file may be distributed under the terms of the quickfixengine.org
** license as defined by quickfixengine.org and appearing in the file
** LICENSE included in the packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.quickfixengine.org/LICENSE for licensing information.
**
** Contact ask@quickfixengine.org if any conditions of this licensing are
** not clear to you.
**
****************************************************************************/

#ifndef ORDERMATCH_APPLICATION_H
#define ORDERMATCH_APPLICATION_H

#include "IDGenerator.h"
#include "OrderMatcher.h"
#include "Order.h"
#include <queue>
#include <iostream>

#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/Values.h>
#include <quickfix/Utility.h>
#include <quickfix/Mutex.h>

#include <quickfix/fix50/NewOrderSingle.h>
#include <quickfix/fix50/OrderCancelRequest.h>
#include <quickfix/fix50/MarketDataRequest.h>

class Application : public FIX::Application,
                    public FIX::MessageCracker
{
    /*!
     *  Overload for class 'FIX::Application'.
     */

    /*!
     *  @brief      Callback for Session create.
     *  @details    Callback function when the FIX Session gets
     *              created.
     *  @param  param1  The FIX Session ID.
     */
    void onCreate(const FIX::SessionID&)
    { }

    /*!
     *  @brief      Callback for Logon.
     *  @details    Callback function when the FIX Session receives
     *              a FIX Logon message.
     *  @param  param1  The FIX Session ID.
     */
    void onLogon(const FIX::SessionID& sessionID);

    /*!
     *  @brief      Callback for Logout.
     *  @details    Callback function when the FIX Session receives