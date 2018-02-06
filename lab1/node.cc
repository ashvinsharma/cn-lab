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

#include "node.h"

Define_Module(Node);

void Node::initialize()
{
    inGate=gate("in");
    outGate=gate("out");
    address=par("id");
    count=9;
    if(address==1){
        cMessage* event=new cMessage();
        scheduleAt(0,event);
    }
}

void Node::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        Pkt* p=new Pkt();
        p->setId(1);
        p->setSrc(1);
        p->setDest(2);
        p->setType(0);
        send(p,outGate);
    }else{
        Pkt* m=check_and_cast<Pkt*>(msg);
        if(m->getType()==0){
            Pkt* a=new Pkt();
            a->setId(m->getId());
            a->setSrc(2);
            a->setDest(1);
            a->setType(1);
            send(a,outGate);
        }else{
            if(count>0){
                count--;
                Pkt* p=new Pkt();
                p->setId(10-count);
                p->setSrc(1);
                p->setDest(2);
                p->setType(0);
                send(p,outGate);
            }
        }
    }
}
