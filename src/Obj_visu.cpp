#include "Obj_visu.h"
#include <fstream>
#include <cmath>
#include <iostream>

using namespace OBJ_VISU;

// ==========================================
// Implementation SEGMENT
// ==========================================

Segment::Segment(Float3 pos1, Float3 pos2, SDL_Color col)
{
    this->p1 = new Point;
    this->p2 = new Point;
    p1->init(pos1, col);
    p2->init(pos2, col);
    // Pour la 2D simple, on initialise la position écran directement avec les coordonnées
    p1->setPositionOnScreen(pos1.x, pos1.y);
    p2->setPositionOnScreen(pos2.x, pos2.y);
    this->color = col;
}

Segment::~Segment()
{
    delete p1;
    delete p2;
}

Segment::Segment(const Segment& other)
{
    this->p1 = new Point();
    this->p2 = new Point();
    *this->p1 = *other.p1;
    *this->p2 = *other.p2;
    this->color = other.color;
}

Segment& Segment::operator=(const Segment& other)
{
    if (this == &other)
    {
        return *this;
    }
    delete p1;
    delete p2;

    p1 = new Point();
    p2 = new Point();

    *p1 = *other.p1;
    *p2 = *other.p2;
    this->color = other.color;
    return *this;
}

void Segment::render(SDL_Renderer* ren, bool ShowPoints)
{
    if (ShowPoints)
    {
        p1->render(ren);
        p2->render(ren);
    }
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
    // Utilise les positions écrans calculées (positionOnScreen)
    SDL_FPoint points[] = { 
        {p1->getPosition().x, p1->getPosition().y}, // Attention: ici on utilise coords pour la 2D simple
        {p2->getPosition().x, p2->getPosition().y} 
    };
    
    // Si tu as un système de caméra/projection, tu devrais utiliser positionOnScreen ici.
    // Pour ton code actuel 2D, on va utiliser getPosition() modifié par rotate.
    SDL_RenderLine(ren, p1->getPosition().x, p1->getPosition().y, p2->getPosition().x, p2->getPosition().y);
}

void Segment::set(Float3 pos1, Float3 pos2)
{
    this->p1->init(pos1);
    this->p2->init(pos2);
}

// ==========================================
// Implementation OBJECT_2D
// ==========================================

void Object_2D::add_segment(Segment& segment)
{
    this->segments.push_back(segment);
    updateCenter(); // Met à jour le centre à chaque ajout
}

void Object_2D::render(SDL_Renderer* ren, bool ShowPoints)
{
    for (auto& segment : this->segments)
    {
        segment.render(ren, ShowPoints);
    }
}

void Object_2D::rotate(float theta, float center_x, float center_y)
{
    for (auto& seg : this->segments)
    {
        // Rotation point 1
        float x1 = seg.get_x1() - center_x;
        float y1 = seg.get_y1() - center_y;

        float x1_rot = x1 * std::cos(theta) - y1 * std::sin(theta);
        float y1_rot = x1 * std::sin(theta) + y1 * std::cos(theta);

        Float3 new_p1(x1_rot + center_x, y1_rot + center_y, 0);

        // Rotation point 2
        float x2 = seg.get_x2() - center_x;
        float y2 = seg.get_y2() - center_y;

        float x2_rot = x2 * std::cos(theta) - y2 * std::sin(theta);
        float y2_rot = x2 * std::sin(theta) + y2 * std::cos(theta);

        Float3 new_p2(x2_rot + center_x, y2_rot + center_y, 0);

        seg.set(new_p1, new_p2);
    }
    this->updateCenter();
}

void Object_2D::rotate(float theta)
{
    // Utilise le centre actuel de l'objet
    this->rotate(theta, center.getPosition().x, center.getPosition().y);
}

void Object_2D::updateCenter()
{
    float mid_x = 0;
    float mid_y = 0;

    if (segments.empty()) return;

    for (auto& segment : segments)
    {
        mid_x += (segment.get_x1() + segment.get_x2()) / 2;
        mid_y += (segment.get_y1() + segment.get_y2()) / 2;
    }
    
    float cx = mid_x / static_cast<float>(segments.size());
    float cy = mid_y / static_cast<float>(segments.size());
    
    center.init(Float3(cx, cy, 0));
}

// ==========================================
// Implementation TRIANGLE_2D
// ==========================================

Triangle_2D::Triangle_2D(float x1, float y1, float x2, float y2, float x3, float y3)
{
    p1_coords = {x1, y1, 0};
    p2_coords = {x2, y2, 0};
    p3_coords = {x3, y3, 0};

    // Création des segments
    Segment s1(p1_coords, p2_coords);
    Segment s2(p2_coords, p3_coords);
    Segment s3(p3_coords, p1_coords); // Fermer le triangle

    this->add_segment(s1);
    this->add_segment(s2);
    this->add_segment(s3);

    this->updateCenter();
}

// ==========================================
// Implementation OBJECT_3D
// ==========================================

void Object_3D::add_segment(Segment& segment)
{
    this->segments.push_back(segment);
    updateCenter();
}

void Object_3D::render(SDL_Renderer* ren, bool ShowPoints)
{
    // Note: Pour une vraie 3D, il faudrait ici projeter les points 3D vers 2D
    // en utilisant une matrice de projection ou une caméra.
    // Ici, on affiche simplement les coordonnées X et Y (projection orthographique simple).
    for (auto& segment : this->segments)
    {
        segment.render(ren, ShowPoints);
    }
}

void Object_3D::rotate(float theta_x, float theta_y, float theta_z)
{
    // Exemple de rotation simple autour du centre de l'objet pour chaque point
    float cx = center.x;
    float cy = center.y;
    float cz = center.z;

    for (auto& seg : this->segments)
    {
        Point* points[] = { seg.getP1(), seg.getP2() };

        for (auto* p : points) {
            float x = p->getPosition().x - cx;
            float y = p->getPosition().y - cy;
            float z = p->getPosition().z - cz;
            
            // Rotation Z (Roll)
            if (theta_z != 0) {
                float old_x = x; 
                x = x * cos(theta_z) - y * sin(theta_z);
                y = old_x * sin(theta_z) + y * cos(theta_z);
            }

            // Rotation Y (Yaw)
            if (theta_y != 0) {
                float old_x = x;
                x = x * cos(theta_y) + z * sin(theta_y);
                z = -old_x * sin(theta_y) + z * cos(theta_y);
            }
            
            // Rotation X (Pitch) - Optionnel
             if (theta_x != 0) {
                float old_y = y;
                y = y * cos(theta_x) - z * sin(theta_x);
                z = old_y * sin(theta_x) + z * cos(theta_x);
            }

            // Mise à jour
            p->init(Float3(x + cx, y + cy, z + cz));
        }
    }
}

void Object_3D::updateCenter()
{
    float mid_x = 0;
    float mid_y = 0;
    float mid_z = 0;

    if (segments.empty()) return;

    for (auto& segment : segments)
    {
        mid_x += (segment.getP1()->getPosition().x + segment.getP2()->getPosition().x) / 2;
        mid_y += (segment.getP1()->getPosition().y + segment.getP2()->getPosition().y) / 2;
        mid_z += (segment.getP1()->getPosition().z + segment.getP2()->getPosition().z) / 2;
    }

    center.x = mid_x / static_cast<float>(segments.size());
    center.y = mid_y / static_cast<float>(segments.size());
    center.z = mid_z / static_cast<float>(segments.size());
}