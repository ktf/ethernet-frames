//
// Created by kevin on 5/29/16.
//

#ifndef NETWORK_DISCOVERY_ETHERNETDISCOVERY_H
#define NETWORK_DISCOVERY_ETHERNETDISCOVERY_H

#include <set>

#include "EthernetSocket.h"
#include "ISocketListener.h"

namespace  Network {

    class EthernetDiscovery
        : public ISocketListener
    {
    public:

        enum MessageType : uint8_t
        {
            EMPTY = 0,
            HELLO = 1,
            BEGIN = 2,
            READY = 3,
            START = 4,
            TEST = 5,
            REQUEST = 6,
            YES = 7,
            NO = 8,
            SEND_PACKET = 9,
            PROBE = 10
        };

        EthernetDiscovery(EthernetSocket& ethernetSocket);

        bool dataArrival(EthernetFrame& ef, uint8_t * data, size_t len) override;
        void master();
        void slave();

        // Algorithm 1
        void getAllDevices();
        // Algorithm 2
        void partitionBottomLayer();
        // Algorithm 3
        bool testPermutation(const MacAddress &gateway, const MacAddress& i, const MacAddress& j, const MacAddress& k);
        // Algorithm 4
        void discoverNetwork();


    private:
        EthernetSocket & ethernetSocket;

        std::vector<MacAddress> slaveMacs;

        std::vector<std::set<size_t>> connectivitySet;

        MessageType lastMessage;
        bool testReceived;

    };

}

#endif //NETWORK_DISCOVERY_ETHERNETDISCOVERY_H
