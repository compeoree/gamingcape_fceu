#include "common.h"

bool directoryExists(const char* dirname)
{
	DWORD res = GetFileAttributes(dirname);
	return res != 0xFFFFFFFF && res & FILE_ATTRIBUTE_DIRECTORY;
}

void WindowBoundsCheckResize(int &windowPosX, int &windowPosY, int windowSizeX, long windowRight)
{
		if (windowRight < 59) {
		windowPosX = 59 - windowSizeX;
		}
		if (windowPosY < -18) {
		windowPosY = -18;
		} 
}

void WindowBoundsCheckNoResize(int &windowPosX, int &windowPosY, long windowRight)
{
		if (windowRight < 59) {
		windowPosX = 0;
		}
		if (windowPosY < -18) {
		windowPosY = -18;
		} 
}
// Check if a filename/path has an extension. Extensions can be up to 4 characters.
// Extension strings must begin with a . or they won't work right.
void AddExtensionIfMissing(char * name,unsigned int maxsize,const char * extension) {
	//if user did not add an extension, add it for them
	
	std::string tempName = name;
	
	//Non-null terminated lengths of both strings, +1 for null termination
	if ((strlen(name) + strlen(extension) + 1) <= maxsize) {
		unsigned int x = tempName.find_last_of(".");

		//If the extension(".????") is longer then 5 characters, it's probably part of the filename. If x == -1, wasn't found
		if ((x < (tempName.size() - 6)) || (x == -1)) {
			//If everything above passed, append the extension, and update the string
			tempName.append(extension);
			strcpy(name, tempName.c_str());
		}
	}
}

// Overloaded operator of above, which deals with native std::string variants.
void AddExtensionIfMissing(std::string &name,const char * extension) {
	//if user did not add an extension, add it for them

	unsigned int x = name.find_last_of(".");

	//If the extension(".????") is longer then 5 characters, it's probably part of the filename. If x == -1, wasn't found
	if ((x < (name.size() - 6)) || (x == -1))
		name.append(extension);
}

std::string GetPath(std::string filename)
{
	return filename.substr(0,filename.find_last_of("/\\") + 1);
}

bool IsRelativePath(char* name)
{
	if (name[0] == '.')
		if (name[1] == '\\') return true;
		else if (name[1] == '.' && name[2] == '\\') return true;
	return false;
}

bool IsRelativePath(const char* name)
{
	if (name[0] == '.')
		if (name[1] == '\\') return true;
		else if (name[1] == '.' && name[2] == '\\') return true;
	return false;
}

bool IsRelativePath(std::string name)
{
	if (name[0] == '.')
		if (name[1] == '\\') return true;
		else if (name[1] == '.' && name[2] == '\\') return true;
	return false;
}

//Precondition: IsRelativePath() == true
std::string ConvertRelativePath(std::string name)
{
	extern std::string BaseDirectory;
	return BaseDirectory + '\\' + name.substr(2, name.length());
}