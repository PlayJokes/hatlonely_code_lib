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
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


std::string me;
std::string tty;

class PtsUser {
public:
	PtsUser(const std::string &user, const std::string &pts):
		_user(user), _pts(pts) {
		std::string pts_path = "/dev/" + _pts;
		if (_check_user_tty()) {
			_fd = open(pts_path.c_str(), O_WRONLY);
		} else {
			_fd = -1;
		}
	}
	void say(const std::string &line) {
		std::string text = "[" +  _timenow() + " " + me + " " + tty +  "] " + line + "\n";
		write(_fd, text.c_str(), text.length());
	}
	std::string to_string() const {
		std::ostringstream oss;
		oss << _user << "  " << _pts << "  " << _fd;
		return oss.str();
	}
	int compare(const PtsUser &pu) const {
		if (_pts != pu._pts) {
			return strcmp(_pts.c_str(), pu._pts.c_str());
		} else if (_user != pu._user) {
			return strcmp(_user.c_str(), pu._user.c_str());
		}
		return 0;
	}
	std::string get_user() {
		return _user;
	}
	std::string get_pts() {
		return _pts;
	}
	int get_fd() {
		return _fd;
	}
private:
	std::string _timenow() const {
		char strtime[80];
		time_t t;
		time(&t);
		strftime(strtime, sizeof(strtime), "%y-%m-%d %H:%M:%S", localtime(&t));
		return std::string(strtime);
	}
	bool _check_user_tty() {
		struct stat buf;
		if ((stat(("/dev/" + _pts).c_str(), &buf)) != 0 ) {
			std::cout << "can not open" << std::endl;
			return false;
		}
		if (strcmp(getpwuid(buf.st_uid) -> pw_name, _user.c_str()) != 0) {
			std::cout << "wrong name" << std::endl;
			return false;
		}

		return true;
	}

	std::string _user;
	std::string _pts;
	int _fd;
};

inline bool operator < (const PtsUser &pu1, const PtsUser &pu2) {
	return pu1.compare(pu2) < 0;
}

std::string whoami() {
	return std::string(getpwuid(getuid()) -> pw_name);
}
std::string get_tty() {
	std::string tty = std::string(ttyname(STDIN_FILENO));
	return tty.substr(5, tty.length() - 5);
}

int main(int argc, char *argv[]) {
	std::vector<PtsUser> pts_users;
	int user_num = (argc - 1) / 2;

	for (int i = 0; i < user_num; i++) {
		PtsUser pts_user = PtsUser(argv[i * 2 + 1], argv[i * 2 + 2]);
		if (pts_user.get_fd() != -1) {
			pts_users.push_back(pts_user);
		}
	}

	me = whoami();
	tty = get_tty();

	char buf[1024];
	while (std::cin.getline(buf, sizeof(buf))) {
		std::string line = std::string(buf);
		if (line[0] == '@') {
			int first_index_of_space = line.find_first_of(' ');
			int last_index_of_space = line.find_last_of(' ');
			std::string user = line.substr(1, first_index_of_space - 1);
			std::string pts = line.substr(last_index_of_space + 1,
					line.length() - last_index_of_space - 1);
			PtsUser pts_user = PtsUser(user, pts);
			if (pts_user.get_fd() != -1) {
				pts_users.push_back(pts_user);
			}

		} else {
			for (std::vector<PtsUser>::iterator it = pts_users.begin();
					it != pts_users.end(); ++it) {
				it->say(line);
			}
		}
	}

	std::cout << "hello world" << std::endl;

	return 0;
}
