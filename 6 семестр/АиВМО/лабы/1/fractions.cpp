#include "fractions.h"

long long Fraction::gcd(long long a,long long b)
{
	return b ? gcd(b, a%b) : a;
}

long long Fraction::lcm(long long a,long long b)
{
	return std::abs(a*b)/gcd(a,b); 
}

std::istream& operator>>(std::istream& input,Fraction& data)
{
	std::string str,str1;
	bool check=false;
	long long num=0,denom=1;

	input>>str;
	
	for (unsigned long long i=0;i<str.length();i++)
	{
		if (str[i]=='/')
		{
			str1=str.substr(0,i);
			num=std::stoi(str1);
			str1=str.substr(i+1,str.length()-1-i);
			denom=std::stoi(str1);						
			
			check=true;
			break;
		}
	}
	
	data.setNumerator(num);
	data.setDenominator(denom);

	if (!check)
		data.setNumerator(std::stoi(str));
	
	return input;
}
std::ostream& operator<<(std::ostream& output,Fraction& data)
{
	if (data.getDenominator()==1)
		output<<data.getNumerator();
	else
		output<<data.getNumerator()<<"/"<<data.getDenominator();

	return output;
}

long long Fraction::getNumerator()
{
	return numerator;	
}

long long Fraction::getDenominator()
{
	return denominator;
}

void Fraction::setNumerator(long long num)
{
	numerator = num; 
}

void Fraction::setDenominator(long long denom)
{
	denominator = denom;
}

Fraction Fraction::operator+(Fraction other)
{
	long long g = Fraction::lcm(this->getDenominator(),other.getDenominator());

	Fraction result((g/this->getDenominator())*this->getNumerator()+(g/other.getDenominator())*other.getNumerator(),g);
	
	long long gc = Fraction::gcd(result.getNumerator(),result.getDenominator());

	if (gc<0)
		gc*=-1;

	result.setNumerator(result.getNumerator()/gc);
	result.setDenominator(result.getDenominator()/gc);

	return result;
}

Fraction Fraction::operator-(Fraction other)
{
	long long g = Fraction::lcm(this->getDenominator(),other.getDenominator());

	Fraction result((g/this->getDenominator())*this->getNumerator()-(g/other.getDenominator())*other.getNumerator(),g);
	
	long long gc = Fraction::gcd(result.getNumerator(),result.getDenominator());

	if (gc<0)
		gc*=-1;

	result.setNumerator(result.getNumerator()/gc);
	result.setDenominator(result.getDenominator()/gc);

	return result;
}

Fraction Fraction::operator*(Fraction other)
{
	long long num = this->getNumerator()*other.getNumerator();
	long long denom = this->getDenominator()*other.getDenominator();

	long long g = Fraction::gcd(num,denom);

	Fraction result(num/g,denom/g);

	if (result.getDenominator()<0)
	{
		result.setNumerator(result.getNumerator()*-1);
		result.setDenominator(result.getDenominator()*-1);
	}

	return result;
}

Fraction Fraction::operator/(Fraction other)
{
	long long num = this->getNumerator()*other.getDenominator();
	long long denom = this->getDenominator()*other.getNumerator();

	long long g = Fraction::gcd(num,denom);
	
	Fraction result(num/g,denom/g);

	if (result.getDenominator()<0)
	{
		result.setNumerator(result.getNumerator()*-1);
		result.setDenominator(result.getDenominator()*-1);
	}
		
	return result;
}

bool Fraction::operator==(Fraction other)
{
	if (this->getNumerator()*other.getDenominator()==this->getDenominator()*other.getNumerator())
		return true;

	return false;
}

bool Fraction::operator>(Fraction other)
{
	if (this->getNumerator()*other.getDenominator()>this->getDenominator()*other.getNumerator())
		return true;

	return false;
}

Fraction Fraction::Abs(Fraction fr)
{
	Fraction c =fr;

	if (c.getNumerator()<0)
		c.setNumerator(c.getNumerator()*-1);

	return c;
}




