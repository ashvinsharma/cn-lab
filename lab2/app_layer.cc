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

#include "app_layer.h"

Define_Module(App_layer);

void App_layer::initialize()
{
    fromDL = gate("fromDL");
    toDL = gate("toDL");
    addr = par("id");
    count = 9;

    if(addr == 1)
    {
        cMessage* event = new cMessage();
        scheduleAt(0, event);
        EV << "Self Message triggered";
    }
}

void App_layer::handleMessage(cMessage *msg)
{
    if(msg -> isSelfMessage())
    {
        A_PDU* p = new A_PDU();
        p -> setPid(1);
        p -> setSrc(1);
        p -> setDest(2);
        p -> setType(0); //data
        send(p, toDL);
        EV << "Message is sent to AL --> DL";
    }
    else
    {
        A_PDU* prev = check_and_cast<A_PDU*>(msg);
        if(prev->getType() == 0)
        {
            EV << "Data is received\n";
            A_PDU* next = new A_PDU();
            next->setPid(prev->getPid());
            next->setSrc(2);
            next->setDest(1);
            next->setType(1); //ack
            EV << "Sent ack from AL";
            send(next, toDL);
        }else if(prev->getType() == 1)
        {
            if(count > 0)
            {
                count--;
                A_PDU* p = new A_PDU();
                p -> setPid(10 - count);
                p -> setSrc(1);
                p -> setDest(2);
                p -> setType(0); //data
                send(p, toDL);
            }

        }
    }
}
