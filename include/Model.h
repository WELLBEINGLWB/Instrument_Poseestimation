#pragma once
#include <iostream>
#include <fstream>
#include <thread>
#include <future>
#include <sdf/parser.hh>
#include "Mesh.h"
#include "Render.h"
#include "FileSystem.h"
#include "PoseParameters.h"

using namespace std;

enum{ NORMALS, TANGENTS};

class Model{
public:
    Model(const char* rootDirectory, const char* modelFile, bool withPoseEstimation = true);
    ~Model();
    void render(VectorXd &pose, Mat &img, bool clear, string program = "color");
    void render(Mat &img, bool clear, string program = "color");
    void updateViewMatrix(sf::Window &window);

    void visualize(int type = NORMALS);

    Renderer *renderer;
    Poseestimator *poseestimator;
private:
    vector<Mesh*> meshes;
    FileSystem *filesystem;
};