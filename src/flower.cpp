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
    createPetal(8);
    // createCenter();
    renderer.setDepthTest(false);
    renderer.blendMode(agl::ADD);
  }

  void createPetal(int size) {
    renderer.loadTexture("particle", "../textures/petal.png", 0);

    for (int i = 0; i < size; i++) {
      Particle particle;
      particle.color = vec4(1.0, 1.0, 1.0, 1.0);
    //   particle.color = vec4(agl::randomUnitCube(), 1);
      particle.size = 1.0;
      particle.rot = i * rotVal;
      float currDegree = 360 / 8 * i;
      float radians = currDegree * (M_PI / 180);
      particle.pos = vec3(0.5 * cos(radians), 0.5 * sin(radians), 0);
    //   particle.pos = agl::randomUnitCube();
    //   particle.vel = agl::randomUnitCube();
      particle.isDone = true;
      particles1.push_back(particle);
    }

    // float radians = currDegree * (M_PI / 180);

    // int x = (rad * cos(radians)) + centerPos.xLoc;
    // int y = (rad * sin(radians)) + centerPos.yLoc;
  }

//   void createCenter() {
//     renderer.loadTexture("center", "../texture/center.png", 0);

//     Particle center;
//     center.color = vec4(1, 0.86, 0.4, 1);
//     center.size = 1.0;
//     center.rot = 0.0;
//     center.pos = vec3(0, 0, 0);
//     center.vel = vec3(0, 0, 0);
//     center.isDone = false;
//     centerPart = center;
//   }

  void updatePetal(float dt) {
    for (int i = 0; i < particles1.size(); i++) {
      Particle particle = particles1[i];
      if (particle.size >= 1.0) {
        // while (particle.color.w > 0) {
        // if (particle.size >= 1.0) {
            // particle.vel = vec3(1);
            // particle.vel = agl::randomUnitCube();
            // particle.pos = particle.pos * vec3(1.2, 1.2, 1.2);
            // particle.pos += particle.vel * dt;
            particle.color.w -= 0.001;
            // particle.pos = particle.pos + dt * particle.vel;
        // }
      }
    // }
    //   if (particle.size >= 1.0) {
    //     // particle.vel = vec3(1);
    //     particle.vel = agl::randomUnitCube();
    //     // particle.pos = particle.pos * vec3(1.2, 1.2, 1.2);
    //     particle.pos += particle.vel * dt;
    //     particle.color -= vec4(0, 0, 0, 0.01);
    //     // particle.pos = particle.pos + dt * particle.vel;
    //   }
        // particle.color = vec4(agl::randomUnitCube(), 1);
        // particle.size = 1.0;
        // particle.rot = 0.0;
        // particle.vel = agl::randomUnitCube();
        // particle.isDone = false;
    //   } else {
        // particle.prevPos = particle.pos;
        // particle.pos = particle.pos + dt * particle.vel;
        // particle.pos = vec3(cos(val), sin(val), 0);
        // particle.rot += 0.1;
        // particle.size += 0.001;

        // particle.color.w -= 0.008;
        // if (particle.color.w < 0) {
        //   particle.color.w = 0;
        //   particle.isDone = true;
        // }
    //   }

      particles1[i] = particle;
    }
  }

  void drawPetal() {
    renderer.texture("image", "particle");
    for (int i = 0; i < particles1.size(); i++) {
      Particle particle = particles1[i];
      renderer.sprite(particle.pos, particle.color, particle.size, particle.rot);
    }
  }

//   void drawCenter() {
//     // renderer.texture("centerImage", "center");
//     renderer.sprite(centerPart.pos, centerPart.color, centerPart.size, centerPart.rot);
//   }

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
    position = vec3(0, 0, 0); //2 * cos(val) + cameraPos.x, 2 * sin(val) + cameraPos.y, 0);
    val += 0.02;
    // renderer.sprite(position, vec4(1.0f), 1.0f);
    updatePetal(dt());
    drawPetal();
    // drawCenter();
    renderer.endShader();

    // renderer.beginShader();

  }

protected:

  vec3 eyePos = vec3(0, 0, 5); // vec3(0, 0, 3);
  vec3 lookPos = vec3(0, 0, 0);
  vec3 up = vec3(0, 1, 0);
  vec3 position = vec3(1, 0, 0);

  std::vector<Particle> particles1;
  std::vector<Particle> particles2;

  std::vector<string> textures;
  Particle centerPart;

  float val = 0;
  vec3 cameraPos = renderer.cameraPosition();
  vec3 velocity;
  float threshold = 0.1;
  float rotVal = -0.8;
  int iter = 0;
};

int main(int argc, char** argv)
{
  Viewer viewer;
  viewer.run();
  return 0;
}