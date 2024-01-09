#ifndef TTW_MODULE_HPP
#define TTW_MODULE_HPP

#include "flecs.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace TTW
{

enum markL {
	X,
	O
};

struct Mark {
	markL letter;
};

struct Pos {
	int r;							//Row
	int c;							//Column
};

struct module {
	module (flecs::world& world);	//Ctor that loads module
};

}

#ifdef __cplusplus
}
#endif

#endif
