#include "polynomial.hpp"
#include <iomanip>
#include <sstream>

using namespace std;

size_t BASE = 2;

Polynomial::Polynomial(const std::string& value)
{
    stringstream stream;
    stream << hex << value;
    size_t x;
    stream >> x;
    do {
        coeffs_.push_back((int) x % BASE);
        x -= x % 2;
        x /= 2;
    } while(x > 0);
}

Polynomial::Polynomial(const vector<int> &coeffs) : coeffs_(coeffs)
{
}

const std::vector<int>& Polynomial::coeffs() const
{
    return coeffs_;
}

string Polynomial::str() const
{
    size_t result = 0;
    size_t base = 1;
    for(size_t i=0; i<coeffs_.size(); ++i)
    {
        result += coeffs_[i] * base;
        base *= BASE;
    }
    stringstream stream;
    stream << hex << result;
    return stream.str();
}
