
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

#ifndef ORDERMATCH_ORDER_H
#define ORDERMATCH_ORDER_H

#include <string>
#include <iomanip>
#include <ostream>

class Order
{
  friend std::ostream& operator<<( std::ostream&, const Order& );

public:
  enum Side { buy, sell };
  enum Type { market, limit };

  Order( const std::string& clientId, const std::string& symbol,
         const std::string& owner, const std::string& target,