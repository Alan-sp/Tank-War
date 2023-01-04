#include <string>

#ifndef BASE64_CPP
#define BASE64_CPP

namespace Base64 {
	char base[64] =
	{ 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
	'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
	'0','1','2','3','4','5','6','7','8','9','+','/' };
	int num[100000];
	std::string encrypt(std::string x) {
		std::string ans;
		int cnt = 0;
		for (int i = 0; i < x.length(); i++) {
			int res = (int)x[i];
			for (int i = 7; i >= 0; i--) {
				if (res >= pow(2, i)) {
					num[++cnt] = 1;
					res -= pow(2, i);
				}
				else {
					num[++cnt] = 0;
				}
			}
		}
		while ((cnt % 6)) {
			num[++cnt] = 0;
		}
		for (int i = 1; i <= cnt; i += 6) {
			int res = 0;
			for (int j = 0; j <= 5; j++) {
				if (num[i + j]) {
					res += pow(2, 5 - j);
				}
			}
			ans += base[res];
		}
		return ans;
	}
	std::string decode(std::string x) {
		std::string ans;
		int cnt = 0;
		for (int i = 0; i < x.length(); i++) {
			int res = 0;
			if (x[i] <= 'Z' && x[i] >= 'A') {
				res = x[i] - 'A';
			}
			if (x[i] <= 'z' && x[i] >= 'a') {
				res = x[i] - 'a' + 26;
			}
			if (x[i] <= '9' && x[i] >= '0') {
				res = x[i] - '0' + 52;
			}
			if (x[i] == '+') {
				res = 62;
			}
			if (x[i] == '/') {
				res = 63;
			}
			for (int j = 5; j >= 0; j--) {
				if (res >= pow(2, j)) {
					res -= pow(2, j);
					num[++cnt] = 1;
				}
				else {
					num[++cnt] = 0;
				}
			}
		}
		for (int i = 1; i <= cnt; i += 8) {
			int res = 0;
			for (int j = 0; j <= 7; j++) {
				if (num[i + j]) {
					res += pow(2, 7 - j);
				}
			}
			ans += (char)res;
		}
		return ans;
	}
}


#endif // !BASE64_CPP


