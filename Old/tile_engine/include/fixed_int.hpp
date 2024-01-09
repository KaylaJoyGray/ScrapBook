#ifndef FIXED_INT_H
#define FIXED_INT_H

#include <cstdint>

using int8   = std::int8_t;		// -128 to 127
using uint8  = std::uint8_t;	// 0 to 255

using int16  = std::int16_t;	// -32768 to 32767
using uint16 = std::uint16_t;	// 0 to 65535

using int32	 = std::int32_t;	// -2,147,483,648 to 2,147,483,647
using uint32 = std::uint32_t;	// 0 to 4,294,967,295

using int64  = std::int64_t;	// -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807	
using uint64 = std::uint64_t;	// 0 to 18,446,744,073,709,551,615

#endif
