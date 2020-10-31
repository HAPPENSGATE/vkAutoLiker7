# QuickFIX Trading Platform
Basic C++ FIX trading platform using the QuickFIX Engine.

### Motivation
I was recently involved in implementing a [FIX](http://www.fixprotocol.org/) message client.
We are using our own proprietary FIX engine to implement it, but I was urged to have a look
at the QuickFIX Engine. This project is based massively on the example code that comes with
the engine. I just removed support for the various FIX protocol versions and kept only
FIX 5.0 SP2. Also made a few changes/additions to the matching engine to return
a FIX 5.0 SP2 `FIX::ExecutionReport` message with all the required fields.

### Description
The project contains two tasks, *tradeclient* and *ordermatch*. They are both console
based. The first sends orders and the latter stores them a