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
    renderer.loadShader("simple-texture",
      "../shaders/simple-texture.vs",
      "../shaders/simple-texture.fs");

    Image img;
    img.load("../textures/tree.png", true);
    renderer.loadTexture("tree", img, 0);
    // TODO: Use the width and the height of the image to scale the billboard

    renderer.loadTexture("grass", "../textures/grass.png", 0);
    renderer.blendMode(agl::BLEND);
  }

  vec3 camPos(float rad, float azi, float elev) {
    vec3 camPOV;
    camPOV.x = rad * cos(azi) * cos(elev);
    camPOV.y = rad * sin(elev);
    camPOV.z = rad * sin(azi) * cos(elev);

    return camPOV;
  }

  // Controls the camera's up and down direction, Y
  void upDir(int x, int dx) {
    float windHeight = height();

    azimuth += dx / 5;
  }

  // Controls the camera's right and left direction, X
  void rightDir(int y, int dy) {
    float windWidth = width();

    elevation += dy / 5;
  }

  void mouseMotion(int x, int y, int dx, int dy) {
    if (mouseClicked) { //mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
         upDir(x, dx);
         rightDir(y, dy);

         if (azimuth > 360) {
            azimuth = fmod(azimuth, 360);
         } else if (azimuth < 0) {
            azimuth = 360 - fmod(azimuth, 360);
         }

         if (elevation > 90) {
            elevation = -90 + fmod(elevation, 90);
         } else if (elevation < -90) {
            elevation = 90 + fmod(elevation, -90);
         } 

         // eyePos = camLocation(radius, azimuth, elevation);
      }
  }

  void mouseDown(int button, int mods) {
    // button is clicked
      if (button == GLFW_MOUSE_BUTTON_LEFT) {
         mouseClicked = true;
      }
  }

  void mouseUp(int button, int mods) {
    // button is not clicked
      if (button == GLFW_MOUSE_BUTTON_LEFT) {
         mouseClicked = false;
      }
  }

  void scroll(float dx, float dy) {
  }

  void draw() {
    renderer.beginShader("simple-texture");

    float aspect = ((float)width()) / height();
    renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

    cameraPos = camPos(radius, azimuth, elevation);
    eyePos = cameraPos;

    renderer.lookAt(eyePos, lookPos, up);

    // draw plane
    renderer.texture("Image", "grass");
    renderer.push();
    renderer.translate(vec3(0.0, -0.5, 0));
    renderer.scale(vec3(2.0f));
    renderer.plane();
    renderer.pop();

    // draw tree
    renderer.texture("Image", "tree");
    renderer.push();
    
    normalN = normalize(cameraPos - lookPos);
    thetaY = atan2(normalN.x, normalN.z);
    vec3 yAxis = vec3(0, 1, 0);
    renderer.rotate(thetaY, yAxis);
    
    renderer.translate(vec3(-0.5, -0.5, 0));
    renderer.quad(); // vertices span from (0,0,0) to (1,1,0)
    renderer.pop();

    renderer.endShader();
  }

protected:
  vec3 eyePos = vec3(0, 0, 2);
  vec3 lookPos = vec3(0, 0, 0);
  vec3 up = vec3(0, 1, 0);

  vec3 cameraPos = vec3(0, 0, 0);
  bool mouseClicked = false;
  float azimuth = 0;
  float elevation = 0;
  float radius = 2;
  vec3 normalN;
  float thetaY;
  int scaleY = 0;
};

int main(int argc, char** argv)
{
  Viewer viewer;
  viewer.run();
  return 0;
}
