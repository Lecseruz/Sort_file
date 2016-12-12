// ext_sort_name.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
//#include <deque>
#include <chrono>
#include <ctime>



struct line
{
	std::string name;
	std::string surname;
	short year;
	size_t size() const
	{
		size_t sz = sizeof(std::string);
		return (sz + name.size() + sz + surname.size() + sizeof(year));
	}
};

bool operator < (const line& line1, const line& line2)
{
	return (line1.name < line2.name);
}

bool operator >(const line& line1, const line& line2)
{
	return (line1.name > line2.name);
}

std::ostream & operator<<(std::ostream & output, line const & str)
{
	output << str.surname << " " << str.name << " " << str.year;
	return output;
}

std::istream & operator >> (std::istream & input, line & str)
{
	input >> str.surname >> str.name >> str.year;
	return input;
}

bool operator != (const line& line_, const std::string& string_)
{
	return (line_.surname != string_);
}

struct inp
{
	line st;
	std::ifstream *file;
	inp(const line& st_, std::ifstream* file_) : st(st_), file(file_) {}
};


bool operator < (const inp& inp_1, const inp& inp_2)
{
	return (inp_1.st > inp_2.st);
}


auto sorting(const std::string input_adress, const std::string output_adress, const unsigned int memory)
{
	//std::ifstream fin("C:/Users/Dell/Documents/Visual Studio 2015/Projects/extended_sort/fix/8.txt", std::ios::binary);
	std::ifstream fin(input_adress, std::ios::binary);
	if (fin.is_open() == false) throw ("Cant open ur file");
	//std::ofstream fout("C:/Users/Dell/Documents/Visual Studio 2015/Projects/extended_sort/fix/8out.txt", std::ios::binary);
	std::ofstream fout(output_adress, std::ios::binary);
	size_t num_buff = 0;
	while (fin.eof() == false)
	{
		line st;
		std::ofstream buff(std::to_string(num_buff + 1) + ".txt", std::ios::binary);
		//std::deque<line> deque_;
		std::vector<line> vector_;
		for (unsigned int size = 0; (size + 50) < memory * 1024 * 1024; size += 50)
		{
			if (!fin.eof() && (fin >> st) && (st != ""))  vector_.push_back(st);
			size += st.size();
			// 			std::getline(fin, s);
				//	deque_.push_back(s);
		}
		std::sort(vector_.begin(), vector_.end());
		for (auto i : vector_)
		{
			if (i != "") buff << i << std::endl;
		}
		num_buff++;
		buff.close();
	}
	fin.close();
	std::priority_queue<inp> PriQue;
	for (size_t i = 0; i < num_buff; ++i)
	{
		std::ifstream* f_ = new std::ifstream(std::to_string(i + 1) + ".txt", std::ios::binary);
		line str;
		*f_ >> str;
		inp inp_(str, f_);
		PriQue.push(inp_);
	}
	while (PriQue.empty() == false)
	{
		inp inp_ = PriQue.top();
		PriQue.pop();
		if (inp_.st != "")
		{
			fout << inp_.st << std::endl;
		}
		if (!(*inp_.file).eof() && (*inp_.file >> inp_.st))
		{
			PriQue.push(inp_);
		}
		else
		{
			(*(inp_.file)).close();
		}
	}
	for (size_t i = 0; i < num_buff; ++i)
	{
		remove((std::to_string(i + 1) + ".txt").data());
	}
	fout.close();
}

/*void main(){
std::string in, out;
unsigned long int memory_size;
std::cout << "input path: "; std::cin >> in;
std::cout << "output path: "; std::cin >> out;
std::cout << "write memory(mb): "; std::cin >> memory_size;
std::chrono::time_point<std::chrono::system_clock> start, end;
start = std::chrono::system_clock::now();
sorting(in, out, memory_size);
end = std::chrono::system_clock::now();
int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
(end - start).count();
std::time_t end_time = std::chrono::system_clock::to_time_t(end);
std::cout << "finished computation at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds << "s\n";
system("pause");
}
*/
