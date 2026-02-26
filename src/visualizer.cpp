#include <iostream>
#include "visualizer.h"
#include "camera.h"
using namespace VISU;

Visualizer::Visualizer() : window(nullptr), renderer(nullptr), camera(nullptr), is_running(false) {}
Visualizer::~Visualizer() { delete camera; }

void Visualizer::init(const char *title, int width, int heigth, bool fullscreen)
{

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_WindowFlags flags = SDL_WINDOW_HIGH_PIXEL_DENSITY;

    if (fullscreen)
    {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        is_running = false;
        return;
    }

    window = SDL_CreateWindow(title, width, heigth, flags);
    if (!window)
    {
        std::cerr << "Window Error: " << SDL_GetError() << std::endl;
        is_running = false;
        return;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        std::cerr << "Renderer Error: " << SDL_GetError() << std::endl;
        is_running = false;
    }
    else
    {
        SDL_SetRenderLogicalPresentation(renderer, width, heigth, SDL_LOGICAL_PRESENTATION_LETTERBOX);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        is_running = true;
        freeze = false;
        camera = new Camera(90.0f,OBJ_VISU::Float3(0, 0, -400.0f), (float)width, (float)heigth);
    }
}

void Visualizer::handleEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            is_running = false;
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                isOrbiting = true; 
            } else if (event.button.button == SDL_BUTTON_MIDDLE) {
                isPanning = true; 
            }
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (SDL_GetModState() & SDL_KMOD_LSHIFT) {
                    isPanning = true;  
                } else {
                    isOrbiting = true; 
                }
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                isOrbiting = false;
            } else if (event.button.button == SDL_BUTTON_MIDDLE) {
                isPanning = false;
            }
            break;

        case SDL_EVENT_MOUSE_MOTION:
            if (isOrbiting) {
                camera->setDeltaPitchAndYaw(event.motion.xrel, event.motion.yrel);
            } 
            else if (isPanning) {
                camera->pan((float)event.motion.xrel, (float)event.motion.yrel);
            }
            break;

        case SDL_EVENT_MOUSE_WHEEL:
        {
            float scroll = event.wheel.y;
            if (scroll != 0) {
                float currentDist = camera->getOrbitDistance();
                
                // Note : Le trackpad du Mac a un défilement très fluide (inertiel). 
                // On réduit un peu le multiplicateur (ex: 5.0f au lieu de 20.0f) pour éviter de zoomer trop violemment.
                float newDist = currentDist - (scroll * 5.0f); 
                
                if (newDist < 1.0f) newDist = 1.0f;
                camera->setOrbitDistance(newDist);
            }
            break;
        }

        } 
    } 
    const bool *state = SDL_GetKeyboardState(NULL);
    OBJ_VISU::Float3 move(0, 0, 0);

    if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_RIGHT])
        move.x += 20.0f;
    if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_LEFT])
        move.x -= 20.0f;
    if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
        move.y += 20.0f;
    if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
        move.y -= 20.0f;
    if (state[SDL_SCANCODE_SPACE])
        move.z += 20.0f;
    if (state[SDL_SCANCODE_RSHIFT])
        move.z -= 20.0f;


    if (move.x != 0 || move.y != 0 || move.z != 0)
    {
        camera->setNextMovement(move);
    }
}

void Visualizer::update(int count)
{
    if (!freeze)
    {
        for (auto object : objects)
        {
            OBJ_VISU::Float3 center = {100.f, 100.f, 100.f};

            if (object)
            {
                OBJ_VISU::Object_3D *obj3d = dynamic_cast<OBJ_VISU::Object_3D *>(object);

                if (obj3d != nullptr)
                {
                    //obj3d->rotateArround(0.01f, 0.01f, 0.01f, center);
                }
                else
                {
                    //object->rotate(0.01f, 0.01f, 0.01f);
                }
            }
        }

        if (camera)
        {
            camera->move();
            camera->rotate();

            for (auto object : objects)
            {
                if (object)
                {
                    object->project(camera);
                }
            }
        }
    }
}

void Visualizer::render(bool ShowPoints = false)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (auto object : this->objects)
    {
        object->render(renderer, camera, ShowPoints);
    }
    SDL_RenderPresent(renderer);
}

void Visualizer::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Visualizer::add_object(OBJ_VISU::Object *object)
{
    objects.push_back(object);
}