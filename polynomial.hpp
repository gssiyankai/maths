#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <vector>
#include <string>

class Polynomial
{

public:
    Polynomial(const std::string& value);
    Polynomial(unsigned int coeffs);

    bool operator ==(const Polynomial& o) const;
    unsigned int coeffs() const;
    std::string str() const;
    Polynomial derivative() const;
    Polynomial multiply() const;
    std::vector<Polynomial> divide(const Polynomial& divisor) const;

private:
    unsigned int coeffs_;

};

#endif