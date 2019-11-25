//#include <iostream>
//
//#include "geometry/vector3.h"
//#include "displayer/displayer.h"
//
//#define N 294
//
//int main() {
//  displayer::Displayer<N> displayer;
//
//  int idx = 0;
//  while (1) {
//
//    renderer::Vector3 outputBuffer[N];
////    for (int i = 0; i < N; i += 2) {
////      outputBuffer[i] = {1.0f, 0.1f, 0.5f};
////    }
//    outputBuffer[idx] = {0.1f, 1.0f, 0.5f};
//    for (int i = idx*N/6; i < (idx+1)*N/6; i++) {
//      outputBuffer[i] = {0.1f, 1.0f, 0.5f};
//    }
//    idx = (idx + 1 )% N;
//    if (idx > 5) {
//      idx = 0;
//    }
//
////    std::cout << "Output buffer:" << std::endl;
////    for (int i = 0; i < N; i++) {
////      std::cout << "{" << outputBuffer[i].x << "," << outputBuffer[i].y << "," << outputBuffer[i].z << "}" << std::endl;
////    }
//
//    displayer.display((displayer::Color *) outputBuffer);
//    usleep(250000L);
//  }
//}

//#include "geometry/vector3.h"
//#include "renderer/renderer.h"
//#include "displayer/color.h"
//#include "displayer/displayer.h"
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//
//#define N 49
//
//std::vector<renderer::Vector3> samplePoints;
//
//inline std::vector<std::string> tokenizeOnWhitespace(const std::string& line) {
//  std::istringstream tokenizer(line);
//  std::vector<std::string> tokens;
//
//  for (std::string token; tokenizer >> token; ) {
//    tokens.push_back(token);
//  }
//
//  return tokens;
//}
//
//void parseLine(const std::string& line) {
//  std::vector<std::string> tokens = tokenizeOnWhitespace(line);
//
//  float x = std::stof(tokens[0]);
//  float y = std::stof(tokens[1]);
//  float z = std::stof(tokens[2]);
//
//  samplePoints.push_back({x, y, z});
//}
//
//int main() {
//  std::ifstream file("resources/cube.map");
//
//  for (std::string line; std::getline(file, line);) {
//    parseLine(line);
//  }
//
//
//  renderer::Renderer renderer;
//  displayer::Displayer<N> displayer;
//
//  // Arguments are {position}, {rotation}, {scale}
//  renderer::Entity &teapot = renderer.createEntity({3, 2, 0}, {0, 0, 0}, {1, 1, 1},
//                                                   renderer.loadMesh("resources/teapot.obj"));
//  int i = 0;
//  while(1) {
//    // To modify after creation:
//    teapot.position.z = ((float) i-50)/40;
//    printf("z: %f\n", ((float) i-50)/40);
//    i = (i+1) % 100;
//    teapot.scale.x = 0.7;
//    teapot.scale.y = 0.7;
//    teapot.scale.z = 0.25;
//
//    renderer::Vector3 outputBuffer[N];
//    renderer.render<N>(samplePoints.data(), outputBuffer);
//
//    displayer.display((displayer::Color *) outputBuffer);
//  }
//}

// #################### 3D
extern "C" {
#include "controller/joystick.h"
}

#include "geometry/vector3.h"
#include "renderer/renderer.h"
#include "displayer/color.h"
#include "displayer/displayer.h"
#include <chrono>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

#define N 294


int main() {
  Joystick_init();
  renderer::Renderer renderer("resources/cube.map", 0.1, 0.5);
  displayer::Displayer<N> displayer;

  // Arguments are {position}, {rotation}, {scale}
  //renderer::Entity &teapot = renderer.createEntity({1, 3, 1}, {0, 0, 0}, {0.5, 0.5, 0.5}, {0.25, 0, 0},
  //                                                 renderer.loadMesh("resources/teapot.obj"));

  // px,py,pz, rx,ry,rz, sx,sy,sz
  float cubeValues[] = {3, 3, 1, 0, 0, 0, 2, 2, 2};
  auto cubeMesh = renderer.loadMesh("resources/cube.obj");
  float teapotValues[] = {3, 3, 1, 0, 0, 0, 0.5, 0.5, 0.5};
  auto teapotMesh = renderer.loadMesh("resources/teapot.obj");
  renderer::Entity &currentObject = renderer.createEntity({cubeValues[0], cubeValues[1], cubeValues[2]},
                                                          {cubeValues[3], cubeValues[4], cubeValues[5]},
                                                          {cubeValues[6], cubeValues[7], cubeValues[8]},
                                                          {0, 0, 0.175/5},
                                                          renderer.loadMesh("resources/teapot.obj"));
  currentObject.mesh = cubeMesh;
  auto currentValues = cubeValues;
  bool isCube = true;


  //currentObject.mesh = smileyMesh;
//  for (int i = 0; i < N; ++i) {
//    printf("Sample point %d: %lf, %lf, %lf\n", i, samplePoints[i].x, samplePoints[i].y, samplePoints[i].z);
//  }
//  int i = 0;
  auto time = std::chrono::high_resolution_clock::now();
  // TRUE: position mode, FALSE: rotation mode
  bool isPositionMode = true;
  int lastRightBumperValue = 0;
  int lastLeftBumperValue = 0;
  float dimness = 0.175/5;
  float stickThreshold = 0.3;
  float triggerThreshold = 0.3;

  float currentR = 0;
  float currentG = 0;
  float currentB = 1;


  while(true) {
    displayer::Color outputBuffer[294];
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> difference = now - time;
    time = now;

    // Xbox button, exit program
    //int homeBtn = Joystick_getState(BUTTON, HOME);
    //if (homeBtn) {
    //  break;
    //}

    // Left bumper, switch between objects
    int leftBumperBtn = Joystick_getState(BUTTON, L_BUMPER);
    if (leftBumperBtn) {
      if (lastLeftBumperValue == 0) {
        if (isCube) {
          // switch to teapot
          currentValues = teapotValues;
          currentObject.mesh = teapotMesh;
        } else {
          // switch to cube
          currentValues = cubeValues;
          currentObject.mesh = cubeMesh;
        }
        currentObject.position.x = currentValues[0];
        currentObject.position.y = currentValues[1];
        currentObject.position.z = currentValues[2];
        currentObject.rotation.x = currentValues[3];
        currentObject.rotation.y = currentValues[4];
        currentObject.rotation.z = currentValues[5];
        currentObject.scale.x = currentValues[6];
        currentObject.scale.y = currentValues[7];
        currentObject.scale.z = currentValues[8];
        isCube = !isCube;
      }
    }
    lastLeftBumperValue = leftBumperBtn;

    // Right bumper, switch between modes
    int rightBumperBtn = Joystick_getState(BUTTON, R_BUMPER);
    if (rightBumperBtn) {
      if (lastRightBumperValue == 0) {
        isPositionMode = !isPositionMode;
      }
    }
    lastRightBumperValue = rightBumperBtn;

    // Back Button, reset position
    int backBtn = Joystick_getState(BUTTON, SELECT);
    if (backBtn) {
      currentObject.position.x = currentValues[0];
      currentObject.position.y = currentValues[1];
      currentObject.position.z = currentValues[2];
      currentObject.rotation.x = currentValues[3];
      currentObject.rotation.y = currentValues[4];
      currentObject.rotation.z = currentValues[5];
      currentObject.scale.x = currentValues[6];
      currentObject.scale.y = currentValues[7];
      currentObject.scale.z = currentValues[8];
    }

    // COLORS :)
    // RED
    int bBtn = Joystick_getState(BUTTON, B);
    if (bBtn) {
      currentR = 1;
      currentG = 0;
      currentB = 0;
    }
    // GREEN
    int aBtn = Joystick_getState(BUTTON, A);
    if (aBtn) {
      currentR = 0;
      currentG = 1;
      currentB = 0;
    }
    // BLUE
    int xBtn = Joystick_getState(BUTTON, X);
    if (xBtn) {
      currentR = 0;
      currentG = 0;
      currentB = 1;
    }
    // YELLOW
    int yBtn = Joystick_getState(BUTTON, Y);
    if (yBtn) {
      currentR = 1;
      currentG = 1;
      currentB = 0;
    }

    // Load joysticks values
   float lStickX = Joystick_getState(AXIS, L_STICK_X) / (float) 32500;
    if (abs(lStickX) < stickThreshold)
      lStickX = 0;
    float lStickY = Joystick_getState(AXIS, L_STICK_Y) / (float) 32500;
    if (abs(lStickY) < stickThreshold)
      lStickY = 0;
    float rStickY = Joystick_getState(AXIS, R_STICK_Y) / (float) 32500;
    if (abs(rStickY) < stickThreshold)
      rStickY = 0;
    float rStickX = Joystick_getState(AXIS, R_STICK_X) / (float) 32500;
    if (abs(rStickX) < stickThreshold)
      rStickX = 0;
    printf("modifierx: %f\n", lStickX);
    printf("modifiery: %f\n", lStickY);
    printf("modifierz: %f\n", rStickY);

    if (isPositionMode) {
      // Position
      //printf("difference: %f\n", difference.count());
      currentObject.position.x += lStickX * difference.count() / 500;
      currentObject.position.y -= lStickY * difference.count() / 500;
      currentObject.position.z += rStickY * difference.count() / 500;
    } else {
      // Rotation
      currentObject.rotation.x += lStickY * difference.count() / 500;
      currentObject.rotation.y += lStickX * difference.count() / 500;
      currentObject.rotation.z += rStickX * difference.count() / 500;
    }

    // Triggers (scale)
    float leftTrigger = Joystick_getState(AXIS, L_TRIGGER);
    leftTrigger = leftTrigger != 0 ? (leftTrigger + 32500) / (float) 32500 : 0;
    if (abs(leftTrigger) < triggerThreshold)
      leftTrigger = 0;
    float rightTrigger = Joystick_getState(AXIS, R_TRIGGER);
    rightTrigger = rightTrigger != 0 ? (rightTrigger + 32500) / (float) 32500 : 0;
    if (abs(rightTrigger) < triggerThreshold)
      rightTrigger = 0;
    printf("Left trigger: %f\n", leftTrigger);
    printf("Right trigger: %f\n", rightTrigger);
    if (leftTrigger) {
      currentObject.scale.x -= leftTrigger * difference.count() / 500;
      currentObject.scale.y -= leftTrigger * difference.count() / 500;
      currentObject.scale.z -= leftTrigger * difference.count() / 500;
    }
    if (rightTrigger) {
      currentObject.scale.x += rightTrigger * difference.count() / 500;
      currentObject.scale.y += rightTrigger * difference.count() / 500;
      currentObject.scale.z += rightTrigger * difference.count() / 500;
    }

    // DPAD up/down: change brightness
    float dpadY = -Joystick_getState(AXIS, DPAD_Y) / (float) 32500;
    if (abs(dpadY) < stickThreshold)
      dpadY = 0;
    if (dpadY) {
      if ((dimness == 1 && dpadY < 0) || (dimness == 0 && dpadY > 0) || (dimness > 0 && dimness < 1)) {
        dimness += dpadY * difference.count() / 500;
      }
      if (dimness > 1) {
        dimness = 1;
      }
      if (dimness < 0) {
        dimness = 0;
      }
    }
    std::cout << "dpadY: " << dpadY << std::endl;
    std::cout << "dimness: " << dimness << std::endl;

    //teapot2.color.g = 0.175;

    currentObject.color.r = currentR * dimness;
    currentObject.color.g = currentG * dimness;
    currentObject.color.b = currentB * dimness;

    renderer.render<N>(outputBuffer);
    displayer.display(outputBuffer);
    float sleep_time = 0;
    if (difference.count() < 20) {
      sleep_time = 20-difference.count();
    }

    timespec sleepValue = {0};
    sleepValue.tv_nsec = sleep_time * 1000000L;
    printf("difference: %fms, sleeping for %f\n", difference.count(), sleep_time);
    nanosleep(&sleepValue, NULL);
  }

  Joystick_cleanUp();
}