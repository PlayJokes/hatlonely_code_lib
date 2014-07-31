// @file mysql_manager.h
// @desc
// @auth hatlonely(hatlonely@gmail.com)
// @date 2014-07-15


#ifndef HL_MYSQL_MANAGER_H
#define HL_MYSQL_MANAGER_H

#include <stdio.h>
#include <stdarg.h>
#include <mysql.h>
#include <iostream>
#include <string>

#define __VERSION_ID__ 1.0


#define MM_LOG(level, fmt, arg...) \
    do { \
        mmlog(level, "[%s:%d][%s]"fmt, __FILE__, __LINE__, __FUNCTION__, ##arg); \
    } while(0)

#define MM_FATAL(fmt, arg...) MM_LOG(0, fmt, ##arg)
#define MM_WARNING(fmt, arg...) MM_LOG(1, fmt, ##arg)
#define MM_NOTICE(fmt, arg...) MM_LOG(2, fmt, ##arg)
#define MM_TRACE(fmt, arg...) MM_LOG(3, fmt, ##arg)

namespace hl {

enum MmErrorType {
    MM_SUCCESS = 0,
    MM_CONNECT_FAIL,
    MM_INSERT_FAIL,
    MM_QUERY_FAIL
};

extern void mmlog(int level, const char *fmt, ...);

struct mysql_conn_t {
    std::string host;
    std::string user;
    std::string passwd;
    std::string database;
    uint32_t port;

    mysql_conn_t();
    mysql_conn_t(const mysql_conn_t &mysql_conn);
    mysql_conn_t &operator = (const mysql_conn_t &mysql_conn);
};

class MysqlManager {
public:
    MysqlManager();
    ~MysqlManager();

    int options(enum mysql_option option, const char *arg);
    int connect(mysql_conn_t &mysql_conn);
    int insert(const std::string table, const std::string keys, const std::string values);
    int load(const std::string table, const std::string file);
    int query(const std::string query);

private:
    MYSQL _mysql;
    mysql_conn_t _mysql_conn;
    bool _is_connected;

    MysqlManager(const MysqlManager &);
    MysqlManager &operator = (const MysqlManager &);
};

};  // hl

#endif  // HL_MYSQL_MANAGER_H
