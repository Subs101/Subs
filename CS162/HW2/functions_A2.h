/********************************************************************************************************
** Program Filename:  A2.cpp

** Author: Subhei Shaar

** Date: 2/4/2015

** Description: This program creates a class for rational numbers. Rational numbers are defined as (a / b)
				where a and b are integer values and b is not zero. Here are all the things you need to know 
				about the class:
				
				- 2 private member vars
				
					- numerator , denominator
					
				- 6 overloaded operators as friend functions
				
					- >>, <<, + , - , / , *
					
				- 6 public member functions
				
					-Numneg() Transforms rational number to have negative in numerator only
					-reduce() Reduces a rational number by the GCF
					-setters and getters for num and den
				
				
** Input: 
		  1. Rational number of form ( a / b ) ,where a and b are integer values.

		  2. Arithmetic expression in the form  q  (+-/*)  r , where q and r are rational numbers 
		  and (+-/*) are the allowed operators.

** Output: 
			1. printed rational number in its most reduced form to the screen using overloaded << operator.
			
			2. correct reduced rational number output to arithmetic expression using only 2 rational numbers.
			
*********************************************************************************************************/



#ifndef MARKER
#define MARKER



#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace std;




class RationalNumber
{
	private:
	
		int num;
		
		int den;
		
	public:
	
		 RationalNumber (int,int);			//constructor to take in num and den
		 
		 RationalNumber (); 				//constructor with no operands
		
		 friend ostream& operator<<(const ostream&  , const RationalNumber & );
		
		 friend istream& operator>>(const istream& , const RationalNumber &);
		
		 friend RationalNumber operator*(const RationalNumber &, const RationalNumber &);
		
		 friend RationalNumber operator/(const RationalNumber &, const RationalNumber &);
		
		 friend RationalNumber operator+(const RationalNumber &, const RationalNumber &);
		
		 friend RationalNumber operator-(const RationalNumber &, const RationalNumber &);
		
		/* converts numerator to negative if den is negative */
		
		void NumNeg();
		
		/*function that calculates GCF to reduce */
		
		void reduce();	
		
		/* standard setters and getters for numerator and denominator variables*/
		
		void setNum(int n);
		
		void setDen(int d);
		
		int getNum();
		
		int getDen();
	
	
	
	
};




void TestRational();

void ExpressionCalc(char&, RationalNumber& , RationalNumber& );










#endif