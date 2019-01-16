/******************************************************************************
 * File : scheduel_handeler.h
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/ 
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <stdio.h>
#include <ctime>
#include <iomanip>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>

/* Constants -----------------------------------------------------------------*/
#define BUFFER_SIZE 500

/* Constants -----------------------------------------------------------------*/
const std::string BaseURL = "https://roostertest.windesheim.nl/WebUntis/Timetable.do?request.preventCache=1543327601812&";
const std::string RequestClassData = "ajaxCommand=getWeeklyTimetable&elementType=4&departmentId=0&filterId=2&";
const int ClassID = 328;

/* Classes -------------------------------------------------------------------*/
class CurlHandler{	
	public:
		void getLessonInfo();
		std::string curlRequest(int ID);
		static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
		std::string getCurlURL(int ID);
		std::string getDateField();
		std::string getDate();
		std::string getIdField(int ID);
		void parseJson(std::string* buffer);
		int getCurrentTime();
		void moveLessonTimes(int lesson);
		std::string getLessonTime(Json::Value obj, int lessonId, int lesson);
		std::string formatFullTime(std::string startTime, std::string endTime);
		std::string formatTime(std::string time);
		std::string getLessonTeachers(Json::Value obj, int i);
		void getFreeFrom();
};
