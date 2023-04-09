// Bryn Mawr College, alinen, 2020
//

#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"

using namespace std;
using namespace glm;
using namespace agl;

class Viewer : public Window {
public:
  Viewer() : Window() {
  }

  void setup() {
    setWindowSize(1000, 1000);
    renderer.loadShader("billboard-animated", 
      "../shaders/billboard-animated.vs", 
      "../shaders/billboard-animated.fs");

    renderer.loadTexture("fire", "../textures/ParticleFlamesSheet.png", 0);
    renderer.setDepthTest(false);
    renderer.blendMode(agl::ADD);
  }

  void updateFire() {
    float miniTransp = transp;
    float miniMoveUp = moveUp;

    for (int i = 0; i < 5; i++) {
        renderer.sprite(vec3(0.0, miniMoveUp, 0.0), vec4(1.0f, 1.0f, 1.0f, miniTransp), 1.0);
        miniTransp += 0.05;
        miniMoveUp -= 0.005;
    }
  }

  void mouseMotion(int x, int y, int dx, int dy) {
  }

  void mouseDown(int button, int mods) {
  }

  void mouseUp(int button, int mods) {
  }

  void scroll(float dx, float dy) {
    eyePos.z += dy;
  }

  void draw() {
    renderer.beginShader("billboard-animated");
    renderer.texture("image", "fire");

    // 10 fps => each frame 1/10 long, e.g. when time = 1s, we play frame 10
    int numFrames = elapsedTime() * 10; // Finds current frame based on time
    int uniqueFrames = numRows * numCols; // Finds the amount of unique frames
    frame = numFrames % uniqueFrames; // Gets which frame type it is

    renderer.setUniform("Frame", frame);
    renderer.setUniform("Rows", numRows);
    renderer.setUniform("Cols", numCols);

    float aspect = ((float)width()) / height();
    renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

    renderer.lookAt(eyePos, lookPos, up);

    updateFire();
    // transp = 0.6;
    // moveUp = 0.0;

    if (frame == sameFrame) {
        transp += 0.02;
        moveUp -= 0.005;
    } else {
        transp = 0.0;
        moveUp = 0.0;
    }

    renderer.sprite(vec3(0.0, 0.0, 0.0), vec4(1.0f, 1.0f, 1.0f, transp), 1.0);
    
    // numFrames = elapsedTime() * 6;
    // frame = numFrames % uniqueFrames;
    // frame += 1;

    // if (frame == 33) {
    //     frame = 1;
    // }

    // renderer.setUniform("Frame", frame);
    // renderer.sprite(vec3(0.0, moveUp, 0.0), vec4(1.0f, 1.0f, 1.0f, transp), 1.0);

    sameFrame = frame;

    renderer.endShader();
  }

protected:

  vec3 eyePos = vec3(0, 0, 2);
  vec3 lookPos = vec3(0, 0, 0);
  vec3 up = vec3(0, 1, 0);
  int frame = 0;
  int numRows = 4;
  int numCols = 8;
  float transp = 0.0f;
  int sameFrame = 1;
  float moveUp = 0.0f;
};

int main(int argc, char** argv)
{
  Viewer viewer;
  viewer.run();
  return 0;
}