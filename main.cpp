#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <chrono>
//string array to hold character sets
const std::string chars[] = { "abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "!\"#$%&'()*+,-./:;<=>?@[]^_{|}~", "0123456789" };
//string to hold similar characters (to remove)
const std::string hahayes = "O0l1I5S2Z";

/**
	function to check if a given string reference is an integer
	@param reference to string
  	@return boolean if the string is an integer or not
*/
bool is_int(std::string const& n) noexcept
{
	if (std::isdigit(n[0]) || (n.size() > 1 && (n[0] == '-' || n[0] == '+')))
	{
		for (std::string::size_type i{ 1 }; i < n.size(); ++i)
			if (!std::isdigit(n[i]))
				return false;

		return true;
	}
	return false;
}

/**
	function to generate a password
	@param integer for length
  	@return string with password
*/
std::string generate_password(int len) {
	std::string pw;
	char t;
	for (int x = 0; x < len; x += 4) {
		for (int y = x; y < x + 4 && y < len; y++) {
			do {
				t = chars[y % 4].at(rand() % chars[y % 4].size());
			} while (hahayes.find(t) != hahayes.npos);
			pw.append(1, t);
		}
	}
	std::random_shuffle(pw.begin(), pw.end());
	return pw;
}

int main()
{
	std::cout << "welcome to baumfx' secure password generator." << std::endl;
	std::cout << "please enter the length of your password: ";
	std::string pwlength_string;
	std::getline(std::cin, pwlength_string);
	std::cout << std::endl << "please enter how many passwords to generate: ";
	std::string pwamount_string;
	std::getline(std::cin, pwamount_string);
	
	if (!is_int(pwlength_string) || !is_int(pwamount_string)) { std::cout << "error. entered values are not integers." << std::endl; return 0; }

	int pwamount = std::stoi(pwamount_string);
	int pwlength = std::stoi(pwlength_string);

	//measure execution time of password generation
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	for (int c = 0; c < pwamount; c++) {
		std::cout << "password #" << c + 1 << ": " << generate_password(pwlength) << "\n";
	}

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	std::cout << "successfully generated " << pwamount << " passwords in " << duration << " ms." << std::endl;
}
