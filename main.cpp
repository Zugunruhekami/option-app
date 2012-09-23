#include<cstdio>
#include<cstdio>
#include<vector>
#include<string>

#include"tinyxml/tinyxml.h"
#include "option.h"

using namespace std;

TiXmlDocument ProcessRequest(const TiXmlDocument &doc);
TiXmlElement *GetModelResults(const TiXmlElement *elem);

int main()
{  
  string filename = "request.xml";
  TiXmlDocument doc(filename.c_str());
  bool loadOkay = doc.LoadFile();
  if(loadOkay)
  {     
    TiXmlDocument response = ProcessRequest(doc); 
  } 
  else
  {
    printf("Error: %s not loaded.", filename.c_str());  
  }
  
  return 0;
}

TiXmlDocument ProcessRequest(const TiXmlDocument &doc)
{  
  TiXmlDocument response("response.xml");
  const TiXmlElement * elem = doc.RootElement()->FirstChildElement();
  
  while(elem) 
  { 
    TiXmlElement * response_elem = GetModelResults(elem);
    response.LinkEndChild(response_elem);
    elem = elem->NextSibling() ? elem->NextSibling()->ToElement() : NULL;
  }
 
  return response;
}

TiXmlElement *GetModelResults(const TiXmlElement *elem)
{
  TiXmlElement *list = new TiXmlElement("ResultList");
  
  string ticker = elem->Attribute("ticker");
  double strike = atof(elem->Attribute("strike"));
  double expiry = atof(elem->Attribute("expiry"));
  double rate = atof(elem->Attribute("rate"));
  double div = atof(elem->Attribute("div"));
  
  double args[] = {0,.25,rate, div, expiry };
  
  VanillaCall call(strike);

  for(int i = 0; i!= 10; ++i)
  { 
    double spot = 40.0 + static_cast<double>(i)/10.0 * 10.0;
    args[0] = spot;

    double price = call.Price(args);
    HedgeRatios greeks = call.Greeks(args);

    printf("%f : %f delta=%f, gamma=%f, theta=%f, vega=%f, rho=%f\n", spot, price, greeks.delta, greeks.gamma, greeks.theta, greeks.vega, greeks.rho);
  }
  return list;  
}

