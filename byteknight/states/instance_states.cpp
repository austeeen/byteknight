#include "instance_states.hpp"
#include "scene/instance.hpp"

/**************************************************************************************************/

StartUp<Instance>::StartUp(Instance* o): BaseState<Instance>(o)
{}
void StartUp<Instance>::enter()
{}
void StartUp<Instance>::next(sptr<SquareEvent> e)
{}
void StartUp<Instance>::exit()
{}
void StartUp<Instance>::update(const float dt)
{}
void StartUp<Instance>::render(sf::RenderWindow* window)
{}

/**************************************************************************************************/

Running<Instance>::Running(Instance* o): BaseState<Instance>(o)
{}
void Running<Instance>::enter()
{}
void Running<Instance>::next(sptr<SquareEvent> e)
{
    switch(e->msg) {
        case MSG::CTLR_PRESSED: {
            switch(e->binding.binding)
            {
                case io::quit: {
                    this->_obj->node->notifyNode(mkptr<SquareEvent>(MSG::EXIT_GAME), "scene_manager");
                    break;
                }
                case io::menu: {
                    this->_obj->node->notifyNode(mkptr<SquareEvent>(MSG::OPEN_PAUSE_MENU), "scene_manager");
                    break;
                }
                default: { break; }
            }
            break;
        }
        case MSG::TEAM_LOST: {
            this->_obj->switchState(statekey::teardown, e);
            break;
        }
        default: { break; }
    }
}
void Running<Instance>::exit()
{}
void Running<Instance>::update(const float dt)
{}
void Running<Instance>::render(sf::RenderWindow* window)
{}

/**************************************************************************************************/

TearDown<Instance>::TearDown(Instance* o): BaseState<Instance>(o)
{}
void TearDown<Instance>::enter(sptr<SquareEvent> e)
{
    std::cout << "GAME OVER!" << std::endl;
    if (e->msg_str != "") {
        std::cout << e->msg_str << " LOST" << std::endl;
    }
}
void TearDown<Instance>::next(sptr<SquareEvent> e)
{}
void TearDown<Instance>::exit()
{
    this->_obj->node->notifyNode(mkptr<SquareEvent>(MSG::EXIT_GAME), "scene_manager");
}
void TearDown<Instance>::update(const float dt)
{
    bool exit = true;
    for (auto& lyr : this->_obj->layers) {
        exit &= lyr->canExit();
    }
    if (exit) {
        this->_obj->switchState(statekey::startup);
    }
}
void TearDown<Instance>::render(sf::RenderWindow* window)
{}
