#include "cli.hpp"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bytearray.hpp"

static char nameless[] = "NameLess";

Cli::Cli(const char *new_name)
{
	if(!new_name) {
		name = nameless;
	} else {
		int len = strlen(new_name);
		if(len <= max_name_len) {
			name = new char[len + 1];
			strcpy(name, new_name);
		} else {
			name = nameless;
		}
	}
}

Cli::~Cli()
{
	if(name)
		delete[] name;
}

void Cli::PrintWelcome()
{
	char user_name[40];
	getlogin_r(user_name, sizeof(user_name));

	PrintBorder();
	PrintLeftBorder(4);
	printf(" %s! %s %s. ", \
			user_name,
			welcome_msg,
			name);
	PrintRightBorder(4);
	PrintBorder();
}

void Cli::PrintGoodbye()
{
	PrintBorder();
	PrintLeftBorder(7);
	printf(" %s ", goodbye_msg);
	PrintRightBorder(7);
	PrintBorder();
}

void Cli::PrintUnknown()
{
	printf("%s\n", unknown_msg);
}

void Cli::PrintBorder(int len)
{
	int i;
	for(i = 0; i < len; i++)
		printf("%s", border_msg);
	printf("/\n");
}

void Cli::PrintLeftBorder(int len)
{
	int i;
	for(i = 0; i < len; i++)
		printf("%s", left_border_msg);
}

void Cli::PrintRightBorder(int len)
{
	int i;
	for(i = 0; i < len; i++)
		printf("%s", right_border_msg);
	printf("\n");
}

void Cli::PrintOperatorInput()
{
	//printf("%s", operator_msg);
	write(STDOUT_FILENO, operator_msg, sizeof(operator_msg));
}

void Cli::PrintClientInput()
{
	write(STDOUT_FILENO, client_msg, sizeof(client_msg));
}

void Cli::HandleExit()
{
	PrintGoodbye();
	exit(0);
}

void Cli::PrintHex(ByteArray &data, int offset)
{
	int i, len;
	len = data.GetBytesNum();
	for(i = offset; i < len; i++) {
		printf("%02x", data[i]);
	}
	printf("\n");
}
