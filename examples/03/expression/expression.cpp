#include "expression.hh"
#include <iostream>

using namespace std;

Expression::Expression(char oper, int left_val, int right_val): left_value_(left_val), right_value_(right_val), left_sub_expression_(nullptr), right_sub_expression_(nullptr)
{
    set_oper(oper);
}

Expression::Expression(char oper, Expression* left_expr, Expression* right_expr): left_value_(0), right_value_(0), left_sub_expression_(left_expr), right_sub_expression_(right_expr)
{
    set_oper(oper);
}

void Expression::set_oper(char ch)
{
    if(ch == '*' or ch == '+') {
        oper_ = ch;
    } else {
        std::cout << "Invalid operator: " << ch << endl;
    }
}

int Expression::evaluate() const
{
    int left = 0;
    int right = 0;

    if(left_sub_expression_ != nullptr) {
        left = left_sub_expression_->evaluate();
    } else {
        left = left_value_;
    }

    if(right_sub_expression_ != nullptr) {
        right = right_sub_expression_->evaluate();
    } else {
        right = right_value_;
    }

    if(oper_ == '*') {
        return left * right;
    } else {
        return left + right;
    }
}
