#include "Syntax.h"
#include <memory>
#include "GeometricalObject.h"

Sphere::Sphere(double radius) {
    auto a = std::make_unique<int>(5);

    // jesus fucking christ
    // this is sqrt(x^2 + y^2 + z^2) + n
    // todo I need to find a better way, probably with operation overloading?
    range = std::make_unique<Binary>(
            std::make_unique<Sqrt>(
                    std::make_unique<Binary>(
                            std::make_unique<Binary>(
                                    std::make_unique<Var>(X),
                                    std::make_unique<Number>(2.0),
                                    Operator::OP_POW
                            ),
                            std::make_unique<Binary>(
                                    std::make_unique<Binary>(
                                            std::make_unique<Var>(Y),
                                            std::make_unique<Number>(2.0),
                                            Operator::OP_POW),
                                    std::make_unique<Binary>(
                                            std::make_unique<Var>(Z),
                                            std::make_unique<Number>(2.0),
                                            Operator::OP_POW),
                                    Operator::OP_PLUS
                            ),
                            Operator::OP_PLUS
                    )
            ),
            std::make_unique<Number>(radius),
            Operator::OP_PLUS
    );
}
