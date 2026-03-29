#pragma once
#include <string>


class Shader
{
public:
	Shader(const std::string& path);
	void Use() const;
	bool IsLoaded() const;
	int GetUniformLocation(const std::string& name) const;
private:
	unsigned int ID{};
	static unsigned int load(const std::string& path, unsigned int type);
};