#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Définition de la structure de liste
typedef struct s_list
{
	void *content; // Contenu de l'élément de la liste
	struct s_list *next; // Pointeur vers l'élément suivant de la liste
}		t_list;

// Création d'un nouvel élément de liste
t_list *ft_lstnew(char *content)
{
	t_list	*newlst; // Déclaration d'un nouvel élément de liste

	newlst = malloc(sizeof(t_list)); // Allocation de mémoire pour le nouvel élément
	if (newlst == NULL) // Si l'allocation échoue, retourner NULL
		return (NULL);
	newlst ->content = content; // Affectation du contenu à l'élément
	newlst->next = NULL; // Initialisation du pointeur suivant à NULL
	return (newlst); // Retourner le nouvel élément
}

// Ajout d'un élément au début de la liste
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new) // Si la liste et le nouvel élément existent
	{
		new->next = *lst; // Le nouvel élément pointe vers le premier élément de la liste
		*lst = new; // Le nouvel élément devient le premier de la liste
	}
}

// Récupération du dernier élément de la liste
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst) // Si la liste est vide, retourner NULL
		return (NULL);
	while (lst->next) // Tant que l'élément suivant existe
	{
		lst = lst->next; // Passer à l'élément suivant
	}
	return (lst); // Retourner le dernier élément
}

// Ajout d'un élément à la fin de la liste
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lstlast; // Déclaration d'un pointeur vers le dernier élément
	if (!(*lst)) // Si la liste est vide
		*lst = new; // Le nouvel élément devient le premier (et le dernier) de la liste
	else if (lst && new) // Si la liste et le nouvel élément existent
	{
		lstlast = ft_lstlast(*lst); // Récupération du dernier élément de la liste
		lstlast->next = new; // Le dernier élément pointe vers le nouvel élément
	}
}

// Suppression d'un élément de la liste
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst) // Si l'élément existe
	{
		if (del) // Si la fonction de suppression existe
			del(lst->content); // Suppression du contenu de l'élément
		free(lst); // Libération de la mémoire de l'élément
	}
}

// Suppression de tous les éléments de la liste
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *next; // Déclaration d'un pointeur vers l'élément suivant

	next = (void *)0; // Initialisation du pointeur à NULL
	if (!lst && !del) // Si la liste et la fonction de suppression n'existent pas, retourner
		return ;
	while(*lst) // Tant que la liste existe
	{
		next = (*lst)->next; // Récupération de l'élément suivant
		ft_lstdelone(*lst, del); // Suppression de l'élément courant
		*lst = next; // Passage à l'élément suivant
	}
}

// Application d'une fonction à tous les éléments de la liste
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL && !f) // Si la liste est vide ou la fonction n'existe pas, retourner
		return ;
	while(lst) // Tant que la liste existe
	{
		f(lst->content); // Application de la fonction au contenu de l'élément
		lst = lst->next; // Passage à l'élément suivant
	}

}

// Création d'une nouvelle liste en appliquant une fonction à tous les éléments de la liste originale
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst; // Déclaration de la nouvelle liste
	t_list	*current; // Déclaration d'un pointeur vers l'élément courant
	char	*new_content;
	new_lst = NULL; // Initialisation de la nouvelle liste à NULL
	while(lst && f) // Tant que la liste et la fonction existent
	{
		new_content = strdup(f(lst->content));
		current = ft_lstnew(new_content); // Création d'un nouvel élément avec le contenu transformé
		if (!current) // Si la création de l'élément échoue
		{
			ft_lstclear(&new_lst, del); // Suppression de la nouvelle liste
			return (NULL); // Retourner NULL
		}
		ft_lstadd_front(&new_lst, current); // Ajout du nouvel élément au début de la nouvelle liste
		lst = lst->next; // Passage à l'élément suivant de la liste originale
	}
	return (new_lst); // Retourner la nouvelle liste
}

// Comptage du nombre d'éléments dans la liste
int	ft_lstsize(t_list *lst)
{
	int	lst_len; // Déclaration du compteur

	if (!lst) // Si la liste est vide, retourner 0
		return (0);
	lst_len = 0; // Initialisation du compteur à 0
	while(lst) // Tant que la liste existe
	{
		lst = lst->next; // Passage à l'élément suivant
		lst_len++;	// Incrémentation du compteur
	}
	return (lst_len); // Retourner le nombre d'éléme
}

void print_content(void *content)
{
    printf("%s\n", (char *)content);
}

int main()
{
    t_list *list = NULL;
    t_list *new_node;

    // Test ft_lstnew and ft_lstadd_front
    new_node = ft_lstnew("Hello");
    ft_lstadd_front(&list, new_node);

    new_node = ft_lstnew("World");
    ft_lstadd_front(&list, new_node);

    // Test ft_lstiter
    ft_lstiter(list, print_content);

    // Test ft_lstsize
    printf("List size: %d\n", ft_lstsize(list));

    // Test ft_lstlast
    t_list *last = ft_lstlast(list);
    printf("Last element: %s\n", (char *)last->content);

    // Test ft_lstadd_back
    new_node = ft_lstnew("!");
    ft_lstadd_back(&list, new_node);
    ft_lstiter(list, print_content);

    // Test ft_lstmap
    t_list *mapped_list = ft_lstmap(list, (void *(*)(void *))strdup, free);
    ft_lstiter(mapped_list, print_content);

    // Test ft_lstclear
    ft_lstclear(&list, free);
    ft_lstclear(&mapped_list, free);

    return 0;
}

