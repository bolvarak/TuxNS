///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "DDNS.h"

///////////////////////////////////////////////////////////////////////////////
/// Constructor //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

DDNSController::DDNSController(HeimdallGI::CGI *&hgiRequest, QObject *qoParent) : QObject(qoParent) {
	// Set the request into the instance
	this->mRequest   = hgiRequest;
	// Instantiate the ISPConfig interface
	this->mIspConfig = new HeimdallGI::ISPConfig;
	// Make the API Error signal connection
	connect(&mIspConfig, SIGNAL(apiError(QString,QString)),                         this, SLOT(ispConfigApiErrorOccurred(QString,QString)));
	// Make the Network Error signal connection
	connect(&mIspConfig, SIGNAL(networkError(QNetworkReply::NetworkError,QString)), this, SLOT(ispConfigNetworkErrorOccurred(QNetworkReply::NetworkError,QString)));
	// Make the Response Ready signal connection
	connect(&mIspConfig, SIGNAL(responseReady(QVariantMap)),                        this, SLOT(ispConfigResponseReady(QVariantMap)));
}

///////////////////////////////////////////////////////////////////////////////
/// Destructor ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

DDNSController::~DDNSController() {}

///////////////////////////////////////////////////////////////////////////////
/// Protected Methods ////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void DDNSController::determineContentType() {
	// Determine the content type
	switch(this->mResponseType) {
		// Json
		case ResponseType::Json      : this->mRequest->SetContentType(HeimdallGI::CGI::ContentTypeJSON) ; break;
		// JsonP
		case ResponseType::JsonP     : this->mRequest->SetContentType(HeimdallGI::CGI::ContentTypeJS)   ; break;
		// Tesseract
		case ResponseType::Tesseract : this->mRequest->SetContentType(HeimdallGI::CGI::ContentTypeText) ; break;
		// Xml
		case ResponseType::Xml       : this->mRequest->SetContentType(HeimdallGI::CGI::ContentTypeXML)  ; break;
		// Default to Json
		default                      : this->mRequest->SetContentType(HeimdallGI::CGI::ContentTypeJSON) ; break;
	}
	// We're done
	return;
}

void DDNSController::determineResponseType(HeimdallGI::CGI *&hgiRequest) {
	// Check for a JSONP callback
	if (hgiRequest->GetParam("callback") != NULL) {
		// Set the response type
		this->mResponseType = ResponseType::JsonP;
		// We're done
		return;
	}
	// Check for a format param
	if (hgiRequest->GetParam("format") != NULL) {
		// Check for JSON
		if (hgiRequest->GetParam("format") == "json") {
			// Set the response type
			this->mResponseType = ResponseType::Json;
			// We're done
			return;
		}
		// Check for tesseract
		if ((hgiRequest->GetParam("format") == "tesseract") || (hgiRequest->GetParam("format") == "tml")) {
			// Set the response type
			this->mResponseType = ResponseType::Tesseract;
			// We're done
			return;
		}
		// Check for XML
		if (hgiRequest->GetParam("format") == "xml") {
			// Set the response type
			this->mResponseType = ResponseType::Xml;
			// We're done
			return;
		}
	}
	// Default the response type to JSON
	this->mResponseType = ResponseType::Json;
	// We're done
	return;
}

void DDNSController::determineTemplate(HeimdallGI::View *&hgiResponse) {
	// Determine the response type
	switch (this->mResponseType) {
		// Json
		case ResponseType::Json      : hgiResponse->SetTemplate("api/json")      ; break;
		// JsonP
		case ResponseType::JsonP     : hgiResponse->SetTemplate("api/jsonp")     ; break;
		// Tesseract
		case ResponseType::Tesseract : hgiResponse->SetTemplate("api/tesseract") ; break;
		// Xml
		case ResponseType::Xml       : hgiResponse->SetTemplate("api/xml")       ; break;
		// Default to Json
		default                      : hgiResponse->SetTemplate("api/json")      ; break;
	}
	// We're done
	return;
}

void DDNSController::encodeResponse(HeimdallGI::View *&hgiResponse, QString strPageValueName, QVariantMap qvmResponse) {

}

void DDNSController::signIntoIspConfig() {
	// Suppress the response
	this->suppressResponse();
	// A request is pending
	this->requestIsPending();
	// Make the request
	this->mIspConfig->startSession();
	// Wait for the response
	while (this->mPendingRequest) {
		// Loop
		continue;
	}

}

///////////////////////////////////////////////////////////////////////////////
/// Protected Slots //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void DDNSController::ispConfigResponseReady(QVariantMap qvmResponse) {
	// Set the response into the instance
	this->mResponse = qvmResponse;

}

///////////////////////////////////////////////////////////////////////////////
/// Public Methods ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
/// Public Slots & View Methods //////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


