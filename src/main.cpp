#include "PDL.h"
#include "SDL.h"
#include "SDL_image.h"
#include "chipmunk/headers/chipmunk.h"
#include <iostream>
#include <vector>

using namespace std;

const float FRAMES_PER_SECOND = 60.0;

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 480;
const int PADDING = 20;

const int GRAVITY = 600; // gravity strength

// making these global because I'm lazy
SDL_Surface *screen;
SDL_Surface *ball;

void updateShape(void*, void*);
void defineBorders(cpSpace*);

int main(int argc, char* argv[]) {
  bool in_loop = true;
  float xForce;                     
  float yForce;

  // create the file path to the ball image
  // Note: only get the PATH from PDL_GetCallingPath if on the device.  When building
  // from the desktop just hardcode the ball_path variable. PDL_GetCallingPath
  // only seems to work on the device.
  char app_dir[255];
  int ret = PDL_GetCallingPath(app_dir, 256);
  string ball_path(app_dir);
  ball_path.append("assets/ball.gif");

  // SDL setup
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0);
  if (screen == NULL) return -1;
  SDL_Event event;
  SDL_Joystick *joystick = SDL_JoystickOpen(0);
  ball = IMG_Load(ball_path.c_str());
  
  // chipmunk setup
  cpSpace *space;
  cpBody *body;
  
  cpInitChipmunk();
  space = cpSpaceNew();
  space->iterations = 10;
  space->elasticIterations = 10;
  space->gravity = cpv(0, GRAVITY);
  
  defineBorders(space);
  
  // gameloop
  while (in_loop) {
    // get data from the accelerometer
    xForce = (float) SDL_JoystickGetAxis(joystick, 0) / 32768.0;                     
    yForce = (float) SDL_JoystickGetAxis(joystick, 1) / 32768.0;
    
    space->gravity = cpv(xForce * GRAVITY, yForce * GRAVITY);
    
    // capture the events and send the relevent tap events to the game scene
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        in_loop = false;
        
      else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if ((event.motion.x > PADDING && event.motion.x < SCREEN_WIDTH - PADDING) &&
            (event.motion.y > PADDING && event.motion.y < SCREEN_HEIGHT - PADDING)) {
          body = cpBodyNew(10.0f, INFINITY);
          body->p = cpv(event.motion.x, event.motion.y);
          cpSpaceAddBody(space, body);
        
          cpShape *shape = cpSpaceAddShape(space, cpCircleShapeNew(body, 20.0, cpvzero));
          shape->e = 0.3f;
          shape->u = 0.1f;
        }
      }
    }

    // clear the screen
    SDL_FillRect(SDL_GetVideoSurface(), NULL, 0);

    // recalculate the physics objects
    cpSpaceStep(space, 1.0f/FRAMES_PER_SECOND);
    cpSpaceHashEach(space->activeShapes, &updateShape, NULL);
    
    // update the display
    SDL_Flip(screen);
  }
  
  // shutdown Chipmunk
  cpSpaceFreeChildren(space);
  cpSpaceFree(space);

  // shutdown SDL
  SDL_FreeSurface(ball);
  PDL_Quit();
  SDL_Quit();
  
  return 0;
}


// update a shape's visual representation
void updateShape(void *ptr, void* unused) {
  cpShape *shape = (cpShape*)ptr;
  
  // make sure the shape is constructed correctly
  if(shape == NULL || shape->body == NULL) {
    return;
  }
  
  // Use a temporary rectangle to pass our x and y to the offsets when blitting
  SDL_Rect offset;
  offset.x = shape->body->p.x;
  offset.y = shape->body->p.y;
  
  SDL_BlitSurface(ball, NULL, screen, &offset);
}


// create borders around the screen
void defineBorders(cpSpace *space) {
  cpBody *body = cpBodyNew(INFINITY, INFINITY);
  float border_elasticity = 0.3f;
  float border_friction = 1.0f;
  
  // top border
  cpShape *border_top = cpSegmentShapeNew(body, cpv(-PADDING, -PADDING), cpv(SCREEN_WIDTH - PADDING, -PADDING), 1.0f);
  border_top->e = border_elasticity; border_top->u = border_friction;
  cpSpaceAddStaticShape(space, border_top);
  
  // right border
  cpShape *border_right = cpSegmentShapeNew(body, cpv(SCREEN_WIDTH - PADDING, -PADDING), cpv(SCREEN_WIDTH - PADDING, SCREEN_HEIGHT - PADDING), 1.0f);
  border_right->e = border_elasticity; border_right->u = border_friction;
  cpSpaceAddStaticShape(space, border_right);
  
  // bottom border
  cpShape *border_bottom = cpSegmentShapeNew(body, cpv(-PADDING, SCREEN_HEIGHT - PADDING), cpv(SCREEN_WIDTH - PADDING, SCREEN_HEIGHT - PADDING), 1.0f);
  border_bottom->e = border_elasticity; border_bottom->u = border_friction;
  cpSpaceAddStaticShape(space, border_bottom);
  
  // left border
  cpShape *border_left = cpSegmentShapeNew(body, cpv(-PADDING, -PADDING), cpv(-PADDING, SCREEN_HEIGHT - PADDING), 1.0f);
  border_left->e = border_elasticity; border_left->u = border_friction;
  cpSpaceAddStaticShape(space, border_left);
}