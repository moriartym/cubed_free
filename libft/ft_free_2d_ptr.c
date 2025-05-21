#include "libft.h"

void ft_free_2d_ptr(void ***ptr, int y)
{
    int i;

    if (!ptr || !*ptr)
        return;
    i = 0;
    while (i < y)
    {
        if ((*ptr)[i])
            free((*ptr)[i]);
        i++;
    }
    free(*ptr);
    *ptr = NULL;
}