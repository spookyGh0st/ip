#include "Syntax.h"

class Expr {
public:
    static Expr X;
    static Expr Y;
    static Expr Z;
};

class Number: public Expr{
public:
    double value;
};

class Sqrt: public Expr{
public:
    Expr body ;
    explicit Sqrt(Expr body){ // todo there must be a better way for this
        this->body = body;
    }
};


class Binary{
public:
    Expr x;
    Expr y;
};

class Plus: public Expr, Binary{ };
class Minus: public Expr, Binary{ };
class Multiply: public Expr, Binary{ };
class Divide: public Expr, Binary{ };
class Pow: public Expr, Binary{ };


class GeometricalObject{
    virtual Expr range() = 0;
};

class Sphere: public GeometricalObject{
public:
    double radius;
    Expr range() override{
        return Sqrt()

    }
};
