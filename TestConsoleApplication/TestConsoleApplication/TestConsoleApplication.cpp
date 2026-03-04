#include "Header.h"

int main() {
    Segment3D s1(Vector3D(1.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0))
        , s2(Vector3D(2.0, 0.0, 0.00001), Vector3D(2.0, 0.0, 3.00001));
    
    decltype(auto) result = Intersect(s1, s2);
    
    std::cout << std::scientific << std::setprecision(15)<< "x: " << result.x() << std::endl
                                                         << "y: " << result.y() << std::endl
                                                         << "z: " << result.z() << std::endl;
    return 0;
}

auto 
Intersect(const Segment3D& s1, const Segment3D& s2) -> Vector3D {

    decltype(auto) result = intersection_checker(s1, s2);
    if (result.status() == ResultStatus::Intersection) return result.value();
    std::cout << result.message() << std::endl;
    return empty_vector;
}