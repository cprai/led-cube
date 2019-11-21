extern "C" {
//#include "controller/joystick.h"
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

#define PADDLE_RADIUS 3

void pong() {
  renderer::Renderer renderer("resources/cube.map", 0.1, 0.5);
  displayer::Displayer<N> displayer;

  auto& cubeMesh = renderer.loadMesh("resources/cube.obj");

  auto& paddle = renderer.createEntity(
    {0, 0, 5},
    {0, 0, 0},
    {2*PADDLE_RADIUS, 2*PADDLE_RADIUS, 0},
    {0, 0, 1},
    cubeMesh
  );

  auto& ball = renderer.createEntity(
    {0, 0, 5},
    {0, 0, 0},
    {1, 1, 1},
    {0, 1, 0},
    cubeMesh
  );

  displayer::Color outputBuffer[N];

  renderer::Vector3 ballVelocity = {1, 1, -1};

  auto time1 = std::chrono::high_resolution_clock::now();

  renderer.render<N>(outputBuffer);
  displayer.display(outputBuffer);

  auto time2 = std::chrono::high_resolution_clock::now();
  auto delta = (time2 - time1).count()/1000.0f;

  while (1) {
    ball.position = ball.position + ballVelocity*delta;

    if (ball.position.x <= 0.0f) ballVelocity.x = +1.0f*std::abs(ballVelocity.x);
    if (ball.position.x >= 6.0f) ballVelocity.x = -1.0f*std::abs(ballVelocity.x);
    if (ball.position.y <= 0.0f) ballVelocity.y = +1.0f*std::abs(ballVelocity.y);
    if (ball.position.y >= 6.0f) ballVelocity.y = -1.0f*std::abs(ballVelocity.y);
    if (ball.position.z <= 0.0f) ballVelocity.z = +1.0f*std::abs(ballVelocity.z);
    if (ball.position.z >= 5.0f) ballVelocity.z = -1.0f*std::abs(ballVelocity.z);
    
    if (ball.position.z >= 5.0f) {

    }

    time1 = std::chrono::high_resolution_clock::now();

    renderer.render<N>(outputBuffer);
    displayer.display(outputBuffer);

    time2 = std::chrono::high_resolution_clock::now();
    delta = (time2 - time1).count()/1000.0f;
  }
}