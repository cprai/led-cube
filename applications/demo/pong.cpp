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

#define PADDLE_RADIUS 0.3

#define BALL_SPEED 0.000001
#define PADDLE_SPEED 0.000000001

void pong() {
  renderer::Renderer renderer("resources/cube.map", 0.1, 0.5);
  displayer::Displayer<N> displayer;

  auto& cubeMesh = renderer.loadMesh("resources/cube.obj");

  auto& paddle = renderer.createEntity(
    {2, 2, 4},
    {0.5, 0.5, 0.5},
    {2*PADDLE_RADIUS, 2*PADDLE_RADIUS, 0},
    {0, 0, 0.0175},
    cubeMesh
  );

  auto& ball = renderer.createEntity(
    {0, 0, 5},
    {0, 0, 0},
    {0.5, 0.5, 0.5},
    {0, 0.0175, 0},
    cubeMesh
  );


  renderer::Vector3 ballVelocity = {1, 1, -1};

  float delta;

  while (1) {
    printf("paddle x: %f, paddle y: %f, paddle z: %f\n", paddle.position.x, paddle.position.y, paddle.position.z);
    displayer::Color outputBuffer[N];
    ball.position = ball.position + ballVelocity*delta*BALL_SPEED;

    if (ball.position.x <= 0.0f) ballVelocity.x = +1.0f*std::abs(ballVelocity.x);
    if (ball.position.x >= 6.0f) ballVelocity.x = -1.0f*std::abs(ballVelocity.x);
    if (ball.position.y <= 0.0f) ballVelocity.y = +1.0f*std::abs(ballVelocity.y);
    if (ball.position.y >= 6.0f) ballVelocity.y = -1.0f*std::abs(ballVelocity.y);
    if (ball.position.z <= 0.0f) ballVelocity.z = +1.0f*std::abs(ballVelocity.z);
    if (ball.position.z >= 5.0f) ballVelocity.z = -1.0f*std::abs(ballVelocity.z);
    
    if (ball.position.z >= 5.0f) {

    }

    renderer::Vector3 controllerInput = {Joystick_getState(AXIS, L_STICK_X), -Joystick_getState(AXIS, L_STICK_Y), 0.0f};

    if (paddle.position.x < 0.0f) delta = 0.0f, paddle.position.x = 0.0f;
    if (paddle.position.x > 6.0f) delta = 0.0f, paddle.position.x = 6.0f;
    if (paddle.position.y < 0.0f) delta = 0.0f, paddle.position.y = 0.0f;
    if (paddle.position.y > 6.0f) delta = 0.0f, paddle.position.y = 6.0f;

    paddle.position = paddle.position + controllerInput*delta*PADDLE_SPEED;

    auto time1 = std::chrono::high_resolution_clock::now();

    renderer.render<N>(outputBuffer);
    displayer.display(outputBuffer);

    auto time2 = std::chrono::high_resolution_clock::now();
    delta = (time2 - time1).count()/1000.0f;
  }
}