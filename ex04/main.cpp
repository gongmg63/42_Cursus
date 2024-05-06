#include <iostream>
#include <fstream>
#include <string>

std::string replace_str(std::string line, std::string s1, std::string s2)
{
	std::string	tmp;
	int	pos;

	pos = line.find(s1);
	while (pos != -1)
	{
		tmp = line.substr(0, pos);
		tmp += s2;
		line = line.substr(pos + s1.size());
		line = tmp + line;
		pos = line.find(s1, pos + s1.size());
	}
	line += "\n";
	return (line);
}

int main(int ac, char *av[])
{
	std::ifstream	readfile;
	std::ofstream	writefile;
	std::string		line;

	if (ac != 4)
	{
		std::cout << "Please input <filename> <s1> <s2>" << std::endl;
		return (1); 
	}
	readfile.open(av[1]);
	writefile.open(std::string(av[1]) + ".replace");
	while (!readfile.eof())
	{
		getline(readfile, line);
		line = replace_str(line, av[2], av[3]);
		writefile.write(line.c_str(), line.size());
	}
	readfile.close();
	writefile.close();
}