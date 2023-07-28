/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:35:39 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/26 15:35:26 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include<unistd.h>
# include<stdlib.h>
# include "./get_next_line/get_next_line.h"
# include "./ft_printf/ft_printf.h"

# define __INT_MIN -2147483648
# define __INT_MAX 2147483647

typedef struct s_list	t_list;
typedef enum e_assert	t_assert;

struct s_list
{
	void	*content;
	t_list	*next;
};

typedef enum e_bool
{
	__FALSE = 0,
	__TRUE = 1
}				t_bool;

enum e_assert
{
	INFERIOR = -2,
	EQUAL = 1,
	SUPERIOR = 2
};

/*
**ft_atoi -- convert a string to an integer
**
**	DESCRIPTION
**		The ft_atoi() function converts the initial portion of the string
**		pointed to by nptr to int.
**	RETURN VALUE
**		The converted value or 0 on error.
*/
int				ft_atoi(const char *nptr);

/*
**ft_bzero -- zero a byte string
**
**	DESCRIPTION
**		The ft_bzero() function erases the data in the n bytes of the memory
**		starting at the location pointed to by s, by writing zeros
**		(bytes containing '\0') to that area.
**	RETURN VALUE
**		None.
*/
void			ft_bzero(void *s, unsigned int n);

/*
**ft_calloc -- allocate and free dynamic memory
**
**	DESCRIPTION
**		The  ft_calloc() function allocates memory for an array of nmemb
**		elements of size bytes each and returns a pointer to the 
**		allocated memory. The memory is set to zero.  If nmemb or
**		size is 0, then ft_calloc()	returns NULL.
**	RETURN VALUE
**	ft_calloc returns a pointer to the allocated memory, which is 
**	suitably aligned for any built-in type.  On error, ft_calloc 
**	returns NULL.  NULL may also be returned by a successful call
**	to ft_calloc() with nmemb or size equal to zero.
*/
void			*ft_calloc(unsigned int nmemb, unsigned int size);

/*
**ft_isalnum -- character classification function
**
**	DESCRIPTION
**		checks for an alphanumeric character; it is equivalent
**		to (isalpha(c) || isdigit(c)).
**	RETURN VALUE
**		The value returned is nonzero if the character c is alphanumeric,
**		and zero if not.
*/
int				ft_isalnum(int c);

/*
**ft_isalpha -- character classification function
**
**	DESCRIPTION
**		checks  for  an  alphabetic  character.
**	RETURN VALUE
**		The value returned is nonzero if the character c is alphabetic,
**		and zero if not.
*/
int				ft_isalpha(int c);

/*
**ft_isascii -- character classification function
**
**	DESCRIPTION
**		checks whether c is a 7-bit unsigned char value that fits into the
**		ASCII character set.
**	RETURN VALUE
**		The value returned is nonzero if the character c is ASCII character,
**		and zero if not.
*/
int				ft_isascii(int c);

/*
**ft_isdigit -- character classification function
**
**	DESCRIPTION
**		checks for a digit (0 through 9).
**	RETURN VALUE
**		The value returned is nonzero if the character c is a digit,
**		and zero if not.
*/
int				ft_isdigit(int c);

/*
**ft_isprint -- character classification function
**
**	DESCRIPTION
**		checks for any printable character including space.
**	RETURN VALUE
**		The value returned is nonzero if the character c is printable,
**		and zero if not.
*/
int				ft_isprint(int c);

/*
**ft_itoa
**
**	PARAMETERS
**		n: the integer to convert.
**	DESCRIPTION
**		Allocates (with malloc(3)) and returns a string
**		representing the integer received as an argument.
**		Negative numbers must be handled.
**	RETURN VALUE
**		The string representing the integer. NULL if the
**		allocation fails.
*/
char			*ft_itoa(int n);

/*
**ft_memchr -- scan memory for a character
**
**	DESCRIPTION
**		The  ft_memchr()  function  scans  the  initial n bytes of the memory
**		area pointed to by s for the first instance of c.  Both c and the
**		bytes of the memory area pointed to by s  are  interpreted
**		as unsigned char.
**	RETURN VALUE
**		The ft_memchr() function returns a pointer to the matching byte or NULL
**		if the character does not occur in the given memory area.
*/
void			*ft_memchr(const void *s, int c, unsigned int n);

/*
**ft_memcmp -- compare memory areas
**
**	DESCRIPTION
**		The  ft_memcmp()  function  compares  the first n bytes
**		(each interpreted as unsigned char) of the memory areas
**		s1 and s2.
**	RETURN VALUE
**		The ft_memcmp() function returns an integer less than, 
**		equal to, or greater than zero if the first n bytes of
**		s1 is found, respectively, to be less than, to match, or
**		be greater than the first n bytes of s2.
**
**		For a nonzero return value, the sign is determined by
**		the sign of the  difference  between  the first pair 
**		of bytes (interpreted as unsigned char) that differ in
**		s1 and s2.
**		If n is zero, the return value is zero.
*/
int				ft_memcmp(const void *s1, const void *s2, unsigned int n);

/*
**ft_memcpy -- copy memory area
**
**	DESCRIPTION
**		The  ft_memcpy() function copies n bytes from memory area src
**		to memory area dest.  The memory areas must not overlap.
**		Use ft_memmove() if the memory areas do overlap.
**	RETURN VALUE
**		The ft_memcpy() function returns a pointer to dest.
*/
void			*ft_memcpy(void *dest, const void *src, unsigned int n);

/*
**ft_memmove -- copy memory area
**
**	DESCRIPTION
**		The ft_memmove() function copies n bytes from memory area
**		src to memory area dest.  The memory areas may overlap:
**		copying takes place as though the bytes in src are first
**		copied into a  temporary  array that does not overlap src
**		or dest, and the bytes are then copied from the temporary
**		array to dest.
**	RETURN VALUE
**		The ft_memmove() function returns a pointer to dest.
*/
void			*ft_memmove(void *dest, const void *src, unsigned int n);

/*
**ft_memset -- fill memory with a constant byte
**
**	DESCRIPTION
**		The  ft_memset() function fills the first n bytes of the
**		memory area pointed to by s with the constant byte c.
**	RETURN VALUE
**		The ft_memset() function returns a pointer to the memory
**		area s.
*/
void			*ft_memset(void *s, int c, unsigned int n);

/*
**ft_putchar_fd
**
**	PARAMETERS
**		c: The character to output.
**		fd: The file descriptor on which to write.
**	DESCRIPTION
**		Outputs the character ’c’ to the given file descriptor.
**	RETURN VALUE
**		None
*/
void			ft_putchar_fd(char c, int fd);

/*
**ft_putendl_fd
**
**	PARAMETERS
**		s: The string to output.
**		fd: The file descriptor on which to write.
**	DESCRIPTION
**		Outputs the string ’s’ to the given file descriptor, followed by a newline.
**	RETURN VALUE
**		None
*/
void			ft_putendl_fd(char *s, int fd);

/*
**ft_putnbr_fd
**
**	PARAMETERS
**		n: The integer to output.
**		fd: The file descriptor on which to write.
**	DESCRIPTION
**		Outputs the integer ’n’ to the given file descriptor.
**	RETURN VALUE
**		None
*/
void			ft_putnbr_fd(int n, int fd);

/*
**ft_putstr_fd
**
**	PARAMETERS
**		s: The string to output.
**		fd: The file descriptor on which to write.
**	DESCRIPTION
**		Outputs the string ’s’ to the given file descriptor.
**	RETURN VALUE
**		None
*/
void			ft_putstr_fd(char *s, int fd);

/*
**ft_split
**
**	PARAMETERS
**		s: The string to be split.
**		c: The delimiter character.
**	DESCRIPTION
**		Allocates (with malloc(3)) and returns an array
**		of strings obtained by splitting ’s’ using the
**		character ’c’ as a delimiter. The array must be
**		ended by a NULL pointer.
**	RETURN VALUE
**		The array of new strings resulting from the split.
**		NULL if the allocation fails.
*/
char			**ft_split(char const *s, char c);

/*
**ft_splitwset
**
**	PARAMETERS
**		s: The string to be split.
**		set: The set of delimiting characters.
**	DESCRIPTION
**		Allocates (with malloc(3)) and returns an array
**		of strings obtained by splitting ’s’ using the set of
**		characters in ’set’ as a delimiters. The array must be
**		ended by a NULL pointer.
**	RETURN VALUE
**		The array of new strings resulting from the split.
**		NULL if the allocation fails.
*/
char			**ft_splitwset(char const *s, char *set);

/*
**ft_strchr -- locate character in string
**
**	DESCRIPTION
**		The  ft_strchr()  function  returns  a  pointer  to the first
**		occurrence of the character c in the string s.
**		Here "character" means "byte"; these functions do not work with
**		wide or multibyte characters.
**	RETURN VALUE
**		The ft_strchr() function returns a pointer to the matched
**		character or NULL  if  the character is not found.  The terminating
**		null byte is considered part of the string, so that if c is specified
**		as '\0', these functions return a pointer to the terminator.
*/
char			*ft_strchr(const char *s, int c);

/*
**ft_strdup -- duplicate a string
**
**	DESCRIPTION
**		The  ft_strdup() function returns a pointer to a new string which
**		is a duplicate of the string s. Memory for the new string is obtained
**		with malloc(3), and can be freed with free(3).
**	RETURN VALUE
**		On  success, the ft_strdup() function returns a pointer to the
**		duplicated string.  It returns NULL if insufficient memory was
**		available, with errno set to indicate the cause of the error.
*/
char			*ft_strdup(const char *s);

/*
**ft_striteri
**
**	PARAMETERS
**		s: The string on which to iterate.
**		f: The function to apply to each character.
**	DESCRIPTION
**		Applies the function f to each character of the
**		string passed as argument, and passing its index
**		as first argument. Each character is passed by
**		address to f to be modified if necessary
**	RETURN VALUE
**		None.
*/
void			ft_striteri(char *s, void (*f)(unsigned int, char*));

/*
**ft_strjoin
**
**	PARAMETERS
**		s1: The prefix string.
**		s2: The suffix string.
**	DESCRIPTION
**		Allocates (with malloc(3)) and returns a new
**		string, which is the result of the concatenation
**		of ’s1’ and ’s2’.
**	RETURN VALUE
**		The new string. NULL if the allocation fails.
*/
char			*ft_strjoin(char const *s1, char const *s2);

/*
**ft_strlcat -- size-bounded string concatenation
**
**	DESCRIPTION
**		The ft_strlcpy() and ft_strlcat() functions copy and concatenate
**		strings respectively.  They are designed to be safer, more consistent,
**		and less error prone replacements for strncpy(3) and strncat(3).
**		Unlike those functions, ft_strlcpy() and ft_strlcat() take the full
**		size of the buffer (not just the length) and guarantee to NUL-terminate
**		the result (as long as size is larger than 0 or, in the case of
**		ft_strlcat(), as long as there is at least one byte free in dst).
**		Note that a byte for the NUL should be included in size.  Also note that
**		ft_strlcpy() and ft_strlcat() only operate on true “C” strings.
**		This means that for ft_strlcpy() src must be NUL-terminated and for
**		ft_strlcat() both src and dst must be NUL-terminated.
**		The ft_strlcpy() function copies up to size - 1 characters from the
**		NUL-terminated string src to dst, NUL-terminating the result.
**		The ft_strlcat() function appends the NUL-terminated string src to the
**		end of dst. It will append at most size - strlen(dst) - 1 bytes,
**		NUL-terminating the result.
**	RETURN VALUES
**		The ft_strlcpy() and ft_strlcat() functions return the total length
**		of the string they tried to create.
**		For strlcpy() that means the length of src. For ft_strlcat() that means
**		the initial length of dst plus the length of src. While this may seem
**		somewhat confusing, it was done to make truncation detection simple.
**
**		Note, however, that if ft_strlcat() traverses size characters without
**		finding a NUL, the length of the string is considered to be size and the
**		destination string will not be NUL-terminated (since there was no space
**		for the NUL).  This keeps ft_strlcat() from running off the end of a
**		string.  In practice this should not happen (as it means that either
**		size is incorrect or that dst is not a proper “C” string). The check
**		exists to prevent potential security problems in incorrect code.
*/
unsigned int	ft_strlcat( char *dst, const char *src, unsigned int size);

/*
**ft_strlcpy -- size-bounded string copying
**
**	DESCRIPTION
**		The ft_strlcpy() and ft_strlcat() functions copy and concatenate
**		strings respectively.  They are designed to be safer, more consistent,
**		and less error prone replacements for strncpy(3) and strncat(3).
**		Unlike those functions, ft_strlcpy() and ft_strlcat() take the full
**		size of the buffer (not just the length) and guarantee to NUL-terminate
**		the result (as long as size is larger than 0 or, in the case of
**		ft_strlcat(), as long as there is at least one byte free in dst).
**		Note that a byte for the NUL should be included in size.  Also note that
**		ft_strlcpy() and ft_strlcat() only operate on true “C” strings.
**		This means that for ft_strlcpy() src must be NUL-terminated and for
**		ft_strlcat() both src and dst must be NUL-terminated.
**		The ft_strlcpy() function copies up to size - 1 characters from the
**		NUL-terminated string src to dst, NUL-terminating the result.
**		The ft_strlcat() function appends the NUL-terminated string src to the
**		end of dst. It will append at most size - strlen(dst) - 1 bytes,
**		NUL-terminating the result.
**	RETURN VALUES
**		The ft_strlcpy() and ft_strlcat() functions return the total length
**		of the string they tried to create.
**		For strlcpy() that means the length of src. For ft_strlcat() that means
**		the initial length of dst plus the length of src. While this may seem
**		somewhat confusing, it was done to make truncation detection simple.
**
**		Note, however, that if ft_strlcat() traverses size characters without
**		finding a NUL, the length of the string is considered to be size and the
**		destination string will not be NUL-terminated (since there was no space
**		for the NUL).  This keeps ft_strlcat() from running off the end of a
**		string.  In practice this should not happen (as it means that either
**		size is incorrect or that dst is not a proper “C” string). The check
**		exists to prevent potential security problems in incorrect code.
*/
unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int size);

/*
**ft_strlen -- calculate the length of a string
**
**	DESCRIPTION
**		The ft_strlen() function calculates the length of the string pointed to
**		by s, excluding the terminating null byte ('\0').
**	RETURN VALUE
**		The ft_strlen() function returns the number of bytes in the string
**		pointed to by s.
*/
unsigned int	ft_strlen(const char *s);

/*
**ft_strmapi
**
**	PARAMETERS
**		s: The string on which to iterate.
**		f: The function to apply to each character.
**	DESCRIPTION
**		Applies the function ’f’ to each character of the
**		string ’s’ to create a new string (with malloc(3))
**		resulting from successive applications of ’f’.
**	RETURN VALUE
**		The string created from the successive applications
**		of ’f’. Returns NULL if the allocation fails.
*/
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*
**ft_strncmp -- compare two strings
**
**	DESCRIPTION
**		The strcmp() function compares the two strings s1 and s2.
**		The comparison is done using unsigned characters.
**		strcmp() returns an integer indicating the result of the
**		comparison, as follows:
**		• 0, if the s1 and s2 are equal;
**		• a negative value if s1 is less than s2;
**		• a positive value if s1 is greater than s2.
**		The  ft_strncmp() function is similar, except it compares
**		only the first (at most) n bytes of s1 and s2.
**	RETURN VALUE
**		The strcmp() and ft_strncmp() functions return an integer
**		less than, equal to, or greater than zero if s1 (or the first n
**		bytes thereof) is found, respectively, to be less than, to match,
**		or be greater than s2.
*/
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);

/*
**ft_strnstr -- locate a substring in a string
**
**	DESCRIPTION
**		The ft_strnstr() function locates the first occurrence of the
**		null-terminated string little in the string big, where not more
**		than len characters are searched.  Characters that appear after
**		a ‘\0’ character are not searched.
**	RETURN VALUES
**		If little is an empty string, big is returned; if little occurs
**		nowhere in big, NULL is returned; otherwise a pointer to the first
**		character of the first occurrence of little is returned.
*/
char			*ft_strnstr(const char *s1, const char *s2, unsigned int len);

/*
**ft_strrchr -- locate character in string
**
**	DESCRIPTION
**		The ft_strrchr() function returns a pointer to the last occurrence
**		of  the  character  c  in  the string s.
**		Here "character" means "byte"; these functions do not work with wide
**		or multibyte characters.
**	RETURN VALUE
**		The ft_strrchr() function returns a pointer to the matched character
**		or NULL if the character is not found. The terminating null byte is
**		considered part of the string, so that if c is specified as '\0',
**		these functions return a pointer to the terminator.
*/
char			*ft_strrchr(const char *s, int c);

/*
**ft_strtrim
**
**	PARAMETERS
**		s1: The string to be trimmed.
**		set: The reference set of characters to trim.
**	DESCRIPTION
**		Allocates (with malloc(3)) and returns a copy of
**		’s1’ with the characters specified in ’set’ removed
**		from the beginning and the end of the string.
**	RETURN VALUE
**		The trimmed string. NULL if the allocation fails.
*/
char			*ft_strtrim(char const *s1, char const *set);

/*
**ft_substr
**
**	PARAMETERS
**	s: The string from which to create the substring.
**	start: The start index of the substring in the string ’s’.
**	len: The maximum length of the substring.
**	DESCRIPTION
**		Allocates (with malloc(3)) and returns a substring
**		from the string ’s’.
**		The substring begins at index ’start’ and is of
**		maximum size ’len’.
**	RETURN VALUE
**		The substring. NULL if the allocation fails.
*/
char			*ft_substr(char const *s, unsigned int start, unsigned int len);

/*
**ft_tolower, ft_toupper -- convert uppercase or lowercase
**
**	DESCRIPTION
**		These functions convert lowercase letters to uppercase,
**		and vice versa.
**		If c is a lowercase letter, ft_toupper() returns its uppercase
**		equivalent, if an uppercase representation exists in the current
**		locale.  Otherwise, it returns  c.
**		If  c is an uppercase letter, ft_tolower() returns its lowercase
**		equivalent, if a lowercase representation exists in the current
**		locale.  Otherwise, it returns  c.
**		If c is neither an unsigned char value nor EOF, the behavior of these
**		functions is undefined.
**	RETURN VALUE
**		The value returned is that of the converted letter, or c if the
**		conversion was not possible.
*/
int				ft_tolower(int c);

/*
**ft_toupper, ft_tolower -- convert uppercase or lowercase
**
**	DESCRIPTION
**		These functions convert lowercase letters to uppercase,
**		and vice versa.
**		If c is a lowercase letter, ft_toupper() returns its uppercase
**		equivalent, if an uppercase representation exists in the current
**		locale.  Otherwise, it returns  c.
**		If  c is an uppercase letter, ft_tolower() returns its lowercase
**		equivalent, if a lowercase representation exists in the current
**		locale.  Otherwise, it returns  c.
**		If c is neither an unsigned char value nor EOF, the behavior of these
**		functions is undefined.
**	RETURN VALUE
**		The value returned is that of the converted letter, or c if the
**		conversion was not possible.
*/
int				ft_toupper(int c);

/*
**ft_lstadd_back
**
**	PARAMETERS
**		lst: The address of a pointer to the first link of a list.
**		new: The address of a pointer to the element to be added to the list.
**	DESCRIPTION
**		Adds the element ’new’ at the end of the list.
**	RETURN VALUE
**		None
*/
void			ft_lstadd_back(t_list **lst, t_list *new);

/*
**ft_lstadd_front
**
**	PARAMETERS
**		lst: The address of a pointer to the first link of a list.
**		new: The address of a pointer to the element to be added to the list.
**	DESCRIPTION
**		Adds the element ’new’ at the beginning of the list.
**	RETURN VALUE
**		None
*/
void			ft_lstadd_front(t_list **lst, t_list *new);

/*
**ft_lstclear
**
**	PARAMETERS
**		lst: The adress of a pointer to an element.
**		del: The adress of the function used to delete the content of the
**		element.
**	DESCRIPTION
**		Deletes and frees the given element and every
**		successor of that element, using the function ’del’	and free(3).
**		Finally, the pointer to the list must be set to NULL.
**	RETURN VALUE
**		None
*/
void			ft_lstclear(t_list **lst, void (*del)(void*));

/*
**ft_lstdelone
**
**	PARAMETERS
**		lst: The element to free.
**		del: The address of the function used to delete the content.
**	DESCRIPTION
**		Takes as a parameter an element and frees the
**		memory of the element’s content using the function
**		’del’ given as a parameter and free the element.
**		The memory of ’next’ must not be freed.
**	RETURN VALUE
**		None
*/
void			ft_lstdelone(t_list *lst, void (*del)(void *));

/*
**ft_lstiter
**
**	PARAMETERS
**		lst: The adress of a pointer to an element.
**		f: The adress of the function used to iterate on the list.
**	DESCRIPTION
**		Iterates the list ’lst’ and applies the function
**		’f’ to the content of each element.
**	RETURN VALUE
**		None
*/
void			ft_lstiter(t_list *lst, void (*f)(void *));

/*
**ft_lstlast
**
**	PARAMETERS
**		lst: The beginning of the list.
**	DESCRIPTION
**		Returns the last element of the list.
**	RETURN VALUE
**		Last element of the list.
*/
t_list			*ft_lstlast(t_list *lst);

/*
**ft_lstmap
**
**	PARAMETERS
**		lst: The adress of a pointer to an element.
**		f: The adress of the function used to iterate on the list.
**		del: The adress of the function used to delete the content
**		of an element if needed.
**	DESCRIPTION
**		Iterates the list ’lst’ and applies the function
**		’f’ to the content of each element. Creates a new
**		list resulting of the successive applications of
**		the function ’f’. The ’del’ function is used to
**		delete the content of an element if needed.
**	RETURN VALUE
**		The new list. NULL if the allocation fails.
*/
t_list			*ft_lstmap(t_list *lst, \
void *(*f)(void *), void (*del)(void *));

/*
**ft_lstnew
**
**	PARAMETERS
**		content: The content to create the new element with.
**	DESCRIPTION
**		Allocates (with malloc(3)) and returns a new
**		element. The variable ’content’ is initialized
**		with the value of the parameter ’content’. The
**		variable ’next’ is initialized to NULL.
**	RETURN VALUE
**		The new element.
*/
t_list			*ft_lstnew(void *content);

/*
**ft_lstsize
**
**	PARAMETERS
**		lst: The beginning of the list.
**	DESCRIPTION
**		Counts the number of elements in a list.
**	RETURN VALUE
**		Length of the list.
*/
int				ft_lstsize(t_list *lst);

/*
**ft_freestr
**
**	PARAMETERS
**		str: address of the pointer to the memory to free.
**	DESCRIPTION
**		free a string pointer (type char*) and reset it to NULL.
*/
void			ft_freestr(char **str);

/*
**ft_freesplit
***Deprecated** - This function does not actually reset to NULL
**				the pointer **str after freeing it.
**				Please use ft_free2str().
**	PARAMETERS
**		str: the pointer to free.
**	DESCRIPTION
**		free a double pointer (type char**) so specificly
**		the pointer returned by ft_split().
*/
void			ft_freesplit(char **str);

/*
**ft_free2str
**
**	PARAMETERS
**		str: address of the pointer to the memory to free.
**	DESCRIPTION
**		free a double pointer (type char**) so specificly
**		the pointer returned by ft_split() and reset it to NULL.
*/
void			ft_free2str(char ***str);

#endif
