// Bryn Mawr College, alinen, 2020
//

#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"

using namespace std;
using namespace glm;
using namespace agl;

struct Particle {
  glm::vec3 pos;
  glm::vec3 vel;
  glm::vec4 color;
  float rot;
  float size;
  bool isDone;
  glm::vec3 prevPos;
};

class Viewer : public Window {
public:
  Viewer() : Window() {
  }

  void setup() {
    setWindowSize(1000, 1000);
    createRainDrops(500);
    renderer.setDepthTest(false);
    renderer.blendMode(agl::ADD);
  }

  void createRainDrops(int size)
  {
    renderer.loadTexture("particle", "../textures/cube.png", 0);
    for (int i = 0; i < size; i++)
    {
      Particle particle;
      particle.color = vec4(0.4, 0.7, 1, 1);
      particle.size = 0.05;
      particle.rot = 0.0;
      int randLoc = (1 + (rand() % 9)) / 10;
      int randSection = (rand() % 3);
      particle.pos = vec3(randLoc + randSection, 3, 0);
      particle.vel = vec3(0, -0.1, 0);
    //   particle.isDone = true;
      mParticles.push_back(particle);
    }
  }

  void updateRainDrops(float dt)
  {
    for (int i = 0; i < mParticles.size(); i++) {
      Particle particle = mParticles[i];
      
    //   if (particle.isDone) {
    //     // particle.pos = position;
    //     // particle.rot = 0.0;
    //     particle.vel = agl::randomUnitCube();
    //     // particle.isDone = false;
    //   } else {
        // particle.prevPos = particle.pos;
        particle.pos += dt + particle.vel;
        // particle.pos = particle.pos + dt * particle.vel;
        // particle.rot += 0.1;
        // particle.size += 0.001;

        // particle.color.w -= 0.008;
        // if (particle.color.w < 0) {
        //   particle.color.w = 0;
        //   particle.isDone = true;
        // }
    //   }

      mParticles[i] = particle;
    }
  }

  void drawRainDrops()
  {
    renderer.texture("image", "particle");
    for (int i = 0; i < mParticles.size(); i++)
    {
      Particle particle = mParticles[i];
      renderer.sprite(particle.pos, particle.color, particle.size, particle.rot);
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

  void keyUp(int key, int mods) {
  }

  void draw() {
    renderer.beginShader("sprite");

    float aspect = ((float)width()) / height();
    renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

    renderer.lookAt(eyePos, lookPos, up);
    // vec3 cameraPos = renderer.cameraPosition();
    // position = vec3(2 * cos(val) + cameraPos.x, 2 * sin(val) + cameraPos.y, 0);
    // val += 0.02;
    // renderer.sprite(position, vec4(1.0f), 0.25f);
    updateRainDrops(dt());
    drawRainDrops();
    renderer.endShader();
  }

protected:

  vec3 eyePos = vec3(0, 0, 5); // vec3(0, 0, 3);
  vec3 lookPos = vec3(0, 0, 0);
  vec3 up = vec3(0, 1, 0);
  vec3 position = vec3(1, 0, 0);

  std::vector<Particle> mParticles;

  float val = 0;
  vec3 cameraPos = renderer.cameraPosition();
  vec3 velocity;
  float threshold = 0.1;
  int iter = 0;
};

int main(int argc, char** argv)
{
  Viewer viewer;
  viewer.run();
  return 0;
}