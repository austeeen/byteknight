#ifndef EVT_NETWORK_HPP
#define EVT_NETWORK_HPP

#include <cmath>
#include <cstdio>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include <deque>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "input_types.hpp"
class EventNode;

// idea - break up event node into less functional but faster/lighter/concise sub-types such as
//  listener,  dispatcher, subscriber, channel, etc.


class EventNetwork
{
public:
    EventNetwork();
    ~EventNetwork();
    // todo these used to be default args and made more sense that way -- re-evaluate
    EventNode* newNode(const std::string& nd_name, bool create_channel=true);
    EventNode* newNode(const std::string& nd_name, const std::string& chn_name);
    void deleteNode(const std::string& nd_name);
    bool channelExists(const std::string& chn_name);
    void newChannel(const std::string& chn_name);
    void deleteChannel(const std::string& chn_name);
    void subscribe(const std::string& nd_name, const std::string& chn_name);
    void subscribeNew(const std::string& nd_name, const std::string& chn_name);
    void observe(const std::string& listener_nd, const std::string& observed_nd);
    void emitToNode(SquareEvent *event, const std::string& nd_name);
    void emitToChannel(SquareEvent *event, const std::string& chn_name);
    void flipEvents();
    void clearNodes();

    const std::string& tostr() const; // todo

private:
    void __pushToNode(SquareEvent *event, const std::string& nd_name);

    std::map<std::string, EventNode*> node_table;
    std::map<std::string, std::set<std::string>> channel_table;
    std::set<std::string> received_events;
    std::set<std::string> processed_events;
};


#endif // EVT_NODE_HPP
