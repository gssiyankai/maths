#ifndef UTILS
#define UTILS

#include <vector>

class Utils
{

public:
    template <typename T>
            static std::vector< std::pair<T,T> > combination2(const std::vector<T>& a);

};

template <typename T>
std::vector< std::pair<T,T> > Utils::combination2(const std::vector<T>& a)
{
    std::vector< std::pair<T,T> > r;
    for(int i = 0; i < a.size(); ++i)
    {
        for(int j = i+1; j<a.size(); ++j)
        {
            r.push_back(std::pair<T,T>(a[i], a[j]));
        }
    }
    return r;
}

#endif