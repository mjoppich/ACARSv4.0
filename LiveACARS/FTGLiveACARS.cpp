#include "FTGLiveACARS.h"

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

#include <qdebug.h>

#include <Core/ACARSDataBunk.h>
#include <Base\ACARSTimeSpan.h>


FTGLiveACARS::FTGLiveACARS(QObject *pParent)
	: LiveACARS(pParent)
{
	m_pNetworkManager = new QNetworkAccessManager(this);
	this->connect(m_pNetworkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(loadingFinished(QNetworkReply *)));

}


FTGLiveACARS::~FTGLiveACARS()
{
}


/*

post_material:='';
post_material:=post_material+'pilotid='+HTTPEncodePW(ACARS.pilot.pid);
post_material:=post_material+'&flightnumber='+HTTPEncodePW(ACARS.FlightNumber);
post_material:=post_material+'&aircraft='+HTTPEncodePW(ACARS.aircraft.aircraft);
post_material:=post_material+'&aircraftreg='+HTTPEncodePW(ACARS.aircraft.aircraft_registration);
post_material:=post_material+'&depairport='+HTTPEncodePW(ACARS.departure_airport.airport.waypoint);
post_material:=post_material+'&arrairport='+HTTPEncodePW(ACARS.arrival_airport.airport.waypoint);
post_material:=post_material+'&depair_lon='+HTTPEncodePW(floattostr(ACARS.departure_airport.airport.longitude,ls));
post_material:=post_material+'&depair_lat='+HTTPEncodePW(floattostr(ACARS.departure_airport.airport.latitude,ls));
post_material:=post_material+'&arrair_lon='+HTTPEncodePW(floattostr(ACARS.arrival_airport.airport.longitude,ls));
post_material:=post_material+'&arrair_lat='+HTTPEncodePW(floattostr(ACARS.arrival_airport.airport.latitude,ls));
post_material:=post_material+'&altitude='+HTTPEncodePW(inttostr(FSUIPC.data.altitude));
post_material:=post_material+'&machspeed='+HTTPEncodePW(floattostr(roundto(FSUIPC.data.machspeed,-2),ls));
post_material:=post_material+'&groundspeed='+HTTPEncodePW(inttostr(FSUIPC.data.groundspeed));
post_material:=post_material+'&heading='+HTTPEncodePW(inttostr(round(FSUIPC.data.heading)));

//DIST TO DESTINATION
distancecalc:=ACARS.arrival_airport.airport;
post_material:=post_material+'&disttodest='+HTTPEncodePW(inttostr(round(calculate_distance(FSUIPC.data.ac_latitude,FSUIPC.data.ac_longitude,distancecalc.latitude,distancecalc.longitude)))); //'--- nm';
//TIME TO DESTINATION
if FSUIPC.data.groundspeed<>0 then
begin
dist:=calculate_distance(distancecalc.latitude,distancecalc.longitude,FSUIPC.data.ac_latitude,FSUIPC.data.ac_longitude);
post_material:=post_material+'&timetodest='+HTTPEncodePW(add_zero(round(dist) div FSUIPC.data.groundspeed)+':'+add_zero(round((round(dist) mod FSUIPC.data.groundspeed)/FSUIPC.data.groundspeed*60)));
end;

post_material:=post_material+'&flightstate='+HTTPEncodePW(fstatus_to_string(flightstatus));
post_material:=post_material+'&acarsversion='+HTTPEncodePW(copy(ACARS.version,0,3));
post_material:=post_material+'&current_lon='+HTTPEncodePW(floattostr(FSUIPC.data.ac_longitude,ls));
post_material:=post_material+'&current_lat='+HTTPEncodePW(floattostr(FSUIPC.data.ac_latitude,ls));
*/

bool FTGLiveACARS::Send(ACARSDataBunk* pData)
{

    QUrlQuery postData;
	postData.addQueryItem("pilotid",pData->getACARSUsername());
	postData.addQueryItem("remark","");
	postData.addQueryItem("flightstate","unknown");
	postData.addQueryItem("flightnumber", pData->getFlightNumber());
	postData.addQueryItem("aircraft", pData->getAircraft()->getFTGCode());
	postData.addQueryItem("aircraftreg", pData->getAircraft()->getRegistration());
	postData.addQueryItem("depairport", pData->getDepartureAirport()->getICAOCode());
	postData.addQueryItem("arrairport", pData->getArrivalAirport()->getICAOCode());
	postData.addQueryItem("depair_lon", ts(pData->getDepartureAirport()->getLatLon()->getLon()));
	postData.addQueryItem("depair_lat", ts(pData->getDepartureAirport()->getLatLon()->getLat()));
	postData.addQueryItem("arrair_lon", ts(pData->getArrivalAirport()->getLatLon()->getLon()));
	postData.addQueryItem("arrair_lat", ts(pData->getArrivalAirport()->getLatLon()->getLat()));
	postData.addQueryItem("altitude", ts(pData->getAltitude("ft")));
	postData.addQueryItem("machspeed", ts(pData->getMachSpeed(),2));
	postData.addQueryItem("groundspeed", ts(qRound(pData->getGroundSpeed())));
	postData.addQueryItem("heading", ts(pData->getHeading()));
	float dist = ACARSLatLon::DistanceFromTo(pData->getDepartureAirport()->getLatLon(),pData->getArrivalAirport()->getLatLon(),"nm");
	postData.addQueryItem("disttodest", ts(dist,4));

	postData.addQueryItem("timetodest", pData->getTimeToDest()->toString());
	postData.addQueryItem("acarsversion", "4.0");
	postData.addQueryItem("current_lon", ts(pData->getPositionLatLon()->getLon()));
	postData.addQueryItem("current_lat", ts(pData->getPositionLatLon()->getLat()));

    QNetworkRequest oRequest = QNetworkRequest(QUrl("http://www.flyingtigersgroup.org/acarsftg/ftgacars/write_live.asp"));
    oRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    m_pNetworkManager->post(oRequest, postData.toString().toStdString().c_str());

	return true;
}

bool FTGLiveACARS::loadingFinished(QNetworkReply * reply)
{

	qDebug() << reply->readAll();

	return true;
}
