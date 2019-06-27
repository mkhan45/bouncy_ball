#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

const int SPEED = 10;
const float RADIUS = 10.0;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

struct point{
    float x;
    float y;
};

struct ball{
    struct point pos;
    struct point vel;
};

int main(){
    struct point pos;
    pos.x = SCREEN_WIDTH/2;
    pos.y = SCREEN_HEIGHT/2;

    struct point vel;
    vel.x  = rand() % SPEED;
    vel.y  = rand() % SPEED;

    struct ball Ball;
    Ball.pos = pos;
    Ball.vel = vel;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
    else{
        window = SDL_CreateWindow("SDL Window",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN);
        if (window == NULL){
            printf("Error creating window: %s\n", SDL_GetError());
        }else{//SDL Initialized correctly
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            int count = 0;
            
            while(count < 1000){

                if (Ball.pos.x + RADIUS/2 >= SCREEN_WIDTH || Ball.pos.x - RADIUS/2 <= 0) {Ball.vel.x *= -1;}
                if (Ball.pos.y + RADIUS/2 >= SCREEN_HEIGHT || Ball.pos.y - RADIUS/2 <= 0) {Ball.vel.y *= -1;}

                Ball.pos.x += Ball.vel.x;
                Ball.pos.y += Ball.vel.y;

                filledCircleRGBA(renderer, Ball.pos.x, Ball.pos.y, RADIUS, 255, 255, 255, 255);

                SDL_RenderPresent(renderer);
                SDL_UpdateWindowSurface(window);

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                //remaining time goes into time2 but doesn't get used
                struct timespec time;
                struct timespec time2;
                time.tv_sec = 0;
                time.tv_nsec = 16666670;
                nanosleep(&time, &time2);

                count++;
            }
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
