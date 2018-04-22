#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

int get_args(char**& args, int& size)
{
	vector<string> t;
	while (true)
	{
		static string buf = "";
		char c = char(cin.get());
		if (c == EOF) 
			return 1;
		if (c == ' ' || c == '\t' || c == '\n')
		{
			if (buf != "")
			{
				t.push_back(buf);
				buf = "";
			}
			if (c == '\n')
				break;
			continue;
		}
		buf += c;
	}
	size = t.size() + 1; 										//args[0] = filename; args[n] = NULL;
	args = (char**)calloc(t.size() + 1, sizeof(char*));
	if (args == NULL)
	{
		return -1;
	}
	for (size_t i = 0; i < size - 1; ++i) 
	{
		args[i] = (char*)malloc(sizeof(char) * t[i].size());
		char* cpy = strdup(t[i].c_str());
		if (args[i] == NULL || cpy == NULL)
		{
			for (size_t j = 0; j < i; ++j)
				free(args[j]);
			free(args);
			if (!args[i]) free(args[i]);
			if (!cpy) free(cpy);
			return -1;
		}
		args[i] = cpy;
	}
	args[size - 1] = NULL;
	return 0;
}

int main()
{
	while (true)
	{
		char** args;
		int size;
		printf("$ ");
		int res = get_args(args, size);
		if (res == -1) 
		{
			perror("Couldn't allocate memory");
			continue;
		} 
		else if (res == 1)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		pid_t pid = fork();
		if (!pid)
		{
			execve(args[0], args, NULL);
			perror("Couldn't execute given command");
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			int status;
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("Error occurred during waiting for child process");
			}
			else
			{
				printf("Returned value: %d\n", status);
			}
			for (int i = 0; i < size; ++i)
				free(args[i]);
			free(args);
		}
		else
		{
			perror("Couldn't create a process");
		}
	}
	return 0;
}