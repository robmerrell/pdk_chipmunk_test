#include "SDL.h"
#include "SDL_Image.h"
#include "chipmunk/chipmunk.h"
#include <iostream>
#include <vector>

using namespace std;

const float FRAMES_PER_SECOND = 60.0;

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 480;

const int GRAVITY = 600; // gravity strength

// making these a global because I'm lazy
SDL_Surface *screen;
vector <SDL_Surface*> balls;

// update a shape's visual representation
void updateShape(void *ptr, void* unused) {
  cpShape *shape = (cpShape*)ptr;
  
  // make sure the shape is constructed correctly
  if(shape == NULL || shape->body == NULL || shape->data == NULL) {
    return;
  }
  
  SDL_Surface *ball = (SDL_Surface*)shape->data;

  // Use a temporary rectangle to pass our x and y to the offsets when blitting
  SDL_Rect offset;
  offset.x = shape->body->p.x;
  offset.y = shape->body->p.y;
  
  SDL_BlitSurface(ball, NULL, screen, &offset);
}


int main(int argc, char* argv[]) {
  bool in_loop = true;
  
  // SDL setup
  SDL_Init(SDL_INIT_EVERYTHING);
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0);
  if (screen == NULL) return -1;
  SDL_Event event;
  
  // chipmunk setup
  cpSpace *space;
  cpBody *body;
  cpBody *borderBody; // body for the border around the outer edges of the screen
  
  cpInitChipmunk();
  space = cpSpaceNew();
  space->iterations = 10;
  space->gravity = cpv(0, GRAVITY);

  // gameloop
  while (in_loop) {
    // capture the events and send the relevent tap events to the game scene
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        in_loop = false;
        
      else if (event.type == SDL_MOUSEBUTTONDOWN) {
        SDL_Surface *ball = IMG_Load("assets/ball.png");
        
        body = cpBodyNew(10.0f, INFINITY);
        body->p = cpv(event.motion.x, event.motion.y);
        cpSpaceAddBody(space, body);
        
        cpShape *shape = cpSpaceAddShape(space, cpCircleShapeNew(body, 20.0, cpvzero));
        shape->e = 0.3f;
        shape->u = 0.7f;
        shape->data = ball;
      }
    }

    // recalculate the physics objects
    cpSpaceStep(space, 1.0f/FRAMES_PER_SECOND);
    cpSpaceHashEach(space->activeShapes, &updateShape, NULL);

    // update the display
    SDL_Flip(screen);
    
    // cap the framerate
    
  }
  
  SDL_Quit();
  
  return 0;
}