/*
 ==============================================================================
 
 This file is part of the iPlug 2 library. Copyright (C) the iPlug 2 developers. 
 
 See LICENSE.txt for  more info.
 
 ==============================================================================
*/

#ifndef _IPLUGAPI_
#define _IPLUGAPI_

/**
 * @file
 * @copydoc IPlugAPP
 */


#include "IPlugPlatform.h"
#include "IPlugAPIBase.h"
#include "IPlugProcessor.h"

struct IPlugInstanceInfo
{
  void* pAppHost;
};

class IPlugAPPHost;

/**  Standalone application base class for an IPlug plug-in
*   @ingroup APIClasses */
class IPlugAPP : public IPlugAPIBase
               , public IPlugProcessor<PLUG_SAMPLE_DST>
{
public:
  IPlugAPP(IPlugInstanceInfo instanceInfo, IPlugConfig config);
  
  //IPlugAPIBase
  void BeginInformHostOfParamChange(int idx) override {};
  void InformHostOfParamChange(int idx, double normalizedValue) override {};
  void EndInformHostOfParamChange(int idx) override {};
  void InformHostOfProgramChange() override {};
  void EditorStateChanged(int viewWidth, int viewHeight, const IByteChunk& data) override;

  //IEditorDelegate
  void SendSysexMsgFromUI(const ISysEx& msg) override;
  
  //IPlugProcessor
  bool SendMidiMsg(const IMidiMsg& msg) override;
  bool SendSysEx(const ISysEx& msg) override;
  
  //IPlugAPP
  void AppProcess(double** inputs, double** outputs, int nFrames);

private:
  IPlugAPPHost* mAppHost = nullptr;
  IPlugQueue<IMidiMsg> mMidiMsgsFromCallback {MIDI_TRANSFER_SIZE};
  IPlugQueue<SysExData> mSysExMsgsFromCallback {SYSEX_TRANSFER_SIZE};

  friend class IPlugAPPHost;
};

IPlugAPP* MakePlug(void* pAPPHost);

#endif
