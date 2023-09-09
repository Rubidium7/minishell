

#include "minishell.h"

char	*remove_string_section(char *str, int start, int end)
{
	int		size;
	char	*ans;
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	if (!str || start < 0 || end < 0 || end <= start
		|| (ft_strlen(str) - (end - start) < 0))
		return (str);
	size = ft_strlen(str) - (end - start);
	ans = malloc(sizeof(char) * (size + 1));
	if (!ans)
		return (free(str), NULL);
	while (str[i])
	{
		if (!(i >= start && i < end))
		{
			ans[i2] = str[i];
			i2++;
		}
		i++;
	}
	ans[i2] = '\0';
	return (free(str), ans);
}

void	add_content(char *str, int *i, char *content)
{
	int	i2;

	i2 = 0;
	while (content[i2])
	{
		str[*i] = content[i2];
		*i += 1;
		i2++;
	}
}

char	*add_string_to(char *str, char *content, int start)
{
	int		size;
	char	*ans;
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	if (!str || !ft_strlen(content) || start < 0)
		return (str);
	size = ft_strlen(str) + ft_strlen(content);
	ans = malloc(sizeof(char) * (size + 1));
	if (!ans)
		return (free(str), NULL);
	if (i == start)
		add_content(ans, &i2, content);
	while (str[i])
	{
		if (i == start)
			add_content(ans, &i2, content);
		ans[i2] = str[i];
		i2++;
		i++;
	}
	ans[i2] = '\0';
	return (free(str), ans);
}