##############################################################################
#                                   VARIABLES                                 #
###############################################################################

PROJECT_DIR  := .
SRC_DIR      := $(PROJECT_DIR)/SRC
INC_DIR      := $(PROJECT_DIR)/include
SUBDIRS      := built env exec from_pipex handle_utils handle_utils/handler_cast_t_shell handle_utils/handler_operator main old_parser parser signal built/echo built/export

LIBFT_INC    := $(INC_DIR)/LIBFT
LIBFT_DIR    := $(INC_DIR)/LIBFT
LIBFT_A      := $(LIBFT_DIR)/libft.a

OBJ_DIR      := obj/
SRC_C        := $(foreach s,$(SUBDIRS),$(wildcard $(SRC_DIR)/$(s)/*.c))
ALL_C        := $(SRC_C)
ALL_OBJ      := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)%.o,$(ALL_C))
ALL_PATHS    := -I$(INC_DIR) -I$(LIBFT_INC)

CC           := cc

# FLAGS POUR RELEASE (par défaut)
RELEASE_FLAGS := -Wall -Wextra -Werror $(ALL_PATHS)
RELEASE_LDFLAGS := -lreadline

# FLAGS POUR DEBUG (avec AddressSanitizer & debug info)
DEBUG_FLAGS := -g -fsanitize=address -fno-omit-frame-pointer -Wall -Wextra -Werror $(ALL_PATHS)
DEBUG_LDFLAGS := -lreadline -fsanitize=address

# Sera changé dynamiquement par la cible 'debug'
CFLAGS   := $(RELEASE_FLAGS)
LDFLAGS  := $(RELEASE_LDFLAGS)

##############################################################################
#                                FONCTIONS                                   #
##############################################################################

define print_clean
	@if [ -d "$(OBJ_DIR)" ] && [ "$$(ls -A $(OBJ_DIR))" ]; then \
		echo "Suppression de tous les fichiers objets... 🧹"; \
		rm -rf $(OBJ_DIR); \
	else \
		echo "$(OBJ_DIR) déjà vide, rien à nettoyer ! ✨"; \
	fi
endef

##############################################################################
#                                   RÈGLES                                   #
##############################################################################

# Compilateur : .c → .o (dans OBJ_DIR)
$(OBJ_DIR)%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Libft
$(LIBFT_A):
	@echo "Vérification de libft..."
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "ERREUR : dossier $(LIBFT_DIR) introuvable"; exit 1; \
	fi
	@$(MAKE) -C "$(LIBFT_DIR)"

##############################################################################
#                                 CIBLES                                     #
##############################################################################

# CIBLE PAR DÉFAUT (release)
all: minishell

minishell: $(ALL_OBJ) $(LIBFT_A)
	@echo "Édition des liens pour minishell... 🚀"
	$(CC) $(CFLAGS) $(ALL_OBJ) $(LIBFT_A) -o $@ $(LDFLAGS)
	@echo "✅ Compilation terminée !"

# CIBLE DEBUG (mode debug)
debug: CFLAGS=$(DEBUG_FLAGS)
debug: LDFLAGS=$(DEBUG_LDFLAGS)
debug: fclean
	@echo "Compilation en mode DEBUG (AddressSanitizer + debug info)..."
	$(MAKE) minishell

# CLEAN
clean:
	$(call print_clean)

# FCLEAN (tout)
fclean: clean
	@if [ -f minishell ]; then \
		echo "Suppression de l'exécutable minishell... 💀"; \
		rm -f minishell; \
	else \
		echo "Aucun exécutable à supprimer ! 💤"; \
	fi

# FCLEAN ALL (libft inclus)
fclean-all: fclean
	@echo "Suppression de libft.a... 🧨"
	@$(MAKE) -C $(LIBFT_DIR) fclean

# REBUILD
re: fclean all

# HELP
help:
	@echo "------ [\033[1;36mMinishell Makefile\033[0m] ------"
	@echo "Cibles principales :"
	@echo "  make           : Compilation en mode release"
	@echo "  make debug     : Compilation avec AddressSanitizer et debug"
	@echo "  make clean     : Nettoie les fichiers objets (.o)"
	@echo "  make fclean    : Nettoie .o + exécutable"
	@echo "  make fclean-all: Nettoie .o + exe + libft.a"
	@echo "  make re        : Recompile tout (équivaut à fclean puis all)"
	@echo "  make help      : Affiche cette aide"
	@echo ""
	@echo "Astuce: './minishell' pour lancer le shell !"
	@echo "Astuce: 'make debug' pour traquer les SEGFAULTS 🔥"

##############################################################################
#                                DIVERS                                      #
##############################################################################

.PHONY: all debug clean fclean fclean-all re help
