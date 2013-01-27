/*
Compile:
	make ctflog CFLAGS=-Wall

Tests:
	#1
	export SSH_CLIENT='172.25.141.1 3209 22'
	echo 'test' | ./ctflog

	#2
	export SSH_CLIENT='172.25.141.1'
	echo 'test' | ./ctflog

	#3
	export SSH_CLIENT='../../ 22 '
	echo 'test' | ./ctflog

	#4
	export SSH_CLIENT=''
	echo 'test' | ./ctflog
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE 2048
#define FILE_SIZE 512

void abort(void);
char * get_ip_address(const char *);
char * get_src_port(const char *);
_Bool ip_address_is_valid(const char *);
void current_time(char *, size_t);

int main(void)
{
	char buffer[BUF_SIZE] = { 0x00 },
	filename[FILE_SIZE] = { 0x00 },
	*ip_address = NULL,
	*src_port = NULL,
	timestamp[FILE_SIZE] = { 0x00 } ;
	FILE *output = NULL;

	ip_address = get_ip_address(getenv("SSH_CLIENT"));
	src_port = get_src_port(getenv("SSH_CLIENT"));
	current_time(timestamp, FILE_SIZE-1);

	if (ip_address && src_port && ip_address_is_valid(ip_address))
	{
		snprintf(filename, FILE_SIZE-1, "%s/%s_%s", "/tmp/", ip_address, src_port);
		free(ip_address); free(src_port); ip_address = NULL;
		output = fopen(filename, "a");
		fputs(timestamp, output);
		fgets(buffer, BUF_SIZE, stdin);
		fputs(buffer, output);
		fclose(output);
		output = NULL;
		return (0);
	}
	abort();
	return (0);
}

void abort(void)
{
	fprintf(stderr,
			"So, you DO enjoy trying new and unfamiliar things. \
				   \nThough, I suspect these things aren't so unfamiliar ...\n");
	exit(1);
}
/*
    78.108.63.44 6056 22
    ^^^^^^^^^^^^
 */
char * get_ip_address(const char *input)
{
	const char *start, *end;
	start = input;
	if (input && (end = strstr(start, " ")) != NULL)
	{
		char *out = malloc(end - start + 1);
		if (out != NULL)
		{
			memcpy(out, start, (end - start));
			out[end - start] = '\0';
			return out;
		}
	}
	return NULL;
}
/*
    78.108.63.44 6056 22
                 ^^^^
 */
char * get_src_port(const char *input)
{
	const char *start, *end;
	start = input;
	if (input && (start = strstr(input, " ")) != NULL)
	{
		start++;
		if ((end = strstr(start, " ")) != NULL)
		{
			char *out = malloc(end - start + 1);
			if (out != NULL)
			{
				memcpy(out, start, (end - start));
				out[end - start] = '\0';
				return out;
			}
		}
	}
	return NULL;
}
/* Returns: True (valid), False (invalid) */
_Bool ip_address_is_valid(const char *input)
{
	struct in_addr ia;
	return (inet_aton(input, &ia) != 0);
}
void current_time(char *string, size_t string_length)
{
	time_t now;
	now = time(NULL);
	snprintf(string, string_length, "--\n%s--\n", asctime(localtime(&now)));
}
