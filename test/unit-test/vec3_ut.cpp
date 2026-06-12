#include "../../src/vec3.h"

#include <cassert>
#include <cmath>
#include <iostream>

int main() {
    vec3 a(1, 2, 3);
    vec3 b(4, 5, 6);

    vec3 sum = a + b;
    assert(sum.x() == 5);
    assert(sum.y() == 7);
    assert(sum.z() == 9);

    vec3 diff = b - a;
    assert(diff.x() == 3);
    assert(diff.y() == 3);
    assert(diff.z() == 3);

    vec3 scaled = 2.0 * a;
    assert(scaled.x() == 2);
    assert(scaled.y() == 4);
    assert(scaled.z() == 6);

    assert(std::abs(a.length() - std::sqrt(14)) < 1e-9);

    std::cout << "All vec3 tests passed.\n";
}
