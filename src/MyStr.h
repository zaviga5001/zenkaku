#ifndef MYSTR_H
#define MYSTR_H
#include <sstream>
#include <string>
#include <vector>

namespace mystd
{
	template < typename T > std::string to_string( const T& n )
        {
		std::ostringstream stm ;
		stm << n ;
		return stm.str() ;
	}
} // mystd

class CMyStr
{
public:
	static std::vector< std::string > separate(std::string tmpstr);
	static int length(std::string tmpstr);
	static int capacity(std::string tmpstr);
	static std::string substr(std::string tmpstr, int i);
	static std::string substr(std::string tmpstr, int i, int j);
};
#endif	// MYSTR_H
