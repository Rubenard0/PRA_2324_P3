#ifndef DICT_H
#define DICT_H

#include <string>
#include <stdexcept>

template <typename V>
class Dict {
public:
    virtual void insert(std::string key, V value) = 0;
    virtual V search(std::string key) = 0;
    virtual V remove(std::string key) = 0;
    virtual int entries() = 0;
    virtual ~Dict() = default;
};

#endif // DICT_H