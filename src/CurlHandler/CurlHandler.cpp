#include "CurlHandler.h"

// ----------------------------------------------------------------------------
// Global variables
// ----------------------------------------------------------------------------
std::string lessonName1;
std::string lessonName2;
std::string lessonTime1;
std::string lessonTime2;
std::string lessonTeachers1;
std::string lessonTeachers2;
std::string freeFrom;
int lessonTimeArray[20][2];
int lessonAmount;

// ----------------------------------------------------------------------------
// Functions
// ----------------------------------------------------------------------------
/**
* @brief This function retrieves & parses json
* @retuns none
* @note
*/
void CurlHandler::getLessonInfo(){
	std::string jsonBuffer = CurlHandler.curlRequest(ClassID);
	CurlHandler.parseJson(&jsonBuffer);
	CurlHandler.getFreeFrom();
	CurlHandler.outputInfo();
}

/**
* @brief This function requests Room data from roostertest.windesheim.nl by RoomID.
* @retuns none
* @note needs a pointer to a string buffer & RoomID int
*/
std::string CurlHandler::curlRequest(int ID){
	CURL *curl;
	CURLcode res;
	std::string URLString = CurlHandler.getCurlURL(ID);
	std::string buffer;
	//String to Char array
	char * URL = new char [URLString.length()+1];
	strcpy(URL, URLString.c_str());
	curl = curl_easy_init();
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, URL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_COOKIE, "schoolname=\"Windesheim\"");
		res = curl_easy_perform(curl);
		/* Check for errors */
		if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return buffer;
}

/**
* @brief This function is used by curlRequest as WriteCallback
* @retuns
* @note
*/
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

/**
* @brief This function creates the curl request URL with Date & RoomID.
* @retuns String of URL
* @note Needs a RoomID
*/
std::string CurlHandler::getCurlURL(int ID){
	std::string Date = CurlHandler.getDateField();
	std::string RoomID = CurlHandler.getIdField(ID);
	std::string URL = BaseURL + RequestClassData + Date + RoomID;
	return URL;
}

/**
* @brief This function creates Date part of the curl request URL.
* @retuns String with date in following format: data=YYYYMMDD&
* @note
*/
std::string CurlHandler::getDateField(){
	std::ostringstream streamDate;
	streamDate << "date=" << CurlHandler.getDate() << "&";
	std::string Date(streamDate.str());
	return Date;
}

/**
* @brief This function returns current date.
* @retuns String with date in following format: YYYYMMDD
* @note
*/
std::string CurlHandler::getDate(){
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	std::ostringstream streamDate;
	streamDate << (timePtr->tm_year + 1900) << std::setw(2) << std::setfill('0') << (timePtr->tm_mon + 1) << std::setw(2) << std::setfill('0') << timePtr->tm_mday;
	std::string Date(streamDate.str());
	return Date;
}

/**
* @brief This function creates RoomID part of the curl request URL.
* @retuns String with RoomID in following format: elementId=RoomID.
* @note Needs a RoomID
*/
std::string CurlHandler::getIdField(int ID){
	std::ostringstream streamID;
	streamID << "elementId=" << ID;
	std::string RoomID(streamID.str());
	return RoomID;
}

/**
* @brief This function parses json and saves lesson data
* @retuns none
* @note
*/
void CurlHandler::parseJson(std::string* buffer){
	int lessonId;
	Json::Value obj;
	Json::Reader reader;
	reader.parse(*buffer, obj); // reader can also read strings
   	const Json::Value& characters = obj["result"]["data"]["elementPeriods"][std::to_string(ClassID)]; // array of characters
	for (int i = 0; i < characters.size(); i++){
		if(characters[i]["date"].asString() == CurlHandler.getDate()){
			if(characters[i]["endTime"].asInt() > CurlHandler.getCurrentTime()){
				if(lessonId != characters[i]["lessonId"].asInt()){
					if(characters[i]["startTime"].asInt() < lessonTimeArray[1][1] || lessonTimeArray[1][1] == 0){
						lessonAmount++;
						CurlHandler.moveLessonTimes(1);
						lessonId	= characters[i]["lessonId"].asInt();
						lessonName1	= characters[i]["lessonText"].asString();	//set lessonName1
						lessonTime1	= CurlHandler.getLessonTime(obj, lessonId, 1);		//set lessonTime1
						lessonTeachers1	= CurlHandler.getLessonTeachers(obj, i);			//set lessonTeachers1
					} else if(characters[i]["startTime"].asInt() < lessonTimeArray[2][1] || lessonTimeArray[2][1] == 0){
						lessonAmount++;
						CurlHandler.moveLessonTimes(2);
						lessonId	= characters[i]["lessonId"].asInt();
						lessonName2	= characters[i]["lessonText"].asString();	//set lessonName1
						lessonTime2	= CurlHandler.getLessonTime(obj, lessonId, 2);		//set lessonTime1
						lessonTeachers2 = CurlHandler.getLessonTeachers(obj, i);			//set lessonTeachers1
					} else {
						for(int j = 3; j > lessonAmount; j++){
							if(characters[i]["startTime"].asInt() < lessonTimeArray[j][1] || lessonTimeArray[j][1] == 0){
								lessonAmount++;
								CurlHandler.moveLessonTimes(j);
								lessonId = characters[i]["lessonId"].asInt();
								CurlHandler.getLessonTime(obj, characters[i]["lessonId"].asInt(), j);
								break;
							}
						}
					}
				}       
			}		
		}	
	}
}

/**
* @brief This function returns current time
* @retuns int with hour and minutes in following format: HHMM
* @note
*/
int CurlHandler::getCurrentTime(){
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int time = (timePtr->tm_hour * 100) + timePtr->tm_min;
	return time;
}

/**
* @brief This function movesLessonTimes
* @retuns None
* @note moves until given lesson;
*/
void CurlHandler::moveLessonTimes(int lesson){
	if(lesson == 1 && lessonName1 != ""){
		lessonName2	= lessonName1;
		lessonTime2	= lessonTime1;
		lessonTeachers2	= lessonTeachers1;
	}
	for(int i = lessonAmount; i < lesson; i--){
		lessonTimeArray[i][1] = lessonTimeArray[i-1][1];
		lessonTimeArray[i][2] = lessonTimeArray[i-1][2];
	}
}

/**
* @brief This function gets the endTime of a lesson and returns lessontime
* @retuns String with lesson times in following format: HH:MM - HH:MM
* @note
*/
std::string CurlHandler::getLessonTime(Json::Value obj, int lessonId, int lesson){
	const Json::Value& characters = obj["result"]["data"]["elementPeriods"][std::to_string(ClassID)]; // array of characters
	int startTime = 2400;
	int endTime = 0;
	for (int i = 0; i < characters.size(); i++){
		if(characters[i]["date"].asString() == getDate()){
			if(lessonId == characters[i]["lessonId"].asInt()){
				if(characters[i]["startTime"].asInt() < startTime){
					startTime = characters[i]["startTime"].asInt();
				}
				if(characters[i]["endTime"].asInt() > endTime){
					endTime = characters[i]["endTime"].asInt();
				}
			}
		}
	}
	lessonTimeArray[lesson][1] = startTime;
	lessonTimeArray[lesson][2] = endTime;
	return CurlHandler.formatFullTime(std::to_string(startTime), std::to_string(endTime));
}

/**
* @brief This function merges startTime & endTime String into single formatted string
* @retuns String with lesson times in following format: HH:MM - HH:MM
* @note
*/
std::string CurlHandler::formatFullTime(std::string startTime, std::string endTime){
	std::ostringstream lessonTimeStream;	
	lessonTimeStream << formatTime(startTime) << " - " << formatTime(endTime);
	return lessonTimeStream.str();
}

/**
* @brief This function adds : to time string HHMM -> HH:MM
* @retuns String with times in following format: HH:MM
* @note
*/
std::string CurlHandler::formatTime(std::string time){
	std::ostringstream timeStream;
	timeStream << std::setw(4) << std::setfill('0') << time;
	std::string formattedTime = timeStream.str();
	formattedTime.insert(2,":");
	return CurlHandler.formattedTime;
}

/**
* @brief This function gets the teachers from a lesson
* @retuns String with teacher(s) of a lesson
* @note
*/
std::string CurlHandler::getLessonTeachers(Json::Value obj, int i){
	std::string teachers;
	const Json::Value& characters = obj["result"]["data"]["elementPeriods"][std::to_string(ClassID)]; // array of characters
	const Json::Value& teacherid = characters[i]["elements"];
	for (int j = 0; j < teacherid.size(); j++){
		int type = teacherid[j]["type"].asInt();
		if(type == 2){
			int teacherId = teacherid[j]["id"].asInt();
			const Json::Value& teacherNameJson = obj["result"]["data"]["elements"];	
			for (int k = 0; k < teacherNameJson.size(); k++){
				if(teacherNameJson[k]["id"] == teacherId){
					teachers += teacherNameJson[k]["longName"].asString() + "(" + teacherNameJson[k]["name"].asString() + "), ";
				}	
			}
		}
	}
	//remove ", " from last teacher
	teachers.pop_back();
	teachers.pop_back();
	return teachers;
}

/**
* @brief This function calculates when the room is free
* @retuns none
* @note sets the freeFrom String
*/
void CurlHandler::getFreeFrom(){
	int from = 0;
	int till = 2400;
	if(lessonTimeArray[1][1] > getCurrentTime() || lessonTimeArray[1][1] == 0){
		freeFrom = "Momenteel Vrij";
	} else {
		for(int i = 1; i <= lessonAmount; i++){
			if(from < lessonTimeArray[i][2]){
				from = lessonTimeArray[i][2];
				if(lessonTimeArray[i+1][1] != from && lessonTimeArray[i+1][1] > from){
					till = lessonTimeArray[i+1][1];
					break;
				}
			}
		}
		std::ostringstream freeFromStream;
		if(till == 2400){
			freeFromStream << "Vrij van: " << formatTime(std::to_string(from));
		} else {
			freeFromStream << "Vrij van: " << formatTime(std::to_string(from)) << " - " << formatTime(std::to_string(till));
		}
		freeFrom = freeFromStream.str();
	}
}

/**
* @brief Outputs Lesson info in used format
* @retuns none
* @note
*/
*char  CurlHandler::outputInfo(){
	char *ret = (char *) malloc(sizeof(char) * BUFFER_SIZE):
	sprintf(ret, "%s;%s;%s;%s;%s;%s;%s;", lessonTime1, lessonTime2, lessonName1, lessonName2, lessonTeachers1, lessonTeachers, freeFrom); 
	return ret;
}