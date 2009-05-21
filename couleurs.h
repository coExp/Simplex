/*******************************************************************************

    Change la couleur du text en ligne de commande.
    Deux version : Windows et Linux/Unix
    
*******************************************************************************/

#ifdef WIN32

    #include <windows.h>
    #define textcolor(color) \
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)

	#define BLACK    textcolor( 0 );
	#define RED      textcolor( 12 );
	#define GREEN    textcolor( 2 );
	#define YELLOW   textcolor( 14 );
	#define BLUE     textcolor( 9 );
	#define PURPLE   textcolor( 13 );
	#define CYAN     textcolor( 11 );
	#define GREY     textcolor( 8 );
    #define DEFAULT_COLOR textcolor( 7 );

#else

    #ifndef BG_LIGHT
    	#define BLACK    printf("\033[1;30m");
    	#define RED      printf("\033[1;31m");
    	#define GREEN    printf("\033[1;32m");
    	#define YELLOW   printf("\033[1;33m");
    	#define BLUE     printf("\033[1;34m");
    	#define PURPLE   printf("\033[1;35m");
    	#define CYAN     printf("\033[1;36m");
    	#define GREY     printf("\033[1;37m");
    #else // else BG_LIGHT
    	#define BLACK    printf("\033[0;30m");
    	#define RED      printf("\033[0;31m");
    	#define GREEN    printf("\033[0;32m");
    	#define YELLOW   printf("\033[0;33m");
    	#define BLUE     printf("\033[0;34m");
    	#define PURPLE   printf("\033[0;35m");
    	#define CYAN     printf("\033[0;36m");
    	#define GREY     printf("\033[0;37m");
    #endif // endif BG_LIGHT

    #define DEFAULT_COLOR printf("\033[0;m");
    
#endif
