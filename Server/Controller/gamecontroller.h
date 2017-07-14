/**
  @file
  @author Stefan Frings
*/

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

using namespace stefanfrings;

/**
  This controller displays a HTML form and dumps the submitted input.
*/


class GameController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(GameController)
public:

    /** Constructor */
    GameController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // GAMECONTROLLER_H
