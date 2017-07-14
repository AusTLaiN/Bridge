/**
  @file
  @author Stefan Frings
*/

#include "gamecontroller.h"

GameController::GameController()
{}

void GameController::service(HttpRequest& request, HttpResponse& response)
{
    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");

    qDebug("ok");
    qDebug(request.getParameter("rank"));
    qDebug(request.getParameter("suit"));
    response.write("ok", true);

    /*if (request.getParameter("action")=="show")
    {
        response.write("<html><body>");
        response.write("Name = ");
        response.write(request.getParameter("name"));
        response.write("<br>City = ");
        response.write(request.getParameter("city"));
        response.write("</body></html>",true);
    }
    else
    {
        response.write("<html><body>");
        response.write("<form method=\"post\">");
        response.write("  <input type=\"hidden\" name=\"action\" value=\"show\">");
        response.write("  Name: <input type=\"text\" name=\"name\"><br>");
        response.write("  City: <input type=\"text\" name=\"city\"><br>");
        response.write("  <input type=\"submit\">");
        response.write("</form>");
        response.write("</body></html>",true);
    }*/
}

