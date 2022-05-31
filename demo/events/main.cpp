#include "event_network.hpp"
#include "event_node.hpp"

EventNetwork* network;
EventNode* node1;
EventNode* node2;
EventNode* node3;
EventNode* node4;

void print_events(EventNode *n)
{
    std::cout << "-- " << n->name() << std::endl;
    while (n->hasEvents())
        std::cout << n->pop()->msg_str << std::endl;
    std::cout << "--------" << std::endl;
}

void flip(int& i)
{
    print_events(node1);
    print_events(node2);
    print_events(node3);
    print_events(node4);
    network->flipEvents();
    std::cout << "-------------- " << std::to_string(i) << " -------------------" << std::endl;
    i ++;
}

int main()
{
    network = new EventNetwork();
    node1 = network->newNode("node1", false);
    node2 = network->newNode("node2", true);
    node3 = network->newNode("node3", std::string("channel3"));
    node4 = network->newNode("node4", true);

    node2->observe("node1");
    node3->subscribe("node2");
    node4->subscribe("node2");
    node4->subscribe("channel3");

    int i = 0;
    while (i < 5) {
        SquareEvent* e1 = new SquareEvent{"first msg of: " + std::to_string(i)};
        SquareEvent* e2 = new SquareEvent{"second msg of: " + std::to_string(i)};

        node1->notifySelf(e1);
        node2->notifyMyChannel(e1);
        node3->notifyChannel(e2, "node4");
        node1->notifyObservers(e2);

        flip(i);
    }

    flip(i);
    flip(i);
    flip(i);
}
