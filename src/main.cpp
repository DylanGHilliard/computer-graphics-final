#ifdef _WIN32
#include <windows.h>
#include <SDL_main.h>
#endif

#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include "Canis/Canis.hpp"
#include "Canis/Entity.hpp"
#include "Canis/Graphics.hpp"
#include "Canis/Window.hpp"
#include "Canis/Shader.hpp"
#include "Canis/Debug.hpp"
#include "Canis/IOManager.hpp"
#include "Canis/InputManager.hpp"
#include "Canis/Camera.hpp"
#include "Canis/Model.hpp"
#include "Canis/World.hpp"
#include "Canis/Editor.hpp"
#include "Canis/FrameRateManager.hpp"

using namespace glm;

// git restore .
// git fetch
// git pull

// 3d array
std::vector<std::vector<std::vector<unsigned int>>> map = {};

// declaring functions
void SpawnLights(Canis::World &_world);
void LoadMap(std::string _path);
void Rotate(Canis::World &_world, Canis::Entity &_entity, float _deltaTime);

#ifdef _WIN32
#define main SDL_main
extern "C" int main(int argc, char* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    Canis::Init();
    Canis::InputManager inputManager;
    Canis::FrameRateManager frameRateManager;
    frameRateManager.Init(60);

    /// SETUP WINDOW
    Canis::Window window;
    window.MouseLock(true);

    unsigned int flags = 0;

    if (Canis::GetConfig().fullscreen)
        flags |= Canis::WindowFlags::FULLSCREEN;

    window.Create("Hello Graphics", Canis::GetConfig().width, Canis::GetConfig().heigth, flags);
    /// END OF WINDOW SETUP

    Canis::World world(&window, &inputManager, "assets/textures/lowpoly-skybox/");
    SpawnLights(world);

    Canis::Editor editor(&window, &world, &inputManager);

    Canis::Graphics::EnableAlphaChannel();
    Canis::Graphics::EnableDepthTest();

    /// SETUP SHADER
    Canis::Shader shader;
    shader.Compile("assets/shaders/hello_shader.vs", "assets/shaders/hello_shader.fs");
    shader.AddAttribute("aPosition");
    shader.Link();
    shader.Use();
    shader.SetInt("MATERIAL.diffuse", 0);
    shader.SetInt("MATERIAL.specular", 1);
    shader.SetFloat("MATERIAL.shininess", 64);
    shader.SetBool("WIND", false);
    shader.UnUse();

    Canis::Shader grassShader;
    grassShader.Compile("assets/shaders/hello_shader.vs", "assets/shaders/hello_shader.fs");
    grassShader.AddAttribute("aPosition");
    grassShader.Link();
    grassShader.Use();
    grassShader.SetInt("MATERIAL.diffuse", 0);
    grassShader.SetInt("MATERIAL.specular", 1);
    grassShader.SetFloat("MATERIAL.shininess", 64);
    grassShader.SetBool("WIND", true);
    grassShader.SetFloat("WINDEFFECT", 0.2);
    grassShader.UnUse();
    /// END OF SHADER

    Canis::Shader brickShader;
    brickShader.Compile("assets/shaders/hello_shader.vs", "assets/shaders/hello_shader.fs");
    brickShader.AddAttribute("aPosition");
    brickShader.Link();
    brickShader.Use();
    brickShader.SetInt("MATERIAL.diffuse", 0);
    brickShader.SetInt("MATERIAL.specular", 1);
    brickShader.SetFloat("MATERIAL.shininess", 32);
    brickShader.SetBool("WIND", false);
    brickShader.UnUse();
    
    Canis::Shader logShader;
    logShader.Compile("assets/shaders/hello_shader.vs", "assets/shaders/hello_shader.fs");
    logShader.AddAttribute("aPosition");
    logShader.Link();
    logShader.Use();
    logShader.SetInt("MATERIAL.diffuse", 0);
    logShader.SetInt("MATERIAL.specular", 1);
    logShader.SetFloat("MATERIAL.shininess", 32);
    logShader.SetBool("WIND", false);
    logShader.UnUse();

    Canis::Shader plankShader;
    plankShader.Compile("assets/shaders/hello_shader.vs", "assets/shaders/hello_shader.fs");
    plankShader.AddAttribute("aPosition");
    plankShader.Link();
    plankShader.Use();
    plankShader.SetInt("MATERIAL.diffuse", 0);
    plankShader.SetInt("MATERIAL.specular", 1);
    plankShader.SetFloat("MATERIAL.shininess", 64);
    plankShader.SetBool("WIND", false);
    plankShader.UnUse();

    Canis::Shader grassBlockShader;
    grassBlockShader.Compile("assets/shaders/hello_shader.vs", "assets/shaders/hello_shader.fs");
    grassBlockShader.AddAttribute("aPosition");
    grassBlockShader.Link();
    grassBlockShader.Use();
    grassBlockShader.SetInt("MATERIAL.diffuse", 0);
    grassBlockShader.SetInt("MATERIAL.specular", 1);
    grassBlockShader.SetFloat("MATERIAL.shininess", 32);
    grassBlockShader.SetBool("WIND", false);
    grassBlockShader.UnUse();

    Canis::Shader fireShader;
    fireShader.Compile("assets/shaders/fire_shader.vs", "assets/shaders/fire_shader.fs");
    fireShader.AddAttribute("aPosition");
    fireShader.Link();
    fireShader.Use();
    fireShader.SetInt("MATERIAL.diffuse", 0);
    fireShader.SetInt("MATERIAL.specular", 1);
    fireShader.SetFloat("MATERIAL.shininess", 64);
    fireShader.SetBool("WIND", false);
    fireShader.SetFloat("ANIMATION_SPEED", 2.0f);
    fireShader.SetInt("FIREANIMATION.fireTexture1", 2);
    fireShader.SetInt("FIREANIMATION.fireTexture2", 3);
    fireShader.SetInt("FIREANIMATION.fireTexture3", 4);
    fireShader.SetInt("FIREANIMATION.fireTexture4", 5);
    fireShader.UnUse();

    
    Canis::Shader flowerShader;
    flowerShader.Compile("assets/shaders/hello_shader.vs", "assets/shaders/hello_shader.fs");
    flowerShader.AddAttribute("aPosition");
    flowerShader.Link();
    flowerShader.Use();
    flowerShader.SetInt("MATERIAL.diffuse", 0);
    flowerShader.SetInt("MATERIAL.specular", 1);
    flowerShader.SetFloat("MATERIAL.shininess", 64);
    flowerShader.SetBool("WIND", true);
    flowerShader.SetFloat("WINDEFFECT", 0.2);
    flowerShader.UnUse();
    
    Canis::Shader dirtShader;
    dirtShader.Compile("assets/shaders/hello_shader.vs", "assets/shaders/hello_shader.fs");
    dirtShader.AddAttribute("aPosition");
    dirtShader.Link();
    dirtShader.Use();
    dirtShader.SetInt("MATERIAL.diffuse", 0);
    dirtShader.SetInt("MATERIAL.specular", 1);
    dirtShader.SetFloat("MATERIAL.shininess", 64);
    dirtShader.SetBool("WIND", false);
    dirtShader.UnUse();
    
    Canis::Shader cobblestoneShader;
    cobblestoneShader.Compile("assets/shaders/hello_shader.vs", "assets/shaders/hello_shader.fs");
    cobblestoneShader.AddAttribute("aPosition");
    cobblestoneShader.Link();
    cobblestoneShader.Use();
    cobblestoneShader.SetInt("MATERIAL.diffuse", 0);
    cobblestoneShader.SetInt("MATERIAL.specular", 1);
    cobblestoneShader.SetFloat("MATERIAL.shininess", 64);
    cobblestoneShader.SetBool("WIND", false);
    cobblestoneShader.UnUse();

    /// Load Image
    Canis::GLTexture glassTexture = Canis::LoadImageGL("assets/textures/glass.png", true);
    Canis::GLTexture grassTexture = Canis::LoadImageGL("assets/textures/grass.png", false);
    Canis::GLTexture flowerTexture= Canis::LoadImageGL("assets/textures/blue_orchid.png", false);
    Canis::GLTexture textureSpecular = Canis::LoadImageGL("assets/textures/container2_specular.png", true);
    Canis::GLTexture brickTexture = Canis::LoadImageGL("assets/textures/bricks.png", true);
    Canis::GLTexture logTexture = Canis::LoadImageGL("assets/textures/oak_log.png", true);
    Canis::GLTexture plankTexture = Canis::LoadImageGL("assets/textures/oak_planks.png", true);
    Canis::GLTexture grassBlockTexture = Canis::LoadImageGL("assets/textures/grass_block_top.png", true);
    Canis::GLTexture fireTexture1 = Canis::LoadImageGL("assets/textures/fire_textures/fire_1.png", true);
    Canis::GLTexture fireTexture2 = Canis::LoadImageGL("assets/textures/fire_textures/fire_2.png", true);
    Canis::GLTexture fireTexture3 = Canis::LoadImageGL("assets/textures/fire_textures/fire_3.png", true);
    Canis::GLTexture fireTexture4 = Canis::LoadImageGL("assets/textures/fire_textures/fire_4.png", true);
    Canis::GLTexture dirtTexture = Canis::LoadImageGL("assets/textures/dirt.png", true);
    Canis::GLTexture cobblestoneTexture = Canis::LoadImageGL("assets/textures/cobblestone.png", true);
    /// End of Image Loading

    /// Load Models
    Canis::Model cubeModel = Canis::LoadModel("assets/models/cube.obj");
    Canis::Model grassModel = Canis::LoadModel("assets/models/plants.obj");
    Canis::Model fireModel = Canis::LoadModel("assets/models/fire.obj");
    
    /// END OF LOADING MODEL

    // Load Map into 3d array
    LoadMap("assets/maps/level.map");

    // Loop map and spawn objects
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            for (int z = 0; z < map[y][x].size(); z++)
            {
                Canis::Entity entity;
                entity.active = true;
 
                switch (map[y][x][z])
                {
                case 1: // places a glass block
                    entity.tag = "glass";
                    entity.albedo = &glassTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &cubeModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 2: // places a grass block
                    entity.tag = "grass";
                    entity.albedo = &grassTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &grassModel;
                    entity.shader = &grassShader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    entity.Update = &Rotate;
                    world.Spawn(entity);

                    break;
                case 3: // Place Bricks Block
                    entity.tag = "bricks";
                    entity.albedo = &brickTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &cubeModel;
                    entity.shader = &brickShader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 4: // Place Oak Log
                    entity.tag = "oak_log";
                    entity.albedo = &logTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &cubeModel;
                    entity.shader = &logShader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 5:     // Place Oak Planks
                    entity.tag = "oak_plank";
                    entity.albedo = &plankTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &cubeModel;
                    entity.shader = &plankShader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 6:    // Place Gras Dirt block
                    entity.tag = "grass_block";
                    entity.albedo = &grassBlockTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &cubeModel;
                    entity.shader = &grassBlockShader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    // Checks if the block above is empty
                    if (map[y+1][x][z] == 0){
                        auto now = std::chrono::system_clock::now();
                        auto duration = now.time_since_epoch();
                        auto millis = std::chrono:: duration_cast<std::chrono::milliseconds>(duration).count();
                        srand(static_cast<unsigned int>(millis+ x+ y+z));
                        int randVal = rand() % 10;
                        // Creates Grass On top of the block at a 50% rate
                        if (randVal == 1 || randVal == 2 || randVal == 3 ){
                            entity.tag = "grass";
                            entity.albedo = &grassTexture;
                            entity.specular = &textureSpecular;
                            entity.model = &grassModel;
                            entity.shader = &grassShader;
                            entity.transform.position = vec3(x + 0.0f, y + 1.0f, z + 0.0f);
                            entity.Update = &Rotate;
                            world.Spawn(entity);
                        }
                        if (randVal == 4){
                            entity.tag = "flower";
                            entity.albedo = &flowerTexture;
                            entity.specular = &textureSpecular;
                            entity.model = &grassModel;
                            entity.shader = &flowerShader;
                            entity.transform.position = vec3(x + 0.0f, y + 1.0f, z + 0.0f);
                            entity.Update = &Rotate;
                            world.Spawn(entity);
                        }

                    }
                    break;
                case 7:
                    entity.tag = "fire";
                    entity.albedo = &fireTexture1;
                    entity.animationTextures = std::deque<Canis::GLTexture>();
                    entity.animationTextures.push_front(fireTexture2);
                    entity.animationTextures.push_front(fireTexture3);
                    entity.animationTextures.push_front(fireTexture4);
                    entity.animationTextures.push_front(fireTexture1);
                    entity.animationSpeed = 0.5f;
                    entity.specular = &textureSpecular;
                    entity.model = &fireModel;
                    entity.shader = &fireShader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 8:     // dirt block
                    entity.tag = "dirt";
                    entity.albedo = &dirtTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &cubeModel;
                    entity.shader = &dirtShader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 9:     // Cobblestone
                    entity.tag = "cobblestone";
                    entity.albedo = &cobblestoneTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &cubeModel;
                    entity.shader = &cobblestoneShader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                default:
                    break;
                }
            }
        }
    }

    double deltaTime = 0.0;
    double fps = 0.0;

    // Application loop
    while (inputManager.Update(Canis::GetConfig().width, Canis::GetConfig().heigth))
    {
        deltaTime = frameRateManager.StartFrame();
        Canis::Graphics::ClearBuffer(COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT);

        world.Update(deltaTime);
        world.Draw(deltaTime);

        editor.Draw();

        window.SwapBuffer();

        // EndFrame will pause the app when running faster than frame limit
        fps = frameRateManager.EndFrame();

        Canis::Log("FPS: " + std::to_string(fps) + " DeltaTime: " + std::to_string(deltaTime));
    }

    return 0;
}

void Rotate(Canis::World &_world, Canis::Entity &_entity, float _deltaTime)
{
    //_entity.transform.rotation.y += _deltaTime;
}

void LoadMap(std::string _path)
{
    std::ifstream file;
    file.open(_path);

    if (!file.is_open())
    {
        printf("file not found at: %s \n", _path.c_str());
        exit(1);
    }

    int number = 0;
    int layer = 0;

    map.push_back(std::vector<std::vector<unsigned int>>());
    map[layer].push_back(std::vector<unsigned int>());

    while (file >> number)
    {
        if (number == -2) // add new layer
        {
            layer++;
            map.push_back(std::vector<std::vector<unsigned int>>());
            map[map.size() - 1].push_back(std::vector<unsigned int>());
            continue;
        }

        if (number == -1) // add new row
        {
            map[map.size() - 1].push_back(std::vector<unsigned int>());
            continue;
        }

        map[map.size() - 1][map[map.size() - 1].size() - 1].push_back((unsigned int)number);
    }
}

void SpawnLights(Canis::World &_world)
{
    Canis::DirectionalLight directionalLight;
    directionalLight.ambient = vec3(0.2f, 0.2f, 0.2f);
    directionalLight.diffuse = vec3(0.5f);
    _world.SpawnDirectionalLight(directionalLight);

    Canis::PointLight pointLight;
    pointLight.position = vec3(0.0f);
    pointLight.ambient = vec3(0.2f);
    pointLight.diffuse = vec3(0.5f);
    pointLight.specular = vec3(1.0f);
    pointLight.constant = 1.0f;
    pointLight.linear = 0.09f;
    pointLight.quadratic = 0.032f;
    pointLight.flicker = false;

    //_world.SpawnPointLight(pointLight);

    pointLight.position = vec3(-2.0f, -2.0f, -1.0f);
    _world.SpawnPointLight(pointLight);
        

    //light right of house door
    pointLight.position = vec3(5.0f, 6.0f, 19.0f);
  
    _world.SpawnPointLight(pointLight);

    //light right of house door
    pointLight.position = vec3(5.0f, 5.0f, 7.0f);

    _world.SpawnPointLight(pointLight);

\

    // fire light
    pointLight.position = vec3(19.0f, 1.0f, 13.0f);
    pointLight.ambient = vec3(0.2f, 0.1f, 0.01f);
    pointLight.flicker = true;
    _world.SpawnPointLight(pointLight);
    
}