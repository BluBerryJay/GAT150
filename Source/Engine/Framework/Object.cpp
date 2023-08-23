#include "Object.h"
namespace kiko
{
	CLASS_DEFINITION(Object)
	void Object::Read(const json_t& value)
	{
		READ_DATA(value, name);

	
	}
}