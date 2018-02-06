//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "p_layer.h"

Define_Module(P_layer);

void P_layer::initialize()
{
    fromDL = gate("fromDL");
    toNode = gate("toNode");
    toDL = gate("toDL");
    fromNode = gate("fromNode");
}

void P_layer::handleMessage(cMessage *msg)
{
    if(msg->getArrivalGate() == fromDL)
    {
        DL_PDU* prev_msg = check_and_cast<DL_PDU*>(msg);
        P_PDU* new_msg = new P_PDU();

        new_msg->encapsulate(prev_msg);
        new_msg->setType(prev_msg->getType());
        sendDelayed(new_msg, 1, toNode);
        EV << "Message is sent PL --> PL";
    }
    else if(msg->getArrivalGate() == fromNode)
    {
        P_PDU* prev_msg = check_and_cast<P_PDU*>(msg);
        DL_PDU* new_msg = new DL_PDU();

        new_msg = check_and_cast<DL_PDU*>(prev_msg->decapsulate());
        send(new_msg, toDL);
        delete prev_msg;
        EV << "Message is sent DL <-- PL";
    }
}
