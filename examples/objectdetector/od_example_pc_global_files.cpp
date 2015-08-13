//
// Created by sarkar on 16.06.15.
//

/** \brief Example of the usage of global pipeline
   *
   * \author Kripasindhu Sarkar
   *
   */


#include <common/utils/ODFrameGenerator.h>
#include "common/pipeline/ObjectDetector.h"
//#include "common/pipeline/ODDetection.h"
#include "detectors/global3D/ODPointCloudGlobalMatching.h"


using namespace std;
int main(int argc, char *argv[])
{

  std::string training_input_dir(argv[1]), trained_data_dir(argv[2]), pointcloud_file(argv[3]);

  //trainer
  od::ODTrainer *trainer = new od::g3d::ODCADDetectTrainer3DGlobal(training_input_dir, trained_data_dir);
  trainer->train();


  //detector
  od::g3d::ODCADDetector3DGlobal<> *detector = new od::g3d::ODCADDetector3DGlobal<>();
  detector->setTrainingInputLocation(training_input_dir);
  detector->setTrainingDataLocation(trained_data_dir);
  detector->init();


  //Get a scene
  od::ODScenePointCloud<pcl::PointXYZRGBA> *frame;
  vector<od::ODDetection3D *> detections;

  od::ODFrameGenerator<od::ODScenePointCloud<pcl::PointXYZRGBA>, od::GENERATOR_TYPE_FILE_LIST> frameGenerator(pointcloud_file);
  while(frameGenerator.isValid())
  {
    //get frame
    frame = frameGenerator.getNextFrame();


    od::ODDetections3D * detections = detector->detectOmni(frame);

    for(int i = 0; i < detections->size(); i++)
    {
      detections->at(i)->printSelf();
    }

    //vis.removePointCloud ("frame");
    //vis.addPointCloud<pcl::PointXYZRGBA> (frame->getPointCloud(), "frame");

    //vis.spinOnce (5);

    //free frame
    delete frame;
  }

  return 0;
}
