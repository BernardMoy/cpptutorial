#include <memory>
#include <vector>
#include <map>
#include <iostream>

/* Don't worry about this class until Task 5. */
class Complex {
  double Real;
  double Imaginary;

public:
  /* There are multiple constructors here, which take different arguments.
  Complex() creates the complex number 0+0i.
  Complex(r,m) creates the complex number r+mi. */
  Complex() : Real(0), Imaginary(0) {};
  Complex(double r, double m) : Real(r), Imaginary(m) {};
  double realPart() { return Real; };
  double imagPart() { return Imaginary; };
  void printComplex() {
    // TODO: TASK 5
  };
};

Complex addComplex(Complex l, Complex r) {
  return Complex(l.realPart() + r.realPart(), l.imagPart() + r.imagPart());
}

Complex negComplex(Complex l) {
  return Complex(-l.realPart(), -l.imagPart());
}

class ExprAST {
public:
    ExprAST() {};
    // TODO: TASK 6
};

class NumAST : public ExprAST {
  double Val;

public:
  NumAST(double val) : Val(val) {}
};

class ConstAST : public ExprAST {
  double E;

  public:
    ConstAST(double e) : E(e) {}
};

class ImaginaryAST : public ExprAST {
  double imagPart;

  public:
    ImaginaryAST(double imagPart) : imagPart(imagPart) {}
};

class AddAST : ExprAST {
  std::unique_ptr<ExprAST> Left;
  std::unique_ptr<ExprAST> Right;

  public:
    AddAST(std::unique_ptr<ExprAST> l, std::unique_ptr<ExprAST> r) : Left(std::move(l)), Right(std::move(r)) {
    }
};

class SubAST : ExprAST {
  std::unique_ptr<ExprAST> Left;
  std::unique_ptr<ExprAST> Right;

  public:
    SubAST(std::unique_ptr<ExprAST> l, std::unique_ptr<ExprAST> r) : Left(std::move(l)), Right(std::move(r)) {
    }
};

class MultiAddAST : ExprAST {
  std::vector<std::unique_ptr<ExprAST>> Exprs;

  public:
    MultiAddAST(std::vector<std::unique_ptr<ExprAST>> exprs) : Exprs(std::move(exprs)) {
    }
};


std::unique_ptr<ExprAST> exampleTree() {
  std::unique_ptr<ExprAST> fourMinusThree =
    std::make_unique<SubAST>(std::make_unique<ImaginaryAST>(4), std::make_unique<NumAST>(3));
  
  std::unique_ptr<ExprAST> threeMinusTwo = 
    std::make_unique<SubAST>(std::make_unique<NumAST>(3), std::make_unique<NumAST> (2));

  std::unique_ptr<ExprAST> oneMinus = 
    std::make_unique<SubAST>(std::make_unique<NumAST>(1), std::move(fourMinusThree));
}


/*
std::unique_ptr<ExprAST> constantsSum() {
  std::vector<std::unique_ptr<ExprAST>> consts;
  consts.push_back(std::make_unique<ConstAST>("a"));
  consts.push_back(std::make_unique<ConstAST>("b"));
  consts.push_back(std::make_unique<ConstAST>("c"));
  return std::make_unique<MultiAddAST>(std::move(consts));
}
*/

int main() {
  std::cout << "Hello World" << std::endl;
  // TODO: TASK 9
  // TODO: TASK 12
}
