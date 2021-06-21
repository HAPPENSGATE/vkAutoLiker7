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

#ifndef ORDERMATCH_ORDERMATCHER_H
#define ORDERMATCH_ORDERMATCHER_H

#include "Market.h"
#include <map>
#include <iostream>

class OrderMatcher
{
  typedef std::map < std::string, Market > Markets;
public:
  bool insert( const Order& order )
  {
    Markets::iterator i = m_markets.find( order.getSymbol() );
    if ( i == m_markets.end() )
      i = m_markets.insert( std::make_pair( order.getSymbol(), Market() ) ).first;
    return i->second.insert( order );
  }

  void erase( const Order& order )
  {
    Markets::iterator i = m_markets.find( order.getSymbol() );
    if ( i == m_markets.end() ) return ;
    i->second.erase( order );
  }

  Order& find( std::string 