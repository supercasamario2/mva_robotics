#include <iostream>
#include "base.hpp"


// constructeur avec régions 
baseGCS::baseGCS(std::vector<HPolyhedron> regions){
    std::copy(regions.begin(), regions.end(), std::back_inserter(this->regions));
}
// constructeur par défaut pour voir si ça marche
baseGCS::baseGCS(){std::cout << "bonjour je suis le gcs" << std::endl;}

// ajout des noeuds source / target au graph
void baseGCS::addSourceTarget(Eigen::VectorXd source, Eigen::VectorXd target){
    // j'ai séparé la condition en 2 cas jsp trop ce qu'il se passe si 
    // on donne nullptr à RemoveVertex et j'ai la flemme d'essayer

    // le paramètre "edges" n'est pas utilisé dans les programmes d'exemples sur le 
    // github de l'article, donc on peut le dégager je pense

    if(this->source != nullptr){
        this->gcs.RemoveVertex(this->source);
    }
    if(this->target != nullptr){
        this->gcs.RemoveVertex(this->target);
    }
    this->source = this->gcs.AddVertex(Point(source));
    std::cout << this->source->name() << std::endl;
}

// TODO : continuer 
void baseGCS::findStartGoalEdges(){

}
