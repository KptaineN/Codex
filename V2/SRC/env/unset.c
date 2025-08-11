

/*

????????????????????????????????????????????

Ce que doit faire unset

unset VAR1 VAR2

→ Supprime une ou plusieurs variables de la liste d’environnement.
🧱 À implémenter dans unset.c
🔹 Fonction principale

int	ft_unset(t_env **env_list, char **args);

    Ignore args[0] (qui est "unset"), commence à args[1]

    Pour chaque VAR :

        Vérifie si c’est un identifiant valide

        Supprime le nœud t_env correspondant dans la liste

🔧 Fonctions utiles à coder

int	is_valid_identifier(const char *str);
void	remove_env_node(t_env **env, const char *key);

🧪 Exemple

unset PATH
→ supprime PATH de la liste

unset 1abc
→ erreur, nom invalide

🧼 Bonus : gestion des erreurs

    Si identifiant invalide :

        export 1abc=bad → export: '1abc': not a valid identifier

        unset 9VAR → unset: '9VAR': not a valid identifier+

*/