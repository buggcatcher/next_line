
#include "next_line.h"

static char *fd_reader(int fd)//                                        1
{
    size_t  char_read;
    char    *buffer;

    buffer = ft_calloc_bzero(sizeof(char), BUFFER_SIZE + 1);
    if(!buffer)
        return (NULL);
    char_read = read(fd, buffer, BUFFER_SIZE);
    if (char_read == 0)
    {
        free(buffer);
        return (NULL);
    }
    else if (char_read == -1)
    {
        perror("Error reading from file descriptor\n");
        free(buffer);
        return (NULL);
    }
    return (buffer);
}
 
static char *extract_from_buffer(char **mtx)//                          2
{
    char    *line;
    char    *char_left;
    int     x;

    x = 0;
    if (!mtx || !*mtx)
        return NULL;
    while((*mtx)[x] != '\n' && (*mtx)[x] != '\0')
        x++;
    if ((*mtx)[x] == '\n')
    {
        line = ft_substr(*mtx, 0, x + 1);
        if(!line)
            return(NULL);
        char_left = ft_substr(*mtx, x + 1, ft_strlen(*mtx) - (x + 1));
        if (!char_left)
        {
            free(line);
            return(NULL);
        }
        free(*mtx);
        *mtx = char_left;
        return(line);
    }
    return(NULL);
}
// gestire il caso in cui la riga non contiene \n ma non e' vuota

char *ft_substr(char const *s, unsigned int start, size_t len)//        3
{
    char *new;
    size_t strlen;
    size_t end;

    if (!s)
        return (0);
    strlen = ft_strlen(s);
    end = 0;
    if (start <= strlen)
        end = strlen - start;
    if (start > strlen)
        return (ft_calloc_bzero(1, sizeof(char)));
    if (end > len)
        end = len;
    new = (char *)ft_calloc_bzero(end + 1, sizeof(char));
    if (!new)
        return (0);
    ft_strlcpy(new, s + start, end + 1);
    return (new);
}

static char *read_and_assemble(char **mtx, int fd)//                    4
{
    char    *read_line;
    char    *tmp;
    char    *line;

    line = extract_from_buffer(mtx);
    if (line)
        return (line);
    read_line = fd_reader(fd);
    if (!read_line)
    {
        line = ft_strdup(*mtx);
        free(*mtx);
        *mtx = NULL;
        if (*line)
            return(line);
        free (line);
        return(NULL);
    }
    tmp = ft_strjoin(*mtx, read_line);
    free(*mtx);
    free(read_line);
    *mtx = tmp;
    return(read_and_assemble(mtx, fd));
}
 
char *gtnxl(int fd)//                                                   5
{
    static char *buffer;

    if (read(fd, NULL, 0) < 0 || fd < 0 || BUFFER_SIZE <= 0)
    {
        free(buffer);
        buffer = NULL;
        return(NULL);
    }
    if (!buffer)
        buffer = ft_strdup("");
    return (read_and_assemble(&buffer, fd));
}

/* QUESTO VA IN UTILS */

void *ft_calloc_bzero(size_t elements, size_t size)//                   1
{
  size_t i;
  char *array;

  i = 0;
  array = (void *)malloc(elements * size);
  if (array == NULL)
    return (NULL);
  while (i < elements * size) {
    array[i] = '\0';
    i++;
  }
  return (array);
}


char	*ft_strjoin(char const *s1, char const *s2)//                   2
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)ft_calloc_bzero(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (str);
}

size_t ft_strlen(const char *s)//                                       3
{
    size_t i = 0;

    while (s[i] != '\0')
    {
        i++;
    }

    return i;
}

char *ft_strdup(const char *s1)//                                       4
{
    char *s2 = malloc((ft_strlen(s1) + 1) * sizeof(char));

    if (s2 == NULL)
    {
        return NULL;
    }

    for (int i = 0; s1[i] != '\0'; i++)
    {
        s2[i] = s1[i];
    }

    s2[ft_strlen(s1)] = '\0';

    return s2;
}

size_t ft_strlcpy(char *dst, const char *src, size_t dst_size)//         5
{
    size_t i = 0;

    if (dst_size == 0)
        return ft_strlen(src);

    while (src[i] && i < dst_size - 1)
    {
        dst[i] = src[i];
        i++;
    }

    dst[i] = '\0';

    return ft_strlen(src);
}
/*  TEST PER READ E BUFFER

int main(void)
{
    int fd;
    char *buffer;
    int n;

    fd = open("lorem.txt", O_RDONLY);
    n = 1;
    if (fd < 0)
    {
        perror("Error opening file\n");
        return 1;
    }
    while ((buffer = fd_reader(fd)) != NULL)
    {
        printf("linea %d: %s\n", n, buffer);
        n++;
        free(buffer);
    }
    close(fd);
    return 0;
}*/

/*  TEST PER SUBSTR

int main()
{
    char *s = "Hello, world!";
    unsigned int start = 7;
    size_t len = 5;
    char *substr = ft_substr(s, start, len);

    if (substr)
    {
        printf("Substring: %s\n", substr);
        free(substr);
    }
    else
    {
        printf("ft_substr failed to allocate memory\n");
    }

    return 0;
}*/

/*  TEST PER READ E ASSEMBLE

int main()
{
    int fd = open("test.txt", O_RDONLY); // replace "test.txt" with your test file
    char *buffer = NULL;
    char *line;

    if (fd < 0)
    {
        perror("Error opening file\n");
        return 1;
    }

    while ((line = read_and_assemble(&buffer, fd)) != NULL)
    {
        printf("Line: %s\n", line);
        free(line);
    }

    free(buffer);
    close(fd);
    return 0;
}*/

int main()
{
    int fd = open("lorem.txt", O_RDONLY);
    char *line;
    int i = 1;

    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }

    while ((line = gtnxl(fd)) != NULL)
    {
        printf("Linea %d: %s",i ,line);
        i++;
        free(line);
    }

    close(fd);
    return 0;
}

