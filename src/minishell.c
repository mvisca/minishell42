#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;

	initialize(&ms, ac, av, envp);
/*	manejador de señales para evitar salir con 
		ctrl + c
		ctrol + \
		ctrol + D
		revisar	*/
	while (1)
	{
		interface_get_line(&ms);
		printf("Ha ingresado: %s\n", ms.line);

		// LEXER
		// PARSER
			// recibe t_lex y crea t_cmd
			// deja t_lex limpio y vacío
			// 
		// EXECUTOR
			// la siguiente líneas es temporar
			// terminal minishell
			// será parte del manejo de comandos
				// exit es una especie de "builtin"?
					// en este caso debe limpiar memoria
				// exit es un comando que a través de execv?
			// bucle de pipes
				// EXPANDER
					// antes de enviar a ejecutar se expande
				// FILEDESCRIPTORS
					// antesde enviar a ejecutar 
				// envía a ejecutar

		if (ft_strnstr(ft_strtrim(ms.line, " \t"), "exit", 4))
			break ;
	}
	// clean all memory; 
		// linked list env
		// linked list tokens ??
		// esta de limpiar se llama también dentro de la ejecución de un 
	return (0);
}
