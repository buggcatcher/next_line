
#ifndef NEXT_LINE_H
# define NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	    *ft_reader(int fd, char *selection);
void	    *ft_calloc_bzero(size_t nmemb, size_t size);
static char *extract_from_buffer(char **mtx);
static char *read_and_assemble(char **mtx, int fd);
char        *gtnxl(int fd);
void        *ft_calloc_bzero(size_t elements, size_t size);
char        *ft_substr(char const *s, unsigned int start, size_t len);
char	    *ft_strjoin(char const *s1, char const *s2);
size_t      ft_strlen(const char *s);
char        *ft_strdup(const char *s1);
size_t      ft_strlcpy(char *dst, const char *src, size_t dst_size);

#endif
 
