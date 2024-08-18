#include "PropertyBag.h"
#include <iostream>

int main(int argc [[maybe_unused]], char** argv [[maybe_unused]])
{
    StringPropertyBag<int> pb1({{1, {"eins"}}, {2, {"zwei"}}});

    return 0;
}
