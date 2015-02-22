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
                    std::vector<T> , std::vector<T> > > split(const std::vector<T>& a,
                                                              std::vector<T> a1, std::vector<T> a2,
                                                              unsigned int n_begin, unsigned int n_end,
                                                              unsigned int iter, unsigned int size);

};

template <typename T>
std::vector<
        std::pair< std::vector<T>, std::vector<T> > > Utils::split(const std::vector<T>& a)
{
    std::vector< std::pair< std::vector<T>, std::vector<T> > > r;
    for(int i = 1; i <= a.size()/2; ++i)
    {
        const std::vector< std::pair< std::vector<T>, std::vector<T> > >&  ri = split(a,
                                                                                      std::vector<T>(), std::vector<T>(),
                                                                                      0, a.size(), 0, i);
        r.insert(r.end(), ri.begin(), ri.end());
    }
    return r;
}

template <typename T>
std::vector<
        std::pair<
                std::vector<T> , std::vector<T> > > Utils::split(const std::vector<T>& a,
                                                                 std::vector<T> a1, std::vector<T> a2,
                                                                 unsigned int n_begin, unsigned int n_end,
                                                                 unsigned int iter, unsigned int size)
{
    std::vector< std::pair< std::vector<T>, std::vector<T> > > r;
    return r;
}

#endif
