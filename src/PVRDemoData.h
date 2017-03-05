#pragma once
/*
 *      Copyright (C) 2011 Pulse-Eight
 *      http://www.pulse-eight.com/
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
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include <vector>
#include "p8-platform/util/StdString.h"
#include <kodi/addon-instance/PVRClient.h>

struct PVRDemoEpgEntry
{
  int         iBroadcastId;
  std::string strTitle;
  int         iChannelId;
  time_t      startTime;
  time_t      endTime;
  std::string strPlotOutline;
  std::string strPlot;
  std::string strIconPath;
  int         iGenreType;
  int         iGenreSubType;
//  time_t      firstAired;
//  int         iParentalRating;
//  int         iStarRating;
//  bool        bNotify;
//  int         iSeriesNumber;
//  int         iEpisodeNumber;
//  int         iEpisodePartNumber;
//  std::string strEpisodeName;
};

struct PVRDemoChannel
{
  bool                    bRadio;
  int                     iUniqueId;
  int                     iChannelNumber;
  int                     iSubChannelNumber;
  int                     iEncryptionSystem;
  std::string             strChannelName;
  std::string             strIconPath;
  std::string             strStreamURL;
  std::vector<PVRDemoEpgEntry> epg;
};

struct PVRDemoRecording
{
  bool        bRadio;
  int         iDuration;
  int         iGenreType;
  int         iGenreSubType;
  std::string strChannelName;
  std::string strPlotOutline;
  std::string strPlot;
  std::string strRecordingId;
  std::string strStreamURL;
  std::string strTitle;
  std::string strDirectory;
  time_t      recordingTime;
};

struct PVRDemoTimer
{
  int             iChannelId;
  time_t          startTime;
  time_t          endTime;
  PVR_TIMER_STATE state;
  std::string     strTitle;
  std::string     strSummary;
};

struct PVRDemoChannelGroup
{
  bool             bRadio;
  int              iGroupId;
  std::string      strGroupName;
  int              iPosition;
  std::vector<int> members;
};

class PVRDemoData : public kodi::addon::CInstancePVRClient
{
public:
  PVRDemoData(KODI_HANDLE kodiInstance);
  virtual ~PVRDemoData(void);

  virtual std::string GetBackendName(void) override { return "pulse-eight demo pvr add-on"; }
  virtual std::string GetBackendVersion(void) override { return "0.1"; }
  virtual std::string GetConnectionString(void) override { return "connected"; }
  virtual std::string GetBackendHostname(void) override { return ""; }

  virtual PVR_ERROR GetDriveSpace(long long& iTotal, long long& iUsed) override;

  virtual void GetCapabilities(PVR_ADDON_CAPABILITIES& pCapabilities) override;

  virtual int GetChannelsAmount(void) override;
  virtual PVR_ERROR GetChannels(bool bRadio, std::vector<PVR_CHANNEL>& channels) override;

  virtual int GetChannelGroupsAmount(void) override;
  virtual PVR_ERROR GetChannelGroups(bool bRadio, std::vector<PVR_CHANNEL_GROUP>& groups) override;
  virtual PVR_ERROR GetChannelGroupMembers(const PVR_CHANNEL_GROUP& group, std::vector<PVR_CHANNEL_GROUP_MEMBER>& members) override;

  virtual PVR_ERROR GetEPG(const PVR_CHANNEL& channel, time_t iStart, time_t iEnd, std::vector<EPG_TAG>& epg) override;

  virtual int GetRecordingsAmount(bool bDeleted) override;
  virtual PVR_ERROR GetRecordings(bool bDeleted, std::vector<PVR_RECORDING>& kodiRecordings) override;

  virtual int GetTimersAmount(void) override;
  virtual PVR_ERROR GetTimers(std::vector<PVR_TIMER>& timers) override;

  virtual bool OpenLiveStream(const PVR_CHANNEL &channel) override;
  virtual void CloseLiveStream(void) override;
  virtual bool SwitchChannel(const PVR_CHANNEL &channel) override;
  virtual PVR_ERROR SignalStatus(PVR_SIGNAL_STATUS &signalStatus) override;

private:
  bool LoadDemoData(void);
  bool GetChannel(const PVR_CHANNEL &channel, PVRDemoChannel &myChannel);

  bool                             m_bIsPlaying;
  PVRDemoChannel                   m_currentChannel;
  std::vector<PVRDemoChannelGroup> m_groups;
  std::vector<PVRDemoChannel>      m_channels;
  std::vector<PVRDemoRecording>    m_recordings;
  std::vector<PVRDemoRecording>    m_recordingsDeleted;
  std::vector<PVRDemoTimer>        m_timers;
  time_t                           m_iEpgStart;
  std::string                      m_strDefaultIcon;
  std::string                      m_strDefaultMovie;
};
