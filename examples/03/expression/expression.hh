#ifndef EXPRESSION__HH
#define EXPRESSION__HH

// A simple but stupid way to define an expression
class Expression
{
public:
    Expression(char oper, int left_val, int right_val);
    Expression(char oper, Expression* left_expr, Expression* right_expr);
    int evaluate() const;

private:
    void set_oper(char ch);
    int left_value_;
    int right_value_;
    char oper_;
    Expression* left_sub_expression_;
    Expression* right_sub_expression_;
};

#endif
