///////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifndef GEOIPCONTROLLER_H
#define GEOIPCONTROLLER_H

///////////////////////////////////////////////////////////////////////////////
/// Includes /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QtCore/QByteArray"
#include "QtCore/QEventLoop"
#include "QtNetwork/QHostAddress"
#include "QtCore/QJsonDocument"
#include "QtCore/QJsonObject"
#include "QtCore/QObject"
#include "QtCore/QProcess"
#include "QtCore/QString"
#include "QtCore/QStringList"
#include "QtCore/QTime"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtCore/QVariant"
#include "QtCore/QVariantMap"
#include "QtCore/QXmlStreamWriter"
#include "../externals/HeimdallGI/CGI.h"
#include "../externals/HeimdallGI/Configuration.h"
#include "../externals/HeimdallGI/DBI.h"
#include "../externals/HeimdallGI/MaxMind.h"
#include "../externals/HeimdallGI/Log.h"
#include "../externals/HeimdallGI/View.h"

///////////////////////////////////////////////////////////////////////////////
/// GeoIPController Class Definition /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class GeoIPController : public QObject
{
	/**
	 * Ensure this class is recognized by Qt
	 */
	Q_OBJECT

	///////////////////////////////////////////////////////////////////////////
	/// Protected Methods & Properties ///////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	protected:

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * This property contains our MaxMind DB interface
		 * @brief GeoIPController::mMaxMind
		 * @var HeimdallGI::MaxMind
		 */
		HeimdallGI::MaxMind mMaxMind;

		/**
		 * @paragraph This property contains the logger instance
		 * @brief GeoIPController::mLogger
		 * @var HeimdallGI::Log* GeoIPController::mLogger
		 */
		HeimdallGI::Log* mLogger;

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method logs the GeoIP request
		 * @brief GeoIPController::logRequest()
		 * @param HeimdallGI::CGI *hgiRequest
		 * @param QString strResponseFormat
		 * @param QString strResponse
		 * @return void
		 */
		void logRequest(HeimdallGI::CGI *hgiRequest, QString strResponseFormat, QString strResponse);

		/**
		 * @paragraph This method determines which database to open based on the IP address version
		 * @brief GeoIPController::openConnection()
		 * @param const QHostAddress qhaIpAddress
		 * @return void
		 */
		void openConnection(const QHostAddress &qhaIpAddress);

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public:

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		explicit GeoIPController(HeimdallGI::CGI *&hgiRequest, QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Destructor ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		~GeoIPController();

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the framework logger into the instance
		 * @brief GeoIPController::setLogger()
		 * @param HeimdallGI::Log* hgiLog
		 * @return GeoIPController*
		 */
		GeoIPController* setLogger(HeimdallGI::Log* &hgiLog) { this->mLogger = hgiLog; return this; }

	///////////////////////////////////////////////////////////////////////////
	/// View Methods /////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public slots:

		/**
		 * @paragraph This method loads the geolocation based on the client's IP address and returns JSON/JSONP
		 * @brief GeoIPController::dynamicJSON()
		 * @param HeimdallGI::CGI* hgiRequest
		 * @param HeimdallGI::View* hgiResponse
		 * @return void
		 */
		void dynamicJSON(HeimdallGI::CGI* &hgiRequest, HeimdallGI::View* &hgiResponse);

		/**
		 * @paragraph This method loads the geolocation based on the client;s IP address and returns XML
		 * @brief GeoIPController::dynamicXML()
		 * @param HeimdallGI::CGI* hgiRequest
		 * @param HeimdallGI::View* hgiResponse
		 */
		void dynamicXML(HeimdallGI::CGI* &hgiRequest, HeimdallGI::View* &hgiResponse);

		/**
		 * @paragraph This method loads the geolocation based on a provided IP address and returns JSON/JSONP
		 * @brief GeoIPController::staticJSON()
		 * @param HeimdallGI::CGI* hgiRequest
		 * @param HeimdallGI::View* hgiResponse
		 */
		void staticJSON(HeimdallGI::CGI* &hgiRequest, HeimdallGI::View* &hgiResponse);

		/**
		 * @paragraph This method loads the geolocation based on a provided IP address and returns XML
		 * @brief GeoIPController::staticXML()
		 * @param HeimdallGI::CGI* hgiRequest
		 * @param HeimdallGI::View* hgiResponse
		 */
		void staticXML(HeimdallGI::CGI* &hgiRequest, HeimdallGI::View* &hgiResponse);

///////////////////////////////////////////////////////////////////////////////
/// End GeoIPController Class Definition /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

};

///////////////////////////////////////////////////////////////////////////////
/// End Definitions //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#endif
