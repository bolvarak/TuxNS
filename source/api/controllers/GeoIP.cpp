///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "GeoIP.h"

///////////////////////////////////////////////////////////////////////////////
/// Constructor //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

GeoIPController::GeoIPController(HeimdallGI::CGI *&hgiRequest, QObject* qoParent) : QObject(qoParent) {}

///////////////////////////////////////////////////////////////////////////////
/// Destructor ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

GeoIPController::~GeoIPController() {}

///////////////////////////////////////////////////////////////////////////////
/// Protected Methods ////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void GeoIPController::logRequest(HeimdallGI::CGI *hgiRequest, QString strResponseFormat, QString strResponse) {
	// Determine the Requestor IP address
	const QHostAddress qhaIpAddress    = QHostAddress(hgiRequest->GetRequestHeader("REMOTE_ADDR"));
	// Determine the GeoIP Address
	const QHostAddress qhaGeoIpAddress = ((hgiRequest->GetParam("ipAddress") == NULL || hgiRequest->GetParam("ipAddress").isEmpty()) ? QHostAddress(hgiRequest->GetRequestHeader("REMOTE_ADDR")) : QHostAddress(hgiRequest->GetParam("ipAddress")));
	// Initialize the database connection
	QSqlDatabase qsdAPI                = QSqlDatabase::addDatabase(HeimdallGI::Configuration::Get("Database.sqlDriver").toString());
	// Set the host name
	qsdAPI.setHostName(HeimdallGI::Configuration::Get("Database.serverHost").toString());
	// Set the host port
	qsdAPI.setPort(HeimdallGI::Configuration::Get("Database.serverPort").toInt());
	// Set the database name
	qsdAPI.setDatabaseName(HeimdallGI::Configuration::Get("Database.dataBase").toString());
	// Set the database username
	qsdAPI.setUserName(HeimdallGI::Configuration::Get("Database.userName").toString());
	// Set the database password
	qsdAPI.setPassword(HeimdallGI::Configuration::Get("Database.userPass").toString());
	// Open the database connection
	if (qsdAPI.open()) {
		// Create the query
		QSqlQuery* qsqRequest = new QSqlQuery(qsdAPI);
		// Prepare the query
		qsqRequest->prepare(HeimdallGI::Configuration::Get("sqlQueries.logRequest").toString());
		// Bind the requestor address and version
		qsqRequest->addBindValue(qhaIpAddress.toString());
		qsqRequest->addBindValue((qhaIpAddress.protocol() == QAbstractSocket::IPv6Protocol) ? 6 : 4);
		// Bind the GeoIP address and version
		qsqRequest->addBindValue(qhaGeoIpAddress.toString());
		qsqRequest->addBindValue((qhaGeoIpAddress.protocol() == QAbstractSocket::IPv6Protocol) ? 6 : 4);
		// Bind the response format
		qsqRequest->addBindValue(strResponseFormat);
		// Bind the response
		qsqRequest->addBindValue(strResponse);
		// Execute the query
		if (qsqRequest->exec()) {
			// We're done with this query
			qsqRequest->finish();
			// We're done with the datase connection
			qsdAPI.close();
		}
	}
}

void GeoIPController::openConnection(const QHostAddress &qhaIpAddress) {
	// Check for IPv6
	if (qhaIpAddress.protocol() == QAbstractSocket::IPv6Protocol) {
		// Initialize the GeoIP Database
		this->mMaxMind.openConnection(HeimdallGI::Configuration::Get("Paths.geoIpCityDatabase6").toString(), HeimdallGI::Configuration::Get("Paths.geoIpIspDatabase6").toString());
	} else {
		// Initialize the GeoIP Database
		this->mMaxMind.openConnection(HeimdallGI::Configuration::Get("Paths.geoIpCityDatabase").toString(), HeimdallGI::Configuration::Get("Paths.geoIpIspDatabase").toString());
	}
}

///////////////////////////////////////////////////////////////////////////////
/// View Methods /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void GeoIPController::dynamicJSON(HeimdallGI::CGI *&hgiRequest, HeimdallGI::View *&hgiResponse) {
	// Default the response format
	QString strResponseFormat = "json";
	// Check for JSONP
	if (hgiRequest->GetParam("callback") != NULL) {
		// Set the view for JSONP
		hgiResponse->SetTemplate("api/jsonp");
		// Set the content type
		hgiRequest->SetContentType(HeimdallGI::CGI::ContentTypeJS);
		// Set the callback into the view
		hgiResponse->SetPageValue("callBack", hgiRequest->GetParam("callback"));
		// Reset the response format
		strResponseFormat = "jsonp";
	} else {
		// Set the view for JSON
		hgiResponse->SetTemplate("api/json");
		// Set the content type
		hgiRequest->SetContentType(HeimdallGI::CGI::ContentTypeJSON);
	}
	// Create the JSON placeholder
	QJsonObject qjoResponse;
	// Create the timer
	QTime qtTimer;
	// Create a passive placeholder
	int intTimePassed;
	// Start the timer
	qtTimer.start();
	// Open the connection
	this->openConnection(QHostAddress(hgiRequest->GetRequestHeader("REMOTE_ADDR")));
	// Query the database
	HeimdallGI::GeoRecord geoRecord = this->mMaxMind.findByAddress(QHostAddress(hgiRequest->GetRequestHeader("REMOTE_ADDR")));
	// Create the QProcess call to traceroute
	// QProcess* qpTraceRoute = new QProcess();
	// Create the arguments list
	// QStringList qslArguments;
	// Add the max hops
	// qslArguments.append("--max-hops=120");
	// Add the IP address
	// qslArguments.append(hgiRequest->GetRequestHeader("REMOTE_ADDR"));
	// Start the trace
	// qpTraceRoute->start("traceroute", qslArguments);
	// Set the read channel
	// qpTraceRoute->setReadChannelMode(QProcess::MergedChannels);
	// Wait for bytes to be written
	// qpTraceRoute->waitForBytesWritten();
	// Wait for the command to finish
	// qpTraceRoute->waitForFinished(30000);
	// Grab the elapsed time
	intTimePassed = qtTimer.elapsed();
	// Split the data
	// QStringList qslTraces = QString::fromLatin1(qpTraceRoute->readAll()).split(QRegularExpression("\\n"));
	// Remove the first trace
	// qslTraces.removeFirst();
	// Create the list placeholder
	// QJsonArray qjaTraceRoute;
/*
	// Iterate over the list
	for (int intTrace = 0; intTrace < qslTraces.size(); ++intTrace) {
		// Split the trace
		QStringList qslTrace = qslTraces.at(intTrace).split(QRegularExpression("\\s\\s"));
		// Create the map
		QVariantMap qvmTrace;
		// Add the hop
		qvmTrace.insert("hop",       (0 < qslTrace.size() ? qslTrace.at(0).trimmed() : NULL));
		// Add the host name
		qvmTrace.insert("hostName",  (1 < qslTrace.size() ? qslTrace.at(1).trimmed() : NULL));
		// Add the first datagram
		qvmTrace.insert("dataGram1", (2 < qslTrace.size() ? qslTrace.at(2).trimmed() : NULL));
		// Add the second datagram
		qvmTrace.insert("dataGram2", (3 < qslTrace.size() ? qslTrace.at(3).trimmed() : NULL));
		// Add the third datagram
		qvmTrace.insert("dataGram3", (4 < qslTrace.size() ? qslTrace.at(4).trimmed() : NULL));
		// Append the map
		qjaTraceRoute.append(QJsonValue(QJsonObject::fromVariantMap(qvmTrace)));
	}
*/
	// Grab the elapsed time
	intTimePassed = qtTimer.elapsed();
	// Set the record into the response
	qjoResponse.insert("city",         geoRecord.mCity);
	qjoResponse.insert("region",       geoRecord.mRegion);
	qjoResponse.insert("country",      geoRecord.mCountry);
	qjoResponse.insert("countryISO",   geoRecord.mCountryISO);
	qjoResponse.insert("continentISO", geoRecord.mContinentISO);
	qjoResponse.insert("isp",          geoRecord.mISP);
	qjoResponse.insert("latitude",     geoRecord.mLatitude);
	qjoResponse.insert("longitude",    geoRecord.mLongitude);
	qjoResponse.insert("timeZone",     geoRecord.mTimeZone);
	qjoResponse.insert("ipAddress",    hgiRequest->GetRequestHeader("REMOTE_ADDR"));
	qjoResponse.insert("timeTaken",    (intTimePassed / 1000));
	qjoResponse.insert("timeTakenMS",  intTimePassed);
	qjoResponse.insert("referenceURI", QString("https://api.cdndepo.com/geoip/%1/json").arg(hgiRequest->GetRequestHeader("REMOTE_ADDR")));
	qjoResponse.insert("userAgent",    hgiRequest->GetRequestHeader("HTTP_USER_AGENT"));
	// qjoResponse.insert("traceRoute",   QJsonValue(qjaTraceRoute));
	// Set the JSON into the view
	hgiResponse->SetPageValue("responseJSON", QJsonDocument(qjoResponse).toJson());
	// Log the request
	this->logRequest(hgiRequest, strResponseFormat, QString(QJsonDocument(qjoResponse).toJson()));
}

void GeoIPController::dynamicXML(HeimdallGI::CGI *&hgiRequest, HeimdallGI::View *&hgiResponse) {
	// Set the view for XML
	hgiResponse->SetTemplate("api/xml");
	// Set the content type
	hgiRequest->SetContentType(HeimdallGI::CGI::ContentTypeXML);
	// Create the buffer
	QByteArray qbaXML;
	// Create the XML stream
	QXmlStreamWriter qxswXML(&qbaXML);
	// Start the XML document
	qxswXML.setAutoFormatting(true);
	qxswXML.writeStartDocument();
	// Create the timer
	QTime qtTimer;
	// Create a passive placeholder
	int intTimePassed;
	// Start the timer
	qtTimer.start();
	// Open the connection
	this->openConnection(QHostAddress(hgiRequest->GetRequestHeader("REMOTE_ADDR")));
	// Query the database
	HeimdallGI::GeoRecord geoRecord = this->mMaxMind.findByAddress(QHostAddress(hgiRequest->GetRequestHeader("REMOTE_ADDR")));
	// Create the QProcess call to traceroute
	// QProcess* qpTraceRoute = new QProcess();
	// Create the arguments list
	// QStringList qslArguments;
	// Add the max hops
	// qslArguments.append("--max-hops=120");
	// Add the IP address
	// qslArguments.append(hgiRequest->GetRequestHeader("REMOTE_ADDR"));
	// Start the trace
	// qpTraceRoute->start("traceroute", qslArguments);
	// Set the read channel
	// qpTraceRoute->setReadChannelMode(QProcess::MergedChannels);
	// Wait for bytes to be written
	// qpTraceRoute->waitForBytesWritten();
	// Wait for the command to finish
	// qpTraceRoute->waitForFinished(30000);
	// Grab the elapsed time
	intTimePassed = qtTimer.elapsed();
	// Split the data
	// QStringList qslTraces = QString::fromLatin1(qpTraceRoute->readAll()).split(QRegularExpression("\\n"));
	// Remove the first line
	// qslTraces.removeFirst();
	// Open the element
	qxswXML.writeStartElement("geoIP");
	// Set the reference into the element
	qxswXML.writeAttribute("href", QString("https://api.cdndepo.com/geoip/%1/xml").arg(hgiRequest->GetRequestHeader("REMOTE_ADDR")));
	// Set the time taken in ms in to the element
	qxswXML.writeAttribute("timeTaken", QString::number((intTimePassed / 1000), 'g', 3));
	qxswXML.writeAttribute("timeTakenMS", QString::number(intTimePassed, 'g', 3));
	// Set the record into the response
	qxswXML.writeTextElement("city",         geoRecord.mCity);
	qxswXML.writeTextElement("region",       geoRecord.mRegion);
	qxswXML.writeTextElement("country",      geoRecord.mCountry);
	qxswXML.writeTextElement("countryISO",   geoRecord.mCountryISO);
	qxswXML.writeTextElement("continentISO", geoRecord.mContinentISO);
	qxswXML.writeTextElement("isp",          geoRecord.mISP);
	qxswXML.writeTextElement("latitude",     QString::number(geoRecord.mLatitude,  'g', 18));
	qxswXML.writeTextElement("longitude",    QString::number(geoRecord.mLongitude, 'g', 18));
	qxswXML.writeTextElement("timeZone",     geoRecord.mTimeZone);
	qxswXML.writeTextElement("ipAddress",    hgiRequest->GetRequestHeader("REMOTE_ADDR"));
	qxswXML.writeTextElement("timeTaken",    QString::number((intTimePassed / 1000), 'g', 3));
	qxswXML.writeTextElement("timeTakenMS",  QString::number(intTimePassed, 'g', 3));
	qxswXML.writeTextElement("referenceURI", QString("https://api.cdndepo.com/geoip/%1/xml").arg(hgiRequest->GetRequestHeader("REMOTE_ADDR")));
	qxswXML.writeTextElement("userAgent",    hgiRequest->GetRequestHeader("HTTP_USER_AGENT"));
/*
	// Create a new element
	qxswXML.writeStartElement("traceRoute");
	// Iterate over the list
	for (int intTrace = 0; intTrace < qslTraces.size(); ++intTrace) {
		// Start the hop element
		qxswXML.writeStartElement("hop");
		// Split the trace
		QStringList qslTrace = qslTraces.at(intTrace).split(QRegularExpression("\\s\\s"));
		// Add the attribute
		qxswXML.writeAttribute("number", qslTrace.at(0).trimmed());
		// Add the hop
		qxswXML.writeTextElement("hopNumber", (0 < qslTrace.size() ? qslTrace.at(0).trimmed() : QString::null));
		// Add the host name
		qxswXML.writeTextElement("hostName",  (1 < qslTrace.size() ? qslTrace.at(1).trimmed() : QString::null));
		// Add the first datagram
		qxswXML.writeTextElement("dataGram1", (2 < qslTrace.size() ? qslTrace.at(2).trimmed() : QString::null));
		// Add the second datagram
		qxswXML.writeTextElement("dataGram2", (3 < qslTrace.size() ? qslTrace.at(3).trimmed() : QString::null));
		// Add the third datagram
		qxswXML.writeTextElement("dataGram3", (4 < qslTrace.size() ? qslTrace.at(4).trimmed() : QString::null));
		// Close the hop
		qxswXML.writeEndElement();
	}
	// Close the trace route element
	qxswXML.writeEndElement();
*/
	// Close the element
	qxswXML.writeEndElement();
	// Close the document
	qxswXML.writeEndDocument();
	// Set the XML into the view
	hgiResponse->SetPageValue("responseXML", QString(qbaXML));
	// Log the request
	this->logRequest(hgiRequest, "xml", QString(qbaXML));
}

void GeoIPController::staticJSON(HeimdallGI::CGI *&hgiRequest, HeimdallGI::View *&hgiResponse) {
	// Default the response format
	QString strResponseFormat = "json";
	// Check for JSONP
	if (hgiRequest->GetParam("callback") != NULL) {
		// Set the view for JSONP
		hgiResponse->SetTemplate("api/jsonp");
		// Set the content type
		hgiRequest->SetContentType(HeimdallGI::CGI::ContentTypeJS);
		// Set the callback into the view
		hgiResponse->SetPageValue("callBack", hgiRequest->GetParam("callback"));
		// Reset the response format
		strResponseFormat = "jsonp";
	} else {
		// Set the view for JSON
		hgiResponse->SetTemplate("api/json");
		// Set the content type
		hgiRequest->SetContentType(HeimdallGI::CGI::ContentTypeJSON);
	}
	// Create the JSON placeholder
	QJsonObject qjoResponse;
	// Check for an IP
	if ((hgiRequest->GetParam("ipAddress") == NULL) || hgiRequest->GetParam("ipAddress").isEmpty()) {
		// Aet the error
		qjoResponse.insert("error", QString("No IP Address Found"));
		// Set the response
		hgiResponse->SetPageValue("responseJSON", QJsonDocument(qjoResponse).toJson());
		// We're done
		return;
	}
	// Create the timer
	QTime qtTimer;
	// Create a passive placeholder
	int intTimePassed;
	// Start the timer
	qtTimer.start();
	// Open the connection
	this->openConnection(QHostAddress(hgiRequest->GetParam("ipAddress")));
	// Query the database
	HeimdallGI::GeoRecord geoRecord = this->mMaxMind.findByAddress(QHostAddress(hgiRequest->GetParam("ipAddress")));
	// Create the QProcess call to traceroute
	// QProcess* qpTraceRoute = new QProcess();
	// Create the arguments list
	// QStringList qslArguments;
	// Add the max hops
	// qslArguments.append("--max-hops=120");
	// Add the IP address
	// qslArguments.append(hgiRequest->GetParam("ipAddress"));
	// Start the trace
	// qpTraceRoute->start("traceroute", qslArguments);
	// Set the read channel
	// qpTraceRoute->setReadChannelMode(QProcess::MergedChannels);
	// Wait for bytes to be written
	// qpTraceRoute->waitForBytesWritten();
	// Wait for the command to finish
	// qpTraceRoute->waitForFinished(30000);
	// Grab the elapsed time
	// intTimePassed = qtTimer.elapsed();
	// Split the data
	// QStringList qslTraces = QString::fromLatin1(qpTraceRoute->readAll()).split(QRegularExpression("\\n"));
	// Remove the first trace
	// qslTraces.removeFirst();
	// Create the list placeholder
	// QJsonArray qjaTraceRoute;
/*	// Iterate over the list
	for (int intTrace = 0; intTrace < qslTraces.size(); ++intTrace) {
		// Split the trace
		QStringList qslTrace = qslTraces.at(intTrace).split(QRegularExpression("\\s\\s"));
		// Create the map
		QVariantMap qvmTrace;
		// Add the hop
		qvmTrace.insert("hop",       (0 < qslTrace.size() ? qslTrace.at(0).trimmed() : NULL));
		// Add the host name
		qvmTrace.insert("hostName",  (1 < qslTrace.size() ? qslTrace.at(1).trimmed() : NULL));
		// Add the first datagram
		qvmTrace.insert("dataGram1", (2 < qslTrace.size() ? qslTrace.at(2).trimmed() : NULL));
		// Add the second datagram
		qvmTrace.insert("dataGram2", (3 < qslTrace.size() ? qslTrace.at(3).trimmed() : NULL));
		// Add the third datagram
		qvmTrace.insert("dataGram3", (4 < qslTrace.size() ? qslTrace.at(4).trimmed() : NULL));
		// Append the map
		qjaTraceRoute.append(QJsonValue(QJsonObject::fromVariantMap(qvmTrace)));
	}
*/
	// Grab the elapsed time
	intTimePassed = qtTimer.elapsed();
	// Set the record into the response
	qjoResponse.insert("city",         geoRecord.mCity);
	qjoResponse.insert("region",       geoRecord.mRegion);
	qjoResponse.insert("country",      geoRecord.mCountry);
	qjoResponse.insert("countryISO",   geoRecord.mCountryISO);
	qjoResponse.insert("continentISO", geoRecord.mContinentISO);
	qjoResponse.insert("isp",          geoRecord.mISP);
	qjoResponse.insert("latitude",     geoRecord.mLatitude);
	qjoResponse.insert("longitude",    geoRecord.mLongitude);
	qjoResponse.insert("timeZone",     geoRecord.mTimeZone);
	qjoResponse.insert("ipAddress",    hgiRequest->GetParam("ipAddress"));
	qjoResponse.insert("timeTaken",    (intTimePassed / 1000));
	qjoResponse.insert("timeTakenMS",  intTimePassed);
	qjoResponse.insert("referenceURI", QString("https://api.cdndepo.com/geoip/%1/json").arg(hgiRequest->GetParam("ipAddress")));
	qjoResponse.insert("userAgent",    hgiRequest->GetRequestHeader("HTTP_USER_AGENT"));
	// qjoResponse.insert("traceRoute",   QJsonValue(qjaTraceRoute));
	// Set the JSON into the view
	hgiResponse->SetPageValue("responseJSON", QJsonDocument(qjoResponse).toJson());
	// Log the request
	this->logRequest(hgiRequest, strResponseFormat, QString(QJsonDocument(qjoResponse).toJson()));
}

void GeoIPController::staticXML(HeimdallGI::CGI *&hgiRequest, HeimdallGI::View *&hgiResponse) {
	// Set the view for XML
	hgiResponse->SetTemplate("api/xml");
	// Set the content type
	hgiRequest->SetContentType(HeimdallGI::CGI::ContentTypeXML);
	// Create the buffer
	QByteArray qbaXML;
	// Create the XML stream
	QXmlStreamWriter qxswXML(&qbaXML);
	// Start the XML document
	qxswXML.setAutoFormatting(true);
	qxswXML.writeStartDocument();
	// Check for an IP address
	if ((hgiRequest->GetParam("ipAddress") == NULL) || hgiRequest->GetParam("ipAddress").isEmpty()) {
		// Open the element
		qxswXML.writeStartElement("geoip");
		// Set the reference into the element
		qxswXML.writeAttribute("href", QString("https://api.cdndepo.com/geoip/%1/xml").arg(hgiRequest->GetParam("ipAddress")));
		// Set the error
		qxswXML.writeTextElement("error", "No IP Address Found");
		// Close the element
		qxswXML.writeEndElement();
		// Close the document
		qxswXML.writeEndDocument();
		// Set the response into the view
		hgiResponse->SetPageValue("responseXML", QString(qbaXML));
		// We're done
		return;
	}
	// Create the timer
	QTime qtTimer;
	// Create a passive placeholder
	int intTimePassed;
	// Start the timer
	qtTimer.start();
	// Open the connection
	this->openConnection(QHostAddress(hgiRequest->GetParam("ipAddress")));
	// Query the database
	HeimdallGI::GeoRecord geoRecord = this->mMaxMind.findByAddress(QHostAddress(hgiRequest->GetParam("ipAddress")));
	// Create the QProcess call to traceroute
	// QProcess* qpTraceRoute = new QProcess();
	// Create the arguments list
	// QStringList qslArguments;
	// Add the max hops
	// qslArguments.append("--max-hops=120");
	// Add the IP address
	// qslArguments.append(hgiRequest->GetRequestHeader("REMOTE_ADDR"));
	// Start the trace
	// qpTraceRoute->start("traceroute", qslArguments);
	// Set the read channel
	// qpTraceRoute->setReadChannelMode(QProcess::MergedChannels);
	// Wait for bytes to be written
	// qpTraceRoute->waitForBytesWritten();
	// Wait for the command to finish
	// qpTraceRoute->waitForFinished(30000);
	// Grab the elapsed time
	intTimePassed = qtTimer.elapsed();
	// Split the data
	// QStringList qslTraces = QString::fromLatin1(qpTraceRoute->readAll()).split(QRegularExpression("\\n"));
	// Remove the first line
	// qslTraces.removeFirst();
	// Open the element
	qxswXML.writeStartElement("geoip");
	// Set the reference into the element
	qxswXML.writeAttribute("href", QString("https://api.cdndepo.com/geoip/%1/xml").arg(hgiRequest->GetParam("ipAddress")));
	// Set the time taken in ms in to the element
	qxswXML.writeAttribute("timeTaken", QString::number((intTimePassed / 1000), 'g', 3));
	qxswXML.writeAttribute("timeTakenMS", QString::number(intTimePassed, 'g', 3));
	// Set the record into the response
	qxswXML.writeTextElement("city",         geoRecord.mCity);
	qxswXML.writeTextElement("region",       geoRecord.mRegion);
	qxswXML.writeTextElement("country",      geoRecord.mCountry);
	qxswXML.writeTextElement("countryISO",   geoRecord.mCountryISO);
	qxswXML.writeTextElement("continentISO", geoRecord.mContinentISO);
	qxswXML.writeTextElement("isp",          geoRecord.mISP);
	qxswXML.writeTextElement("latitude",     QString::number(geoRecord.mLatitude,  'g', 18));
	qxswXML.writeTextElement("longitude",    QString::number(geoRecord.mLongitude, 'g', 18));
	qxswXML.writeTextElement("timeZone",     geoRecord.mTimeZone);
	qxswXML.writeTextElement("ipAddress",    hgiRequest->GetParam("ipAddress"));
	qxswXML.writeTextElement("timeTaken",    QString::number((intTimePassed / 1000), 'g', 3));
	qxswXML.writeTextElement("timeTakenMS",  QString::number(intTimePassed, 'g', 3));
	qxswXML.writeTextElement("referenceURI", QString("https://api.cdndepo.com/geoip/%1/xml").arg(hgiRequest->GetParam("ipAddress")));
	qxswXML.writeTextElement("userAgent",    hgiRequest->GetParam("HTTP_USER_AGENT"));
/*	// Create a new element
	qxswXML.writeStartElement("traceRoute");
	// Iterate over the list
	for (int intTrace = 0; intTrace < qslTraces.size(); ++intTrace) {
		// Start the hop element
		qxswXML.writeStartElement("hop");
		// Split the trace
		QStringList qslTrace = qslTraces.at(intTrace).split(QRegularExpression("\\s\\s"));
		// Add the attribute
		qxswXML.writeAttribute("number", qslTrace.at(0).trimmed());
		// Add the hop
		qxswXML.writeTextElement("hopNumber", (0 < qslTrace.size() ? qslTrace.at(0).trimmed() : QString::null));
		// Add the host name
		qxswXML.writeTextElement("hostName",  (1 < qslTrace.size() ? qslTrace.at(1).trimmed() : QString::null));
		// Add the first datagram
		qxswXML.writeTextElement("dataGram1", (2 < qslTrace.size() ? qslTrace.at(2).trimmed() : QString::null));
		// Add the second datagram
		qxswXML.writeTextElement("dataGram2", (3 < qslTrace.size() ? qslTrace.at(3).trimmed() : QString::null));
		// Add the third datagram
		qxswXML.writeTextElement("dataGram3", (4 < qslTrace.size() ? qslTrace.at(4).trimmed() : QString::null));
		// Close the hop
		qxswXML.writeEndElement();
	}
	// Close the trace route element
	qxswXML.writeEndElement();
*/
	// Close the element
	qxswXML.writeEndElement();
	// Close the document
	qxswXML.writeEndDocument();
	// Set the XML into the view
	hgiResponse->SetPageValue("responseXML", QString(qbaXML));
	// Log the request
	this->logRequest(hgiRequest, "xml", QString(qbaXML));
}
