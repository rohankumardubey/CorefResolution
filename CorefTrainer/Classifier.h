//
// Created by alesapin on 04.04.16.
//

#ifndef COREFRESOLUTION_CLASSIFIER_H
#define COREFRESOLUTION_CLASSIFIER_H
#include "fann.h"
#include <string>
#include <vector>
#include "../SyntParser/ParsedPhrase.h"
#include "Document.h"
#include "floatfann.h"

#include <set>
namespace coref {


    class Classifier {


        int numHidden;
        int maxEpochs;
        double reqError;
        int printEpochs;
        static const int NUM_INP;
        static const int NUM_OUTP;
        static const int NUM_LAYERS;
        fann *neuralNetwork;

        void convetToFann(const Triple& ph, fann_type *result) const;
    public:
        Classifier() : numHidden(0), maxEpochs(0), reqError(0), printEpochs(0) { };

        Classifier(int nh, int maxEps, double rE = 0.0001f, int report = 1000) :
                numHidden(nh), maxEpochs(maxEps), reqError(rE), printEpochs(report) {
            neuralNetwork = fann_create_standard(NUM_LAYERS, NUM_INP,
                                                 numHidden, NUM_OUTP);
            fann_set_activation_function_hidden(neuralNetwork, FANN_SIGMOID_SYMMETRIC);
            fann_set_activation_function_output(neuralNetwork, FANN_SIGMOID_SYMMETRIC);
        }

        void train(const std::string &filename);
        void save(const std::string &filename) const;
        void load(const std::string &filename);

        std::vector<ClassifiedTriple> run(const std::vector<Triple> triples) const;
        ClassifiedTriple runSingle(const Triple& t) const;
        ~Classifier() {
            fann_destroy(neuralNetwork);
        }
    };
}

#endif //COREFRESOLUTION_CLASSIFIER_H