#include "event_network.hpp"
#include "event_node.hpp"

namespace bt
{
std::map<std::string, Node*> Network::node_table;
std::set<std::string> Network::received_events;
std::set<std::string> Network::processed_events;

void Network::shutdown()
{
    for (auto [name, node] : node_table)
        delete node;
    node_table.clear();
}
void Network::flipEvents()
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
void Network::clearNodes()
{
    for (auto [name, node] : node_table)
        node->clearAll();
}
const std::string Network::tostr()
{
    // todo
    return "not implemented";
}

/********* node managing *********/
void Network::connectNode(const std::string& nd_name, Node* node)
{
    if (node_table.count(nd_name)) {
        warn("Network::connectNode", "cannot connect node %s -- already connected.", nd_name.c_str());
        return;
    }
    node_table[nd_name] = node;
}
void Network::removeNode(const std::string& nd_name)
{
    node_table.erase(nd_name);
}

/********* channels *********/
void Network::subscribe(const std::string& nd_name, const std::string& chn_node, const std::string& chn_name)
{
    if (!node_table.count(nd_name)) {
        warn("Network::subscribe", "cannot subscribe node %s -- does not exist.", nd_name.c_str());
        return;
    }
    node_table[chn_node]->addSubscriber(nd_name, chn_name);
}

/********* observing *********/
void Network::observe(const std::string& listener_nd, const std::string& observed_nd)
{
    node_table[observed_nd]->setObserver(listener_nd);
}

/********* flagging *********/
void Network::addFlaggedMsg(const MSG msg, const std::string& nd_name)
{
    // todo maybe
}

/********* notifying *********/
void Network::emitToNode(sptr<SquareEvent> event, const std::string& nd_name)
{
    __pushToNode(event, nd_name);
}
void Network::__pushToNode(sptr<SquareEvent> event, const std::string &nd_name)
{
    if(node_table.count(nd_name) == 0) {
        warn("Network::__pushToNode", "cannot push event to %s -- does not exist", nd_name.c_str());
        return;
    }
    received_events.insert(nd_name);
    node_table[nd_name]->push(event);
}
}
