#include "Header.h"

int main() {
    Segment3D s1(Vector3D(4.0, 1.0, 3.0), Vector3D(2.0, 3.0, 7.0))
            , s2(Vector3D(3.0, 0.0, 0.0), Vector3D(3.0, 4.0, 10.0));
    decltype(auto) result = Intersect(s1, s2);
    std::cout << std::scientific << std::setprecision(15) << result.x() << std::endl
                                                          << result.y() << std::endl
                                                          << result.z() << std::endl;
    return 0;
}

auto 
Intersect(const Segment3D& s1, const Segment3D& s2) -> Vector3D {

    decltype(auto) result = intersection_checker(s1, s2);
    if (result.status() == ResultStatus::Intersection) return result.value();
    std::cout << result.message() << std::endl;
    return Vector3D(NAN, NAN, NAN);
}