#ifndef CCINSTANCE_H
#define CCINSTANCE_H

#include <fstream>
#include  <sstream>
#include "CCGraph.h"
#include "_Instance.h"

class CCInstance : public _Instance {
public:

    CCInstance(std::string filename):filename(filename) {

        std::string line;
        std::ifstream readFile(filename);


        if (readFile.is_open()) {

            int size;
            std::string gambiarra;
            readFile >> size;
            this->graph = new CCGraph(size);

            readFile >> this->nClusters;
            readFile >> clustersType;
            readFile >> this->lowerClusterLimit;
            readFile >> this->upperClusterLimit;
            readFile >> gambiarra; // read W

            for (int i = 0; i < size; i++) {
                int w;
                readFile >> w;
                graph->SetNodo(i, w);
            }

            getline(readFile, line);
            while (getline(readFile, line)) {
                int n1, n2, w;
                std::stringstream ss(line);

                ss >> n1;
                ss >> n2;
                ss >> w;

                graph->AddEdge(n1, n2, w);
            }


            readFile.close();

        } else {

            std::cerr << "Could not open the file - '"
                    << filename << "'" << std::endl;

        }




    }

    virtual ~CCInstance() {

        if (graph != nullptr) delete graph;

    }

    std::string GetClustersType() const {
        return clustersType;
    }

    int GetLowerClusterLimit() const {
        return lowerClusterLimit;
    }

    int GetNClusters() const {
        return nClusters;
    }

    int GetSize() const {
        if (this->graph != nullptr) return graph->GetSize();
        return 0;
    }

    int GetUpperClusterLimit() const {
        return upperClusterLimit;
    }

    CCGraph* GetGraph() const {
        return graph;
    }
    
    std::string GetFilename() const {
        return filename;
    }

    friend std::ostream& operator<<(std::ostream& os, const CCInstance& obj) {
        os << "nClusters: " << obj.nClusters << std::endl;
        os << "clustersType: " << obj.clustersType << std::endl;
        os << "lowerClusterLimit: " << obj.lowerClusterLimit << std::endl;
        os << "upperClusterLimit: " << obj.upperClusterLimit << std::endl;
        os << "graph:" << std::endl;
        os << *obj.graph;
        return os;
    }

private:
    std::string filename;
    int nClusters = 0;
    std::string clustersType; // 0 -> ss, i -> ds
    int lowerClusterLimit;
    int upperClusterLimit;

    CCGraph* graph = nullptr;

};

#endif /* CCINSTANCE_H */

