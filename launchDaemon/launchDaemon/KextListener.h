//
//  file: KextListener.h
//  project: lulu (launch daemon)
//  description: listener for events from kernel (header)
//
//  created by Patrick Wardle
//  copyright (c) 2017 Objective-See. All rights reserved.
//

@import Foundation;

#import <sys/ioctl.h>
#import <sys/types.h>
#import <sys/socket.h>
#import <sys/kern_event.h>

//custom struct for network events
// format of data that's broadcast from kext
struct connectionEvent
{
    //process pid
    pid_t pid;

    //local socket address
    struct sockaddr localAddress;
    
    //remote socket address
    struct sockaddr remoteAddress;
    
    //socket type
    int socketType;
};


@interface KextListener : NSObject
{
    
}

/* PROPERTIES */

//list of alerts, by pid
// ensures that only one alert for process is shown to user
@property(nonatomic, retain)NSMutableSet* alerts;

//DNS 'cache'
// mappings of IP:URL
@property(nonatomic, retain)NSMutableDictionary* dnsCache;

/* METHODS */

//init
-(id)init;

//kick off threads to monitor for kext events
-(void)monitor;

//process events from the kernel (queue)
-(void)processEvents;

//remove process from list of alerts
-(void)resetAlert:(pid_t)pid;

@end
