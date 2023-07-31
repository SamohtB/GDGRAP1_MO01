#include "Game.hpp"

using namespace Controller;

Game::Game()
{
    Initialize();

    this->player = new Player();
    this->env = new Environment();
    this->moon = new DirectionalLight();
    LightData data;
    data.light_direction = glm::normalize(glm::vec3(140.0f, 90.0f, 0.0f));
    data.light_color = glm::vec3(1.0f, 1.0f, 1.0f);
    data.ambient_color = glm::vec3(1.0f, 1.0f, 1.0f);
    data.ambient_str = 0.5f;
    data.spec_str = 0.2f;
    data.spec_phong = 16.0f;
    data.intensity = 0.5f;

    this->moon->SetLightData(data);

    CreateClutter();
}

void Controller::Game::CreateClutter()
{
    Clutter* clutter;
    
    /* Chest */
    for (int i = 0; i < 3; i++)
    {
        clutter = new Clutter();
        clutter->Initialize("3D/Clutter/chest.obj", "3D/Clutter/chest_diff.png",
            "Shaders/clutter.vert", "Shaders/clutter.frag");

        clutter->GetTransform()->SetPosition(-10.0f + (i * 10.0f), 0.0f, -40.0f);
        clutter->GetTransform()->SetScale(0.03f);

        clutterList.push_back(clutter);
    }

    /* Table */
    clutter = new Clutter();
    clutter->Initialize("3D/Clutter/table.obj", "3D/Clutter/table_diff.png",
        "Shaders/clutter.vert", "Shaders/clutter.frag");
    clutter->GetTransform()->SetPosition(35.0f, -1.0f, 20.0f);
    clutter->GetTransform()->SetRotation(RotationAxis::YAW, -90.0f);
    clutter->GetTransform()->SetScale(2.0f);

    clutterList.push_back(clutter);

    /* Robot */
    for (int i = 0; i < 2; i++)
    {
        clutter = new Clutter();
        clutter->Initialize("3D/Clutter/robot.obj", "3D/Clutter/robot_diff" + std::to_string(i + 1) + ".png",
           "Shaders/clutter.vert", "Shaders/clutter.frag");
        clutter->GetTransform()->SetPosition(35.0f, 4.0f, 10.0f + (i * 20.0f));
        clutter->GetTransform()->SetRotation(RotationAxis::YAW, -90.0f);
        clutter->GetTransform()->SetScale(2.0f);

        clutterList.push_back(clutter);
    }
    
    /* Recon */
    for (int i = 0; i < 3; i++)
    {
        clutter = new Clutter();
        clutter->Initialize("3D/Clutter/recon.obj", "3D/Clutter/recon_diff.jpg",
            "Shaders/clutter.vert", "Shaders/clutter.frag");
        clutter->GetTransform()->SetPosition(-35.0f, -1.0f, 10.0f + (i * 10.0f));
        clutter->GetTransform()->SetRotation(RotationAxis::YAW, 90.0f);
        clutter->GetTransform()->SetScale(1.0f);

        clutterList.push_back(clutter);
    }

    /* Floor */
    clutter = new Clutter();
    clutter->Initialize("3D/plane.obj", "3D/bricks2.jpg",
        "Shaders/clutter.vert", "Shaders/clutter.frag");
    clutter->GetTransform()->SetPosition(0.0f, -1.5f, 0.0f);
    clutter->GetTransform()->SetRotation(RotationAxis::PITCH, 90.0f);
    clutter->GetTransform()->SetScale(50.0f);
    
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
    CameraData cameraData = this->player->GetCameraData();
    LightData pointLightData = this->player->GetPointLightData();
    LightData dirLightData = this->moon->GetLightData();

    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    this->env->Draw(cameraData);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

    this->player->AssignDirectionalLightData(dirLightData);
    /* Game Object Draw */
    this->player->Draw();

    for (Clutter* clutter : clutterList)
    {
        clutter->Draw(cameraData, pointLightData, dirLightData);
    }

}