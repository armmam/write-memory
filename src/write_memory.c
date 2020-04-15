#include <unistd.h>

void	print_hex(int i)
{
	char	output;

	if (i >= 0 && i <= 9)
		output = i + '0';
	else
		output = i - 10 + 'a';
	write(1, &output, 1);
}

void	process_hex(unsigned char c)
{
	print_hex((int)(c / 16));
	print_hex((int)(c % 16));
}

void	process_chars(unsigned char c)
{
	if (c >= 32 && c <= 126)
		write(1, &c, 1);
	else
		write(1, ".", 1);
}

void	write_memory(const void *addr, size_t size)
{
	unsigned char	*ptr;
	size_t			i;
	size_t			j;

	ptr = (unsigned char *)addr;
	i = 0;
	while (i < size)
	{
		process_hex(ptr[i]);
		if ((i + 1) % 2 == 0 || i == size - 1)
			write(1, " ", 1);
		if ((i + 1) % 16 == 0 || i == size - 1)
		{
			if ((i + 1) % 16 != 0)
			{
				j = (16 - (i + 1) % 16) * 2 + (16 - (i + 1) % 16) / 2;
				while (j-- > 0)
					write(1, " ", 1);
			}
			j = i / 16 * 16;
			while (j <= i)
			{
				process_chars(ptr[j]);
				j++;
			}
			write(1, "\n", 1);
		}
		i++;
	}
}

int		main(void)
{
	int	tab[10] = {0, 23, 150, 255,
	              12, 16,  21, 42};

	write_memory(tab, sizeof(tab));
	return (0);
}
