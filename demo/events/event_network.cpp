#include "event_network.hpp"
#include "event_node.hpp"
#include "input_types.hpp"

EventNetwork::EventNetwork()
{}
EventNetwork::~EventNetwork()
{
    // todo -- this shouldn't be necessary based on python implementation
    //   would normally store weak pointers in the table and have the node be owned and destroyed by
    //   its object
    for (auto [name, node] : node_table)
        delete node;
    node_table.clear();
}
EventNode* EventNetwork::newNode(const std::string& nd_name, bool create_channel)
{
    std::cout << "new node default channel name\n";
    if (node_table.count(nd_name)) {
        std::cout << "cannot create node " << nd_name << " -- already exists." << std::endl;
        return nullptr;
    }
    EventNode* node = new EventNode(nd_name, this);
    if (create_channel)
        node->setChannel(nd_name);
    node_table[nd_name] = node; // weakref
    return node;
}
EventNode* EventNetwork::newNode(const std::string& nd_name, const std::string& chn_name)
{
    std::cout << "new node with channel name\n";
    if (node_table.count(nd_name)) {
        std::cout << "cannot create node " << nd_name << " -- already exists." << std::endl;
        return nullptr;
    }
    EventNode* node = new EventNode(nd_name, this);
    node->setChannel(chn_name);
    node_table[nd_name] = node; // weakref
    return node;
}
void EventNetwork::deleteNode(const std::string& nd_name)
{
    node_table.erase(nd_name);
    if (channel_table.count(nd_name))
        channel_table.erase(nd_name);
    for (auto [net_name, network_set] : channel_table) {
        if (network_set.count(nd_name))
            network_set.erase(nd_name);
    }
}
bool EventNetwork::channelExists(const std::string& chn_name)
{
    return channel_table.count(chn_name) > 0;
}
void EventNetwork::newChannel(const std::string& chn_name)
{
    if (channelExists(chn_name)) {
        std::cout << "cannot create channel " << chn_name << " -- already exists." << std::endl;
        return;
    }
    channel_table[chn_name] = std::set<std::string>();
}
void EventNetwork::deleteChannel(const std::string& chn_name)
{
    if (!channelExists(chn_name)) {
        std::cout << "cannot delete channel " << chn_name << " -- does not exist." << std::endl;
        return;
    }
    channel_table.erase(chn_name);
}
void EventNetwork::subscribe(const std::string& nd_name, const std::string& chn_name)
{
    std::cout << "subscribe " << nd_name << std::endl;
    for(auto& [n, c] : channel_table) {
        std::cout << n << ", ";
    }
    std::cout << std::endl;

    if (!channelExists(chn_name)) {
        std::cout << "cannot subscribe to channel " << chn_name << " -- does not exist." << std::endl;
        return;
    }
    if (!node_table.count(nd_name)) {
        std::cout << "cannot subscribe node " << nd_name << " -- does not exist." << std::endl;
        return;
    }

    channel_table[chn_name].insert(nd_name);
}
void EventNetwork::subscribeNew(const std::string& nd_name, const std::string& chn_name)
{
    if (!channelExists(chn_name)) {
        std::cout << "channel " << chn_name << " does not exist. creating new one" << std::endl;
        newChannel(chn_name);
    }
    channel_table[chn_name].insert(nd_name);
}
void EventNetwork::observe(const std::string& listener_nd, const std::string& observed_nd)
{
    node_table[observed_nd]->setObserver(listener_nd);
}
void EventNetwork::emitToNode(SquareEvent *event, const std::string& nd_name)
{
    __pushToNode(event, nd_name);
}
void EventNetwork::emitToChannel(SquareEvent *event, const std::string& chn_name)
{
    for (auto& sub_name : channel_table[chn_name])
        __pushToNode(event, sub_name);
}
void EventNetwork::flipEvents()
{
    for (auto& node_name : processed_events)
        node_table[node_name]->clearEvents();
    processed_events.clear();

    for (auto& node_name : received_events) {
        node_table[node_name]->enqueueEvents();
        processed_events.insert(node_name);
    }
    received_events.clear();
}
void EventNetwork::clearNodes()
{
    for (auto [name, node] : node_table)
        node->clearAll();
}
void EventNetwork::__pushToNode(SquareEvent *event, const std::string &nd_name)
{
    if(node_table.count(nd_name) == 0) {
        std::cout << "cannot push event to node named " << nd_name << "; does not exist" << std::endl;
        return;
    }
    received_events.insert(nd_name);
    node_table[nd_name]->push(event);
}
