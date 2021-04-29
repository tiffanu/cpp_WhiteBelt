#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int gcd(int x, int y){
	int c;
	x = abs(x);
	y = abs(y);
	while (y != 0){
		x %= y;
		c = y;
		y = x;
		x = c;
	}
	return x;
}

class Rational {
public:
    Rational() {
    	numerator = 0;
    	denominator = 1;
    }

    Rational(int new_numerator, int new_denominator) {
        int d = gcd(new_numerator, new_denominator);
        numerator = new_numerator / d;
        denominator = new_denominator / d;
        if (denominator < 0){
            numerator *= -1;
            denominator *= -1;
        }
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

private:
    int numerator;
    int denominator;
};

Rational operator +(const Rational& lhs, const Rational& rhs){
    int p = lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator();
    int q = lhs.Denominator() * rhs.Denominator();
    Rational res(p, q);
    return res;
}

Rational operator -(const Rational& lhs, const Rational& rhs){
    int p = lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator();
    int q = lhs.Denominator() * rhs.Denominator();
    Rational res(p, q);
    return res;
}

Rational operator *(const Rational& lhs, const Rational& rhs){
    int p = lhs.Numerator() * rhs.Numerator();
    int q = lhs.Denominator() * rhs.Denominator();
    Rational res(p, q);
    return res;
}

Rational operator /(const Rational& lhs, const Rational& rhs){
    int p = lhs.Numerator() * rhs.Denominator();
    int q = lhs.Denominator() * rhs.Numerator();
    Rational res(p, q);
    return res;
}

bool operator ==(const Rational& lhs, const Rational& rhs){
    return lhs.Denominator() == rhs.Denominator() && lhs.Numerator() == rhs.Numerator();
}

bool operator <(const Rational& lhs, const Rational& rhs){
	return lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator();
}

istream& operator >>(istream& stream, Rational& r){
	int new_p, new_q = 0;
	char sep = '.';
	if (stream){
		stream >> new_p;
		stream >> sep;
		stream >> new_q;
	}
	if (new_q != 0 && sep == '/'){
		Rational temp(new_p, new_q);
		r = temp;
	}
    return stream;
}

ostream& operator <<(ostream& stream, const Rational& r){
    stream << r.Numerator() << '/' << r.Denominator();
    return stream;
}
