// @file mysql_manager.cpp
// @desc
// @auth hatlonely(hatlonely@gmail.com)
// @date 2014-07-15


#include "mysql_manager.h"

namespace hl {

void mmlog(int level, const char *fmt, ...) {
    static const uint32_t MAX_MESSAGE_LEN = 1024;

    char message[MAX_MESSAGE_LEN];
    va_list parglist;
    va_start(parglist, fmt);
    vsprintf(message, fmt, parglist);
    va_end(parglist);

    switch (level) {
    case 0:
        std::cout << "[FATAL] " << message << std::endl;
    case 1:
        std::cout << "[WARNING] " << message << std::endl;
    case 2:
        std::cout << "[NOTICE] " << message << std::endl;
    case 3:
        std::cout << "[TRACE] " << message << std::endl;
    }
}

mysql_conn_t::mysql_conn_t() {
    // nothing to do
}

mysql_conn_t::mysql_conn_t(const mysql_conn_t &mysql_conn) {
    host = mysql_conn.host;
    user = mysql_conn.user;
    passwd = mysql_conn.passwd;
    database = mysql_conn.database;
    port = mysql_conn.port;
}

mysql_conn_t &mysql_conn_t::operator = (const mysql_conn_t &mysql_conn) {
    if (this == &mysql_conn) {
        return *this;
    }
    host = mysql_conn.host;
    user = mysql_conn.user;
    passwd = mysql_conn.passwd;
    database = mysql_conn.database;
    port = mysql_conn.port;

    return *this;
}

MysqlManager::MysqlManager() {
    mysql_init(&_mysql);
}

MysqlManager::~MysqlManager() {

}

int MysqlManager::connect(mysql_conn_t &mysql_conn) {
    _mysql_conn = mysql_conn;
    const char *host = _mysql_conn.host.c_str();
    const char *user = _mysql_conn.user.c_str();
    const char *passwd = _mysql_conn.passwd.c_str();
    const char *database = _mysql_conn.database.c_str();
    const uint32_t port = mysql_conn.port;

    if (mysql_real_connect(&_mysql, host, user, passwd, database, port, NULL, 0) == NULL) {
        _is_connected = false;
        MM_FATAL("connect to %s@%s %s at %u fail. Error: %s", user, host, database, port, mysql_error(&_mysql));
        return MM_CONNECT_FAIL;
    }

    _is_connected = true;
    MM_TRACE("connect to %s@%s %s at %u success", user, host, database, port);
    return MM_SUCCESS;
}

int MysqlManager::insert(const std::string table, const std::string keys, const std::string values) {
    static const int MAX_QUERY_LEN = 1024; 

    char query[MAX_QUERY_LEN];
    snprintf(query, MAX_QUERY_LEN, "INSERT INTO %s (%s) VALUES (%s)", table.c_str(), keys.c_str(), values.c_str());

    if (mysql_query(&_mysql, query)) {
        MM_FATAL("%s fail. Error: %s", query, mysql_error(&_mysql));
        return MM_INSERT_FAIL;
    }

    /* MM_TRACE("%s success.", query); */
    return MM_SUCCESS;
}

int MysqlManager::load(const std::string table, const std::string file) {
    static const int MAX_QUERY_LEN = 1024;

    char query[MAX_QUERY_LEN];
    snprintf(query, MAX_QUERY_LEN, "LOAD DATA INFILE '%s' INTO TABLE %s", file.c_str(), table.c_str());
    if (mysql_query(&_mysql, query)) {
        MM_FATAL("%s fail. Error: %s", query, mysql_error(&_mysql));
        return MM_QUERY_FAIL;
    }

    MM_TRACE("%s success.", query);
    return MM_SUCCESS;
}

int MysqlManager::query(const std::string query) {
    if (mysql_query(&_mysql, query.c_str())) {
        MM_FATAL("%s fail. Error: %s", query.c_str(), mysql_error(&_mysql));
        return MM_QUERY_FAIL;
    }

    MM_TRACE("%s success.", query.c_str());
    return MM_SUCCESS;
}

};  // hl



