#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#define SCREEN_WIDTH    1600
#define SCREEN_HEIGHT   900

#define ACCEL 1

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
    SDL_Surface * surface;
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
    SDL_Rect dstrect;

    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = 32;
    srcrect.h = 32;
   
    dstrect.x = 640/2;
    dstrect.y = 480/2;
    dstrect.w = 32;
    dstrect.h = 32;




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
            SDL_Event events;
            SDL_PollEvent(&events);
            player.x = SCREEN_WIDTH/2.0;
            player.y = SCREEN_HEIGHT/2.0;
            while(events.type != SDL_QUIT)
            {
                #define DEBUG 0
                 //User presses a key
                if(events.type == SDL_KEYDOWN ) 
                { 
                    //Select surfaces based on key press 
                    switch(events.key.keysym.sym ) 
                    { 
                        case SDLK_UP: 
                            srcrect.y -= ACCEL;
                            #if DEBUG
                            printf("up");
                            #endif
                            break; 
                        case SDLK_DOWN: 
                            srcrect.y += ACCEL;
                            #if DEBUG
                            printf("down");
                            #endif
                            break;
                        case SDLK_LEFT: 
                            #if DEBUG
                            printf("left");
                            #endif
                            srcrect.x -= ACCEL;
                            break; 
                        case SDLK_RIGHT:
                            #if DEBUG
                            printf("right");
                            #endif
                            srcrect.x += ACCEL;
                            break; 
                        default: 
                            break; 
                    }
                }
                screenSurf = SDL_GetWindowSurface(win);
                SDL_FillRect(screenSurf,NULL,SDL_MapRGB(screenSurf->format,0xAA,0xBB,0xDD));
                SDL_FillRect(screenSurf,&srcrect,SDL_MapRGB(screenSurf->format,0xFF,0x00,0x00));
                SDL_UpdateWindowSurface(win);
                SDL_PollEvent(&events);
            }
            
        }
    }
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0; //dork    
}