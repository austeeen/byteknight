#ifndef EVT_NETWORK_HPP
#define EVT_NETWORK_HPP

#include "common.hpp"
#include "datacore/event_core.hpp"

namespace bt
{
class Node;

// idea - break up event node into less functional but faster/lighter/concise sub-types such as
//  listener,  dispatcher, subscriber, channel, etc.

/*
notifying   -- any node can emit events TO any other node using the target node's name
subscribing -- any node may subscribe to any existing channel by its channel name
observing   -- any node may observe any other existing node by its name

observers -- all events emitted FROM a node are also emitted TO its observer list (observers)
channels -- a node may own a channel that it can emit events TO its channel list (subscribers)
*/

class Network
{
public:
    static void shutdown();
    static void flipEvents();
    static void clearNodes();
    static const std::string tostr();

protected:
    friend class Node;
    /********* node managing *********/
    static void connectNode(const std::string& nd_name, Node* node);
    static void removeNode(const std::string& nd_name);

    /********* channels *********/
    static void subscribe(const std::string& nd_name, const std::string& chn_node, const std::string& chn_name);

    /********* observing *********/
    static void observe(const std::string& listener_nd, const std::string& observed_nd);

    /********* flagging *********/
    static void addFlaggedMsg(const MSG msg, const std::string& nd_name); // todo maybe

    /********* notifying *********/
    static void emitToNode(sptr<SquareEvent> event, const std::string& nd_name);

private:
    static void __pushToNode(sptr<SquareEvent> event, const std::string& nd_name);

    static std::map<std::string, Node*> node_table;
    static std::map<MSG, std::set<std::string>> flagged_msgs;
    static std::set<std::string> received_events;
    static std::set<std::string> processed_events;
};
}

#endif // EVT_NODE_HPP
