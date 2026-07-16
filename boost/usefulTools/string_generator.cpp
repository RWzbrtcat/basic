#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

int main()
{
	boost::uuids::string_generator sgen;
	
	boost::uuids::uuid u1 = sgen("0123456789abcdef0123456789abcdef");
	std::cout << u1 << std::endl;

	boost::uuids::uuid u2 = sgen("01234567-89ab-cdef-0123-456789abcdef");
	std::cout << u2 << std::endl;

	boost::uuids::uuid u3 = sgen(L"{01234567-89ab-cdef-0123-456789abcdef}");
	std::cout << u3 << std::endl;


	return 0;
}
