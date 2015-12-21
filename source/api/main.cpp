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
	// DDNSController* ctrlDDNS      = new DDNSController(hgiGateway);
	// Set the logger into the router
	hgiRouter->SetLogger(hgiLog);
	// Define the GeoIP Dynamic Route
	hgiRouter->AddRoute("/geoip/json",                                                                         ctrlGeoIP, "dynamicJSON");
	hgiRouter->AddRoute("/geoip/xml",                                                                          ctrlGeoIP, "dynamicXML");
	// Define the GeoIP Static Route
	hgiRouter->AddRoute("/geoip/[:ipAddress]/json",                                                            ctrlGeoIP, "staticJSON");
	hgiRouter->AddRoute("/geoip/[:ipAddress]/xml",                                                             ctrlGeoIP, "staticXML");
    /* Define the DDNS Zone Routes
	hgiRouter->AddRoute("/ddns/[:domainName]/[:ipAddress]/[:nameServer1]/[:nameServer2]/[:adminEmail]/add",    ctrlDDNS,  "createZone");
	hgiRouter->AddRoute("/ddns/[:domainName]/delete",                                                          ctrlDDNS,  "deleteZone");
	hgiRouter->AddRoute("/ddns/[:domainName]",                                                                 ctrlDDNS,  "getZone");
	hgiRouter->AddRoute("/ddns/[:domainName]/[:ipAddress]/[:nameServer1]/[:nameServer2]/[:adminEmail]",        ctrlDDNS,  "updateZone");
	// Define the DDNS A Record Routes
	hgiRouter->AddRoute("/ddns/[:domainName]/a/[:recordName]/[:ipAddress]/add",                                ctrlDDNS,  "createARecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/a/[:recordName]/delete",                                          ctrlDDNS,  "deleteARecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/a/[:recordName]",                                                 ctrlDDNS,  "getARecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/a/[:recordName]/[:ipAddress]",                                    ctrlDDNS,  "updateARecord");
	// Define the DDNS AAAA Record Routes
	hgiRouter->AddRoute("/ddns/[:domainName]/aaaa/[:recordName]/[:ipAddress]/add",                             ctrlDDNS,  "createAAAARecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/aaaa/[:recordName]/delete",                                       ctrlDDNS,  "deleteAAAARecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/aaaa/[:recordName]",                                              ctrlDDNS,  "getAAAARecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/aaaa/[:recordName]/[:ipAddress]",                                 ctrlDDNS,  "updateARecord");
	// Define the DDNS Alias Record Routes
	hgiRouter->AddRoute("/ddns/[:domainName]/alias/[:recordName]/[:targetHost]/add",                           ctrlDDNS,  "createAliasRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/alias/[:recordName]/delete",                                      ctrlDDNS,  "deleteAliasRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/alias/[:recordName]",                                             ctrlDDNS,  "getAliasRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/alias/[:recordName]/[:targetHost]",                               ctrlDDNS,  "updateAliasRecord");
	// Define the DDNS CNAME Record Routes
	hgiRouter->AddRoute("/ddns/[:domainName]/cname/[:recordName]/[:targetHost]/add",                           ctrlDDNS,  "createCNameRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/cname/[:recordName]/delete",                                      ctrlDDNS,  "deleteCNameRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/cname/[:recordName]",                                             ctrlDDNS,  "getCNameRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/cname/[:recordName]/[:targetHost]",                               ctrlDDNS,  "updateCNameRecord");
	// Define the DDNS MX Record Routes
	hgiRouter->AddRoute("/ddns/[:domainName]/mx/[:recordName]/[:priority]/[:targetHost]/add",                  ctrlDDNS,  "createMXRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/mx/[:recordName]/[:priority]/delete",                             ctrlDDNS,  "deleteMXRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/mx/[:recordName]",                                                ctrlDDNS,  "getMXRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/mx/[:recordName]/[:priority]/[:targetHost]",                      ctrlDDNS,  "updateMXRecord");
	// Define the DDNS NS Record Routes
	hgiRouter->AddRoute("/ddns/[:domainName]/ns/[:targetHost]/add",                                            ctrlDDNS,  "createNSRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/ns/[:targetHost]/delete",                                         ctrlDDNS,  "deleteNSRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/ns",                                                              ctrlDDNS,  "getNSRecord");
	// Define the DDNS SRV Record Routes
	hgiRouter->AddRoute("/ddns/[:domainName]/srv/[:hostName]/[:targetHost]/[:weight]/[:port]/[:priority]/add", ctrlDDNS,  "createSRVRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/srv/[:hostName]/[:targetHost]/delete",                            ctrlDDNS,  "deleteSRVRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/srv/[:hostName]",                                                 ctrlDDNS,  "getSRVRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/srv/[:hostName]/[:targetHost]/[:weight]/[:port]/[:priority]",     ctrlDDNS,  "updateSRVRecord");
	// Define the DDNS TXT Record Routes
	hgiRouter->AddRoute("/ddns/[:domainName]/alias/[:hostName]/[:textData]/add",                               ctrlDDNS,  "createTXTRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/alias/[:hostName]/delete",                                        ctrlDDNS,  "deleteTXTRecord");
	hgiRouter->AddRoute("/ddns/[:domainName]/alias/[:hostName]",                                               ctrlDDNS,  "getTXTRecord");
    hgiRouter->AddRoute("/ddns/[:domainName]/alias/[:hostName]/[:textData]",                                   ctrlDDNS,  "updateTXTRecord");*/
	// Grab the View
	// HeimdallGI::View* hgiResponse = hgiRouter->Execute(hgiGateway, "/geoip/8.8.8.8/json");
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
