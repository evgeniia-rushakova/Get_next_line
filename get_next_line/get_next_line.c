#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "./libft/libft.h"
#include "get_next_line.h"
#define BUF_SIZE 50

t_list  *find_fd(t_list  *begin, size_t fdnum)
{
	t_list *newlist;
	t_list *save_begin;

	save_begin = begin;
	while (begin->next)
	{
		if (begin->content_size == fdnum)
			return (begin);
		begin = begin->next;
	}
	newlist = ft_lstnew("", fdnum);
	if (newlist)
		return (newlist);
	return (NULL);
}

int  gnl(int fd, char **line)
{
	size_t  i;
	size_t count;
	int  res;
	char buf[BUF_SIZE + 1];
	t_list static *save;
	
	if(!save)
		save = ft_lstnew("", 10);
	else
		save = find_fd(save, fd);
	i = 0;		
	res = read(fd, buf, BUF_SIZE);
	if (res == -1)
		return (-1);
	buf[res] = '\0';
	while (buf[i] != '\n' && i < (size_t)res && buf[i])
		i++;
	*line = ft_strncpy(ft_strnew(i), buf, (i));
	if (i++ < (size_t)res)
	{
		count = i;
		while (buf[count] != '\n' && count < (size_t)res)
			count++;
		save->content = ft_strncpy(ft_strnew(count), &buf[i], count);
	}

	if (line)
	{
		//printf("%s", *line);
		return (1);
	}
	return(0);
}

int			main(int argc, char **argv)
{
	 int fd;
	 char *line;
	 int count = 3;

	  if (argc <= 2)
		   {
			fd = open(argv[1], O_RDONLY);

			while(gnl(fd, &line) == 1 && count)
			{
				printf("This is line: %s\n", line);
				count--;
			}

		   }
	   if (argc > 2)
		     write(2, "Too many arguments.\n", 20);
	    return (0);
}
