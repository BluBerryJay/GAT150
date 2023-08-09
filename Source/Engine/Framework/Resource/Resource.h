#pragma once
#include <string>
#include <memory>
namespace kiko
{
	class Resource
	{
	public:
		virtual ~Resource() = default;
	private:
		virtual bool Create(std::string fileName, ...) = 0;


	};
	template<typename T>
	using res_t = std::shared_ptr<T>;
}
