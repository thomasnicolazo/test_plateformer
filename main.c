#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>


//Screen dimension constants
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT  750



int main( int argc, char* args[] )
{

    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    // initialize character
    SDL_Surface* characterSurface = NULL;
    SDL_Surface* backgroundSurface = NULL;

    // init texture
    SDL_Texture* characterTexture =  NULL;
    SDL_Texture* backgroundTexture =  NULL;
    // init rend
    SDL_Renderer* rend = NULL;


    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        exit(1);
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            exit(2);
        }

        // triggers the program that controls
        // your graphics hardware and sets flags
        Uint32 render_flags = SDL_RENDERER_ACCELERATED;
        // creates a renderer to render our images
        SDL_Renderer* rend = SDL_CreateRenderer(window, -1, render_flags);
        if (!rend){
            printf("Error creating renderer: %s\n", SDL_GetError());
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(3);
        }
        backgroundSurface = SDL_LoadBMP("./texture/background/back.bmp");
        backgroundTexture = SDL_CreateTextureFromSurface(rend, backgroundSurface);

        characterSurface = SDL_LoadBMP("./texture/character/still.bmp");
        characterTexture = SDL_CreateTextureFromSurface(rend, characterSurface);
        SDL_UpdateWindowSurface( window );

        if(backgroundTexture==NULL){
            printf("background texture empty");
        }
        if(characterTexture==NULL){
            printf("chara texture empty");
        }

        // let us control our image position
        // so that we can move it with our keyboard.
        SDL_Rect dest;

        // connects our texture with dest to control position
        SDL_QueryTexture(characterTexture, NULL, NULL, &dest.w, &dest.h);

        // adjust height and width of our image box.
        dest.w /= 6;
        dest.h /= 6;

        // sets initial x-position of object
        dest.x = (1000 - dest.w) / 2;

        // sets initial y-position of object
        dest.y = (1000 - dest.h) / 2;

        // controls animation loop
        int close = 0;

        // speed of box
        int speed = 300;
// animation loop
    while (!close) {
        SDL_Event event;

        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;

            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    dest.y -= speed / 30;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    dest.x -= speed / 30;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    dest.y += speed / 30;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    dest.x += speed / 30;
                    break;
                default:
                    break;
                }
            }
        }

        // right boundary
        if (dest.x + dest.w > 1000)
            dest.x = 1000 - dest.w;

        // left boundary
        if (dest.x < 0)
            dest.x = 0;

        // bottom boundary
        if (dest.y + dest.h > 1000)
            dest.y = 1000 - dest.h;

        // upper boundary
        if (dest.y < 0)
            dest.y = 0;

        // clears the screen
        SDL_RenderClear(rend);
        //SDL_SetRenderDrawColor(rend, 120, 120, 120, 255);
        SDL_RenderCopy(rend, backgroundTexture, NULL, NULL);
        SDL_RenderCopy(rend,characterTexture,NULL,&dest);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);

        // calculates to 60 fps
        SDL_Delay(1000/60);
    }

        //SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

/*
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            renderBackground(screenSurface); //rendu arrière plan

            //Fill the surface white
            //SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

            //Update the surface
            SDL_UpdateWindowSurface( window );
            // recuperation de la surfece avec background
            screenSurface = SDL_GetWindowSurface( window );
            // init character
            Character *ptrPerso = initCharacter( 400, 300);
            printCharacter(ptrPerso);
            // display perso
            DisplayCharacter(ptrPerso, screenSurface);

            //Update the surface
            SDL_UpdateWindowSurface( window );
*/
            //Hack to get window to stay up
            //SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

        }

        // libération de la surface écran
        //SDL_FreeSurface(characterSurface);
        SDL_FreeSurface(screenSurface);
        SDL_FreeSurface(characterSurface);
        SDL_FreeSurface(backgroundSurface);
        // destroy texture
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyTexture(characterTexture);
        // destroy renderer
        SDL_DestroyRenderer(rend);
        //Destroy window
        SDL_DestroyWindow( window );

        //Quit SDL subsystems
        SDL_Quit();
        return 0;
    }
