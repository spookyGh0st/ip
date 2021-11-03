#include <memory>

#ifndef IP_GEOMETICALOBJECT_H
#define IP_GEOMETICALOBJECT_H

// todo namespaces
class GeometricalObject {
public:
    std::unique_ptr<Expr> range;
};

class Sphere : public GeometricalObject {
public:
    explicit Sphere(double radius);
};

#endif //IP_GEOMETICALOBJECT_H
