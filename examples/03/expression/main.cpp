#include "expression.hh"
#include <iostream>

using namespace std;

int main()
{
    int factor1 = 0;
    int factor2 = 0;

    cout << "Input factors of the first product: ";
    cin >> factor1;
    cin >> factor2;
    Expression expr1('*', factor1, factor2);
    //cout << "First expression evaluates to " << expr1.evaluate() << endl;

    // We can now reuse previous variables factor1 and factor2
    cout << "Input factors of the second product: ";
    cin >> factor1;
    cin >> factor2;
    Expression expr2('*', factor1, factor2);
    //cout << "Second expression evaluates to " << expr2.evaluate() << endl;

    // Third expression consists of the two previous ones
    Expression expr3('+', expr1.evaluate(), expr2.evaluate());
    cout << "Third expression evaluates to " << expr3.evaluate() << endl;

    // An alternative way to form a similar expression as previously
    Expression expr4('+', &expr1, &expr2);
    cout << "Fourth expression evaluates to " << expr4.evaluate() << endl;

    return 0;
}
