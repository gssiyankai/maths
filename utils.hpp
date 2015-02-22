#ifndef UTILS
#define UTILS

#include <vector>

class Utils
{

public:
    template <typename T>
        static std::vector<
            std::pair<
                    std::vector<T> , std::vector<T> > > split(const std::vector<T>& a);

private:
    template <typename T>
        static std::vector<
            std::pair<
                    std::vector<T> , std::vector<T> > > split(const std::vector<T>& a, std::vector<T> a1, std::vector<T> a2,
                                                              unsigned int n, unsigned int a1_max_size);

};

template <typename T>
std::vector<
        std::pair< std::vector<T>, std::vector<T> > > Utils::split(const std::vector<T>& a)
{
    std::vector< std::pair< std::vector<T>, std::vector<T> > > r;
    for(unsigned int i = 1; i <= a.size()/2; ++i)
    {
        const std::vector< std::pair< std::vector<T>, std::vector<T> > >&  ri = split(a, std::vector<T>(), std::vector<T>(), 0, i);
        r.insert(r.end(), ri.begin(), ri.end());
    }
    return r;
}

template <typename T>
std::vector<
        std::pair<
                std::vector<T> , std::vector<T> > > Utils::split(const std::vector<T>& a,  std::vector<T> a1, std::vector<T> a2,
                                                                 unsigned int n, unsigned int a1_max_size)
{
    std::vector< std::pair< std::vector<T>, std::vector<T> > > r;
    if(a1.size() < a1_max_size)
    {
        for(unsigned int i = n; i < a.size(); ++i)
        {
            std::vector<T> a1i(a1);
            a1i.push_back(a[i]);
            std::vector<T> a2i(a2);
            for(int j = n; j < i; ++j)
            {
                a2i.push_back(a[j]);
            }
            const std::vector< std::pair< std::vector<T>, std::vector<T> > >& ri = split(a, a1i, a2i, i+1, a1_max_size);
            r.insert(r.end(), ri.begin(), ri.end());
        }
    }
    else
    {
        for(int i = n; i < a.size(); ++i)
        {
            a2.push_back(a[i]);
        }
        r.push_back(make_pair(a1, a2));
    }
    return r;
}

#endif
