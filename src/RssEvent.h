/*
 *  RssEvent.h
 *  Vectagram
 *
 *  Created by Andreas Borg on 06/10/2012
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 
 
 <title>Liftoff News</title>
 <link>http://liftoff.msfc.nasa.gov/</link>
 <description>Liftoff to Space Exploration.</description>
 <language>en-us</language>
 <pubDate>Tue, 10 Jun 2003 04:00:00 GMT</pubDate>
 <lastBuildDate>Tue, 10 Jun 2003 09:41:01 GMT</lastBuildDate>
 <docs>http://blogs.law.harvard.edu/tech/rss</docs>
 <generator>Weblog Editor 2.0</generator>
 <managingEditor>editor@example.com</managingEditor>
 <webMaster>webmaster@example.com</webMaster>
 
 
 Channel info
 */

#ifndef _RssEvent
#define _RssEvent

#include "ofMain.h"

#include "RssTypes.h"
#include "RssEntry.h"

typedef struct Channel{
    string title;
    string link;
    string description;
    string language;
    string pubDate;
    string lastBuiltDate;
    string docs;
    string generator;
    string managingEditor;
    string webMaster;
}Channel;

class RssEvent : public ofEventArgs {
	
  public:
	
	RssEvent(){};//this is from vanderlins exammple...what does this do? how does it realate to static?
    RssType type;
    string   message;

    vector<RssEntry> entries;
    Channel channel;
    static ofEvent <RssEvent> events;
	
};

#endif
