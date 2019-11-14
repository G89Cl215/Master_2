#include <unistd.h> 
#include <signal.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include "microshell.h"

int				g_state = 0;
pid_t			g_lastpid = 0;

unsigned int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void			ft_itoa(char *dest, int value)
{
	unsigned int	i;
	unsigned int	log;
	
	i = value;
	log = 1;
	while (i)
	{
		i /= 10;
		log++;
	}
	i = log;
	dest[i] = '\0';
	while (i--)
	{
		dest[i] = value % 10 + '0';
		value /= 10;
	}
}

void			ft_strcpy(char *dest, char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int				ft_strcmp(char *str1,char *str2)
{
	unsigned int	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}


unsigned int	ft_wcount(char *cmd)
{
	int				state;
	unsigned int	i;
	unsigned int	wc;

	i = 0;
	wc = 0;
	state = 0;
	while (cmd[i])
	{
		if (!state && cmd[i] != ' ')
		{
			state = 1;
			wc++;
		}
		else if (state && cmd[i] == ' ')
					state = 0;
		i++;
	}
	return (wc);
}

void		ft_wcpy(char **args, char *cmd)
{
	int				state;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	state = 0;
	while (cmd[i])
	{
		if (!state && cmd[i] != ' ')
		{
			state = 1;
			args[j++] = &(cmd[i]);
		}
		else if (state && cmd[i] == ' ')
		{
			state = 0;
			cmd[i] = '\0';
		}
		i++;
	}
	args[j] = NULL;
}

void	append_path(char *arg0, char *bin_name) 
{
	unsigned int	bin_len;

	bin_name[0] = '/';
	bin_name[1] = 'b';
	bin_name[2] = 'i';
	bin_name[3] = 'n';
	bin_name[4] = '/';
	bin_len = 0;
	while (arg0[bin_len])
	{
		bin_name[bin_len + 5] = arg0[bin_len];
		bin_len++;
	}
	bin_name[bin_len + 5] = arg0[bin_len];
}

void	expand_var(int ac, char **arg, char **tmp)
{
	unsigned int	i;

	i = 0;
	while (i < ac)
	{
		if (arg[i][0] == '$')
		{
			if (arg[i][1] == '$' && !(arg[i][2]))
			{
				ft_strcpy(tmp[i], "microshell\0");
				arg[i] = tmp[i];
			}
			else if (arg[i][1] == '?' && !(arg[i][2]))
			{
				ft_itoa(tmp[i], g_state);
				arg[i] = tmp[i];
			}
			else if (arg[i][1] == '!' && !(arg[i][2]))
			{
				ft_itoa(tmp[i], g_lastpid);
				arg[i] = tmp[i];
			}
			
		}
		i++;
	} 
}

int		exec_cmd(int ac, char **args)
{
	int				state;
	extern char		**environ;
	unsigned int	bin_len;
	pid_t			pid;
	char			bin_name[ft_strlen(*args) + 6];
	char			tmp[ac][12];

	append_path(*args, bin_name);
	expand_var(ac, args, (char**)tmp);
	if ((pid = fork()) == -1)
	{
		write(2, "microshell: fork error.\n", 24);
		return (DEAD);
	}
	if (!pid)
	{
		if (execve(bin_name, args, environ) == -1)
		{
			write(2, "microshell: parsing error.\n", 27);	
			_exit(DEAD);
		}
	}
	else
		waitpid(pid, &state, WUNTRACED);
	g_state = WEXITSTATUS(state);
	g_lastpid = pid;
	return (WIFEXITED(state) ? LIVING : DEAD);
}

int		parse_exec(char *cmd)
{
	unsigned int	wc = ft_wcount(cmd);
	char			*args[wc + 1];

	ft_wcpy(args, cmd);
	if (ft_strcmp(*args, "exit"))
		return (exec_cmd(wc, args));
	return (EXIT);
}

int		read_line(char cmd[MAX_LINE + 1])
{
	char			read_val;
	unsigned int	i;

	i = 0;
	while (read(0, &read_val, 1) > 0)
	{
		if (read_val == 127 && i > 0)
			i--;
		else if (read_val == '\n' || i == MAX_LINE + 1)
		{
			cmd[i] = '\0';
			return (LIVING);
		}
		else
			cmd[i++] = read_val;
	}
	return (DEAD);
}

int		main(int ac, char **av)
{
	int		state;
	char	cmd[MAX_LINE + 1];

	state = LIVING;
	while (state == LIVING)
	{
		write(1, "microshell de l'ambiance> ", 26);
		if ((state = read_line(cmd)) == DEAD)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		if (!(*cmd))
			continue ;
		state = parse_exec(cmd);
		if (state == EXIT)
			break ;
	}
	return (0);
}
