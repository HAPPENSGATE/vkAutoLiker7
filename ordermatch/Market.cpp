
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

#ifdef _MSC_VER
#pragma warning( disable : 4786 )
#endif

#include "Market.h"
#include <iostream>

bool Market::insert( const Order& order )
{
  if ( order.getSide() == Order::buy )
    m_bidOrders.insert( BidOrders::value_type( order.getPrice(), order ) );
  else
    m_askOrders.insert( AskOrders::value_type( order.getPrice(), order ) );
  return true;
}

void Market::erase( const Order& order )
{
  std::string id = order.getClientID();
  if ( order.getSide() == Order::buy )
  {
    BidOrders::iterator i;
    for ( i = m_bidOrders.begin(); i != m_bidOrders.end(); ++i )
      if ( i->second.getClientID() == id )
      {
        m_bidOrders.erase( i );
        return ;
      }
  }
  else if ( order.getSide() == Order::sell )
  {
    AskOrders::iterator i;
    for ( i = m_askOrders.begin(); i != m_askOrders.end(); ++i )
      if ( i->second.getClientID() == id )
      {
        m_askOrders.erase( i );
        return ;
      }
  }
}

bool Market::match( std::queue < Order > & orders )
{
  while ( true )
  {
    if ( !m_bidOrders.size() || !m_askOrders.size() )
      return orders.size() != 0;

    BidOrders::iterator iBid = m_bidOrders.begin();
    AskOrders::iterator iAsk = m_askOrders.begin();
