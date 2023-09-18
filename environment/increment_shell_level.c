

#include "minishell.h"

t_bool	increment_shell_level(t_shell *core)
{
	char	*level;
	int		nb;
	t_bool	ret;

	level = fetch_env("SHLVL", core);
	if (!level)
		return (set_env("SHLVL", "1", core));
	nb = ft_atoi(level);
	free(level);
	nb++;
	if (nb < 0)
		nb = 0;
	level = ft_itoa(nb);
	if (!level)
		return (TRUE);
	ret = set_env("SHLVL", level, core);
	free(level);
	return (ret);
}