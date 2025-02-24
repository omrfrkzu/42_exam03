#include "get_next_line.h"

static char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_strdup(char *str)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(str) + 1;
	dup = malloc(len);
	if (!dup)
		return (NULL);
	ft_strcpy(dup, str);
	return (dup);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = malloc(len1 + len2 + 1);
	if (!join)
	{
		free(s1);
		return (NULL);
	}
	ft_strcpy(join, s1);
	ft_strcpy(join + len1, s2);
	free(s1);
	return (join);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			tocopy;
	int			count;

	line = ft_strdup(buf);
	if (!line)
		return (NULL);
	while (!(newline = ft_strchr(line, '\n')) && (count = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[count] = '\0';
		line = ft_strjoin(line, buf);
		if (!line)
			return (NULL);
	}
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	if (newline != NULL)
	{
		tocopy = newline - line + 1;
		ft_strcpy(buf, newline + 1);
	}
	else
	{
		tocopy = ft_strlen(line);
		buf[0] = '\0';
	}
	line[tocopy] = '\0';
	return (line);
}
