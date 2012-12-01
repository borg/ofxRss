#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    verdana14.loadFont("verdana.ttf", 14, true, true);
    
    ofAddListener(RssEvent::events, this, &testApp::rssEvent);
    
    string tag = "bw";
    
    ofxRss::load("http://instagram.com/tags/"+tag+"/feed/recent.rss");
}

void testApp::rssEvent(RssEvent &e){
    ofLog()<<"Got rss channel: "<<e.channel.title<<" "<<e.entries.size()<<endl;
    entries = e.entries;
    
    
    //do a save to disk and cache here
    
    total = entries.size();
	
	for(int i = 0; i < total; ++i) {			
		/*ofImage* img = new ofImage();
		images.push_back(img);
		loader.loadFromDisk(img, "of" + ofToString(i) + ".png");
        */
        if(!entries[i].media_content.empty()){
		ofImage* url_img = new ofImage();
		images.push_back(url_img);
		loader.loadFromURL(images.back(), entries[i].media_content);
        }
//        ofLog()<<" entry" <<entries[i].media_content<<endl;
	}
	
	//TODO: no! this should be internal - overloading << doesn't make sense
	//cout << loader << endl;
	
	loader.startThread(false, false);

    
    
    
    
    
};


//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(245, 58, 135);
    if(entries.size()>0){
        for(int i=0;i<entries.size();i++){
            verdana14.drawString(entries[i].media_content, 10, 20*i);
            
        }
    }
    
    // draw the images.
	glColor3f(1,1,1);
	for(int i = 0; i < images.size(); ++i) {
		int x = (i%8);
		int y = (i/8);
		images.at(i)->draw(x*128,y*128, 128,128);
	}	

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}