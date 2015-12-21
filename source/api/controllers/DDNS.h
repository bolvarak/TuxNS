///////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifndef DDNSCONTROLLER_H
#define DDNSCONTROLLER_H

///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QByteArray"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonParseError"
#include "QJsonValue"
#include "QObject"
#include "QString"
#include "QStringList"
#include "QVariant"
#include "QVariantList"
#include "QVariantMap"
#include "externals/HeimdallGI/CGI.h"
#include "externals/HeimdallGI/Configuration.h"
#include "externals/HeimdallGI/DBI.h"
#include "externals/HeimdallGI/ISPConfig.h"
#include "externals/HeimdallGI/View.h"

///////////////////////////////////////////////////////////////////////////////
/// DDNSController Class Definition //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class DDNSController : public QObject
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
		 * @paragraph This property contains the instance of our ISPConfig interface
		 * @brief DDNSController::mIspConfig
		 * @var HeimdallGI::ISPConfig*
		 */
		HeimdallGI::ISPConfig* mIspConfig;

		/**
		 * @paragraph This property tells the system whether or not a request is pending
		 * @brief DDNSController::mPendingRequest
		 * @var bool
		 */
		bool mPendingRequest;

		/**
		 * This property contains the request object
		 * @brief DDNSController::mRequest
		 * @var HeimdallGI::CGI* &mRequest
		 */
		HeimdallGI::CGI* mRequest;

		/**
		 * @paragraph This property contains the response from the interface
		 * @brief DDNSController::mResponse
		 * @var QVariantMap
		 */
		QVariantMap mResponse;

		/**
		 * @paragraph This property tells the system what type of response to send
		 * @brief DDNSController::mResponseType
		 * @var DDNSController::ResponseType
		 */
		ResponseType mResponseType;

		/**
		 * @paragraph This property contains the current session ID for the ISPConfig API
		 * @brief DDNSController::mSessionID
		 * @var QString
		 */
		QString mSessionID;

		/**
		 * @paragraph This property tells the system whether or not to suppress the sending of the response
		 * @brief DDNSController::mSuppressResponse
		 * @var bool
		 */
		bool mSuppressResponse;

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method determines the content type for the response
		 * @brief DDNSController::determineContentType()
		 * @param HeimdallGI::CGI* hgiRequest
		 * @return void
		 */
		void determineContentType(HeimdallGI::CGI *&hgiRequest);

		/**
		 * @paragraph This method determines the response type of the request
		 * @brief DDNSController::determineResponseType()
		 * @return DDNSController::ResponseType
		 */
		ResponseType determineResponseType();

		/**
		 * @paragraph This method determines the template to use for the response
		 * @brief DDNSController::determineTemplate()
		 * @return void
		 */
		void determineTemplate(HeimdallGI::View *&hgiResponse);

		/**
		 * @paragraph This method encodes the response map into the proper format
		 * @brief DDNSController::encodeResponse()
		 * @param HeimdallGI::View* hgiResponse
		 * @param QString strPageValueName
		 * @param QVariantMap qvmResponse
		 * @return void
		 */
		void encodeResponse(HeimdallGI::View *&hgiResponse, QString strPageValueName, QVariantMap qvmResponse);

		/**
		 * @paragraph This method will initialize a session with the ISPConfig API
		 * @brief DDNSController::signIntoIspConfig()
		 * @return void
		 */
		void signIntoIspConfig();

	///////////////////////////////////////////////////////////////////////////
	/// Protected Slots //////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	protected slots:

		/**
		 * @paragraph This slot gets called when an ISPConfig API error occurs
		 * @brief DDNSController::ispConfigApiErrorOccurred()
		 * @param QString strCode
		 * @param QString strErrorMessage
		 * @return void
		 */
		void ispConfigApiErrorOccurred(QString strCode, QString strErrorMessage);

		/**
		 * @paragraph This slot gets called when there was a network error while communicating with the ISPConfig API
		 * @brief DDNSController::ispConfigNetworkErrorOccurred()
		 * @param QNetworkReply::NetworkError qnrError
		 * @param QString strErrorMessage
		 * @return void
		 */
		void ispConfigNetworkErrorOccurred(QNetworkReply::NetworkError qnrError, QString strErrorMessage);

		/**
		 * @paragraph This slot gets called when the response from the ISPConfig API is ready
		 * @brief DDNSController::ispConfigResponseReady()
		 * @param QVariantMap qvmResponse
		 * @return void
		 */
		void ispConfigResponseReady(QVariantMap qvmResponse);

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public:

		///////////////////////////////////////////////////////////////////////
		/// Enumerations /////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This enumeration contains the different response types supported by the API
		 * @brief DDNSController::ResponseType
		 * @var enum
		 */
		enum ResponseType {
			Error     = 0x001,
			Html      = 0x002,
			Json      = 0x003,
			JsonP     = 0x004,
			None      = 0x000,
			Tesseract = 0x005,
			Unknown   = 0x006,
			Xml       = 0x007
		};

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		explicit DDNSController(HeimdallGI::CGI *&hgiRequest, QObject *qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Destructor ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		~DDNSController();

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method tells the system to not suppress the response
		 * @brief DDNSController::doNotSuppressResponse()
		 * @return bool
		 */
		bool doNotSuppressResponse() { this->mSuppressResponse = false; return false; }

		/**
		 * @paragraph This method tells the system that no request is pending
		 * @brief DDNSController::requestIsNotPending()
		 * @return bool
		 */
		bool requestIsNotPending()   { this->mPendingRequest   = false; return false; }

		/**
		 * @paragraph This method tells the system that a request is pending
		 * @brief DDNSController::requestIsPending()
		 * @return bool
		 */
		bool requestIsPending()      { this->mPendingRequest   = true;  return true; }

		/**
		 * @paragraph This method tells the system to suppress the response
		 * @brief DDNSController::suppressResponse()
		 * @return bool
		 */
		bool suppressResponse()      { this->mSuppressResponse = true;  return true; }


	///////////////////////////////////////////////////////////////////////////
	/// Public Slots & View Methods //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public slots:




///////////////////////////////////////////////////////////////////////////////
/// End DDNSController Class Definition //////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

};

///////////////////////////////////////////////////////////////////////////////
/// End Definitions //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#endif
