#ifndef PRP_STATEFUL_H
#define PRP_STATEFUL_H

#include "common.hpp"
#include "states/generic_states.hpp"

template<class T>
class Stateful
{
public:
    Stateful():
    _cur_state(nullptr)
    {}
    ~Stateful() {
        _cur_state = nullptr;
        for (auto [k, s] : _states)
            SQ::destroy(s);
        _states.clear();
    }
    void switchState(statekey next_state) {
        this->__swapNoEnter(next_state);
        this->_cur_state->enter();
    }
    void switchState(statekey next_state, sptr<SquareEvent> e) {
        this->__swapNoEnter(next_state);
        this->_cur_state->enter(e);
    }
    void registerState(statekey key, BaseState<T>* state) {
        this->_states[key] = state;
    }

protected:
    std::map<statekey, BaseState<T>*> _states;
    BaseState<T>* _cur_state;
    statekey _cur_state_key;

private:
    void __swapNoEnter(statekey next_state) {
        if (_cur_state != nullptr) {
            this->_cur_state->exit();
        }
        this->_cur_state_key = next_state;
        this->_cur_state = _states[_cur_state_key];
    }
};

#endif // PRP_STATEFUL_H
