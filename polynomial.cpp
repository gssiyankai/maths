#include "polynomial.hpp"
#include <iomanip>
#include <sstream>

using namespace std;


Polynomial::Polynomial(const std::string& value) : coeffs_(0)
{
    stringstream stream;
    stream << hex << value;
    stream >> coeffs_;
}

Polynomial::Polynomial(unsigned int coeffs) : coeffs_(coeffs)
{
}

bool Polynomial::operator==(const Polynomial &o) const
{
    return coeffs_ == o.coeffs_;
}

unsigned int Polynomial::coeffs() const
{
    return coeffs_;
}

string Polynomial::str() const
{
    stringstream stream;
    stream << hex << coeffs_;
    return stream.str();
}

Polynomial Polynomial::derivative() const
{
    return Polynomial(coeffs_ >> 1);
}
