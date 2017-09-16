
#include "header.h"


// - Reverse Polish Notation
// use XML/JSON serialization to allow client side configuration, e.g. add a new operator
#include <iostream>
#include <string>
#include <stack>
#include <exception>
#include <sstream>
#include <unordered_map>
#include <stdexcept>

using namespace std;

class Token {
public:
    Token() {};
    virtual ~Token() = 0;
    virtual bool isOperator() const = 0;
    virtual void process(stack<double> &stk) const = 0;
};
Token::~Token() {}

class Operand : public Token {
public:
    Operand(const string &str) {
        m_val = stod(str);
    }
    double val() const { return m_val; }
    virtual bool isOperator() const { return false; }
    virtual void process(stack<double> &stk) const { stk.push(m_val); }
private:
    double m_val;
};

class Operator : public Token {
public:
    Operator(const string &type) {
        m_type = type;
    }
    const string & type() const { return m_type; }
    virtual ~Operator() = 0;
    virtual bool isOperator() const { return true; }
private:
    string m_type;
};
Operator::~Operator() {}

class Add : public Operator {
public:
    Add() : Operator("+") {}
    virtual void process(stack<double> &stk) const {
        if (stk.empty())
            throw runtime_error("illegal operation on Div: stack underflow.");
        double num2 = stk.top();
        stk.pop();
        if (stk.empty())
            throw runtime_error("illegal operation on Div: stack underflow.");
        double num1 = stk.top();
        stk.pop();
        stk.push(num1 + num2);
    }
};

class Sub : public Operator {
public:
    Sub() : Operator("-") {}
    virtual void process(stack<double> &stk) const {
        if (stk.empty())
            throw runtime_error("illegal operation on Div: stack underflow.");
        double num2 = stk.top();
        stk.pop();
        if (stk.empty())
            throw runtime_error("illegal operation on Div: stack underflow.");
        double num1 = stk.top();
        stk.pop();
        stk.push(num1 - num2);
    }
};

class Mul : public Operator {
public:
    Mul() : Operator("+") {}
    virtual void process(stack<double> &stk) const {
        if (stk.empty())
            throw runtime_error("illegal operation on Div: stack underflow.");
        double num2 = stk.top();
        stk.pop();
        if (stk.empty())
            throw runtime_error("illegal operation on Div: stack underflow.");
        double num1 = stk.top();
        stk.pop();
        stk.push(num1 * num2);
    }
};

class Div : public Operator {
public:
    Div() : Operator("+") {}
    virtual void process(stack<double> &stk) const {
        if (stk.empty())
            throw runtime_error("illegal operation on Div: stack underflow.");
        double num2 = stk.top();
        stk.pop();
        if (stk.empty())
            throw runtime_error("illegal operation on Div: stack underflow.");
        double num1 = stk.top();
        stk.pop();
        stk.push(num1 / num2);
    }
};

class TokenFactory {
public:
    TokenFactory() {
        operators["+"] = new Add();
        operators["-"] = new Sub();
        operators["*"] = new Mul();
        operators["/"] = new Div();
    }

    Token * create(const string &param) {
        if (operators.find(param) != operators.end())
            return operators[param];
        else
            return new Operand(param);
    }

private:
    unordered_map<string, Operator *> operators;
};

class RPNCalculator {
public:
    double calculate(const vector<string> &formula) {
        try {
            for (int i = 0; i < formula.size(); ++ i) {
                m_factory.create(formula[i])->process(m_stk);
            }
        } catch(const exception &e) {
            cout << e.what() << endl;
            return -1;
        }

        double result = m_stk.top();
        m_stk.pop();
        if (!m_stk.empty()) {
            cout << "invalid formula. " << endl;
            return -1;
        }

        return result;
    }
private:
    TokenFactory m_factory;
    stack<double> m_stk;
};

int run_RPN() {
    vector<string> f = {"4", "5", "13", "/", "+"};
    RPNCalculator c;
    cout << c.calculate(f) << endl;

    return 0;
}
