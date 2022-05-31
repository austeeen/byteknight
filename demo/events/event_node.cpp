#include "event_node.hpp"

Node::Node(const std::string &node_name, EventNetwork* network) :
node_name(node_name), network(network)
{
    std::cout << "create node " << node_name << std::endl;
}
Node::~Node()
{
    network->deleteNode(this->node_name);
}
void Node::setChannel(const std::string &channel_name)
{
    if (!network->channelExists(channel_name))
        network->newChannel(channel_name);
    this->channel_name = channel_name;
    std::cout << "node " << node_name << " has channel " << channel_name << std::endl;
}
void Node::subscribe(const std::string &channel_name)
{
    network->subscribe(this->node_name, channel_name);
}
void Node::observe(const std::string &node_name)
{
    network->observe(this->node_name, node_name);
}
void Node::setObserver(const std::string &node_name)
{
    observers.push_back(node_name);
}
void Node::notifySelf(SquareEvent *event)
{
    network->emitToNode(event, this->node_name);
}
void Node::notifyNode(SquareEvent *event, const std::string &node_name)
{
    network->emitToNode(event, node_name);
}
void Node::notifyMyChannel(SquareEvent *event)
{
    network->emitToNode(event, this->channel_name);
}
void Node::notifyChannel(SquareEvent *event, const std::string &channel_name)
{
    network->emitToNode(event, channel_name);
}
void Node::notifyObservers(SquareEvent *event)
{
    for (auto& obs_name : this->observers)
        this->notifyNode(event, obs_name);
}
SquareEvent* Node::pop()
{
    SquareEvent* e = this->events.front();
    this->notifyObservers(e);
    events.pop_front();
    return e;
}
void Node::push(SquareEvent *event)
{
    this->queued.push_back(event);
}
void Node::enqueueEvents()
{
    while (!queued.empty()) {
        this->events.push_back(this->queued.front());
        queued.pop_front();
    }
}
void Node::clearEvents() {
    for (auto& event : events) {
        delete event;
        event = nullptr;
    }
    this->events.clear();

}
void Node::clearAll() {
    this->queued.clear();
    this->events.clear();
}
