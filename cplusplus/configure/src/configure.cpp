// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file configure.cpp
// @desc 配置文件类
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-08-23

#include "configure.h"
#include "config_parser.h"
#include "json_parser.h"

namespace hl {

Configure::Configure()
{
    // nothing to do
}

int Configure::load(const std::string& path,
        const std::string& name,
        const std::string& type)
{
    int retval = 0;
    _path = path;
    _name = name;

    ConfigParser *parser = NULL;
    if (type == "json") {
        parser = new JsonParser();
        retval = parser->parse(path, name, _data);
    } else {
        retval = -1;
    }

    if (parser != NULL) {
        delete parser;
    }

    return retval;
}

}  // hl
