#pragma once
/*
 *      Copyright (C) 2010-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "cores/AudioEngine/Interfaces/AEEncoder.h"

extern "C" {
#include "libswresample/swresample.h"
}

/* ffmpeg re-defines this, so undef it to squash the warning */
#undef restrict

class CAEEncoderFFmpeg: public IAEEncoder
{
public:
  CAEEncoderFFmpeg();
  ~CAEEncoderFFmpeg() override;

  bool IsCompatible(const AEAudioFormat& format) override;
  bool Initialize(AEAudioFormat &format, bool allow_planar_input = false) override;
  void Reset() override;

  unsigned int GetBitRate() override;
  AVCodecID GetCodecID() override;
  unsigned int GetFrames() override;

  int Encode(uint8_t *in, int in_size, uint8_t *out, int out_size) override;
  int GetData(uint8_t **data) override;
  double GetDelay(unsigned int bufferSize) override;
private:
  unsigned int BuildChannelLayout(const int64_t ffmap, CAEChannelInfo& layout);

  std::string m_CodecName;
  AVCodecID m_CodecID;
  unsigned int m_BitRate;
  AEAudioFormat m_CurrentFormat;
  AVCodecContext *m_CodecCtx;
  SwrContext *m_SwrCtx;
  CAEChannelInfo m_Layout;
  AVPacket m_Pkt;
  uint8_t m_Buffer[8 + AV_INPUT_BUFFER_MIN_SIZE];
  int m_BufferSize;
  int m_OutputSize;
  double m_OutputRatio;
  double m_SampleRateMul;
  unsigned int  m_NeededFrames;
  bool m_NeedConversion;
};

