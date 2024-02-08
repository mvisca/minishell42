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
		errors_syntax(&ms);

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

		// exit temporal para probar leaks
		if (ft_strnstr(ms.line, "exit", 4))	
		{
			ft_printf("exit\n");
			break ;
		}	
		free(ms.line);
	}
	// clean all memory; 
		// linked list env
		// linked list tokens ??
		// esta de limpiar se llama también dentro de la ejecución de un
	utils_free_ms(&ms);
	return (0);
}