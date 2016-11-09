#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

//struct holding utility functions

struct Utils
{
	//split text by c, store in parts, return the size
	static unsigned int split(std::string text, std::vector<std::string> &parts, char c)
	{
		int start_pos = 0;
		int pos = text.find(c);
		parts.clear();
		
		while(pos != std::string::npos)
		{
			parts.push_back(text.substr(start_pos, pos - start_pos + 1));
			start_pos = pos + 1;
			pos = text.find(c, start_pos);
		}
		parts.push_back(text.substr(start_pos, std::min<int>(pos, text.size() - start_pos - 1)));
		
		return parts.size();
	}
};

#endif