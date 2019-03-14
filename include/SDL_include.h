
/* - Como usar esse arquivo:
 *
 * Onde quiser adicionar, por exemplo, SDL_image e SDL_mixer em um arquivo, faça o seguinte e
 * ele incluirá elas automaticamente e de forma multiplataforma (se usar o makefile tbm fornecido).
 *
 * #define INCLUDE_SDL_IMAGE
 * #define INCLUDE_SDL_MIXER
 * #include "SDL_include.h"
 *
*/


/************************************************
*					SDL.h						*
*************************************************/
#ifdef INCLUDE_SDL 
	#ifdef _WIN32
		#include <SDL2/SDL.h>
	#elif __APPLE__
		#include "TargetConditionals.h"
		#include <SDL2/SDL.h>
	#elif __linux__
		#include <SDL2/SDL.h>
	#else
		#error "Unknown compiler"
	#endif
	#undef INCLUDE_SDL 
#endif // INCLUDE_SDL


/************************************************
*				 SDL_image.h					*
*************************************************/
#ifdef INCLUDE_SDL_IMAGE 
	#ifdef _WIN32
		#include <SDL2/SDL_image.h>
	#elif __APPLE__
		#include "TargetConditionals.h"
		#include <SDL2/SDL_image.h>
	#elif __linux__
		#include <SDL2/SDL_image.h>
	#else
		#error "Unknown compiler"
	#endif
	#undef INCLUDE_SDL_IMAGE 
#endif // INCLUDE_SDL_IMAGE


/************************************************
*				 SDL_mixer.h					*
*************************************************/
#ifdef INCLUDE_SDL_MIXER 
	#ifdef _WIN32
		#include <SDL2/SDL_mixer.h>
	#elif __APPLE__
		#include "TargetConditionals.h"
		#include <SDL2/SDL_mixer.h>
	#elif __linux__
		#include <SDL2/SDL_mixer.h>
	#else
		#error "Unknown compiler"
	#endif
	#undef INCLUDE_SDL_MIXER 
#endif // INCLUDE_SDL_MIXER


/************************************************
*				  SDL_ttf.h						*
*************************************************/
#ifdef INCLUDE_SDL_TTF 
	#ifdef _WIN32
		#include <SDL2/SDL_ttf.h>
	#elif __APPLE__
		#include "TargetConditionals.h"
		#include <SDL2/SDL_ttf.h>
	#elif __linux__
		#include <SDL2/SDL_ttf.h>
	#else
		#error "Unknown compiler"
	#endif
	#undef INCLUDE_SDL_TTF 
#endif // INCLUDE_SDL_TTF


/************************************************
*				  SDL_net.h						*
*************************************************/
#ifdef INCLUDE_SDL_NET 
	#ifdef _WIN32
		#include <SDL2/SDL_net.h>
	#elif __APPLE__
		#include "TargetConditionals.h"
		#include <SDL2/SDL_net.h>
	#elif __linux__
		#include <SDL2/SDL_net.h>
	#else
		#error "Unknown compiler"
	#endif
	#undef INCLUDE_SDL_NET 
#endif // INCLUDE_SDL_NET
