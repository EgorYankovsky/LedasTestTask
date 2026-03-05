#include "pch.h"
#include "Include/Solutions/PointAndLineSolution.h"

auto 
PointAndLineSolution::solve(const Segment3D& s1, const Segment3D& s2) const -> Result<Vector3D> {
    decltype(auto) v1 = s1.get_segmented_vector();
    decltype(auto) v2 = s2.get_segmented_vector();


    // Устанивим, какой именно из сегментов порождает точку.
    Vector3D point;
    Vector3D vector_t0;
    Vector3D vector_coefs;
    
    if (v1.norma() <= _eps) {
        point = s1.start();
        vector_t0 = Vector3D(s2.start().x(),
                           s2.start().y(),
                           s2.start().z());
        vector_coefs = v2;
    }

    if (v2.norma() <= _eps) {
        point = s2.start();
        vector_t0 = Vector3D(s1.start().x(),
                             s1.start().y(),
                             s1.start().z());
        vector_coefs = v1;
    }
	

    Vector3D deltX(point.x() - vector_t0.x(),
                   point.y() - vector_t0.y(),
                   point.z() - vector_t0.z());

    Vector3D alph(vector_coefs.x(), 
                  vector_coefs.y(), 
                  vector_coefs.z());

    // Найдем расстояние между прямой и точкой.
    double dist = sqrt(deltX * deltX - ((deltX * alph) * (deltX * alph)) / (alph * alph));

    if (dist > _eps)
        return Result<Vector3D>::failure(no_intersection_msg, ResultStatus::NoIntersection);

    // Через обратную функцию представления прямой, заданной параметрически, найдем значение t 
    // и проверим находится ли оно в промежутке [0, 1] 
    double t = 0.0;
    if (vector_coefs.x() >= _eps)
        t = (point.x() - vector_t0.x()) / vector_coefs.x();
    else if (vector_coefs.y() >= _eps)
        t = (point.y() - vector_t0.y()) / vector_coefs.y();
    else if (vector_coefs.z() >= _eps)
        t = (point.z() - vector_t0.z()) / vector_coefs.z();

    if (0.0 - _eps <= t && t <= 1.0 + _eps)
        return Result<Vector3D>::success(point, ResultStatus::Intersection);
    return Result<Vector3D>::failure(no_intersection_msg, ResultStatus::NoIntersection);
}