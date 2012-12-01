/*
 *  RssEntry.cpp
 *  mural
 *
 *  Created by Andreas Borg on 15/10/2012
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "RssEntry.h"

//extern int stringToHex(string hex);
//extern void hexToColor(ofColor &col,string hex);


RssEntry::RssEntry(){};
RssEntry::~RssEntry(){};




void RssEntry::parseXML(Element * x){
    
    Element * sub;
    
    sub = x->getChildElement("link");
    if(sub){
        sub->normalize();
        link = ofToString(sub->innerText().c_str());
    }

    sub = x->getChildElement("title");
    if(sub){
        sub->normalize();
        title = ofToString(sub->innerText().c_str());
    }
    
    
    sub = x->getChildElement("description");
    if(sub){
        sub->normalize();
        description = ofToString(sub->innerText().c_str());
    }
    
    sub = x->getChildElement("author");
    if(sub){
        sub->normalize();
        author = ofToString(sub->innerText().c_str());
    }
    sub = x->getChildElement("category");
    if(sub){
        sub->normalize();
        category = ofToString(sub->innerText().c_str());
    }
    sub = x->getChildElement("enclosure");
    if(sub){
        sub->normalize();
        enclosure = ofToString(sub->innerText().c_str());
    }
    sub = x->getChildElement("guid");
    if(sub){
        sub->normalize();
        guid = ofToString(sub->innerText().c_str());
    }
    sub = x->getChildElement("pubDate");
    if(sub){
        sub->normalize();
        pubDate = ofToString(sub->innerText().c_str());
    }
    sub = x->getChildElement("source");
    if(sub){
        sub->normalize();
        source = ofToString(sub->innerText().c_str());
    }
    
        
    //how to get exact NS media?
    NodeList *cnl = x->getElementsByTagNameNS("*","content");
    sub = (Element *) cnl->item(0);
    
    if(sub){
        media_content = ofToString(sub->getAttribute("url").c_str());
        //ofLog()<<"found media content "<<media_content<<endl;
    }
    cnl->release();
    
    
    
    
    
    cnl = x->getElementsByTagNameNS("*","title");
    sub = (Element *) cnl->item(0);
    
    if(sub){
        media_title = ofToString(sub->getAttribute("url").c_str());
    }
    cnl->release();
    
    cnl = x->getElementsByTagNameNS("*","thumbnail");
    sub = (Element *) cnl->item(0);
    
    if(sub){
        media_thumbnail = ofToString(sub->getAttribute("url").c_str());
    }
    cnl->release();
    
     /*  
    media_description = x.getValue("media:description","");
    
    media_credit = x.getValue("media:credit","");
    */
 
}

