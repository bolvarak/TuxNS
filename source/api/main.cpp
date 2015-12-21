///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QCoreApplication"
#include "QVariant"
#include "externals/HeimdallGI/CGI.h"
#include "externals/HeimdallGI/Configuration.h"
#include "externals/HeimdallGI/DBI.h"
#include "externals/HeimdallGI/Log.h"
#include "externals/HeimdallGI/Router.h"
#include "externals/HeimdallGI/Template.h"
#include "externals/HeimdallGI/View.h"

///////////////////////////////////////////////////////////////////////////////
/// Controllers //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

//#include "controllers/DDNS.h"
#include "controllers/GeoIP.h"

///////////////////////////////////////////////////////////////////////////////
/// Dispatch /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This function sets up and dispatches the framework and application
 * @brief main()
 * @param int intArguments
 * @param char* chrArguments
 * @return int
 */
int main(int intArguments, char* chrArguments[]) {
	// Create the application
	QCoreApplication qcaAPI(intArguments, chrArguments);
	// Instantiate the CGI wrapper
	HeimdallGI::CGI* hgiGateway   = HeimdallGI::CGI::Instance();
	// Instantiate the Router
	HeimdallGI::Router* hgiRouter = HeimdallGI::Router::Instance();
	// Instantiate the Logger
	HeimdallGI::Log* hgiLog       = HeimdallGI::Log::Instance();
	// Instantiate the GeoIP controller
	GeoIPController* ctrlGeoIP    = new GeoIPController(hgiGateway);
	// Instantiate the DDNS Controller
	DDNSController* ctrlDDNS      = new DDNSController(hgiGateway);
	// Set the logger into the router
	hgiRouter->SetLogger(hgiLog);
	// Define the GeoIP Dynamic Route
	hgiRouter->AddRoute("/geoip/json",              ctrlGeoIP, "dynamicJSON");
	hgiRouter->AddRoute("/geoip/xml",               ctrlGeoIP, "dynamicXML");
	// Define the GeoIP Static Route
	hgiRouter->AddRoute("/geoip/[:ipAddress]/json", ctrlGeoIP, "staticJSON");
	hgiRouter->AddRoute("/geoip/[:ipAddress]/xml",  ctrlGeoIP, "staticXML");
	// DDNS Routes
	hgiRouter->AddRoute("/ddns/account-details",    )
	// Define the response
	HeimdallGI::View* hgiResponse;
	// Check for a defned request path
	if (intArguments >= 2) {
		// Execute the defined request
		hgiResponse = hgiRouter->Execute(hgiGateway, chrArguments[1]);
	} else {
		// Execute the dynamic request
		hgiResponse = hgiRouter->Execute(hgiGateway);
	}
	// Send the Response
	hgiGateway
		->SetContent(hgiResponse->GetTemplate())
		->WriteResponse();
	// We're done
	return 0;
}
