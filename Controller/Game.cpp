#include "Game.hpp"

using namespace Controller;

Game::Game()
{
    Initialize();
}

void Game::Initialize()
{
    if (!glfwInit())
    {
        exit(-1);
    }

    this->gameWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Thomas Banatin", NULL, NULL);

    if (!gameWindow)
    {
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(gameWindow);
    gladLoadGL();

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::Run()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glfwSetTime(0.0f);
    double tLastUpdate = 0.0f;
    float tTimePerFrame = 1.f / FRAME_RATE_LIMIT;

    while (!glfwWindowShouldClose(gameWindow))
    {
        this->ProcessInput();
        tLastUpdate += glfwGetTime();
        glfwSetTime(0.0f);

        while (tLastUpdate > tTimePerFrame)
        {
            tLastUpdate -= tTimePerFrame;
            this->Update(tTimePerFrame);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->Render();

        glfwSwapBuffers(gameWindow);

        glfwPollEvents();
    }

    glfwTerminate();
}

void Game::ProcessInput()
{

}

void Game::Update(float tDeltaTime)
{

}

void Game::Render()
{
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    //Skybox draw

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

    /* Game Object Draw */

}