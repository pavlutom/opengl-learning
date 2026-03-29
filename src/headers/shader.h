#pragma once
#include <string>


class Shader
{
public:
	Shader(const std::string& path);
	void Use() const;
	bool IsLoaded() const;
	int GetUniformLocation(const std::string& name) const;
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setFloat4(const std::string& name, float x, float y, float z, float w) const;
private:
	unsigned int ID{};
	static unsigned int load(const std::string& path, unsigned int type);
};