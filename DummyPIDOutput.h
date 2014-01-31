#ifndef DUMMYPIDOUTPUT_H
#define DUMMYPIDOUTPUT_H
#include "WPILib.h"
class DummyPIDOutput: public PIDOutput
{
private:
  volatile float _output;
public:
  DummyPIDOutput(){}
  
  void PIDWrite(float output){_output = output;}
  
  float GetOutput(){return _output;}
};
#endif
