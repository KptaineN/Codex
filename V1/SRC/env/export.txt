

/*

?????????????????????????????????????

 implémenter dans export.c
🔹 Fonction principale

int	ft_export(t_env **env_list, char **args);

    env_list → pointeur vers la liste des variables d’environnement

    args → tableau des arguments (args[0] = "export", args[1] = "VAR=42", etc.)

🔧 Étapes pour ft_export

    Si args[1] est NULL → afficher l’environnement (print_export)

    Sinon → pour chaque args[i] :

        Vérifie que c’est un identifiant valide (ex: pas 1abc=val)

        Si = présent :

            si la variable existe → mettre à jour value

            sinon → ajouter nouvelle variable

        Si pas de = → créer la variable avec valeur NULL si elle n’existe pas

🔨 Fonctions utiles à coder

void	print_export(t_env *env);
int		is_valid_identifier(const char *str);
void	add_or_update_env(t_env **env, const char *key, const char *value);
char	*get_key(const char *str);
char	*get_value(const char *str);

🧪 Exemples

export
→ declare -x PATH="/usr/bin"
  declare -x USER="noe"

export NEWVAR=hello
→ ajoute NEWVAR

export PATH=/new/path
→ remplace la valeur
*/