
#include "BigIntUtilities.h"
#include <algorithm>

namespace BigIntUtilities {

	void trimLeadingZeros(std::string& ioString)
	{
		const size_t beginStr = ioString.find_first_not_of("0");
		if (beginStr == std::string::npos)
			ioString = "0";
		else
			ioString = ioString.substr(beginStr);
	}

	void removeWhitespaces(std::string& ioString)
	{
		ioString.erase( std::remove_if(ioString.begin(), ioString.end(), isspace), ioString.end() );
	}

}