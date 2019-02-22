#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define SCREEN_WIDTH    1600
#define SCREEN_HEIGHT   900

#define ACCEL 0.3
#define MAX_ACCEL 1

#define ACCEL_SCALE_DOWN 0.001 

#define ABS(x) x < 0 ? x * -1 : x
//TODO refactor these structs into separate files and folders in order to clean up
typedef struct Entity{
    double x;
    double y;
    double z;
   
    double x_vel;
    double y_vel;
    double z_vel;

    double x_accel;
    double y_accel;
    double z_accel;

    double x_angle; //yaw; 
    double y_angle; //pitch;
    double z_angle; //rotation;

    double x_angle_vel; 
    double y_angle_vel; 
    double z_angle_vel; 

    double x_angle_accel;
    double y_angle_accel;
    double z_angle_accel;

    //Basic Hit Box
    double width;
    double height;
    double depth;
 
    size_t color;
    SDL_Rect * surface;
}Entity;



//TODO change to std::vector
void update(Entity* ents, size_t num_ents){

}

//TODO change to std::vector
void draw(Entity* ents, size_t num_ents){

}

int main(int argc, char* args[]){
    // INIT
    SDL_Window * win = NULL;
    SDL_Surface * screenSurf = NULL;
    SDL_Renderer * renderer = NULL;

    Entity player;
    player.x=0.0;
    player.y=0.0;
    player.z=0.0;
   
    player.x_vel=0.0;
    player.y_vel=0.0;
    player.z_vel=0.0;

    player.x_accel=0.0;
    player.y_accel=0.0;
    player.z_accel=0.0;

    player.x_angle =0.0; 
    player.y_angle =0.0;
    player.z_angle =0.0;

    player.x_angle_vel=0.0;
    player.y_angle_vel=0.0;
    player.z_angle_vel=0.0;

    player.x_angle_accel=0.0;
    player.y_angle_accel=0.0;
    player.z_angle_accel=0.0;

    player.width=0.0;
    player.height=0.0;
    player.depth=0.0;
 
    player.color=0;
    player.surface=NULL;   

    SDL_Rect srcrect;
    player.surface = &srcrect;
    player.surface->x = 0;
    player.surface->y = 0;
    player.surface->w = 32;
    player.surface->h = 32;
   

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("err @ SDL Init");
    }
    else
    {
        win = SDL_CreateWindow("FPS Engine - [Fausto Tommasi (TM)]", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(!win)
        {
            printf("err @ SDL create window");
        }
        else
        {
            renderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
            SDL_Event events;
            SDL_PollEvent(&events);
            player.x = SCREEN_WIDTH/2.0;
            player.y = SCREEN_HEIGHT/2.0;
            while(events.type != SDL_QUIT)
            {
                //UPDATE SECTION
                
                #define DEBUG 0
                 //User presses a key
                if(events.type == SDL_KEYDOWN ) 
                { 
                    //Select surfaces based on key press 
                    switch(events.key.keysym.sym ) 
                    { 
                        case SDLK_UP: 
                            player.y_accel = ABS(player.y_accel) < MAX_ACCEL ? player.y_accel -= ACCEL : -1 * MAX_ACCEL;
                            break; 
                        case SDLK_DOWN: 
                            player.y_accel = ABS(player.y_accel) < MAX_ACCEL ? player.y_accel += ACCEL :  MAX_ACCEL;
                            break;
                        case SDLK_LEFT:
                            player.x_accel = ABS(player.x_accel) < MAX_ACCEL ? player.x_accel -= ACCEL : -1 * MAX_ACCEL;
                            break; 
                        case SDLK_RIGHT:
                            player.x_accel = ABS(player.x_accel) < MAX_ACCEL ? player.x_accel += ACCEL : MAX_ACCEL;
                            break; 
                        case SDLK_r:
                            player.x_accel=0.0;
                            player.y_accel=0.0;
                            player.surface->x = 0;
                            player.surface->y = 0;                        
                        default:
                            player.x_accel *= ACCEL_SCALE_DOWN;
                            player.y_accel *= ACCEL_SCALE_DOWN;
                            break; 
                    }
                }
                
                player.surface->x += player.x_accel;
                player.surface->y += player.y_accel;
                
                //RENDER SECTION
                const size_t buffersize = 50;
                char debug_string [buffersize*4];

                sprintf(debug_string, "x:  %f\n",player.surface->x);
                sprintf(debug_string, "y:  %f\n",player.surface->y);
                sprintf(debug_string, "dx: %f\n",player.x_accel);
                sprintf(debug_string, "dy: %f\n",player.y_accel);

                TTF_Font * Sans = TTF_OpenFont("Sans.ttf",24);
                SDL_Color White = {0xFF,0xFF,0xFF};

                SDL_Surface * sur_msg = TTF_RenderText_Solid(Sans,debug_string,White); 
                SDL_Texture * Message = SDL_CreateTextureFromSurface(renderer,sur_msg);

                SDL_Rect msg_rct;

                msg_rct.x = SCREEN_WIDTH - 210;
                msg_rct.y = SCREEN_HEIGHT + 10;
                msg_rct.w = SCREEN_WIDTH - 10;
                msg_rct.h = SCREEN_HEIGHT + 210;

                SDL_RenderCopy(renderer,Message,NULL,&msg_rct);
                
                screenSurf = SDL_GetWindowSurface(win);
                SDL_FillRect(screenSurf,NULL,SDL_MapRGB(screenSurf->format,0xAA,0xBB,0xDD));
                SDL_FillRect(screenSurf,player.surface,SDL_MapRGB(screenSurf->format,0xFF,0x00,0x00));
                SDL_UpdateWindowSurface(win);
                SDL_PollEvent(&events);
            }
            
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0; //dork    
}