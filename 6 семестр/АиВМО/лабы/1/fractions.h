#ifndef FRACTIONS_H    
#define FRACTIONS_H   

#include <iostream>

class Fraction
{
private:
	long long numerator;
	long long denominator;
public:	
    Fraction():numerator(0),denominator(1){};	
	Fraction(long long num,long long denom):numerator(num),denominator(denom){};
	Fraction(long long num):numerator(num),denominator(1){};
	static long long gcd(long long a,long long b);
	static long long lcm(long long a,long long b);

	long long getNumerator();
	long long getDenominator();
	void setNumerator(long long num);
	void setDenominator(long long denom);



	friend std::istream& operator>>(std::istream& input,Fraction& data);
	friend std::ostream& operator<<(std::ostream& output,Fraction& data);    
	
	Fraction operator+(Fraction other);
	Fraction operator-(Fraction other);
	Fraction operator*(Fraction other);
	Fraction operator/(Fraction other);
	bool operator==(Fraction other);		
	bool operator>(Fraction other);
	operator double(){return ((double)numerator/denominator);};

	static Fraction Abs(Fraction fr); 
};

#endif
