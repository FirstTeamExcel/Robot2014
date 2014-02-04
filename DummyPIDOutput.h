#ifndef DUMMYPIDOUTPUT_H
#define DUMMYPIDOUTPUT_H
#include "WPILib.h"
class DummyPIDOutput: public PIDOutput
{
private:
  volatile float _output;
  //This declares a function pointer called _callback that must be void function(float value);
  void (*_callback)(float);
public:
  DummyPIDOutput(){_callback = (void (*)(float))0;}
  
  void PIDWrite(float output){_output = output;
                              if (_callback != (void (*)(float))0)
                                    _callback(output);}
  
  float GetOutput(){return _output;}
  
  void SetOutputCallback(void (*callback)(float)){_callback = callback;}
};
#endif
