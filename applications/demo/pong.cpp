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

#define DEADZONE 10000

#define PADDLE_RADIUS 1

#define BALL_SPEED 0.0000025
#define PADDLE_SPEED 0.00000000025

void pong(displayer::Displayer<N> &displayer) {
  renderer::Renderer renderer("resources/cube.map", 0.1, 0.5);

  auto& cubeMesh = renderer.loadMesh("resources/cube.obj");

  auto& paddle = renderer.createEntity(
    {2, 2, 5},
    {0.5, 0.5, 0.5},
    {PADDLE_RADIUS, PADDLE_RADIUS, 0},
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

  float delta = 0;

  while (1) {
    // Xbox button, exit program
    int homeBtn = Joystick_getState(BUTTON, HOME);
    if (homeBtn) {
      break;
    }

    printf("paddle x: %f, paddle y: %f, paddle z: %f\n", paddle.position.x, paddle.position.y, paddle.position.z);
    printf("ball x: %f, ball y: %f, ball z: %f\n", ball.position.x, ball.position.y, ball.position.z);
    displayer::Color outputBuffer[N];
    ball.position = ball.position + ballVelocity*delta*BALL_SPEED;

    if (ball.position.x <= 0.0f) ballVelocity.x = +1.0f*std::abs(ballVelocity.x);
    if (ball.position.x >= 6.0f) ballVelocity.x = -1.0f*std::abs(ballVelocity.x);
    if (ball.position.y <= 0.0f) ballVelocity.y = +1.0f*std::abs(ballVelocity.y);
    if (ball.position.y >= 6.0f) ballVelocity.y = -1.0f*std::abs(ballVelocity.y);
    if (ball.position.z <= 0.0f) ballVelocity.z = +1.0f*std::abs(ballVelocity.z);
    if (ball.position.z >= 5.0f) ballVelocity.z = -1.0f*std::abs(ballVelocity.z);
    
    if (ball.position.z >= 4.8f) {
      auto distance = paddle.position - ball.position;
      distance.z = 0;

      auto linearDistance = distance.magnitude();

      if (linearDistance > 2*PADDLE_RADIUS) {
        ball.color = {0.0175f, 0.0f, 0.0f};
      }
      else {
        ball.color = {0.0f, 0.0175f, 0.0f};
      }
    }
    else {
      ball.color = {0.0f, 0.0175f, 0.0f};
    }

    renderer::Vector3 controllerInput = {Joystick_getState(AXIS, L_STICK_X), -Joystick_getState(AXIS, L_STICK_Y), 0.0f};

    if (std::abs(controllerInput.x) < DEADZONE) controllerInput.x = 0;
    if (std::abs(controllerInput.y) < DEADZONE) controllerInput.y = 0;

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