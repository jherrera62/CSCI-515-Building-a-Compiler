//File: Expression.h
#ifndef EXPRESSION_H
#define EXPRESSION_H
//#include "Scope_manager.h"
#include "types_and_ops.h"
class Constant;
class Expression {
  public:
    Expression():evaluated_constant(nullptr) {}
    virtual const Constant* evaluate() const=0;
    virtual GPL::Type type() const=0;
    virtual ~Expression();
    Expression(const Expression&) = delete;
    Expression& operator=(const Expression&) = delete;
  protected:
    //a wrapper around returned constants
    const Constant* ret(const Constant* new_evald_constant) const;
  private:
    //pointer to evaluate()'s created constant so it can be released
    mutable const Constant* evaluated_constant;
};

class Binary_operator : public Expression {
  public:
    Binary_operator(const Expression* lhs, const Expression* rhs) :lhs(lhs), rhs(rhs) {}
    virtual const Constant* evaluate() const=0;
    virtual ~Binary_operator() { delete lhs; delete rhs; }
  protected:
    const Expression* lhs;
    const Expression* rhs;
};

class Unary_operator : public Expression
{
  public:
    Unary_operator(const Expression* rhs) :rhs(rhs) {}
    virtual const Constant* evaluate() const=0;
    virtual ~Unary_operator() { delete rhs; }
  protected:
    const Expression* rhs;	
};

class Plus : public Binary_operator {
  public:
    Plus(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Multiply : public Binary_operator {
  public:
    Multiply(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Minus : public Binary_operator {
  public:
    Minus(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Mod : public Binary_operator {
  public:
    Mod(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Divide : public Binary_operator {
  public:
    Divide(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Or : public Binary_operator {
  public:
    Or(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class And : public Binary_operator {
  public:
    And(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Less_equal : public Binary_operator {
  public:
    Less_equal(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Greater_equal : public Binary_operator {
  public:
    Greater_equal(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Less_than : public Binary_operator {
  public:
    Less_than(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Greater_than : public Binary_operator {
  public:
    Greater_than(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Equal : public Binary_operator {
  public:
    Equal(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Not_equal : public Binary_operator {
  public:
    Not_equal(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Tminus : public Unary_operator {
  public:
    Tminus(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Tnot : public Unary_operator {
  public:
    Tnot(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Tsin : public Unary_operator {
  public:
    Tsin(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Tcos : public Unary_operator {
  public:
    Tcos(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Ttan : public Unary_operator {
  public:
    Ttan(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Tasin : public Unary_operator {
  public:
    Tasin(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Tacos : public Unary_operator {
  public:
    Tacos(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Tatan : public Unary_operator {
  public:
    Tatan(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Tsqrt : public Unary_operator {
  public:
    Tsqrt(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Tabs : public Unary_operator {
  public:
    Tabs(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Tfloor : public Unary_operator {
  public:
    Tfloor(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Trandom : public Unary_operator {
  public:
    Trandom(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Near : public Binary_operator
{
  public:
    Near(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
class Touches : public Binary_operator
{
  public:
    Touches(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs,rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
#endif
