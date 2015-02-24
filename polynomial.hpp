#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <vector>
#include <string>

class Polynomial
{

public:
    Polynomial(const std::string& value);
    Polynomial(std::vector<int> coeffs);

    bool operator ==(const Polynomial& o) const;
    std::vector<int> coeffs() const;
    std::string str() const;
    unsigned int degree() const;
    Polynomial multiply(const Polynomial& m) const;
    Polynomial gcd(const Polynomial& p) const;
    std::vector<Polynomial> factorize() const;

    static std::vector< std::vector<int> > berlekamp_qmatrix(const std::vector<int>& f);
    static std::vector< std::vector<int> > berlekamp_qbasis(const std::vector< std::vector<int> >& qmatrix);

private:
    static unsigned int degree(const std::vector<int>& n);
    static std::vector<int> multiply(const std::vector<int>& n, const std::vector<int>& m);
    static std::vector<int> gcd(std::vector<int> f, std::vector<int> g);
    static std::vector<int> quotient(const std::vector<int>& f, const std::vector<int>& g);
    static std::vector<int> remainder(const std::vector<int>& f, const std::vector<int>& g);
    static std::vector<int> strip(const std::vector<int>& n);

    static std::vector<int> sub_ground(const std::vector<int>& f, int a);
    static std::vector<Polynomial> polynomials(const std::vector< std::vector<int> >& fs);

    std::vector<int> coeffs_;

};

#endif
