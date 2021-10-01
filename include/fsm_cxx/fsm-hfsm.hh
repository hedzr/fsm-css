//
// Created by Hedzr Yeh on 2021/9/29.
//

#ifndef FSM_CXX_FSM_HFSM_HH
#define FSM_CXX_FSM_HFSM_HH


#include "fsm-def.hh"

#include "fsm-assert.hh"
#include "fsm-debug.hh"

#include <algorithm>
#include <functional>
#include <memory>
#include <new>
#include <random>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>

#include <atomic>
#include <condition_variable>
#include <mutex>

// #include <any>
// #include <array>
#include <chrono>
// #include <deque>
// #include <initializer_list>
// #include <list>
// #include <map>
// #include <set>
#include <unordered_map>
#include <vector>

// #include <cstdio>
// #include <cstdlib>
// #include <cstring> // std::strcmp, ...
// #include <iomanip>
// #include <iostream>
#include <string>

#include <math.h>


namespace fsm::hierarchy {

    template<typename T>
    struct state_t {
        virtual ~state_t() {}
        
        using State = state_t<T>;
        using States = std::vector<State>;
        using Parent = State*;
        
        Parent _parent{};
        States _children{};
    };

} // namespace fsm::hierarchy

#endif //FSM_CXX_FSM_HFSM_HH
