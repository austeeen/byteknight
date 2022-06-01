#include "instance_states.hpp"
#include "scene/instance.hpp"

/**************************************************************************************************/

StartUp<bt::Instance>::StartUp(bt::Instance* o): BaseState<bt::Instance>(o)
{}
void StartUp<bt::Instance>::enter()
{}
void StartUp<bt::Instance>::next(sptr<SquareEvent> e)
{}
void StartUp<bt::Instance>::exit()
{}
void StartUp<bt::Instance>::update(const float dt)
{}
void StartUp<bt::Instance>::render(sf::RenderWindow* window)
{}

/**************************************************************************************************/

Running<bt::Instance>::Running(bt::Instance* o): BaseState<bt::Instance>(o)
{}
void Running<bt::Instance>::enter()
{}
void Running<bt::Instance>::next(sptr<SquareEvent> e)
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
void Running<bt::Instance>::exit()
{}
void Running<bt::Instance>::update(const float dt)
{}
void Running<bt::Instance>::render(sf::RenderWindow* window)
{}

/**************************************************************************************************/

TearDown<bt::Instance>::TearDown(bt::Instance* o): BaseState<bt::Instance>(o)
{}
void TearDown<bt::Instance>::enter(sptr<SquareEvent> e)
{
    std::cout << "GAME OVER!" << std::endl;
    if (e->msg_str != "") {
        std::cout << e->msg_str << " LOST" << std::endl;
    }
}
void TearDown<bt::Instance>::next(sptr<SquareEvent> e)
{}
void TearDown<bt::Instance>::exit()
{
    this->_obj->node->notifyNode(mkptr<SquareEvent>(MSG::EXIT_GAME), "scene_manager");
}
void TearDown<bt::Instance>::update(const float dt)
{
    bool exit = true;
    for (auto& lyr : this->_obj->layers) {
        exit &= lyr->canExit();
    }
    if (exit) {
        this->_obj->switchState(statekey::startup);
    }
}
void TearDown<bt::Instance>::render(sf::RenderWindow* window)
{}
