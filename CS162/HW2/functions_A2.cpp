
#include "functions_A2.h"



using namespace std;


/*********************************************************************
** Function: getNum() , getDen() , setNum() , setDen()

** Description:

	These functions are the standard setters and getters
				
	for the numerator and denominator of a rational number.
				
	They are needed because num and den are private member 
				
	variables in the class 'RationalNumber'.
				

** Parameters: void   ,   void   ,    int n   , int d 
*********************************************************************/ 



int RationalNumber::getNum()
{
	return num;
	
}

int RationalNumber::getDen()
{
	return den;
	
}

void RationalNumber::setNum(int n)
{
	num = n;
	
}
void RationalNumber::setDen(int d)
{
	den = d;
	
}


/*********************************************************************
** Function: operator<<

** Description:
	
	This is the overloaded output stream operator for the class RationalNumber.
	
	This makes it easy to print an object that is a RationalNumber without having
	
	to write  "cout << numerator << " / " << denominator " every time. 
	
				

** Parameters: 

ostream& out (cout only used for this program)

RationalNumber q (the rational number object you want to print)
		

*********************************************************************/

ostream& operator<<(ostream& out , RationalNumber & q)
   {
   //modify << so you don't have to specify printing the numerator and denominator
   
   out << q.getNum()<<" / "<< q.getDen();
   
   
   return out;
   
   }
   
   
/*********************************************************************
** Function: operator>>

** Description:
	
	This is the overloaded input stream operator for the class RationalNumber.
	
	Using this allows us to input in the numerator and denominator
	
	of the rational number object as a whole.
	
	Example:
	
	cin >>  q ;
	
	this statement would prompt the user for 3 entries 
	
	cin >> numerator >> slash >> denominator ;
	
				

** Parameters: 

istream& is (cin only used for this program)

RationalNumber q (the rational number object you want to input)
		

*********************************************************************/ 
   
   
   
   
istream& operator>>(istream& is, RationalNumber & q)
{
 int a, b;
 
 char slash; 
 
 
 is >> a >> slash >> b; 
 
 q.setNum(a);
 q.setDen(b);
 
 
 if (slash == '/' && is) {
	 
	q.reduce();
 
	return is; // success
 
 }
 

 return is;
}

/*********************************************************************
** Function: operator*

** Description:
	
	This is the overloaded multiplication operator for the class RationalNumber.
	
	Overloading this operator solves the problem of multiplying two rational numbers.
	
	When the operation is complete the reduce function is called to return the reduced 
	
	result.

	Example: Input of RationalNumber objects  q and r
	
			q * r  =   (num_q * num_r) / (den_q * den_r)
	
				

** Parameters: 

RationalNumber leftOp (left hand operand)

RationalNumber rightOp (right hand operand) 
		

*********************************************************************/ 

RationalNumber operator*(RationalNumber & leftOp, RationalNumber & rightOp)
   {
   RationalNumber result = leftOp;  
   
   // Declare a temporary object to hold the result and
   // set it equal to the left operand

   // Multiply the numerators and denominators of the two rational numbers,
   // storing the result in result

   result.setNum(result.getNum() * rightOp.getNum());
   
   result.setDen(result.getDen() * rightOp.getDen());

   // Reduce the result to lowest terms:

   // First, find the greatest common divisor for the numerator and 
   // denominator of the result

   result.reduce();
	// reduce the result 
   return result;
   }
   
/********************************************************************************
** Function: operator/

** Description:
	
	This is the overloaded division operator for the class RationalNumber.
	
	Overloading this operator solves the problem of dividing two rational numbers.
	
	Dividing rational numbers is the same thing as multiplying by the reciprocal of 
	
	the right operand. When the operation is complete the reduce function is called
	
	to return the reduced result.

	Example: Input of RationalNumber objects  q and r
	
			q / r  =   (num_q * den_r) / (den_q * num_r)
	
				

** Parameters: 

RationalNumber leftOp (left hand operand)

RationalNumber rightOp (right hand operand) 
		

******************************************************************************/ 
   
   
   RationalNumber operator/(RationalNumber & leftOp, RationalNumber & rightOp)
   {
   RationalNumber result = leftOp;  
   
   // Declare a temporary object to hold the result and
   // set it equal to the left operand

   // division is multiplying by the reciprocal, so multiply the
   //numerator of the left op with the denominator of the right op etc.

   result.setNum(result.getNum() * rightOp.getDen());
   
   result.setDen(result.getDen() * rightOp.getNum());

   // Reduce the result to lowest terms:

   // First, find the greatest common divisor for the numerator and 
   // denominator of the result

   result.reduce();
   
	// reduce the result 
   return result;
   }
   
/********************************************************************************
** Function: operator+

** Description:
	
	This is the overloaded addition operator for the class RationalNumber.
	
	Overloading this operator solves the problem of adding two rational numbers.
	
	To add two rational numbers you must first get like denominators. The easiest way
		
	to do this is to multiply each rational number by 1 in the form of the others denominator
	
	divided by itself. Then the addition is just the two numerators added without changing
	
	the denominator. When the operation is complete the reduce function is called
	
	to return the reduced result.
	
	

	Example: Input of RationalNumber objects  q and r
	
			q + r  =  (num_q * den_r  +  num_r * den_q) / (den_q * den _r)
			
			

** Parameters: 

RationalNumber leftOp (left hand operand)

RationalNumber rightOp (right hand operand) 
		

******************************************************************************/ 
   

   
   RationalNumber operator+(RationalNumber & leftOp, RationalNumber & rightOp)
   {
   RationalNumber result = leftOp;  
   
   // Declare a temporary object to hold the result and
   // set it equal to the left operand

  //get common denominators, easiest way to do this is to multiply the rational numbers
  //by the others denominator / denominator
  
  //formula :   a / b + c / d  =  (a*d + c*b) / b*d
  
	
	
   result.setNum(result.getNum() * rightOp.getDen()  +  rightOp.getNum() * result.getDen() );  //a*d +c*b
   
   result.setDen(result.getDen() * rightOp.getDen()); // b*d

   
   
   result.reduce();
	//reduce the result 
   return result;
   }
   
   /********************************************************************************
** Function: operator-

** Description:
	
	This is the overloaded subtraction operator for the class RationalNumber.
	
	Overloading this operator solves the problem of subtracting two rational numbers.
	
	To subtract two rational numbers you must first get like denominators. The easiest way
		
	to do this is to multiply each rational number by 1 in the form of the others denominator
	
	divided by itself. Then the subtraction is just the two numerators added without changing
	
	the denominator. When the operation is complete the reduce function is called
	
	to return the reduced result.
	
	

	Example: Input of RationalNumber objects  q and r
	
			q + r  =  (num_q * den_r  -  num_r * den_q) / (den_q * den _r)
			
			

** Parameters: 

RationalNumber leftOp (left hand operand)

RationalNumber rightOp (right hand operand) 
		

******************************************************************************/
   
    RationalNumber operator-(RationalNumber & leftOp, RationalNumber & rightOp)
   {
	   
   RationalNumber result = leftOp;  
   
   // Declare a temporary object to hold the result and
   // set it equal to the left operand

  //get common denominators, easiest way to do this is to multiply the rational numbers
  //by the others denominator / denominator
  
  //formula :   a / b + c / d  =  (a*d - c*b) / b*d
  
	
	
   result.setNum(result.getNum() * rightOp.getDen()  -  rightOp.getNum() * result.getDen() );  //a*d - c*b
   
   result.setDen(result.getDen() * rightOp.getDen()); // b*d

   
   
   result.reduce(); 	//reduce the result 
   
	
   return result;
   
   }

RationalNumber::RationalNumber()
{
	num = 1;
	den = 1;
	
}

RationalNumber::RationalNumber(int x, int y)
{
	num = x;
	
	den = y;
	
	NumNeg();
	
}

void RationalNumber::NumNeg()
{
	if ((num > 0) && (den < 0))
	{
		
		num = -num;
		den = -den;
		
		
		
	}
	
}

 /********************************************************************************
** Function: reduce 

	Member of RationalNumber class

** Description:

	This function finds the gcf of the numerator and denominator of a rational 
	
	number and reduces the fraction with it. The algorithm for the gcf is in a while
	
	loop as is three lines long. The gcf is found when the effective denominator 
	
	divided by the effective numerator has a remainder of zero. This means the numbers
	
	go into each other. The algorithm starts by dividing the two numbers together then
	
	goes down from there.
	

** Parameters: void


******************************************************************************/

void RationalNumber::reduce()
{
	int a, b, c, gcf;
	
	a = num;
	b = den;
	
	while (a != 0)
	{
		c = a;				//store numerator as c
		
		/* take b mod a  (initially denominator mod numerator) 
		* if this results to be zero then the previous value of a*d
		* that was stored in c is the greatest common factor. This while
		* loop will run for all the values in between a and b until a 
		* reaches 0.
		*/
		
		a = b % a;	
		
		b = c;
		
	}
	
	gcf = b;
	
	num = num / gcf;		// divide both by the newly found gcf
	den = den / gcf;
	
	NumNeg();				// make sure to put neg in numerator to appear proper
	
}

/********************************************************************************
** Function: ExpressionCalc

** Description:

	This function takes in 3 inputs. 2 objects that are rational numbers and
	
	the operator as a character. Once these three are stored as variables we 
	
	need to translate the character into the particular mathematical expression
	
	it corresponds to. This is done by the switch.

	
	

** Parameters: void


******************************************************************************/




void ExpressionCalc(char &op, RationalNumber &q, RationalNumber &r)
{
	
	int n;
	RationalNumber p(1,1);
	
	cout<<"\nEnter Arithmetic Expression in the form:  a / b  (+ - * /)  c / d\n";
	cin>> q >> op >> r;
	
	
	
	
	if (op == '+')
		n = 1;
	
	else if (op == '-')
		n = 2;
	
	else if (op == '*')
		n = 3;
	
	else if (op == '/')
		n = 4;
	
	
	switch(n)
	{
		
		case 1: p = q + r; break;
		
		case 2: p = q - r; break;
		
		case 3: p = q * r; break;
		
		case 4: p = q / r; break;
		
		
		default: break;
	
	}
	
	cout<<p<<endl;
	
	
}

void TestRational()
{
	RationalNumber test(1,1);
	
	cout<<"Testing RationalNumber Class"<<endl;
	
	cout<<"Rational Number:  a / b\n\nEnter in integers for a and b\n";
	cin>>test;
	
	cout<<test;
	
	
}
