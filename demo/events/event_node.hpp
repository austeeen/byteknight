#ifndef EVT_NODE_HPP
#define EVT_NODE_HPP

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

// idea - break up event node into less functional but faster/lighter/concise sub-types such as
//  listener,  dispatcher, subscriber, channel, etc.

// todo - how to manage the nodes and events in heap? maybe revisit shared_ptr?

#include "event_network.hpp"
#include "input_types.hpp"


typedef const unsigned int node_id;


/*
listener
    - subscribes directly to node

dispatcher
    - sends messages to other nodes

subscriber
    - subscribes to a channel

channel
    - sends messages to subscribers
*/

struct node
{
    node_id id;
    std::deque<SquareEvent*> queued;
    std::deque<SquareEvent*> events;
    std::vector<std::string> observers;
};

struct channel
{
    const std::string name;
    const node *owner;
    std::vector<node*> subs;
};

class Node
{
public:
    Node(const std::string &node_name, EventNetwork* network);
    ~Node();
    void setChannel(const std::string &channel_name);
    void subscribe(const std::string &channel_name);
    void observe(const std::string &node_name);
    void setObserver(const std::string &node_name);
    void notifySelf(SquareEvent *event);
    void notifyNode(SquareEvent *event, const std::string &node_name);
    void notifyMyChannel(SquareEvent *event);
    void notifyChannel(SquareEvent *event, const std::string &channel_name);
    void notifyObservers(SquareEvent *event);
    bool hasEvents() const { return !events.empty(); }
    SquareEvent* pop();
    void push(SquareEvent *event);
    void enqueueEvents();
    void clearEvents();
    void clearAll();

    std::ostream& operator<<(std::ostream& os);
    const std::string& tostr() const;
    const std::string& name() const { return node_name; }

private:
    const std::string node_name;
    std::string channel_name;
    EventNetwork* network;
    std::deque<SquareEvent*> queued;
    std::deque<SquareEvent*> events;
    std::vector<std::string> observers;

};

#endif // EVT_NODE_HPP
