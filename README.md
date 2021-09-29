# fsm-cxx

![CMake Build Matrix](https://github.com/hedzr/fsm-cxx/workflows/CMake%20Build%20Matrix/badge.svg) <!-- 
![CMake Build Matrix](https://github.com/hedzr/fsm-cxx/workflows/CMake%20Build%20Matrix/badge.svg?event=release) 
--> [![GitHub tag (latest SemVer)](https://img.shields.io/github/tag/hedzr/fsm-cxx.svg?label=release)](https://github.com/hedzr/fsm-cxx/releases)

`fsm-cxx` is a finite state machina library for C++17, header-only, light-weight but full-featured, and designed for easy binding and friendly programmatic interface.

**WIP**

## Features

- Entry/exit actions
- Event actions
- Transition actions
- [ ] Transition conditions (input action)
- Event payload (classes)
- [ ] Inheritance of states and action functions
- [ ] Documentations (NOT YET)
- [ ] Examples (NOT YET)

---

<!--
Statechart features
Hierarchical states
Entry and exit actions
Internal transitions
Transition actions
Transition guards (conditions)
State history
Event deferring
Orthogonal regions
Statechart extensions
Optional event priority
Optional common base for states and easy definition of dispatching common interface calls to current state
Pushdown automaton
Compile-time checks
Thread safety
Exception safety
No vtables (unless common base feature is used)
Header only
Relatively fast compile time
No external dependencies except STL
-->

## Usages

A simple state machine is:

```cpp
#include <fsm_cxx.hh>
namespace fsm_cxx { namespace test {

    // states

    AWESOME_MAKE_ENUM(my_state,
                      Empty,
                      Error,
                      Initial,
                      Terminated,
                      Opened,
                      Closed)

    // event

    struct event_base {};
    struct begin : public event_base {};
    struct end : public event_base {};
    struct open : public event_base {};
    struct close : public event_base {};

    void test_state_meta() {
        // using namespace hicc::dp::state::meta;
        // using namespace hmeta;
        machine_t<my_state, event_base> m;
        using M = decltype(m);

        m.initial(my_state::Initial)
                .terminated(my_state::Terminated)
                .error(my_state::Error, [](event_base const &, M::Context &, M::State const &, M::Payload const &) { std::cerr << "          .. <error> entering" << '\n'; })
                .state(
                        my_state::Opened,
                        [](event_base const &, M::Context &, M::State const &, M::Payload const &) { std::cout << "          .. <opened> entering" << '\n'; },
                        [](event_base const &, M::Context &, M::State const &, M::Payload const &) { std::cout << "          .. <opened> exiting" << '\n'; })
                .state(
                        my_state::Closed,
                        [](event_base const &, M::Context &, M::State const &, M::Payload const &) { std::cout << "          .. <closed> entering" << '\n'; },
                        [](event_base const &, M::Context &, M::State const &, M::Payload const &) { std::cout << "          .. <closed> exiting" << '\n'; });

        m.transition(my_state::Initial, begin{}, my_state::Closed)
                .transition(
                        my_state::Closed, open{}, my_state::Opened,
                        [](event_base const &, M::Context &, M::State const &, M::Payload const &) { std::cout << "          .. <closed -> opened> entering" << '\n'; },
                        [](event_base const &, M::Context &, M::State const &, M::Payload const &) { std::cout << "          .. <closed -> opened> exiting" << '\n'; })
                .transition(my_state::Opened, close{}, my_state::Closed)
                .transition(my_state::Closed, end{}, my_state::Terminated);
        m.transition(my_state::Opened,
                     M::Transition{end{}, my_state::Terminated,
                                   [](event_base const &, M::Context &, M::State const &, M::Payload const &) { std::cout << "          .. <T><END>" << '\n'; },
                                   nullptr});

        // debug log
        m.on_action_for_debug([&m](auto const &from, auto const &ev, auto const &to, auto const &actions, auto const &payload) {
            std::printf("        [%s] -- %s --> [%s] (payload = %s)\n", m.state_to_sting(from).c_str(), ev.c_str(), m.state_to_sting(to).c_str(), to_string(payload).c_str());
            UNUSED(actions);
        });

        // processing

        m.step_by(begin{});
        m.step_by(open{});
        m.step_by(close{});
        m.step_by(open{});
        m.step_by(end{});
        
        std::printf("---- END OF test_state_meta()\n\n\n");
    }
}

int main() {
    fsm_cxx::test::test_state_meta();
    return 0;
}
```

## For Developer



### Build

> 1. gcc 10+: passed
> 2. clang 12+: passed
> 3. msvc build tool 16.7.2, 16.8.5 (VS2019 or Build Tool) passed

ninja is optional for faster building.

```bash
# configure
cmake -S . -B build/ -G Ninja
# build
cmake --build build/
# install
cmake --install build/
# Or:cmake --build build/ --target install
#
# Sometimes sudo it:
#   sudo cmake --build build/ --target install
# Or:
#   cmake --install build/ --prefix ./install --strip
#   sudo cp -R ./install/include/* /usr/local/include/
#   sudo cp -R ./install/lib/cmake/fsm_cxx /usr/local/lib/cmake/
```


### Other CMake Options

1. `FSM_CXX_BUILD_TESTS_EXAMPLES`=OFF
2. `FSM_CXX_BUILD_DOCS`=OFF
3. ...


## Thanks to JODL

Thanks to [JetBrains](https://www.jetbrains.com/?from=fsm-cxx) for donating product licenses to help develop **fsm-cxx** [![jetbrains](https://gist.githubusercontent.com/hedzr/447849cb44138885e75fe46f1e35b4a0/raw/bedfe6923510405ade4c034c5c5085487532dee4/jetbrains-variant-4.svg)](https://www.jetbrains.com/?from=hedzr/fsm-cxx)


## LICENSE

MIT


## 🔚
