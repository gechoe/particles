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
    createRainDrops(1000);
    renderer.setDepthTest(false);
    renderer.blendMode(agl::ADD);
  }

  float randomize(float min, float max) {
    float randNum = (float)rand() / RAND_MAX;
    float randNumInRange = (max - min) * (randNum) + (min);
    return randNumInRange;
  }

  void createRainDrops(int size) {
    renderer.loadTexture("particle", "../textures/raindrop.png", 0);
    for (int i = 0; i < size; i++) {
      Particle particle;
      particle.color = vec4(0.4, 0.7, 1, 1);
      particle.size = 0.05;

      float randPosX = randomize(left, right);
      float randPosZ = randomize(back, front);
      particle.pos = vec3(randPosX, top, randPosZ);
      
      float rVelY = randomize(speed, speed * 2);
      particle.vel = vec3(0, rVelY, 0);
      
      rainDropParticles.push_back(particle);
    }
  }

  void updateRainDrops(float dt) {
    for (int i = 0; i < rainDropParticles.size(); i++) {
      Particle particle = rainDropParticles[i];

      int randV = rand() % 100;
      float randVel = (speed - (particle.vel.y)) * ((float)randV / 100) + (particle.vel.y);
      particle.vel = vec3(0, randVel, 0);

      if (particle.prevPos.y <= bottom && particle.pos.y > bottom) {
        particle.pos.x = (cos(theta) + randRadius) * randDir;
        particle.pos.y = (sin(theta) + randRadius) * randDir;
        theta += 0.1;
      } else if (particle.prevPos.y <= bottom && particle.pos.y <= bottom) {
        particle.pos = vec3(0, bottom, 0);
        particle.vel = vec3(0);
      } else if (particle.pos.y <= bottom) {
        particle.prevPos = particle.pos;
        // particle.vel = vec3(0);
        randRadius = randomize(0.005, 0.2);
        int twoOptions = 1 + (rand() % 2);

        if (twoOptions == 1) {
            randDir = -1;
        } else {
            randDir = 1;
        }

        particle.pos.x += (cos(theta) + randRadius) * randDir;
        particle.pos.y += (sin(theta) + randRadius) * randDir;
        theta += 0.1;
      } else {
        particle.pos.y += dt + particle.vel.y;
      }

      rainDropParticles[i] = particle;
    }
  }

  void drawRainDrops() {
    renderer.texture("image", "particle");

    // for (int j = 0; j < 10; j++) {
      for (int i = 0; i < rainDropParticles.size(); i++) {
        Particle particle = rainDropParticles[i];
        // if (particle.pos.x % j == 0) {
          renderer.sprite(particle.pos, particle.color, particle.size, particle.rot);
        // }
      }
    // }
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
    updateRainDrops(dt());
    drawRainDrops();

    // renderer.sprite(position, vec4(1.0f), 50.2f);
    renderer.endShader();
  }

protected:
  float left = -4.2f;
  float right = 4.2f;
  float bottom = -2.8f;
  float top = 2.0f;
  float back = -4.2f;
  float front = -0.2f;
  float speed = -0.2f;
  vec3 eyePos = vec3(0, 0, 5); // vec3(0, 0, 3);
  vec3 lookPos = vec3(0, 0, 0);
  vec3 up = vec3(0, 1, 0);
//   vec3 position = vec3(0, bottom * 10, (back - front) / 2);

  std::vector<Particle> rainDropParticles;

  float val = 0;
  vec3 cameraPos = renderer.cameraPosition();
  vec3 velocity;
  float threshold = 0.1;
  int iter = 0;
  float theta = 0;
  float randDir, randRadius;
};

int main(int argc, char** argv)
{
  Viewer viewer;
  viewer.run();
  return 0;
}