#pragma once
#include <string>


class Texture
{
public:
	Texture(const std::string& path);
	void Bind(unsigned short pos) const;
	bool IsLoaded() const;
private:
	unsigned int ID{};
	static unsigned int load(const std::string& path);
};