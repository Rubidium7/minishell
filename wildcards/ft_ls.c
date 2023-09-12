

#include "minishell.h"

static t_bool	sec_is_smaller(char *first, char *second)
{
	size_t	i;

	i = 0;
	while (first[i] && second[i] && first[i] == second[i])
		i++;
	if (second[i] < first[i])
		return (TRUE);
	return (FALSE);
}

static char	**sort_files(char **files)
{
	int		i;
	char	*tmp;

	i = 0;
	while (files[i])
	{
		if (files[i + 1] && sec_is_smaller(files[i], files[i + 1]))
		{
			tmp = files[i];
			files[i] = files[i + 1];
			files[i + 1] = tmp;
			i = 0;
			continue ;
		}
		i++;
	}
	return (files);
}

static char	**copy_files(char **files)
{
	struct dirent	*file_ptr;
	DIR				*dir;
	int				i;

	i = 0;
	dir = opendir(".");
	if (!dir)
		return (error_print(WILDCARD_ERROR), free(files), NULL);
	file_ptr = readdir(dir);
	while (file_ptr)
	{
		if (file_ptr->d_name[0] != '.')
		{
			files[i] = ft_strdup(file_ptr->d_name);
			if (!files[i])
				return (error_print(WILDCARD_ERROR),
					free_ar(files), closedir(dir), NULL);
			i++;
		}
		file_ptr = readdir(dir);
	}
	closedir(dir);
	return (sort_files(files));
}

char	**ft_ls(void)
{
	char			**files;
	int				size;
	struct dirent	*file_ptr;
	DIR				*dir;

	size = 0;
	dir = opendir(".");
	if (!dir)
		return (error_print(WILDCARD_ERROR), NULL);
	file_ptr = readdir(dir);
	while (file_ptr)
	{
		if (file_ptr->d_name[0] != '.')
			size++;
		file_ptr = readdir(dir);
	}
	closedir(dir);
	if (!size)
		return (NULL);
	files = malloc(sizeof(char *) * (size + 1));
	if (!files)
		return (error_print(WILDCARD_ERROR), NULL);
	files[size] = NULL;
	return (copy_files(files));
}