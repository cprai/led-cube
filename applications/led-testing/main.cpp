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
#include "geometry/vector3.h"
#include "renderer/renderer.h"
#include "displayer/color.h"
#include "displayer/displayer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define N 294


int main() {
  renderer::Renderer renderer("resources/cube.map");
  displayer::Displayer<N> displayer;

  // Arguments are {position}, {rotation}, {scale}
  renderer::Entity &teapot = renderer.createEntity({3, 3, 2}, {0, 0, 0}, {1, 1, 1}, {1, 0, 0},
                                                   renderer.loadMesh("resources/teapot.obj"));

//  for (int i = 0; i < N; ++i) {
//    printf("Sample point %d: %lf, %lf, %lf\n", i, samplePoints[i].x, samplePoints[i].y, samplePoints[i].z);
//  }
//  int i = 0;
  while(1) {
    displayer::Color outputBuffer[294];
    // To modify after creation:
//    teapot.position.z = ((float) i - 30) / 10;
//    printf("z: %f\n", ((float) i - 30) / 10);
//    i = (i + 10) % 60;
    teapot.scale.x = 0.6;
    teapot.scale.y = 0.6;
    teapot.scale.z = 0.6;

    renderer.render<N>(outputBuffer);
    displayer.display(outputBuffer);
  }
}