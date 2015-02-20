#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <vector>
#include <string>

class Polynomial
{

public:
    Polynomial(const std::string& value);
    Polynomial(const std::vector<int>& coeffs);

    bool operator ==(const Polynomial& o) const;
    const std::vector<int>& coeffs() const;
    std::string str() const;
    Polynomial derivative() const;

private:
    std::vector<int> coeffs_;

};

#endif