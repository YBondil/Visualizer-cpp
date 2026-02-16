#include <iostream>
#include "visualizer.h"
#include "camera.h"
using namespace VISU;

Visualizer::Visualizer() : window(nullptr), renderer(nullptr), camera(nullptr), is_running(false) {}
Visualizer::~Visualizer() {delete camera;}

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
        camera = new Camera(90.0f, (float)width, (float)heigth);
        camera->move(OBJ_VISU::Float3(0, 0, -400.0f));
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
        }
    }
}

void Visualizer::update(int count)
{

    for (auto object : objects)
    {   
        OBJ_VISU::Float3 center = {0.f, 0.f, 0.f};

        if (object) {
            // TENTATIVE DE CAST : "Est-ce que cet object est un Object_3D ?"
            // Si oui, obj3d sera un pointeur valide. Si non, il sera nullptr (NULL).
            OBJ_VISU::Object_3D* obj3d = dynamic_cast<OBJ_VISU::Object_3D*>(object);

            if (obj3d != nullptr) {
                obj3d->rotateArround(0.01f, 0.01f, 0.01f, center);
            } 
            else {
                object->rotate(0.01f, 0.01f, 0.01f);
            }
        }
    }

    if (camera) {
        for (auto object : objects)
        {
            if (object) {
                object->project(camera);
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
        object->render(renderer, ShowPoints);
    }
    SDL_RenderPresent(renderer);
}

void Visualizer::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Visualizer::add_object(OBJ_VISU::Object* object)
{
    objects.push_back(object);
}