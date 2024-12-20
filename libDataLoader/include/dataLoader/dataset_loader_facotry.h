#pragma once
#include "dataset3RScan.h"
#include "datasetScanNet.h"
#include "datasetVirtual4DSG.h"
#include "dataloader_3rscan.h"
#include "dataloader_scannet.h"
#include "dataloader_virtual4dsg.h"

namespace PSLAM {
    struct  DataLoaderFactory {
        static DatasetLoader_base *Make(
                const std::string &pth, INPUTE_TYPE inputeType = DATASET_DETECT) {
            DatasetLoader_base *output = nullptr;
            // detect datatype by checking file name

            if(inputeType == DATASET_DETECT){
                std::cerr << "detect data type: ";
                if(pth.find(".sens") != std::string::npos || pth.find("scene") != std::string::npos) {
                    inputeType = DATASET_SCANNET;
                    std::cerr << "ScanNet";
                } else if(pth.find("Virtual") != std::string::npos) {
                    inputeType = DATASET_VIRTUAL4DSG;
                    std::cerr << "Virtual4DSG";
                } else {
                    inputeType = DATASET_3RSCAN;
                    std::cerr << "3RScan";
                }
            }

            // Create dataloader
            switch (inputeType) {
                case DATASET_3RSCAN: {
                    auto path = pth.back() == '/'? pth : pth+"/";
                    auto database = std::make_shared<Scan3RDataset>(inputeType, path);
                    output = new DatasetLoader_3RScan(database);
                    break;
                }
                case DATASET_SCANNET: {
                    auto database = std::make_shared<ScanNetDataset>(inputeType, pth);
                    output = new DatasetLoader_ScanNet(database);
                    break;
                }
                case DATASET_VIRTUAL4DSG: {
                    auto path = pth.back() == '/' ? pth : pth + "/";
                    auto database = std::make_shared<Virtual4DSGDataset>(inputeType, path);
                    output = new DatasetLoader_Virtual4DSG(database);
                    
                    break;
                }
                case DATASET_DETECT:
                    break;

            }
            return output;
        }
    };
}