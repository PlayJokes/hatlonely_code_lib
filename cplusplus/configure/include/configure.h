#ifndef _HL_CONFIGURE_H_
#define _HL_CONFIGURE_H_

#include <string>
#include <vector>
#include <iterator>
#include <boost/any.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

namespace hl
{

class Configure {
typedef std::map<std::string, boost::any> MapStrAny;
typedef std::vector<boost::any> VectorAny;

public:
    Configure();
    int load(const std::string& path, 
            const std::string& name, 
            const std::string& type);

    template <typename T> int Configure::get(std::string key_path, T &value)
    {
        static boost::regex vec_reg("([a-zA-Z_]+[a-zA-Z0-9_]*)\\[([0-9]+)\\]");
        static boost::regex map_reg("([a-zA-Z_]+[a-zA-Z0-9_]*)");

        std::vector<std::string> keys;
        boost::split(keys, key_path, boost::is_any_of("."));
    
        boost::any anything = _data;

        for (std::vector<std::string>::iterator it = keys.begin();
                it != keys.end(); ++it) {
            boost::smatch m;
            if (boost::regex_match(*it, m, vec_reg)) {
                std::string key(m[1].first, m[1].second);
                std::string idx(m[2].first, m[2].second);
                uint32_t index = boost::lexical_cast<uint32_t>(idx);

                if (typeid(MapStrAny) != anything.type()) {
                    return -1;
                }
                anything = boost::any_cast<MapStrAny>(anything)[key];

                if (typeid(VectorAny) != anything.type()) {
                    return -1;
                }
                if (boost::any_cast<VectorAny>(anything).size() <= index) {
                    return -1;
                }
                anything = boost::any_cast<VectorAny>(anything)[index];
            } else if (boost::regex_match(*it, m, map_reg)) {
                if (typeid(MapStrAny) != anything.type()) {
                    return -1;
                }
                anything = boost::any_cast<MapStrAny>(anything)[*it];
            } else {
                return -1;
            }
        }

        if (typeid(std::string) != anything.type()) {
            return -1;
        }

        std::string str_val = boost::any_cast<std::string>(anything);
        value = boost::lexical_cast<T>(str_val);
        
        return 0;
    }

private:
    std::string _path;
    std::string _name;

    boost::any _data;
};

}

#endif // _HL_CONFIGURE_H_
