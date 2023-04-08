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
};

class Viewer : public Window {
public:
  Viewer() : Window() {
  }

  void setup() {
    setWindowSize(1000, 1000);
    createSandBlock();
    renderer.setDepthTest(false);
    renderer.blendMode(agl::ADD);
  }

  void createSandBlock()
  {
    renderer.loadTexture("particle", "../textures/cube.png", 0);
    
    Particle particle;
    particle.color = vec4(0.75, 0.66, 0.44, 0.6);
    particle.size = 5;
    particle.rot = 0.0;
    particle.pos = agl::randomUnitCube();
    particle.vel = agl::randomUnitCube();
    particle.isDone = true;
    mParticles.push_back(particle);
  }

  void updateSandStorm(float dt)
  {
    // vec3 cameraPos = renderer.cameraPosition();

    // for (int i = 0; i < mParticles.size(); i++)
    // {
    //   Particle particle = mParticles[i];
    //   particle.pos += particle.vel * dt;
    //   if (particle.pos.x < -1 || particle.pos.x > 1) particle.vel.x = -particle.vel.x;
    //   if (particle.pos.y < -1 || particle.pos.y > 1) particle.vel.y = -particle.vel.y;
    //   if (particle.pos.z < -1 || particle.pos.z > 1) particle.vel.z = -particle.vel.z;
    //   mParticles[i] = particle;
    // }

    // Particle mainParticle = mParticles[0];
    // mainParticle.pos = vec3(2 * cos(val) + cameraPos.x, 2 * sin(val) + cameraPos.y, 0);
    // std::cout << "old  " << mainParticle.vel << std::endl;
    // mainParticle.vel = vec3(mainParticle.vel.x / 2, mainParticle.vel.y / 2, mainParticle.vel.z / 2);
    // std::cout << "new  " << mainParticle.vel << std::endl;
    // mParticles[0] = mainParticle;

    for (int i = 0; i < mParticles.size(); i++) {
      Particle particle = mParticles[i];
      // particle.pos = position;

      // if ((int(val * 10) % 2) == 0) {
      //   particle.pos = position;
      // }

      if (particle.isDone) {
        // particle.pos = position;
        // particle.color.w = 1.0;
        // particle.rot = 0.0;
        // particle.size = 0.25;
        // particle.isDone = false;
        // particle.color = vec4(agl::randomUnitCube(), 1);
        particle.color = vec4(0.75, 0.66, 0.44, 0.6);
        transp = particle.color.w;
        particle.size = 105.0;
        particle.rot = 0.0;
        // particle.vel = agl::randomUnitCube();
        particle.isDone = false;
      } else {
        // particle.pos = vec3(2 * cos(val) + cameraPos.x, 2 * sin(val) + cameraPos.y, 0);
        // particle.pos = vec3(cos(particle.pos.x + dt), sin(particle.pos.y + dt), 0);
        // particle.pos = particle.pos + dt * particle.vel; //vec3(2 * cos(val) + cameraPos.x + 0.1, 2 * sin(val) + cameraPos.y + 0.1, 0); //vec3(particle.pos + dt * particle.vel);
        // particle.pos = particle.pos + particle.vel * dt + vec3(0.5, 0.5, 0.5) * dt * dt;
        // particle.vel = vec3(dt);
        // std::cout << particle.vel << std::endl;
        // particle.vel /= 2;
        // particle.rot += 0.1;
        // particle.size += 0.001;

        particle.color.w -= 0.008;
        
        if (particle.color.w < 0) {
          particle.color.w = 0;
          transp = 0;
          particle.isDone = true;
        }

        // transp = particle.color.w;
      }
      // particle.rot += 0.1;
      // particle.vel = mainParticle.vel;
      mParticles[i] = particle;
    }

    // val += 0.1;

    // for (int i = 0; i < mParticles.size(); i++) {
    //   Particle particle = mParticles[i];
    //   particle.pos = vec3(2 * cos(val) + cameraPos.x, 2 * sin(val) + cameraPos.y, 0);
    //   mParticles[i] = particle;
    // }

    // val += 0.1;


    // for (int i = 0; i < mParticles.size(); i++) {
    //   Particle particle = mParticles[i];
    //   particle.pos = vec3(particle.pos + dt() * particle.vel);
    // }
  }

  void drawSandStorm()
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
    // position = vec3(val, 0, 0);

    if (transp > 0) {
        val += 0.01;
        position = vec3(val, 0, 0);
    }

    if (val > 4) {
        val = -4;
    }

    renderer.sprite(position, vec4(1.0f), 1.0f);
    updateSandStorm(dt());
    drawSandStorm();
    renderer.endShader();
  }

protected:

  vec3 eyePos = vec3(0, 0, 5); // vec3(0, 0, 3);
  vec3 lookPos = vec3(0, 0, 0);
  vec3 up = vec3(0, 1, 0);
  vec3 position = vec3(1, 0, 0);

  std::vector<Particle> mParticles;

  float val = -4;
  vec3 cameraPos = renderer.cameraPosition();
  vec3 velocity;
  float transp;
};

int main(int argc, char** argv)
{
  Viewer viewer;
  viewer.run();
  return 0;
}