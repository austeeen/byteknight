#include "event_node.hpp"

namespace bt
{
Node::Node(const std::string &node_name) : node_name(node_name)
{
    debug("Node", "created %s", node_name.c_str());
    Network::connectNode(node_name, this);
    eit = events.end();
}
Node::~Node()
{
    Network::removeNode(this->node_name);
    queued.clear();
    events.clear();
    channel_list.clear();
    observers.clear();
}

/********* channels *********/
void Node::createChannel(const std::string &channel_name)
{
    if (this->channel_list.count(channel_name) == 0) {
        this->channel_list[channel_name] = std::set<std::string>();
    }
    setChannel(channel_name);
}
void Node::setChannel(const std::string &channel_name)
{
    if (this->channel_list.count(channel_name) == 0) {
        warn("Node::setChannel", "cannot assign node %s to channel %s, channel does not exist", node_name.c_str(), channel_name.c_str());
        return;
    }
    this->current_channel = channel_name;
    debug("Node::setChannel", "node %s on channel %s", node_name.c_str(), channel_name.c_str());
}
void Node::subscribe(const std::string &channel_node, const std::string &channel_name)
{
    Network::subscribe(this->node_name, channel_node, channel_name);
}
void Node::addSubscriber(const std::string &node_name, const std::string &channel_name)
{
    if (this->channel_list.count(channel_name) == 0) {
        warn("Node::addSubscriber", "cannot assign node %s to channel %s, channel does not exist", node_name.c_str(), channel_name.c_str());
        return;
    }
    this->channel_list[channel_name].insert(node_name);
    debug("Node::subscribe", "node %s subscribed to channel %s", node_name.c_str(), channel_name.c_str());
}

/********* observing *********/
void Node::observe(const std::string &node_name)
{
    Network::observe(this->node_name, node_name);
    debug("Node::observe", "node %s observing %s", this->node_name.c_str(), node_name.c_str());
}
void Node::setObserver(const std::string &node_name)
{
    observers.push_back(node_name);
}

/********* flagging *********/
void Node::flagMsg(const MSG msg)
{
    Network::addFlaggedMsg(msg, node_name);
}

/********* notifying *********/
void Node::notifySelf(sptr<SquareEvent> event)
{
    Network::emitToNode(event, this->node_name);
}
void Node::notifyNode(sptr<SquareEvent> event, const std::string &node_name)
{
    Network::emitToNode(event, node_name);
}
void Node::notifyChannel(sptr<SquareEvent> event)
{
    for (auto& node_name : this->channel_list[this->current_channel]) {
        Network::emitToNode(event, node_name);
    }
}
void Node::notifyObservers(sptr<SquareEvent> event)
{
    for (auto& obs_name : this->observers)
        this->notifyNode(event, obs_name);
}

/********* receiving *********/
sptr<SquareEvent> Node::pop()
{
    sptr<SquareEvent> e = *eit;
    eit++;
    this->notifyObservers(e);
    if (e->msg != MSG::CTLR_RELEASED) {
        debug(node_name.c_str(), "popped: %s", e->tostr().c_str());
    }
    return e;
}
void Node::push(sptr<SquareEvent> event)
{
    // debug(node_name.c_str(), "queued: %s", event->tostr().c_str());
    this->queued.push_back(event);
}

/********* event cycle *********/
void Node::enqueueEvents()
{
    for ( auto& evt : this->queued) {
        this->events.push_back(evt);
        // debug(node_name.c_str(), "enqueued: %s", evt->tostr().c_str());
    }
    this->queued.clear();
}
void Node::clearEvents()
{
    for (auto& event : events)
        destroy(event);
    this->events.clear();
    eit = events.begin();
}
void Node::clearAll()
{
    for (auto& e : queued)
        destroy(e);
    this->queued.clear();

    for (auto& e : events)
        destroy(e);
    this->events.clear();
    eit = events.begin();
}
}
