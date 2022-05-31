#ifndef U_UTIL_H
#define U_UTIL_H

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <memory>

namespace SQ
{
    // todo profile to inline
    template<class T> inline void destroy(T*& p) { delete p; p = nullptr; }
    template<class T> inline void destroy(std::shared_ptr<T>& p) { p.reset(); }
    void split(const std::string &s, char delim, std::vector<float> &result);
    void split(const std::string &s, char delim, std::vector<int> &result);
    void split(const std::string &s, char delim, std::vector<std::string> &result);
    std::vector<float> split4(const std::string &s, char delim);
    std::vector<float> split2(const std::string &s, char delim);
}

#endif // U_UTIL_H
