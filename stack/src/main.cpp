#include <iostream>
#include <cassert>
#include "selene.h"

int main()
{
    sel::State state;
    state.Load("./test.lua");

    assert(state["foo"] == 4);
    std::string str = state["bar"][3];
    std::cout << str << std::endl;
    assert(state["bar"]["key"] == "there");

    return 0;
}
