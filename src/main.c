#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static void	run_child(char **args)
{
	execvp(args[0], args);
	perror("execvp");
}

static char	*fork_and_wait(char **args)
{
	pid_t	child;

	child = fork();
	if (child == -1)
	{
		perror("fork");
		return (NULL);
	}
	if (child == 0)
		run_child(args);
	else
		waitpid(child, NULL, 0);
	return (args[0]);
}

static void	tokenize(char *line, char **args)
{
	char	*token;
	int		i;

	i = 0;
	token = strtok(line, " ");
	while (token)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}

static char	*run_cmd(char *line)
{
	char	*args[64];

	tokenize(line, args);
	return (fork_and_wait(args));
}

int	main(void)
{
	char	line[1024];

	printf("Welcome to Oh-my-gosh\n");
	while (1)
	{
		printf(">$ ");
		fgets(line, 1024, stdin);
		line[strlen(line) - 1] = '\0';
		if (!strcmp(line, "exit"))
			exit(0);
		run_cmd(line);
	}
	return (0);
}
