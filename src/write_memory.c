#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
# define BUF_SIZE 4096

void	write_hex(int i, int fd_o)
{
	char	output;

	if (i >= 0 && i <= 9)
		output = i + '0';
	else
		output = i - 10 + 'a';
	write(fd_o, &output, 1);
}

void	process_hex(unsigned char c, int fd_o)
{
	write_hex((int)(c / 16), fd_o);
	write_hex((int)(c % 16), fd_o);
}

void	process_chars(unsigned char c, int fd_o)
{
	if (c >= 32 && c <= 126)
		write(fd_o, &c, 1);
	else
		write(fd_o, ".", 1);
}

void	write_memory(const void *addr, size_t size, int fd_o)
{
	unsigned char	*ptr;
	size_t			i;
	size_t			j;

	ptr = (unsigned char *)addr;
	i = 0;
	while (i < size)
	{
		process_hex(ptr[i], fd_o);
		if ((i + 1) % 2 == 0 || i == size - 1)
			write(fd_o, " ", 1);
		if ((i + 1) % 16 == 0 || i == size - 1)
		{
			if ((i + 1) % 16 != 0)
			{
				j = (16 - (i + 1) % 16) * 2 + (16 - (i + 1) % 16) / 2;
				while (j-- > 0)
					write(fd_o, " ", 1);
			}
			j = i / 16 * 16;
			while (j <= i)
			{
				process_chars(ptr[j], fd_o);
				j++;
			}
			write(fd_o, "\n", 1);
		}
		i++;
	}
}

int		main(int ac, char **av)
{
	int		fd_i;
	int		fd_o;
	int		ret;
	char	buf[BUF_SIZE + 1];
	char	*mem_filename;

	if (ac != 2)
		write(1, "usage: ./write-memory [file ...]\n", 33);
	else
	{
		fd_i = open(av[1], O_RDONLY);
		if (fd_i < 0)
			write(1, "Failed to open the file.\n", 25);
		else
		{
			mem_filename = "memory.txt";
			if (access(mem_filename, F_OK) != -1)
			{
				write(1, "memory.txt already exists. "
					"Proceed with this filename? [y/n]\n", 61);
				scanf("%s", buf);
				if (buf[0] == 'n')
				{
					write(1, "New filename:\n", 14);
					scanf("%s", mem_filename);
				}
					return (0);
			}
			fd_o = open(mem_filename, O_WRONLY | O_CREAT, 0644);
			do
			{
				ret = read(fd_i, buf, BUF_SIZE);
				if (ret < 0)
				{
					write(1, "Error reading the file.\n", 24);
					exit(1);
				}
				write_memory(buf, ret, fd_o);
			} while (ret);
			close(fd_o);
		}
		close(fd_i);
	}
	return (0);
}
