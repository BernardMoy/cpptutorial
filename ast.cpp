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
    std::cout << std::to_string(Real) << "+" << std::to_string(Imaginary) << "i" << std::endl;
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
    virtual Complex evaluate() {
      return Complex();
    }
};

class NumAST : public ExprAST {
  double Val;

public:
  NumAST(double val) : Val(val) {}
  virtual Complex evaluate(){
    return Complex(Val, 0);
  }
};

// global symbol table for constants
std::map<std::string, Complex> constants;

void initialiseConstantsMap(){
  constants["a"] = Complex(1,3);
  constants["b"] = Complex(-2,4);
  constants["c"] = Complex(5,-6);
};

class ConstAST : public ExprAST {
  std::string E;

  public:
    ConstAST(std::string e) : E(e) {}
    virtual Complex evaluate(){
      return constants[E];
    }
};

class ImaginaryAST : public ExprAST {
  double imagPart;

  public:
    ImaginaryAST(double imagPart) : imagPart(imagPart) {}
    virtual Complex evaluate(){
      return Complex(0, imagPart);
    }
};

class AddAST : public ExprAST {
  std::unique_ptr<ExprAST> Left;
  std::unique_ptr<ExprAST> Right;

  public:
    AddAST(std::unique_ptr<ExprAST> l, std::unique_ptr<ExprAST> r) : Left(std::move(l)), Right(std::move(r)) {
    }
    virtual Complex evaluate() override {
      Complex leftResult = Left -> evaluate();
      Complex rightResult = Right -> evaluate();

      return addComplex(leftResult, rightResult);
    }
};

class SubAST : public ExprAST {
  std::unique_ptr<ExprAST> Left;
  std::unique_ptr<ExprAST> Right;

  public:
    SubAST(std::unique_ptr<ExprAST> l, std::unique_ptr<ExprAST> r) : Left(std::move(l)), Right(std::move(r)) {
    }
    virtual Complex evaluate() override {
      Complex leftResult = Left -> evaluate();
      Complex rightResult = Right -> evaluate();

      return addComplex(leftResult, negComplex(rightResult));
    }
};

class MultiAddAST : public ExprAST {
  std::vector<std::unique_ptr<ExprAST>> Exprs;

  public:
    MultiAddAST(std::vector<std::unique_ptr<ExprAST>> exprs) : Exprs(std::move(exprs)) {
    }

    virtual Complex evaluate() override {
      Complex result = Exprs[0] -> evaluate();
      
      // iterate the vector
      for (int i = 1 ; i < Exprs.size(); i++){
        Complex temp = Exprs[i] -> evaluate();
        result = addComplex(result, temp);
      }
      
      return result;
    }
};


std::unique_ptr<ExprAST> exampleTree() {
  std::unique_ptr<ExprAST> fourMinusThree =
    std::make_unique<SubAST>(std::make_unique<ImaginaryAST>(4), std::make_unique<NumAST>(3));
  
  std::unique_ptr<ExprAST> threeMinusTwo = 
    std::make_unique<SubAST>(std::make_unique<NumAST>(3), std::make_unique<NumAST> (2));

  std::unique_ptr<ExprAST> onePlus = 
    std::make_unique<AddAST>(std::make_unique<NumAST>(1), std::move(fourMinusThree));

  std::unique_ptr<ExprAST> result =
    std::make_unique<AddAST>(std::move(threeMinusTwo), std::move(onePlus));
  
  return result;
};



std::unique_ptr<ExprAST> constantsSum() {
  std::vector<std::unique_ptr<ExprAST>> consts;
  consts.push_back(std::make_unique<ConstAST>("a"));
  consts.push_back(std::make_unique<ConstAST>("b"));
  consts.push_back(std::make_unique<ConstAST>("c"));
  return std::make_unique<MultiAddAST>(std::move(consts));
}


int main() {
  std::cout << "Hello World" << std::endl;

  // load and evaluate the hardcoded example tree
  std::unique_ptr<ExprAST> example = exampleTree();
  Complex result = example -> evaluate();
  result.printComplex();   // Expected -1 + 4i

  // print results of constantsSum()
  initialiseConstantsMap();  // initialise the constant map first
  std::unique_ptr<ExprAST> example2 = constantsSum();  // get Complex object of constant sum with given method
  Complex result2 = example2 -> evaluate();
  result2.printComplex();   // Expected 4 + 1i
}
