/*
 *  ofxRss.h
 *  This is a selective goodies version of the ColourLovers API
    http://www.colourlovers.com/api
 *
 *  Created by Andreas Borg on 05/10/2012
 *  Copyright 2012 crea.tion.to. 
 *
 */

#ifndef _ofxRss
#define _ofxRss

#include "ofMain.h"
#include "ofxHttpUtils.h"

#include "RssTypes.h"
#include "RssEntry.h"
#include "RssEvent.h"

//ofxXMLSettings is using TInyXML which doesn't support namespaces..so gotta use something bit more powerful

//http://www.rssboard.org/media-rss#optional-elements


#include "Poco/URIStreamOpener.h"  
#include "Poco/StreamCopier.h"  
#include "Poco/Path.h"  
#include "Poco/URI.h"  
#include "Poco/Exception.h"  
#include "Poco/Net/HTTPStreamFactory.h"  
#include "Poco/XML/XMLString.h"  
#include "Poco/DOM/DOMParser.h"  
#include "Poco/DOM/Document.h"  
#include "Poco/DOM/Attr.h"  
#include "Poco/DOM/NodeIterator.h"  
#include "Poco/DOM/NodeFilter.h"  
#include "Poco/DOM/NamedNodeMap.h"   
#include "Poco/DOM/ChildNodesList.h"
//BORG
#include "Poco/DOM/DOMWriter.h"
//#include "Poco/XML/XMLReader.h" 
#include "Poco/XML/XMLWriter.h" 
#include "Poco/UTF8Encoding.h"

using namespace Poco::XML;



/*
 These string to hex conversions aren't trivial.
 
 What does static do here? Without it compiler comlains abouts duplicates...I just want it a global
 
 */
 static int stringToHex(string hex){
    int aHex;
    stringstream convert ( hex );
    convert>> std::hex >> aHex;
    return aHex;
}



 static void hexToColor(ofColor &col,string hex){
    string r = hex.substr(0,2);
    int ri = stringToHex(r);
    string g = hex.substr(2,2);
    int gi = stringToHex(g);
    string b = hex.substr(4,2);
    int bi = stringToHex(b);
    col.set(ri,gi,bi);
    
}



class ofxRss{
	
  public:
	
    ofxRss();
    ~ofxRss();
    
    
    /*
     orderCol	=	X   [Where X can be: dateCreated, score, name, numVotes, or numViews]
     sortBy	=	X   [Where X can be: ASC or DESC. Default ASC]
     */
    
   static  void load(string url){
        
        
        ofxHttpForm form;//submitting form
       form.name = url;
       form.method = OFX_HTTP_POST;
    //string url = url;
      //  url+="&numResults="+ofToString(numResults) +"&resultOffset="+ofToString(resultOffset)+"&orderCol="+orderCol+"&sortBy="+sortBy;
       form.action = url;

       
       
      
       
       
        
       //form.clearFormFields();//clear out old send data
        
        /*
         for(int i=0;i<form1.elements.size();i++){
         string v = form1.elements[i]->getValue();
         //  isEmpty = ((v=="0" || v =="") && isEmpty);//only test if not already proved wrong
         form.addFormField(form1.elements[i]->name,v);
         // ofLog()<<form1.elements[i]->name<< v <<endl;
         }*/
        
        
        
        ofLog()<<"submitting load: "<<url<<endl;
        //status = PENDING;
       getSingleton().http.addForm(form);
       if(!getSingleton().http.isThreadRunning()){
           getSingleton().http.start();            
       }

       //getSingleton().http.submitForm(form);
        
        
    }

      
    
    
    static string hexToWeb(ofColor col){
        return "#"+ofToHex(col.r)+ofToHex(col.g)+ofToHex(col.b);
    }

    
    
     private:
    
   // int formNum;//number of forms to wait for
    ofxHttpUtils http;
    //static void newResponse(ofxHttpResponse &response);

    string url;
   
    static ofxRss &getSingleton();//check out this pattern...it's quite sweet
    
    
    
    virtual void newResponse(ofxHttpResponse &response) {
        // printf("%s\n", response.responseBody.c_str());
        string responseStr = ofToString(response.status) + ": " + (string)response.responseBody;
        //ofLog()<<responseStr<<endl;
        
        
        Document *document;    
        DOMParser parser;
        //parser.setFeature(Poco::XML::XMLReader::FEATURE_NAMESPACES, false);
        document = parser.parseString(response.responseBody);
        
        
        ChildNodesList *cnl = (ChildNodesList *) document->firstChild()->childNodes();
        
        Channel ch;
        RssEvent newEvent;
        
        
        
        
        
        int i  = 0, l = cnl->length();
        
        while( i < l ){
            
            Element *child = (Element *) cnl->item(i);
           // ofPtr<svgNode> childnode(new svgNode());
            
            if (child->nodeType() == Element::ELEMENT_NODE) {
                const char *name = (const char *) child->localName().c_str();
                
                if (strcmp(name, "channel") == 0){
                    Element *sub;
                    sub = child->getChildElement("title");
                    /*
                     http://www.appinf.com/docs/poco/Poco.XML.Element.html
                     Puts all Text nodes in the full depth of the sub-tree underneath this Element, including attribute nodes
                     */
                    
                    if(sub){
                        sub->normalize();
                        ch.title = ofToString(sub->innerText().c_str());
                    }
                    
                    sub = child->getChildElement("link");
                    
                    if(sub){
                        sub->normalize();
                        ch.link = ofToString(sub->innerText().c_str());
                    }
                    
                    sub = child->getChildElement("description");
                    
                    if(sub){
                        sub->normalize();
                        ch.description = ofToString(sub->innerText().c_str());
                    }
                    
                    sub = child->getChildElement("language");
                    
                    if(sub){
                        sub->normalize();
                        ch.language = ofToString(sub->innerText().c_str());
                    }
                    
                    sub = child->getChildElement("pubDate");
                     
                    if(sub){
                        sub->normalize();
                        ch.pubDate = ofToString(sub->innerText().c_str());
                    }
                    
                    sub = child->getChildElement("lastBuiltDate");
                    
                    if(sub){
                        sub->normalize();
                        ch.lastBuiltDate = ofToString(sub->innerText().c_str());
                    }
                    
                    sub = child->getChildElement("docs");
                     
                    if(sub){
                        sub->normalize();
                        ch.docs = ofToString(sub->innerText().c_str());
                    }
                    
                    sub = child->getChildElement("generator");
                 
                    if(sub){
                        sub->normalize();
                        ch.generator = ofToString(sub->innerText().c_str());
                    }
                    
                    sub = child->getChildElement("managingEditor");
                    
                    if(sub){
                        sub->normalize();
                        ch.managingEditor = ofToString(sub->innerText().c_str());
                    }
                    sub = child->getChildElement("webMaster");
                    
                    if(sub){
                        sub->normalize();
                        ch.webMaster = ofToString(sub->innerText().c_str());
                    }
                    
                    
                    // ofToString(child->getAttribute("width").c_str());
                    ChildNodesList *entries = (ChildNodesList *) child->childNodes();
                                     
                    parseRSS(entries, newEvent);
                    
                    //relesae when not needed
                    entries->release();
                }
                
                
            }
            i++;
        }
        
        newEvent.channel = ch;
        cnl->release();
        ofNotifyEvent(RssEvent::events, newEvent);
    }
    
    
    static void parseRSS(ChildNodesList * &entries, RssEvent &ev){
        
       // entries.pushTag("");
        int numItems = entries->length();

        if(numItems>0){
            for(int i=0;i<numItems;i++){
                              
                RssEntry re;
                re.parseXML((Element *)entries->item(i));
                               
                ev.entries.push_back(re);
              
            }
        }
        //entries.popTag();
    }


};

#endif
