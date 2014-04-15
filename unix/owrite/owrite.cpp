// @file owrite.cpp
// @desc linux command write support Chinese
// @auth hatlonely (hatlonely@gmail.com)
// @date 2014-4-16


#include <fcntl.h>
#include <string.h>

#include <iostream>
#include <set>
#include <string>
#include <sstream>

class PtsUser {
public:
	PtsUser(const std::string &user, const std::string &pts):
		_user(user), _pts(pts) {
		std::string pts_path = "/dev/" + pts;
		_fd = open(pts_path.c_str(), O_WRONLY);
	}
	std::string to_string() const {
		std::ostringstream oss;
		oss << _user << "  " << _pts << "  " << _fd;
		return oss.str();
	}
	bool operator < (const PtsUser &pu) {
		return _user < pu._user;
		if (_fd != pu._fd) {
			return _fd < pu._fd;
		} else if (_pts != pu._pts) {
			return _pts < pu._pts;
		} else if (_user != pu._user) {
			return _user < pu._user;
		}
		return false;
	}
private:
	std::string _user;
	std::string _pts;
	int _fd;
};

inline bool operator < (const PtsUser &pu1, const PtsUser &pu2) {
	return pu1 < pu2;
}

int main(int argc, char *argv[]) {
	std::set<PtsUser> pts_users;
	int user_num = (argc - 1) / 2;

	std::cout << user_num << std::endl;

	for (int i = 0; i < user_num; i++) {
		/* pts_users.insert(PtsUser(argv[i * 2 + 1], argv[i * 2 + 2])); */
		pts_users.insert(PtsUser("aa", "bb"));
		std::cout << (PtsUser("aa", "bb") < PtsUser("cc", "dd")) << std::endl;
		std::cout << (PtsUser("xx", "yy") < PtsUser("cc", "dd")) << std::endl;
		std::cout << ("xx" < "yy") << std::endl;
		std::cout << ("yy" < "xx") << std::endl;
		std::cout << (strcmp("xx", "yy")) << std::endl;
		std::cout << (strcmp("yy", "xx")) << std::endl;
	}

	for (std::set<PtsUser>::iterator it = pts_users.begin();
			it != pts_users.end(); ++it) {
		std::cout << it->to_string() << std::endl;
	}
	std::cout << "hello world" << std::endl;
	return 0;
}

