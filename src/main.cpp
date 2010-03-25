#include "SDL.h"
#include <GLES/gl.h>

#include "chipmunk/chipmunk.h"
#include "chipmunk/drawSpace.h"

cpSpace *space;
cpBody *staticBody;
SDL_Event event;

int main(int argc, char* argv[]) {
  // SDL setup
  int error = SDL_Init(SDL_INIT_VIDEO); 
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
  SDL_SetVideoMode(320, 480, 0, SDL_OPENGL); 
  
  
  // opengl setup
  glClearColor(0, 0, 0, 0); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrthof(0, 320, 480, 0, -1, 1);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glEnableClientState(GL_VERTEX_ARRAY);


  bool in_loop = true;
  int mouse_x, mouse_y = 0;

  while (in_loop) {
    // fps.start();

    // capture the events and send the relevent tap events to the game scene
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        in_loop = false;
    }

    // move
    cpSpaceStep(space, 1.0f/60.f);
    // cpSpaceHashEach(space->activeShapes, &updateShape, NULL);

    // clear display
    glClear(GL_COLOR_BUFFER_BIT);

    // display
    // drawSpaceOptions options = {0,0,1,4.0f,0.0f,1.5f,};
    // drawSpace(space, &options);
    
    // update the screen
    SDL_GL_SwapBuffers();

    // frame++;

    // delay to have a consistent framerate
    // if (fps.get_ticks() < 1000 / ticks_per_sec) {
    //   SDL_Delay((1000/ticks_per_sec) - fps.get_ticks());
    // }
  }
  


  SDL_Quit();

  return 0;
}
