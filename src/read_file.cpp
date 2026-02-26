#include "read_file.h"
#include <fstream>
#include <iostream>
#include <map>

// Un comparateur pour utiliser OBJ_VISU::Float3 comme clé dans la std::map
struct Float3Comparator {
    bool operator()(const OBJ_VISU::Float3& a, const OBJ_VISU::Float3& b) const {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    }
};

namespace VISU {

OBJ_VISU::Object_3D* load_stl(const std::string& filepath, SDL_Color color) {
    // Ouverture en mode binaire
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filepath << std::endl;
        return nullptr;
    }

    // 1. Lire l'en-tête (80 octets que l'on ignore)
    char header[80];
    file.read(header, 80);

    // 2. Lire le nombre de triangles (Un entier non signé sur 4 octets)
    uint32_t num_triangles;
    file.read(reinterpret_cast<char*>(&num_triangles), sizeof(uint32_t));

    std::cout << "Lecture de " << num_triangles << " triangles depuis " << filepath << std::endl;

    OBJ_VISU::Object_3D* obj3d = new OBJ_VISU::Object_3D();
    
    // Map pour fusionner les points (éviter de créer 3 points par triangle)
    std::map<OBJ_VISU::Float3, OBJ_VISU::Point*, Float3Comparator> unique_points;

    // Fonction lambda (interne) pour créer un point ou récupérer un existant
    auto get_or_create_point = [&](float x, float y, float z) -> OBJ_VISU::Point* {
        OBJ_VISU::Float3 pos(x, y, z);
        auto it = unique_points.find(pos);
        if (it != unique_points.end()) {
            return it->second; // Le point existe déjà
        }
        // Le point n'existe pas, on le crée
        OBJ_VISU::Point* new_point = new OBJ_VISU::Point(pos);
        unique_points[pos] = new_point;
        obj3d->add_point(new_point);
        return new_point;
    };

    // 3. Boucler sur chaque triangle
    for (uint32_t i = 0; i < num_triangles; ++i) {
        float normal[3];
        file.read(reinterpret_cast<char*>(normal), 3 * sizeof(float)); // Normale lue mais ignorée ici

        float v1[3], v2[3], v3[3];
        file.read(reinterpret_cast<char*>(v1), 3 * sizeof(float)); // Sommet 1
        file.read(reinterpret_cast<char*>(v2), 3 * sizeof(float)); // Sommet 2
        file.read(reinterpret_cast<char*>(v3), 3 * sizeof(float)); // Sommet 3

        uint16_t attribute_byte_count;
        file.read(reinterpret_cast<char*>(&attribute_byte_count), sizeof(uint16_t)); // Souvent égal à 0

        // Récupérer les 3 points du triangle
        OBJ_VISU::Point* p1 = get_or_create_point(v1[0], v1[1], v1[2]);
        OBJ_VISU::Point* p2 = get_or_create_point(v2[0], v2[1], v2[2]);
        OBJ_VISU::Point* p3 = get_or_create_point(v3[0], v3[1], v3[2]);

        // Ajouter la face pleine
        obj3d->add_face(OBJ_VISU::Face(p1, p2, p3, color));

        /* OPTIONNEL : Si vous voulez afficher les arêtes (fil de fer)
        OBJ_VISU::Segment s1(p1, p2, color);
        OBJ_VISU::Segment s2(p2, p3, color);
        OBJ_VISU::Segment s3(p3, p1, color);
        obj3d->add_segment(s1);
        obj3d->add_segment(s2);
        obj3d->add_segment(s3);
        */
    }

    file.close();
    return obj3d;
}

}