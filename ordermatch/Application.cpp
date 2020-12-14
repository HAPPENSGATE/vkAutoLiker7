
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

#include "Application.h"

#include <quickfix/Session.h>
#include <quickfix/config.h>
#include <quickfix/fix50/ExecutionReport.h>

void Application::onLogon(const FIX::SessionID& sessionID)
{ }

void Application::onLogout(const FIX::SessionID& sessionID)
{ }

void Application::fromApp(const FIX::Message& message,
                          const FIX::SessionID& sessionID)
                          throw(FIX::FieldNotFound,
                                FIX::IncorrectDataFormat,
                                FIX::IncorrectTagValue,
                                FIX::UnsupportedMessageType)
{
  crack(message, sessionID);
}

void Application::onMessage(const FIX50::NewOrderSingle& message,
                            const FIX::SessionID&)
{
    FIX::SenderCompID senderCompID;
    FIX::TargetCompID targetCompID;
    FIX::ClOrdID clOrdID;
    FIX::Symbol symbol;
    FIX::Side side;
    FIX::OrdType ordType;
    FIX::Price price;
    FIX::OrderQty orderQty;
    FIX::TimeInForce timeInForce(FIX::TimeInForce_DAY);

    message.getHeader().getField(senderCompID);
    message.getHeader().getField(targetCompID);
    message.get(clOrdID);
    message.get(symbol);
    message.get(side);
    message.get(ordType);
    if (ordType == FIX::OrdType_LIMIT) {
        message.get(price);
    }
    message.get(orderQty);
    if (message.isSetField(timeInForce)) {
        message.get( timeInForce );
    }

    try {
        if (timeInForce != FIX::TimeInForce_DAY) {
            throw std::logic_error("Unsupported TIF, use Day");
        }

        Order order(clOrdID, symbol, senderCompID, targetCompID,
                    convert(side), convert(ordType),
                    price, (long)orderQty);

        processOrder(order);
    }
    catch(std::exception & e) {
        rejectOrder(senderCompID, targetCompID, clOrdID, symbol, side, e.what());
    }
}

void Application::onMessage(const FIX50::OrderCancelRequest& message,
                            const FIX::SessionID&)
{
    FIX::OrigClOrdID origClOrdID;
    FIX::Symbol symbol;
    FIX::Side side;

    message.get(origClOrdID);
    message.get(symbol);
    message.get(side);

    try {
        processCancel(origClOrdID, symbol, convert(side));
    }
    catch(std::exception&) {
    }