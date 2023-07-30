#include "Game.hpp"

using namespace Controller;

Game::Game()
{
    Initialize();

    this->player = new Player();

    Clutter* clutter;

    clutter = new Clutter();
    clutter->Initialize("3D/Clutter/treasure_chest.obj", "3D/Clutter/Treasurechest_DIFF.png",
        "Shaders/clutter.vert", "Shaders/clutter.frag");

    clutter->GetTransform()->SetPosition(10.0f, 0.0f, 10.0f);   
    clutter->GetTransform()->SetScale(0.1f);
    clutterList.push_back(clutter);

    clutter = new Clutter();
    clutter->Initialize("3D/Clutter/Table.obj", "3D/Clutter/Table Texture.png",
        "Shaders/clutter.vert", "Shaders/clutter.frag");

    clutter->GetTransform()->SetLocalPosition(-10.0f, 0.0f, 10.0f);

    clutterList.push_back(clutter);
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
    this->player->ProcessInput(this->gameWindow);
}

void Game::Update(float tDeltaTime)
{
    this->player->Update(tDeltaTime);
}

void Game::Render()
{
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    //Skybox draw

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

    CameraData cameraData = this->player->GetCameraData();
    LightData pointLightData = this->player->GetPointLightData();
    LightData directionalLightData;

    directionalLightData.light_direction = glm::vec3(0.0f, 3.0f, -10.0f);
    directionalLightData.light_color = glm::vec3(1.0f, 1.0f, 1.0f);
    directionalLightData.ambient_color = glm::vec3(1.0f, 1.0f, 1.0f);
    directionalLightData.ambient_str = 0.2f;
    directionalLightData.spec_str = 0.5f;
    directionalLightData.spec_phong = 16.0f;
    directionalLightData.intensity = 10.0f;

    /* Game Object Draw */
    this->player->Draw();

    for (Clutter* clutter : clutterList)
    {
        clutter->Draw(cameraData, pointLightData, directionalLightData);
    }

}