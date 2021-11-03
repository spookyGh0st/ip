#include "ip/Syntax.hpp"
#include <memory>
#include "ip/GeometricalObject.hpp"

Sphere::Sphere(double radius) {
    auto a = std::make_unique<int>(5);

    // jesus fucking christ
    // this is sqrt(x^2 + y^2 + z^2) + n
    // todo I need to find a better way, probably with operation overloading?
    range = std::make_unique<Plus>(
            std::make_unique<Sqrt>(
                    std::make_unique<Plus>(
                            std::make_unique<Pow>(
                                    std::make_unique<Var>(X),
                                    std::make_unique<Number>(2.0)),
                            std::make_unique<Plus>(
                                    std::make_unique<Pow>(
                                            std::make_unique<Var>(Y),
                                            std::make_unique<Number>(2.0)),
                                    std::make_unique<Pow>(
                                            std::make_unique<Var>(Z),
                                            std::make_unique<Number>(2.0))
                            )
                    )
            ),
            std::make_unique<Number>(radius)
    );
}
