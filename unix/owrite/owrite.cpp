// @file owrite.cpp
// @desc linux command write support Chinese
// @auth hatlonely (hatlonely@gmail.com)
// @date 2014-4-16


#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/stat.h>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>


class Environment {
public:
    static Environment &getInstance() {
        static Environment *environment;
        if (environment == NULL) {
            environment = new Environment();
        }

        return *environment;
    }
    // 获取当前时间
    std::string timenow() const {
        char strtime[80];
        time_t t;
        time(&t);
        strftime(strtime, sizeof(strtime), "%y-%m-%d %H:%M:%S", localtime(&t));
        return std::string(strtime);
    }
    std::string get_user() {
        return _user;
    }
    std::string get_tty() {
        return _tty;
    }
    std::string get_font_style_highlight() {
        return _font_style_highlight;
    }
    std::string get_font_style_default() {
        return _font_style_default;
    }
    void set_user(const std::string &user) {
        _user = user;
    }
    void set_tty(const std::string &tty) {
        _tty = tty;
    }
    void set_font_style_highlight(const std::string &font_style_highlight) {
        _font_style_highlight = font_style_highlight;
    }
    void set_font_style_default(const std::string &font_style_default) {
        _font_style_default = font_style_default;
    }
private:
    Environment() {
        _user = _user_me();
        _tty = _tty_me();
        _font_style_highlight = "\033[0m";
        _font_style_default = "\033[0m";
    }
    // Environment(const Environment &environment) {}
    // Environment &operator =(const Environment &environment) {}
    std::string _user_me() {
        return std::string(getpwuid(getuid()) -> pw_name);
    }
    std::string _tty_me() {
        std::string tty = std::string(ttyname(STDIN_FILENO));
        return tty.substr(5, tty.length() - 5);
    }

    std::string _user;
    std::string _tty;
    std::string _font_style_highlight;
    std::string _font_style_default;
};

enum FrontColor {
    kBlack = 30,
    kRed = 31,
    kGreen = 32,
    kYellow = 33,
    kBlue = 34,
    kFuchsia = 35,
    kCyan = 36,
    kWhite = 37
};

int string_to_color(std::string color) {
    if (color == "black") {
        return kBlack;
    } else if (color == "red") {
        return kRed;
    } else if (color == "green") {
        return kGreen;
    } else if (color == "yellow") {
        return kYellow;
    } else if (color == "blue") {
        return kBlue;
    } else if (color == "fuchsia") {
        return kFuchsia;
    } else if (color == "cyan") {
        return kCyan;
    } else if (color == "white") {
        return kWhite;
    }

    return kBlack;
}

class UserTty {
public:
    UserTty(const std::string &user, const std::string &tty):
        _user(user), _tty(tty) {
        std::string tty_path = "/dev/" + _tty;
        if (_check_user_tty()) {
            _fd = open(tty_path.c_str(), O_WRONLY);
        } else {
            _fd = -1;
        }
    }
    void say(const std::string &line) {
        std::string text = "["
            + Environment::getInstance().get_user() + " "
            + Environment::getInstance().get_tty() +  "] "
            + Environment::getInstance().get_font_style_highlight()
            + line
            + Environment::getInstance().get_font_style_default() + "\n";
        write(_fd, text.c_str(), text.length());
    }
    std::string to_string() const {
        std::ostringstream oss;
        oss << _user << "  " << _tty << "  " << _fd;
        return oss.str();
    }
    int compare(const UserTty &pu) const {
        if (_tty != pu._tty) {
            return strcmp(_tty.c_str(), pu._tty.c_str());
        } else if (_user != pu._user) {
            return strcmp(_user.c_str(), pu._user.c_str());
        }
        return 0;
    }
    std::string get_user() {
        return _user;
    }
    std::string get_tty() {
        return _tty;
    }
    int get_fd() {
        return _fd;
    }

private:
    // 检查用户和tty是否对应
    bool _check_user_tty() {
        struct stat buf;
        if ((stat(("/dev/" + _tty).c_str(), &buf)) != 0 ) {
            std::cout << "[error]" << "无法打开/dev/" << _tty
                << "，没有权限或不存在" << std::endl;
            return false;
        }
        if (strcmp(getpwuid(buf.st_uid) -> pw_name, _user.c_str()) != 0) {
            std::cout << "[error]" << "/dev/" << _tty
                << "属于用户" << getpwuid(buf.st_uid) -> pw_name
                << "，而不是" << _user << std::endl;
            return false;
        }

        return true;
    }

    std::string _user;
    std::string _tty;
    int _fd;
};

inline bool operator < (const UserTty &pu1, const UserTty &pu2) {
    return pu1.compare(pu2) < 0;
}

void show_help() {
    std::cout << "usage: owrite [user tty [user tty [...]]]" << std::endl;
    std::cout << "\t@add <user> <tty>  添加用户" << std::endl;
    std::cout << "\t@del <user> <tty>  删除用户" << std::endl;
    std::cout << "\t@color <color>     修改字体颜色" << std::endl;
    std::cout << "\t\t black, red, green, yellow, blue, fuchsia, cyan, white" << std::endl;
    std::cout << "\t@list/@ls     列出当前用户" << std::endl;
    std::cout << "\t@name <name>  修改用户名" << std::endl;
    std::cout << "\t@help         显示帮助" << std::endl;
    std::cout << "\t@time         显示和发送时间" << std::endl;
    std::cout << "\t@quit/@exit   退出" << std::endl;
}

int main(int argc, char *argv[]) {
    show_help();
    
    std::vector<UserTty> user_ttys;
    int user_num = (argc - 1) / 2;

    for (int i = 0; i < user_num; i++) {
        UserTty user_tty = UserTty(argv[i * 2 + 1], argv[i * 2 + 2]);
        if (user_tty.get_fd() == -1) {
            std::cout << "连接用户失败 " << user_tty.get_user() << " "
                    << user_tty.get_tty() << std::endl;
        } else {
            user_ttys.push_back(user_tty);
            std::cout << "连接用户成功 " << user_tty.get_user() << " "
                    << user_tty.get_tty() << std::endl;
        }
    }

    char buf[1024];
    while (std::cin.getline(buf, sizeof(buf))) {
        std::string line = std::string(buf);

        // 以@开头当成命令
        if (line[0] == '@') {
            // 添加用户
            if (line.substr(0, 4) == "@add") {
                char cmd[5];
                char user[64];
                char tty[64];
                sscanf(buf, "%s %s %s", cmd, user, tty);

                UserTty user_tty = UserTty(user, tty);
                if (user_tty.get_fd() == -1) {
                    std::cout << "添加用户" << user << " " << tty << "失败" << std::endl;
                }
                user_ttys.push_back(user_tty);
            // 删除用户
            } else if (line.substr(0, 4) == "@del") {
                char cmd[5];
                char user[64];
                char tty[64];
                sscanf(buf, "%s %s %s", cmd, user, tty);

                for (std::vector<UserTty>::iterator it = user_ttys.begin(); 
                    it != user_ttys.end(); ++it) {
                    if (it->get_user() == std::string(user) &&
                        it->get_tty() == std::string(tty)) {
                        user_ttys.erase(it);
                    }
                }
            } else if (line.substr(0, 6) == "@color") {
                char cmd[7];
                char color[20];
                sscanf(buf, "%s %s", cmd, color);
                std::ostringstream oss;

                oss << "\033[" << string_to_color(color) << ";1m";
                Environment::getInstance().set_font_style_highlight(oss.str());
            } else if (line.substr(0, 5) == "@exit" || line.substr(0, 5) == "@quit") {
                return 0;
            } else if (line.substr(0, 5) == "@list" || line.substr(0, 3) == "@ls") {
                for (std::vector<UserTty>::iterator it = user_ttys.begin();
                    it != user_ttys.end(); ++it) {
                    std::cout << it->to_string() << std::endl;
                }
            } else if (line.substr(0, 5) == "@name") {
                char cmd[6];
                char name[128];
                sscanf(buf, "%s %s", cmd, name);

                Environment::getInstance().set_user(name);
            } else if (line.substr(0, 5) == "@time") {
                std::string time = Environment::getInstance().timenow();
                std::cout << time << std::endl;
                for (std::vector<UserTty>::iterator it = user_ttys.begin();
                    it != user_ttys.end(); ++it) {
                    it->say(Environment::getInstance().timenow());
                }
            } else if (line.substr(0, 5) == "@help") {
                show_help();
            } else {
                // nothing to do
            }
        } else {
            for (std::vector<UserTty>::iterator it = user_ttys.begin();
                    it != user_ttys.end(); ++it) {
                it->say(line);
            }
        }
    }

    return 0;
}
