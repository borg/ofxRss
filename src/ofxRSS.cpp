/*
 *  ofxRss.cpp
 *  Vectagram
 *
 *  Created by Andreas Borg on 05/10/2012
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxRss.h"




ofxRss::ofxRss(){
    ofAddListener(http.newResponseEvent,this,&ofxRss::newResponse);
};

ofxRss::~ofxRss(){
    if(getSingleton().http.isThreadRunning()){
        getSingleton().http.stop();
    }
};

ofxRss & ofxRss::getSingleton(){
    static ofxRss singleton;
    return singleton;

};



