
#include "minishell.h"

char	*fetch_env(const char *key, t_shell *core)
{
	int	i;

	//should be changed, made it lazily to use for heredoc tmp file directory

	if (!core->env || !key)
		return (NULL);
	i = 0;
	while (core->env[i])
	{
		if (!ft_strncmp(key, core->env[i], ft_strlen(key))) //fucks up if similar keys like VAR & VAR1
		{
			if (core->env[i] + ft_strlen(key))
				return (ft_strdup(core->env[i] + ft_strlen(key) + 1));
			return (ft_strdup(core->env[i] + ft_strlen(key)));
		}
		i++;
	}
	return (NULL);
}