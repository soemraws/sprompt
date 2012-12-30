#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <readline/readline.h>

/* Number of initial slots for items to be read from stdin */
#define INITIAL_SLOTS 64

/* The store of items, read from stdin, for completion */
struct completion_store
{
	char** items;
	size_t slots;
	size_t nitems;
};

typedef struct completion_store completion_store;

static completion_store completions = { NULL, 0, 0};

/* By default, use case-sensitive string comparison */
static int (*prompt_strncmp)(const char *, const char *, size_t) = strncmp;

/* By default, append a space after a completion */
static int append_character = ' ';

void
read_stdin(void)
{
	char buffer[BUFSIZ];
	char *p;
	size_t i;


	if (!(completions.items = calloc(INITIAL_SLOTS, sizeof(completions.items))))
	{
		fprintf(stderr, "Failed to allocate memory\n");
		exit(1);
	}
	completions.slots = INITIAL_SLOTS;

	for(i = 0; fgets(buffer, sizeof(buffer), stdin); i++)
	{
		if (i == completions.slots)
		{
			if(!(completions.items = realloc(completions.items, 2 * sizeof(completions.items))))
			{
				fprintf(stderr, "Failed to allocate memory\n");
				exit(1);
			}
			completions.slots *= 2;
		}
		if((p = strchr(buffer, '\n')))
			*p = '\0';
		completions.items[i] = strdup(buffer);
	}

	completions.nitems = i;

	return;
}

char*
completion_generator(const char* text, int state)
{
	static size_t i, len;

	if (!state)
	{
		i = 0;
		len = strlen(text);
	}

	while(i < completions.nitems)
	{
		i++;
		if(prompt_strncmp(text, completions.items[i-1], len) == 0)
			return strdup(completions.items[i-1]);
	}

	return NULL;
}

char**
prompt_completion(const char* text, int start, int end)
{
	rl_attempted_completion_over = 1;
	rl_completion_append_character = append_character;

	return rl_completion_matches(text, completion_generator);
}

int
main(int argc, char** argv)
{
	size_t i;
	int use_stdin = 1;
	char *line, *prompt;
	FILE* tty = fopen("/dev/tty", "r+");

	rl_instream = tty;
	rl_outstream = tty;

	for(i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-a") == 0)
		{
			i++;
			if (i < argc)
				append_character = (int)(argv[i][0]);
			else
			{
				fprintf(stderr, "Option -a requires argument\n");
				exit(1);
			}
		}
		else if (strcmp(argv[i], "-b") == 0)
		{
			i++;
			if (i < argc)
				rl_completer_word_break_characters = argv[i];
			else
			{
				fprintf(stderr, "Option -b requires argument\n");
				exit(1);
			}
		}
		else if (strcmp(argv[i], "-q") == 0)
		{
			i++;
			if (i < argc)
				rl_completer_quote_characters = argv[i];
			else
			{
				fprintf(stderr, "Option -q requires argument\n");
				exit(1);
			}
		}
		else if (strcmp(argv[i], "-i") == 0)
			prompt_strncmp = strncasecmp;
		else if (strcmp(argv[i], "-f") == 0)
			use_stdin = 0;
		else if (strcmp(argv[i], "-h") == 0)
		{
			fprintf(stderr,"Usage: prompt [options] [string]\n");
			return 0;
		}
		else if (strcmp(argv[i], "--") == 0)
		{
			i++;
			break;
		}
		else break;
	}

	if (use_stdin)
	{
		read_stdin();
		rl_attempted_completion_function = prompt_completion;
	}

	rl_readline_name = "sprompt";

	if (i < argc)
		prompt=argv[i];
	else
		prompt=NULL;

	line = readline(prompt);	

	fclose(tty);

	for (i = 0; i < completions.nitems; i++)
		free(completions.items[i]);

	if (!line || strlen(line) == 0)
		return 1;


	printf("\n%s\n", line);
	return 0;
}
