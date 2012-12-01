/*

 *
 *  Created by Andreas Borg on 15/10/2012
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
http://www.rssboard.org/rss-specification
 
 
 title	The title of the item.	Venice Film Festival Tries to Quit Sinking
 link	The URL of the item.	http://nytimes.com/2004/12/07FEST.html
 description	The item synopsis.	<description>Some of the most heated chatter at the Venice Film Festival this week was about the way that the arrival of the stars at the Palazzo del Cinema was being staged.</description>
 author	Email address of the author of the item. More.	
 category	Includes the item in one or more categories. More.	
 comments	URL of a page for comments relating to the item. More.	
 enclosure	Describes a media object that is attached to the item. More.	
 guid	A string that uniquely identifies the item. More.	
 pubDate	Indicates when the item was published. More.	
 source	The RSS channel that the item came from. More.
 
 
 */

#ifndef _RssEntry
#define _RssEntry

#include "ofMain.h"



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
#include "Poco/DOM/DOMWriter.h"
//#include "Poco/XML/XMLReader.h" 
#include "Poco/XML/XMLWriter.h" 
#include "Poco/UTF8Encoding.h"

using namespace Poco::XML;






class RssEntry {
	
  public:
	
	RssEntry();
    ~RssEntry();
	

    string title;
    string link;
    string description;
    string author;
    string category;
    string comments;
    string enclosure;
    string guid;
    string pubDate;
    string source;
    
    string media_title;//<media:title
    string media_description;
    string media_content;
    string media_thumbnail;
    string media_credit;
   
    void parseXML(Element * x);
    
    private:
    
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
};

#endif
