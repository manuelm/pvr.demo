#include "StreamReader.h"
#include "client.h"

using namespace ADDON;

StreamReader::StreamReader(const std::string &streamURL)
{
  m_streamHandle = XBMC->CURLCreate(streamURL.c_str());

  XBMC->Log(LOG_DEBUG, "StreamReader: Started; url=%s", streamURL.c_str());
}

StreamReader::~StreamReader(void)
{
  if (m_streamHandle)
    XBMC->CloseFile(m_streamHandle);
  XBMC->Log(LOG_DEBUG, "StreamReader: Stopped");
}

bool StreamReader::Start()
{
  return XBMC->CURLOpen(m_streamHandle, XFILE::READ_NO_CACHE);
}

ssize_t StreamReader::ReadData(unsigned char *buffer, unsigned int size)
{
  ssize_t len = XBMC->ReadFile(m_streamHandle, buffer, size);
  XBMC->Log(LOG_DEBUG, "XXX requested=%ld got=%ld", size, len);
  return len;
}

int64_t StreamReader::Seek(long long position, int whence)
{
  return XBMC->SeekFile(m_streamHandle, position, whence);
}

int64_t StreamReader::Position()
{
  return XBMC->GetFilePosition(m_streamHandle);
}

int64_t StreamReader::Length()
{
  return XBMC->GetFileLength(m_streamHandle);
}

std::time_t StreamReader::TimeStart()
{
  return m_start;
}

std::time_t StreamReader::TimeEnd()
{
  return std::time(nullptr);
}

bool StreamReader::IsRealTime()
{
  return true;
}

bool StreamReader::IsTimeshifting()
{
  return false;
}
