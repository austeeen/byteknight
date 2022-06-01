#ifndef EVT_NODE_HPP
#define EVT_NODE_HPP

#include "common.hpp"
#include "event_network.hpp"

namespace bt
{
class Node
{
public:
    Node(const std::string &node_name);
    ~Node();
    void createChannel(const std::string &channel_name);
    void setChannel(const std::string &channel_name);
    void subscribe(const std::string &channel_node, const std::string &channel_name);
    void addSubscriber(const std::string &node_name, const std::string &channel_name);

    void observe(const std::string &node_name);
    void setObserver(const std::string &node_name);

    void flagMsg(const MSG msg);

    void notifySelf(sptr<SquareEvent> event);
    void notifyNode(sptr<SquareEvent> event, const std::string &node_name);
    void notifyChannel(sptr<SquareEvent> event);
    void notifyObservers(sptr<SquareEvent> event);

    bool hasEvents() const { return eit != events.end(); }
    sptr<SquareEvent> pop();
    void push(sptr<SquareEvent> event);
    void enqueueEvents();
    void clearEvents();
    void clearAll();

    std::ostream& operator<<(std::ostream& os);
    const std::string& tostr() const;
    const std::string& name() const { return node_name; }

private:
    std::deque<sptr<SquareEvent>>::iterator eit;
    const std::string node_name;
    std::deque<sptr<SquareEvent>> queued;
    std::deque<sptr<SquareEvent>> events;

    std::string current_channel;
    std::map<std::string, std::set<std::string>> channel_list;
    std::vector<std::string> observers;

};
}

#endif // EVT_NODE_HPP
