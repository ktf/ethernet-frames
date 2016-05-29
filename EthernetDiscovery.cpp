//
// Created by kevin on 5/29/16.
//

#include <iostream>
#include "EthernetDiscovery.h"

using namespace Network;
using namespace std;

bool EthernetDiscovery::dataArrival(Network::EthernetFrame &ef, uint8_t *data, size_t len) {

    switch (*data) {

        case MessageType::HELLO:
        {
            if (ef.destinationMac == MacAddress::GetBroadcastMac()) {
                // Just received a broadcast HELLO, Reply appropriately
                EthernetFrame replyEf;
                replyEf.destinationMac = ef.sourceMac;
                replyEf.sourceMac = ethernetSocket.getInterfaceMac();
                ethernetSocket.send(ef, {MessageType::HELLO});
            } else {
                // Add to list - Verify that we are master
                slaveMacs.push_back(ef.sourceMac);
            }
        }
            break;

        case MessageType::BEGIN:
        {

        }
            break;

        case MessageType::READY:
        {

        }
            break;

        case MessageType::START:
        {

        }
            break;

        case MessageType::TEST:
        {

        }
            break;

        case MessageType::REQUEST:
        {

        }
            break;

        case MessageType::YES:
        {

        }
            break;

        case MessageType::NO:
        {

        }
            break;

        case MessageType::EMPTY:
        default:
            return false;
    }

    return true;
}


EthernetDiscovery::EthernetDiscovery(EthernetSocket &ethernetSocket)
        : ethernetSocket ( ethernetSocket )
{

}

// Algorithm I
void EthernetDiscovery::getAllDevices() {
    // Send a broadcast packet to everyone
    EthernetFrame ef;
    ef.destinationMac = MacAddress::GetBroadcastMac();
    ef.setEtherType(ETH_P_ALL);
    ethernetSocket.send(ef, {MessageType::HELLO});

    // Receive the messages with destination Mac equivalent to ours
    ethernetSocket.setReceiveTimeout(2);
    ethernetSocket.receive(nullptr, &ethernetSocket.getInterfaceMac(), ETH_P_ALL, this);
    ethernetSocket.setReceiveTimeout(0);

    // Print vector
    cout << "Received From: " << slaveMacs.size() <<  endl;
    for (size_t i = 0; i < slaveMacs.size(); ++i) {
        cout << slaveMacs[i] << endl;
    }
}

void EthernetDiscovery::slave() {
    ethernetSocket.receive(nullptr, nullptr, ETH_P_ALL, this);
}






