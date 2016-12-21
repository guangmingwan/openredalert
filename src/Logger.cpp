
#include "Logger.h"

#include <string>
#include <fstream>

//Initalize our static varaibles
Logger* Logger::instanceLog = NULL;;

//Log File constructor
Logger::Logger()
{
  logFile.open("log.txt", std::fstream::out); //Open log file for writing
}

//In our de-contructor, we close our log file
Logger::~Logger()
{
  logFile.close(); //Close our log file
}

//Log some text to our log file
void Logger::Info(std::string str)
{
  logFile << "[INFO]" << str << std::endl;
}

//Log some text to our log file
void Logger::Info(std::string filename, int linenumber, std::string str)
{
  logFile << "[INFO] " << filename << " (" << linenumber << ") :" << str << std::endl;
}

//Log some text to our log file
void Logger::Error(std::string str)
{
  logFile << "[ERROR]" << str << std::endl;
}

//Log some text to our log file
void Logger::Error(std::string filename, int linenumber, std::string str)
{
  logFile << "[Error] " << filename << " (" << linenumber << ") :" << str << std::endl;
}

//Log some text to our log file
void Logger::Warning(std::string str)
{
  logFile << "[WARNING]" << str << std::endl;
}

//Log some text to our log file
void Logger::Warning(std::string filename, int linenumber, std::string str)
{
  logFile << "[WARNING] " << filename << " (" << linenumber << ") :" << str << std::endl;
}

//Log some text to our log file
void Logger::Debug(std::string str)
{
  logFile << "[DEBUG]" << str << std::endl;
}

//Log some text to our log file
void Logger::Debug(std::string filename, int linenumber, std::string str)
{
  logFile << "[DEBUG] " << filename << " (" << linenumber << ") :" << str << std::endl;
}

//Our singleton implementation returns a pointer to our log class
Logger* Logger::getInstance()
{
  if (NULL == instanceLog)
  {
    //Get an instance of our logger
    instanceLog = new Logger();
  }

  return instanceLog;
}

//Cleanup after ourselves
void Logger::freeSingleton()
{
  if( instanceLog != NULL )
  {
    delete instanceLog;
    instanceLog = NULL;
  }
}
