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
            
            this->lowerClusterLimit = new int[this->nClusters];
            this->upperClusterLimit = new int[this->nClusters];
            
            for (int i = 0; i < this->nClusters; i++) {
                
                readFile >> this->lowerClusterLimit[i];
                readFile >> this->upperClusterLimit[i];
                
            }
            
            
            readFile >> gambiarra; // read W

            for (int i = 0; i < size; i++) {
                int w;
                readFile >> w;
                graph->SetNodo(i, w);
                weight += w;
            }

            getline(readFile, line);
            while (getline(readFile, line)) {
                int n1, n2;
                float w;
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
        if(lowerClusterLimit != nullptr) delete [] lowerClusterLimit;
        if(upperClusterLimit != nullptr) delete [] upperClusterLimit;

    }

    std::string GetClustersType() const {
        return clustersType;
    }

    int GetLowerClusterLimit(int indexCluster) const {
        return lowerClusterLimit[indexCluster];
    }

    int GetNClusters() const {
        return nClusters;
    }
    
    int GetWeight() const {
        return weight;
    }

    int GetSize() const {
        if (this->graph != nullptr) return graph->GetSize();
        return 0;
    }

    int GetUpperClusterLimit(int indexCluster) const {
        return upperClusterLimit[indexCluster];
    }

    CCGraph* GetGraph() const {
        return graph;
    }
    
    std::string GetFilename() const {
        return filename;
    }

    friend std::ostream& operator<<(std::ostream& os, const CCInstance& obj) {
        os << "Filename: " << obj.filename << std::endl;
        os << "weight: " << obj.weight << std::endl;
        os << "nClusters: " << obj.nClusters << std::endl;
        os << "clustersType: " << obj.clustersType << std::endl;
        os << "Limits: ";
        int i = 0;
        for(; i < obj.nClusters - 1; i++){
            os << obj.lowerClusterLimit[i];
            os << " " << obj.upperClusterLimit[i] << " - ";
        }
        os << obj.lowerClusterLimit[i];
        os << " " << obj.upperClusterLimit[i] << std::endl;
        os << "graph:" << std::endl;
        os << *obj.graph;
        return os;
    }

private:
    std::string filename;
    int nClusters = 0, weight = 0;
    std::string clustersType; // 0 -> ss, i -> ds
    int *lowerClusterLimit = nullptr;
    int *upperClusterLimit = nullptr;
    CCGraph* graph = nullptr;

};

#endif /* CCINSTANCE_H */

