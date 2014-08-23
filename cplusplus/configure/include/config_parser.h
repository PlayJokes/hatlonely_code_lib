#ifndef _HL_CONFIGURE_PARSER_H_
#define _HL_CONFIGURE_PARSER_H_

#include <boost/any.hpp>

namespace hl {

class ConfigParser {
public:
    virtual int parse(
        const std::string path,
        const std::string name,
        boost::any& container) = 0;
    virtual ~ConfigParser() {}
};

}  // hl

#endif
