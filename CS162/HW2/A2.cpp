

#include "functions_A2.h"


using namespace std;


int main()
{
	/* definition of 3 rational numbers set num and den to 1 as a place holder*/
	
	
	RationalNumber q(1,1);
	
	RationalNumber r(1,1);
	
	RationalNumber z(1,1);
	
	char op;

	/* Test RationalNumber Class using two integers for input */
	
	TestRational();
	
	/* Input expression with 2 rational numbers and an operator */
	
	ExpressionCalc(op , q , r );
	
	
	
	
	
	return 0;
}