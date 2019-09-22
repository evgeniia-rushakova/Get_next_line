/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <jslave@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:09:17 by jslave            #+#    #+#             */
/*   Updated: 2019/09/21 19:21:32 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "./libft/libft.h"
#include "get_next_line.h"
#define BUF_SIZE 10250

int  gnl(int fd, char **line)
{
	int  i;
	size_t lenofbuf;
	int  res;
	char buf[BUF_SIZE + 1];
	char *content;
	t_list static *save;

	lenofbuf = BUF_SIZE;
	i = 0;
	if (!save)
	{
		res = read(fd, buf, BUF_SIZE);
		if (res == -1)
			return (-1);
		buf[res] = '\0';
		while (buf[i] != '\n' && lenofbuf)
		{
			lenofbuf--;
			i++;
		}
		*line = ft_strnew(i);
		ft_strncpy(*line, buf, i);	
		content = ft_strncpy(ft_strnew(ft_strlen(&buf[i])), &buf[i], ft_strlen(&buf[i]));
		save = ft_lstnew(content, ft_strlen(&buf[i]));
	}
	else
	{
		char *test = ((char*)(save->content));
		while (test[i] != '\n' && lenofbuf)
		{
			lenofbuf--;
			i++;
		}
		free(line);
		line = ft_strnew(i);
		//ft_strncpy(*line, test, i);
		//content = ft_strncpy(ft_strnew(ft_strlen(&((char*)(save->content))[i])), &((char*)(save->content))[i], ft_strlen(&((char*)(save->content))[i]));
		//printf("%s\n", content);
		//save->content = content;
		//save = ft_lstnew(content, ft_strlen(&buf[i]));
	}
	
	//printf("%s\n", save->content);
	if (line)
		return (1);
	
	return(0);
}

int			main(int argc, char **argv)
{
	 int fd;
	 char *line;

	  if (argc <= 2)
		   {
			     fd = open(argv[1], O_RDONLY);
				/*   if (fd == -1)
					      write(2, "File name missing.\n", 19);
				   else */
			if (gnl(fd, &line) == 1)
			{
				printf("%s\n", line);
				printf("ok\n");
			}
			if (gnl(fd, &line) == 1)
			{
				printf("%s\n", line);
				printf("ok\n");
			}

		   }
	   if (argc > 2)
		     write(2, "Too many arguments.\n", 20);
	    return (0);
}
